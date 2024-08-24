/*
 *  Cocktail Machine
 *
 *  Requirements:
 *  - https://github.com/neu-rah/ArduinoMenu/
 *  - https://github.com/fmalpartida/New-LiquidCrystal
 *  - https://github.com/SimpleHacks/QDEC
 *  - https://github.com/gin66/FastAccelStepper
 *  - https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences
 *  - https://github.com/madhephaestus/ESP32Servo
 *  - 
 */

#include <LiquidCrystal_I2C.h>
#include <menu.h>
#include <menuIO/lcdOut.h>
#include <menuIO/chainStream.h>

#include "config.h"
#include "pyd_preferences.h"
#include "pyd_menu.h"
#include "pyd_stepper.h"
#include "pyd_servo.h"
#include "bottles.h"
#include "cocktails.h"

FastAccelStepperEngine stepperEngine;
PYD_Stepper stepperCarriage(
    &stepperEngine,
    STEPPER1_PIN_STEP,
    STEPPER1_PIN_DIRECTION,
    STEPPER1_PIN_ENABLE,
    STEPPER1_PIN_ENDSTOP,
    STEPPER1_ENDSTOP_ACTIVE_LOW,
    STEPPER1_REVERSE_DIRECTION,
    STEPPER1_STEPS_MM,
    STEPPER1_MAX_TRAVEL_MM,
    STEPPER1_SPEED,
    STEPPER1_SPEED_HOMING,
    STEPPER1_ACCELERATION
);
PYD_Servo servo(SERVO1_PIN);

// Menu Inputs
PYD_RotaryEncoder rotaryEncoder(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_PIN_BUTTON);
MENU_INPUTS(in, &rotaryEncoder.rotaryEventIn, &rotaryEncoder.keyIn);
// Menu Outputs
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
MENU_OUTPUTS(out,MENU_MAX_DEPTH,LCD_OUT(lcd,{0,0,DISPLAY_COLS,DISPLAY_ROWS}),NONE);

// Menus
int bottleNumber = 1;
int16_t bottleContent = 0;
float bottleQuantity = 0;
float bottlePosition = 0;
result initBottlesMenu()
{
    bottleNumber = 1;
    updateVariables();
    return proceed;
}
result updateVariables()
{
    bottleContent = Prefs.bottleContent[bottleNumber];
    bottleQuantity = Prefs.bottleQuantity[bottleNumber];
    bottlePosition = Prefs.bottlePosition[bottleNumber];
    return proceed;
}
result updatePreferences()
{
    Prefs.bottleContent[bottleNumber] = bottleContent;
    Prefs.bottleQuantity[bottleNumber] = bottleQuantity;
    Prefs.bottlePosition[bottleNumber] = bottlePosition;
    savePreferences();
    return proceed;
}
result savePreferences()
{
    Prefs.saveAll();
    return proceed;
}

int cocktailNumber = -1;
const int PYD_cocktails_N = sizeof(PYD_cocktails)/sizeof(*PYD_cocktails);
Menu::menuValue<typeof(cocktailNumber)>* menuValue_cocktails[PYD_cocktails_N+1];
Menu::prompt* chooseCocktailMenu_data[PYD_cocktails_N+1];
void populateCocktailsMenu()
{
    menuValue_cocktails[0] = new Menu::menuValue<typeof(cocktailNumber)>("Seleziona Cocktail", -1);
    chooseCocktailMenu_data[0] = menuValue_cocktails[0];
    for (int i=0; i<PYD_cocktails_N; i++)
    {
        // TODO: check if cocktail ingredients are available on the machine
        menuValue_cocktails[i+1] = new Menu::menuValue<typeof(cocktailNumber)>(PYD_cocktails[i]->name, i);
        chooseCocktailMenu_data[i+1] = menuValue_cocktails[i+1];
    }
}
const char chooseCocktailMenu_text[] ="";
Menu::menuVariantShadows<typeof(cocktailNumber)> chooseCocktailMenuShadows={
    (Menu::callback)doNothing,
    ((systemStyles)(Menu::_menuData|Menu::_canNav|Menu::_isVariant)),
    chooseCocktailMenu_text,
    noEvent,
    noStyle,
    sizeof(chooseCocktailMenu_data)/sizeof(prompt*),
    chooseCocktailMenu_data,
    &cocktailNumber
};
Menu::choose<typeof(cocktailNumber)> chooseCocktailMenu (chooseCocktailMenuShadows.obj);

// Returns the index of the bottle in the Prefs.bottleContent array
// that contains the ingredient with the given name and quantity
// Returns -1 if the ingredient is not available
// Returns -2 if the ingredient is not available but optional
int bottleAvailable(const PYD_ingredient_t* ingredient)
{
    int bottle = bottleAvailable(ingredient->name, ingredient->quantity);
    if (bottle == -1 && ingredient->optional)
        return -2;
    return bottle;
}
// Returns the index of the bottle in the Prefs.bottleContent array
// that contains the ingredient with the given name and quantity
// Returns -1 if the ingredient is not available
int bottleAvailable(const char *name, int quantity)
{
    int n = sizeof(Prefs.bottleContent)/sizeof(*Prefs.bottleContent);
    for (int i=0; i<n; i++)
        if (strcmp(name, PYD_bottles[Prefs.bottleContent[i]]) == 0)
            if (Prefs.bottleQuantity[i] >= quantity)
                return i;
    return -1;
}
void prepareCocktail()
{
    const PYD_cocktail_t* cocktail = PYD_cocktails[cocktailNumber];
    // Check if cocktail ingredients are available
    bool ingredientsAvailable = true;
    for (int i=0; i<cocktail->len; i++)
        if (bottleAvailable(&cocktail->ingredients[i]) == -1)
            ingredientsAvailable = false;
    if (!ingredientsAvailable)
    {
        lcd.setCursor(0,0);
        lcd.print("Ingredienti mancanti");
        delay(2000);
        return;
    }
    // Pour the ingredients
    servo.move(Prefs.servoIdleAngle);
    delay(Prefs.servoIdleTime);
    lcd.setCursor(0,0);
    lcd.print("Versando:           ");
    for (int i=0; i<cocktail->len; i++)
    {
        int bottle = bottleAvailable(&cocktail->ingredients[i]);
        if (bottle == -1)
            continue;
        if (bottle == -2)
            continue;
        // Move the carriage to the bottle
        stepperCarriage.moveToMM(Prefs.bottlePosition[bottle], true);
        lcd.setCursor(0,1);
        lcd.print("                    ");
        lcd.print(PYD_bottles[Prefs.bottleContent[bottle]]);
        // Pour the ingredient
        int toPour = cocktail->ingredients[i].quantity;
        while (toPour > 0)
        {
            if (toPour >= Prefs.pourFullQuantity)
            {
                servo.move(Prefs.servoPourAngle);
                delay(Prefs.pourFullTime);
                toPour -= Prefs.pourFullQuantity;
            }
            else
            {
                servo.move(Prefs.servoPourAngle);
                delay(round((float)(1000*toPour)/Prefs.pourRate) + Prefs.pourDeadTime);
                toPour = 0;
            }
            servo.move(Prefs.servoIdleAngle);
            if (toPour > 0)
                delay(Prefs.pourRefillTime);
            else
                delay(Prefs.servoIdleTime);
        }
    }
    stepperCarriage.moveToMM(Prefs.glassAccessPosition, true);
    lcd.setCursor(0,0);
    lcd.print("Cocktail pronto!    ");
    lcd.setCursor(0,1);
    lcd.print(cocktail->name);
    lcd.setCursor(0,2);
    lcd.print("                    ");
    lcd.setCursor(0,3);
    lcd.print("                    ");
    delay(2000);
}
MENU(cocktailsMenu,"Prepara Cocktail",doNothing,noEvent,wrapStyle
    ,SUBMENU(chooseCocktailMenu)
    ,OP("Prepara",prepareCocktail,enterEvent)
    ,EXIT("Indietro")
);

const int PYD_bottles_N = sizeof(PYD_bottles)/sizeof(*PYD_bottles);
Menu::menuValue<typeof(bottleContent)>* menuValue_data[PYD_bottles_N];
Menu::prompt* bottleContentMenu_data[PYD_bottles_N];
void populateBottleContentMenu()
{
    for (int i=0; i<PYD_bottles_N; i++)
    {
        menuValue_data[i] = new Menu::menuValue<typeof(bottleContent)>(PYD_bottles[i], i);
        bottleContentMenu_data[i] = menuValue_data[i];
    }
}
const char bottleContentMenu_text[] = "";
Menu::menuVariantShadows<typeof(bottleContent)> bottleContentMenuShadows = {
    (Menu::callback)doNothing,
    ((systemStyles)(Menu::_menuData|Menu::_canNav|Menu::_isVariant|Menu::_parentDraw)),
    bottleContentMenu_text,
    noEvent,
    noStyle,
    sizeof(bottleContentMenu_data)/sizeof(prompt*),
    bottleContentMenu_data,
    &bottleContent
};
Menu::select<typeof(bottleContent)> bottleContentMenu (bottleContentMenuShadows.obj);
MENU(bottlesMenu,"Bottiglie",initBottlesMenu,enterEvent,wrapStyle
    ,FIELD(bottleNumber,"Bottiglia","",1,BOTTLES_NUM,1,0,updateVariables,updateEvent,noStyle)
    ,SUBMENU(bottleContentMenu)
    ,FIELD(bottleQuantity,"Volume","mL",0,2000,100,10,updatePreferences,exitEvent,noStyle)
    ,EXIT("Indietro")
);
void bottlePositionEvent(eventMask e)
{
    if (e == updateEvent)
        stepperCarriage.moveToMM(bottlePosition);
    else if (e == exitEvent)
        updatePreferences();
}
MENU(bottlesCalMenu,"Cal. Bottiglie",initBottlesMenu,enterEvent,wrapStyle
    ,FIELD(bottleNumber,"Bottiglia","",1,BOTTLES_NUM,1,0,updateVariables,updateEvent,noStyle)
    ,FIELD(bottlePosition,"Posizione","mm",0,STEPPER1_MAX_TRAVEL_MM,10,1,bottlePositionEvent,updateEvent|exitEvent,noStyle)
    ,EXIT("Indietro")
);
void servoPourAngleEvent(eventMask e)
{
    if (e == updateEvent)
        servo.move(Prefs.servoPourAngle);
    else if (e == exitEvent)
        savePreferences();
}
void servoIdleAngleEvent(eventMask e)
{
    if (e == updateEvent)
        servo.move(Prefs.servoIdleAngle);
    else if (e == exitEvent)
        savePreferences();
}
void exitServoCalMenu()
{
    servo.move(Prefs.servoIdleAngle);
}
MENU(servoCalMenu,"Cal. Servo",exitServoCalMenu,exitEvent,wrapStyle
    ,FIELD(Prefs.servoPourAngle,"PourAngle","deg",0,180,10,1,servoPourAngleEvent,updateEvent|exitEvent,noStyle)
    ,FIELD(Prefs.servoIdleAngle,"IdleAngle","deg",0,180,10,1,servoIdleAngleEvent,updateEvent|exitEvent,noStyle)
    ,EXIT("Indietro")
);
MENU(dispenserCalMenu,"Cal. Dispenser",doNothing,noEvent,wrapStyle
    ,FIELD(Prefs.pourFullQuantity,"FullQuantity","mL",0,100,1,0,savePreferences,exitEvent,noStyle)
    ,FIELD(Prefs.pourFullTime,"FullTime","ms",0,10000,100,10,savePreferences,exitEvent,noStyle)
    ,FIELD(Prefs.pourRefillTime,"RefillTime","ms",0,10000,100,10,savePreferences,exitEvent,noStyle)
    ,FIELD(Prefs.pourDeadTime,"DeadTime","ms",0,10000,100,10,savePreferences,exitEvent,noStyle)
    ,FIELD(Prefs.pourRate,"PourRate","mL/s",0,100,1,0.1,savePreferences,exitEvent,noStyle)
    ,EXIT("Indietro")
);
void glassAccessPositionEvent(eventMask e)
{
    if (e == updateEvent)
        stepperCarriage.moveToMM(Prefs.glassAccessPosition);
    else if (e == exitEvent)
        savePreferences();
}
MENU(glassCalMenu,"Cal. Bicchiere",doNothing,noEvent,wrapStyle
    ,FIELD(Prefs.glassAccessPosition,"Posizione","mm",0,STEPPER1_MAX_TRAVEL_MM,10,1,glassAccessPositionEvent,updateEvent|exitEvent,noStyle)
    ,EXIT("Indietro")
);
MENU(calibrationMenu,"Calibrazione",doNothing,noEvent,wrapStyle
    ,SUBMENU(bottlesCalMenu)
    ,SUBMENU(servoCalMenu)
    ,SUBMENU(dispenserCalMenu)
    ,SUBMENU(glassCalMenu)
    ,EXIT("Indietro")
);
void restart()
{
    ESP.restart();
}
MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
    ,SUBMENU(cocktailsMenu)
    ,SUBMENU(bottlesMenu)
    ,SUBMENU(calibrationMenu)
    ,OP("Riavvia",restart,enterEvent)
);
NAVROOT(nav, mainMenu, MENU_MAX_DEPTH, in, out);

void setup() {
    // Initialize Serial
    Serial.begin(SERIAL_BAUD_RATE);
    while(!Serial);

    // Initialize Preferences
    if(!Prefs.begin(PREFERENCES_NAMESPACE))
    {
        Serial.println("Cannot load preferences.");
        exit(-1);
    }

    // Initialize Stepper
    stepperEngine.init();
    stepperCarriage.begin();

    // Initialize Rotary Encoder
    rotaryEncoder.begin();

    // Initialize Display
    lcd.begin(DISPLAY_COLS,DISPLAY_ROWS);

    // Menu settings
    populateCocktailsMenu();
    populateBottleContentMenu();
    nav.showTitle=false;
    nav.useUpdateEvent=true;

    // Carriage Homing
    lcd.setCursor(0,0);
    lcd.print("Homing...");
    // Move servo to safe idle position
    servo.move(Prefs.servoIdleAngle);
    stepperCarriage.home();
    // Move carriage to the glass access position
    stepperCarriage.moveToMM(Prefs.glassAccessPosition, true);

    // Servo Test
    lcd.setCursor(0,0);
    lcd.print("Servo Test...");
    servo.move(Prefs.servoPourAngle);
    delay(2000);
    servo.move(Prefs.servoIdleAngle);
    delay(2000);
}

void loop() {
    nav.poll();
    delay(100);
}

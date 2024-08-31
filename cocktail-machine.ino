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
#include "pyd_machine.h"
#include "bottles.h"
#include "cocktails.h"

// Menu Inputs
PYD_RotaryEncoder rotaryEncoder(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_PIN_BUTTON);
MENU_INPUTS(in, &rotaryEncoder.rotaryEventIn, &rotaryEncoder.keyIn);
// Menu Outputs
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
MENU_OUTPUTS(out,MENU_MAX_DEPTH,LCD_OUT(lcd,{0,0,DISPLAY_COLS,DISPLAY_ROWS}),NONE);

/* Menu Variables */
int cocktailNumber = -1;
int glassSize = 1; // 0: normal, 1: large
int bottleNumber = 1;
int16_t bottleContent = 0;
float bottleQuantity = 0;
float bottlePosition = 0;

const int PYD_cocktails_N = sizeof(PYD_cocktails)/sizeof(*PYD_cocktails);
const int PYD_bottles_N = sizeof(PYD_bottles)/sizeof(*PYD_bottles);

Menu::menuValue<typeof(cocktailNumber)>* menuValue_cocktails[127];
Menu::menuValue<typeof(bottleContent)>* menuValue_bottles[PYD_bottles_N];
Menu::prompt* chooseCocktailMenu_data[127];
Menu::prompt* bottleContentMenu_data[PYD_bottles_N];

/* Menu Actions */
// Return the index of the bottle containing the ingredient, -1 if not found, -2 if not found and optional
int isIngredientAvailable(const PYD_ingredient_t* ingredient)
{
    int n = sizeof(Prefs.bottleContent)/sizeof(*Prefs.bottleContent);
    for (int i=0; i<n; i++)
        if (strcmp(ingredient->name, PYD_bottles[Prefs.bottleContent[i]]) == 0)
            if (Prefs.bottleQuantity[i] >= ingredient->quantity)
                return i;
    if (ingredient->optional)
        return -2;
    return -1;
}
bool areIngredientsAvailable(const PYD_cocktail_t* cocktail)
{
    for (int i=0; i<cocktail->len; i++)
        if (isIngredientAvailable(&cocktail->ingredients[i]) == -1)
            return false;
    return true;
}
result onPrepareCocktailEnter()
{
    if (cocktailNumber < 0)
        return proceed;
    const PYD_cocktail_t* cocktail = PYD_cocktails[cocktailNumber];
    if (!areIngredientsAvailable(cocktail))
    {
        lcd.clear();
        lcd.print("Ingredienti mancanti");
        delay(2000);
        return proceed;
    }
    for (int i=0; i<cocktail->len; i++)
    {
        int bottle = isIngredientAvailable(&cocktail->ingredients[i]);
        if (bottle < 0)
            continue;
        lcd.clear();
        lcd.print("Versando:");
        lcd.setCursor(0,1);
        lcd.print(PYD_bottles[Prefs.bottleContent[bottle]]);
        Machine.moveAxis(Prefs.bottlePosition[bottle], true);
        int toPour = cocktail->ingredients[i].quantity;
        if (glassSize == 0)
            toPour /= 2;
        while (toPour > 0)
        {
            if (toPour >= Prefs.pourFullQuantity)
            {
                Machine.moveServo(Prefs.servoPourAngle, false);
                delay(Prefs.pourFullTime);
                toPour -= Prefs.pourFullQuantity;
            }
            else
            {
                Machine.moveServo(Prefs.servoPourAngle, false);
                int d = round((float)(1000*toPour)/Prefs.pourRate) + Prefs.pourDeadTime;
                lcd.setCursor(0,2);
                lcd.print(d);
                delay(d);
                toPour = 0;
            }
            Machine.moveServo(Prefs.servoIdleAngle, false);
            if (toPour > 0)
                delay(Prefs.pourRefillTime);
            else
                delay(Prefs.servoIdleTime);
        }
        Prefs.bottleQuantity[bottle] -= cocktail->ingredients[i].quantity;
    }
    Prefs.saveAll();
    Machine.moveAxis(Prefs.glassAccessPosition, true);
    lcd.clear();
    lcd.print("Cocktail pronto!");
    lcd.setCursor(0,1);
    lcd.print(cocktail->name);
    delay(2000);
    return proceed;
}
result onBottlesMenuEvent(eventMask e)
{
    if (e == enterEvent)
        return onBottlesMenuEnter();
    else if (e == exitEvent)
        return onBottlesMenuExit();
    return proceed;
}
result onBottlesMenuEnter()
{
    bottleNumber = 1;
    onBottleNumberUpdate();
    return proceed;
}
result onBottlesMenuExit()
{
    Serial.println("onBottlesMenuExit");
    Prefs.saveAll();
    Machine.moveAxis(Prefs.glassAccessPosition, false);
    return proceed;
}
void onBottleNumberUpdate()
{
    bottleContent = Prefs.bottleContent[bottleNumber-1];
    bottleQuantity = Prefs.bottleQuantity[bottleNumber-1];
    bottlePosition = Prefs.bottlePosition[bottleNumber-1];
    Machine.moveAxis(bottlePosition, false);
}
void onBottleContentExit()
{
    Prefs.bottleContent[bottleNumber-1] = bottleContent;
}
void onBottleQuantityUpdate()
{
    Prefs.bottleQuantity[bottleNumber-1] = bottleQuantity;
}
void onBottlePositionUpdate()
{
    Prefs.bottlePosition[bottleNumber-1] = bottlePosition;
    Machine.moveAxis(bottlePosition, false);
}
void onServoCalMenuExit()
{
    Machine.moveServo(Prefs.servoIdleAngle, false);
}
void onServoPourAngleUpdate()
{
    Machine.moveServo(Prefs.servoPourAngle, false);
}
void onServoIdleAngleUpdate()
{
    Machine.moveServo(Prefs.servoIdleAngle, false);
}
void onGlassAccessPositionUpdate()
{
    Machine.moveAxis(Prefs.glassAccessPosition, false);
}
void onCalibrationMenuExit()
{
    Machine.moveServo(Prefs.servoIdleAngle, false);
    Machine.moveAxis(Prefs.glassAccessPosition, false);
    Prefs.saveAll();
}
result clearMemoryEnter()
{
    Prefs.clearAll();
    return proceed;
}
result onRestartMenuEnter()
{
    Machine.moveAxis(10, true);
    ESP.restart();
    return proceed;
}

/* Menu Definition */
Menu::menuVariantShadows<typeof(cocktailNumber)> chooseCocktailMenuShadows={
    (Menu::callback) doNothing,
    ((systemStyles) (Menu::_menuData|Menu::_canNav|Menu::_isVariant)),
    "",
    noEvent,
    noStyle,
    sizeof(chooseCocktailMenu_data)/sizeof(prompt*),
    chooseCocktailMenu_data,
    &cocktailNumber
};
Menu::choose<typeof(cocktailNumber)> chooseCocktailMenu(chooseCocktailMenuShadows.obj);
TOGGLE(glassSize,toggleGlassSizeMenu,"Bicchiere: ",doNothing,noEvent,noStyle
    ,VALUE("Normale",0,doNothing,noEvent)
    ,VALUE("Grande",1,doNothing,noEvent)
);
MENU(cocktailsMenu,"Prepara Cocktail",doNothing,noEvent,wrapStyle
    ,SUBMENU(chooseCocktailMenu)
    ,SUBMENU(toggleGlassSizeMenu)
    ,OP("Prepara",onPrepareCocktailEnter,enterEvent)
    ,EXIT("Indietro")
);
Menu::menuVariantShadows<typeof(bottleContent)> bottleContentMenuShadows = {
    (Menu::callback) onBottleContentExit,
    ((systemStyles) (Menu::_menuData|Menu::_canNav|Menu::_isVariant|Menu::_parentDraw)),
    "",
    exitEvent,
    noStyle,
    sizeof(bottleContentMenu_data)/sizeof(prompt*),
    bottleContentMenu_data,
    &bottleContent
};
Menu::select<typeof(bottleContent)> bottleContentMenu(bottleContentMenuShadows.obj);
MENU(bottlesMenu,"Bottiglie",onBottlesMenuEvent,enterEvent|exitEvent,wrapStyle
    ,FIELD(bottleNumber,"Bottiglia","",1,BOTTLES_NUM,1,0,onBottleNumberUpdate,updateEvent,noStyle)
    ,SUBMENU(bottleContentMenu)
    ,FIELD(bottleQuantity,"Volume","mL",0,2000,100,10,onBottleQuantityUpdate,updateEvent,noStyle)
    ,EXIT("Indietro")
);
MENU(bottlesCalMenu,"Cal. Bottiglie",onBottlesMenuEnter,enterEvent,wrapStyle
    ,FIELD(bottleNumber,"Bottiglia","",1,BOTTLES_NUM,1,0,onBottleNumberUpdate,updateEvent,noStyle)
    ,FIELD(bottlePosition,"Posizione","mm",0,STEPPER1_MAX_TRAVEL_MM,10,1,onBottlePositionUpdate,updateEvent,noStyle)
    ,EXIT("Indietro")
);
MENU(servoCalMenu,"Cal. Servo",onServoCalMenuExit,exitEvent,wrapStyle
    ,FIELD(Prefs.servoPourAngle,"PourAngle","deg",0,180,10,1,onServoPourAngleUpdate,updateEvent,noStyle)
    ,FIELD(Prefs.servoIdleAngle,"IdleAngle","deg",0,180,10,1,onServoIdleAngleUpdate,updateEvent,noStyle)
    ,EXIT("Indietro")
);
MENU(dispenserCalMenu,"Cal. Dispenser",doNothing,noEvent,wrapStyle
    ,FIELD(Prefs.pourFullQuantity,"FullQuantity","mL",0,100,1,0,doNothing,noEvent,noStyle)
    ,FIELD(Prefs.pourFullTime,"FullTime","ms",0,10000,100,10,doNothing,noEvent,noStyle)
    ,FIELD(Prefs.pourRefillTime,"RefillTime","ms",0,10000,100,10,doNothing,noEvent,noStyle)
    ,FIELD(Prefs.pourDeadTime,"DeadTime","ms",0,10000,100,10,doNothing,noEvent,noStyle)
    ,FIELD(Prefs.pourRate,"PourRate","mL/s",0,100,1,0.1,doNothing,noEvent,noStyle)
    ,EXIT("Indietro")
);
MENU(glassCalMenu,"Cal. Bicchiere",doNothing,noEvent,wrapStyle
    ,FIELD(Prefs.glassAccessPosition,"Posizione","mm",0,STEPPER1_MAX_TRAVEL_MM,10,1,onGlassAccessPositionUpdate,updateEvent,noStyle)
    ,EXIT("Indietro")
);
MENU(clearMemoryMenu,"Pulisci Memoria",doNothing,noEvent,wrapStyle
    ,OP("Cancella",clearMemoryEnter,enterEvent)
    ,EXIT("Indietro")
);
MENU(calibrationMenu,"Calibrazione",onCalibrationMenuExit,exitEvent,wrapStyle
    ,SUBMENU(bottlesCalMenu)
    ,SUBMENU(servoCalMenu)
    ,SUBMENU(dispenserCalMenu)
    ,SUBMENU(glassCalMenu)
    ,SUBMENU(clearMemoryMenu)
    ,EXIT("Indietro")
);
MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
    ,SUBMENU(cocktailsMenu)
    ,SUBMENU(bottlesMenu)
    ,SUBMENU(calibrationMenu)
    ,OP("Riavvia",onRestartMenuEnter,enterEvent)
);
NAVROOT(nav, mainMenu, MENU_MAX_DEPTH, in, out);

void populateCocktailsMenu()
{
    int k = 0;
    menuValue_cocktails[k] = new Menu::menuValue<typeof(cocktailNumber)>("Seleziona Cocktail", -1);
    chooseCocktailMenu_data[k] = menuValue_cocktails[k];
    for (int i=0; i<PYD_cocktails_N; i++)
    {
        const PYD_cocktail_t* cocktail = PYD_cocktails[i];
        if (areIngredientsAvailable(cocktail))
        {
            k++;
            menuValue_cocktails[k] = new Menu::menuValue<typeof(cocktailNumber)>(cocktail->name, i);
            chooseCocktailMenu_data[k] = menuValue_cocktails[k];
        }
        if (k == 126)
            break;
    }
    ((Menu::menuNodeShadow*)chooseCocktailMenu.shadow)->sz = k+1;
}
void populateBottleContentMenu()
{
    for (int i=0; i<PYD_bottles_N; i++)
    {
        menuValue_bottles[i] = new Menu::menuValue<typeof(bottleContent)>(PYD_bottles[i], i);
        bottleContentMenu_data[i] = menuValue_bottles[i];
    }
}

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

    // Initialize Rotary Encoder
    rotaryEncoder.begin();

    // Initialize Display
    lcd.begin(DISPLAY_COLS,DISPLAY_ROWS);

    // Menu settings
    populateCocktailsMenu();
    populateBottleContentMenu();
    nav.showTitle=false;
    nav.useUpdateEvent=true;

    // Initialize Machine
    Machine.begin();

    // Homing
    lcd.setCursor(0,0);
    lcd.print("Homing...");
    Machine.home();

    // Servo Test
    lcd.setCursor(0,0);
    lcd.print("Servo Test...");
    Machine.servoTest();
    
    Machine.moveAxis(Prefs.glassAccessPosition, true);
}

void loop() {
    nav.poll();
    delay(100);
}

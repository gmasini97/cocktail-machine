/*
 *  Cocktail Machine
 *
 *  Requirements:
 *  - https://github.com/neu-rah/ArduinoMenu/
 *  - https://github.com/fmalpartida/New-LiquidCrystal
 *  - https://github.com/SimpleHacks/QDEC
 *  - https://github.com/gin66/FastAccelStepper
 *  - https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences
 *  - 
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

FastAccelStepperEngine stepperEngine;
PYD_Stepper stepperCarriage(
    &stepperEngine,
    STEPPER1_PIN_STEP,
    STEPPER1_PIN_DIRECTION,
    STEPPER1_PIN_ENABLE,
    STEPPER1_PIN_ENDSTOP,
    STEPPER1_ENDSTOP_ACTIVE_LOW,
    STEPPER1_REVERSE_DIRECTION
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
MENU(cocktailsMenu,"Prepara Cocktail",doNothing,noEvent,wrapStyle
    ,OP("op1",doNothing,noEvent)
    ,EXIT("Indietro")
);
SELECT(bottleContent,bottleContentMenu,"",doNothing,noEvent,noStyle
    ,VALUE("Gin",0,doNothing,noEvent)
    ,VALUE("Vodka",1,doNothing,noEvent)
    ,VALUE("Rum",2,doNothing,noEvent)
    ,VALUE("Tonica",3,doNothing,noEvent)
    ,VALUE("Ginger Beer",4,doNothing,noEvent)
);
MENU(bottlesMenu,"Bottiglie",initBottlesMenu,enterEvent,wrapStyle
    ,FIELD(bottleNumber,"Bottiglia","",1,BOTTLES_NUM,1,1,updateVariables,updateEvent,noStyle)
    ,SUBMENU(bottleContentMenu)
    ,FIELD(bottleQuantity,"Quantità","mL",0,2000,100,10,updatePreferences,exitEvent,noStyle)
    ,EXIT("Indietro")
);
MENU(bottlesCalMenu,"Cal. Bottiglie",initBottlesMenu,enterEvent,wrapStyle
    ,FIELD(bottleNumber,"Bottiglia","",1,BOTTLES_NUM,1,1,updateVariables,updateEvent,noStyle)
    ,FIELD(bottlePosition,"Posizione","mm",0,STEPPER1_MAX_TRAVEL_MM,10,1,updatePreferences,exitEvent,noStyle)
    ,EXIT("Indietro")
);
MENU(servoCalMenu,"Cal. Servo",doNothing,noEvent,wrapStyle
    ,FIELD(Prefs.servoPourAngle,"PourAngle","deg",0,180,10,1,savePreferences,exitEvent,noStyle)
    ,FIELD(Prefs.servoIdleAngle,"IdleAngle","deg",0,180,10,1,savePreferences,exitEvent,noStyle)
    ,EXIT("Indietro")
);
MENU(dispenserCalMenu,"Cal. Dispenser",doNothing,noEvent,wrapStyle
    ,FIELD(Prefs.pourRefillTime,"RefillTime","ms",0,10000,100,10,savePreferences,exitEvent,noStyle)
    ,FIELD(Prefs.pourDeadTime,"DeadTime","ms",0,10000,100,10,savePreferences,exitEvent,noStyle)
    ,FIELD(Prefs.pourRate,"PourRate","mL/s",0,100,1,0.1,savePreferences,exitEvent,noStyle)
    ,EXIT("Indietro")
);
MENU(calibrationMenu,"Calibrazione",doNothing,noEvent,wrapStyle
    ,SUBMENU(bottlesCalMenu)
    ,SUBMENU(servoCalMenu)
    ,SUBMENU(dispenserCalMenu)
    ,EXIT("Indietro")
);
MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
    ,SUBMENU(cocktailsMenu)
    ,SUBMENU(bottlesMenu)
    ,SUBMENU(calibrationMenu)
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
    stepperCarriage.setDynamics(STEPPER1_SPEED_IN_HZ, STEPPER1_ACCELERATION);

    // Initialize Rotary Encoder
    rotaryEncoder.begin();

    // Initialize Display
    lcd.begin(DISPLAY_COLS,DISPLAY_ROWS);

    // Menu settings
    nav.showTitle=false;
    nav.useUpdateEvent=true;

    // Carriage Homing
    lcd.setCursor(0,0);
    lcd.print("Homing...");
    stepperCarriage.home();

    // Servo Test
    lcd.setCursor(0,0);
    lcd.print("Servo Test...");
    servo.test();
}

void loop() {
    nav.poll();
    delay(100);
}

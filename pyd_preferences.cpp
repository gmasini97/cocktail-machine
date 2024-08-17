
#include "pyd_preferences.h"

PYD_Preferences::PYD_Preferences()
{

}

bool PYD_Preferences::begin()
{
  if(!prefs.begin("cocktail"))
    return false;
  loadAll();
  return true;
}

void PYD_Preferences::end()
{
  prefs.end();
}

void PYD_Preferences::loadAll()
{
  for (int i=0; i<BOTTLES_NUM; i++)
  {
    bottleContent[i] = 0;
    bottleQuantity[i] = DEFAULT_BOTTLE_QUANTITY;
    bottlePosition[i] = DEFAULT_BOTTLE_POSITION;
  }
  prefs.getBytes("bottleContent", &bottleContent, sizeof(bottleContent));
  prefs.getBytes("bottleQuantity", &bottleQuantity, sizeof(bottleQuantity));
  prefs.getBytes("bottlePosition", &bottlePosition, sizeof(bottlePosition));
  pourRefillTime  = prefs.getShort("pourRefillTime", DEFAULT_POUR_REFILL_TIME);
  pourDeadTime    = prefs.getShort("pourDeadTime", DEFAULT_POUR_DEAD_TIME);
  pourRate        = prefs.getFloat("pourRate", DEFAULT_POUR_RATE);
  servoPourAngle  = prefs.getShort("servoPourAngle", DEFAULT_SERVO_POUR_ANGLE);
  servoIdleAngle  = prefs.getShort("servoIdleAngle", DEFAULT_SERVO_IDLE_ANGLE);
  autoSave        = prefs.getBool("autoSave", DEFAULT_AUTO_SAVE);
}

void PYD_Preferences::saveAll()
{
  prefs.putBytes("bottleContent", (byte*)(&bottleContent), sizeof(bottleContent));
  prefs.putBytes("bottleQuantity", (byte*)(&bottleQuantity), sizeof(bottleQuantity));
  prefs.putBytes("bottlePosition", (byte*)(&bottlePosition), sizeof(bottlePosition));
  prefs.putShort("pourRefillTime", pourRefillTime);
  prefs.putShort("pourDeadTime", pourDeadTime);
  prefs.putFloat("pourRate", pourRate);
  prefs.putShort("servoPourAngle", servoPourAngle);
  prefs.putShort("servoIdleAngle", servoIdleAngle);
}
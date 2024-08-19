#include "pyd_preferences.h"

PYD_Preferences Prefs;

bool PYD_Preferences::begin(const char* name)
{
  if(!mPreferences.begin(name))
    return false;
  loadAll();
  return true;
}

void PYD_Preferences::end()
{
  mPreferences.end();
}

void PYD_Preferences::loadAll()
{
  for (int i=0; i<BOTTLES_NUM; i++)
  {
    bottleContent[i] = 0;
    bottleQuantity[i] = DEFAULT_BOTTLE_QUANTITY;
    bottlePosition[i] = DEFAULT_BOTTLE_POSITION;
  }
  mPreferences.getBytes("bottleContent", &bottleContent, sizeof(bottleContent));
  mPreferences.getBytes("bottleQuantity", &bottleQuantity, sizeof(bottleQuantity));
  mPreferences.getBytes("bottlePosition", &bottlePosition, sizeof(bottlePosition));
  pourRefillTime  = mPreferences.getShort("pourRefillTime", DEFAULT_POUR_REFILL_TIME);
  pourDeadTime    = mPreferences.getShort("pourDeadTime", DEFAULT_POUR_DEAD_TIME);
  pourRate        = mPreferences.getFloat("pourRate", DEFAULT_POUR_RATE);
  servoPourAngle  = mPreferences.getShort("servoPourAngle", DEFAULT_SERVO_POUR_ANGLE);
  servoIdleAngle  = mPreferences.getShort("servoIdleAngle", DEFAULT_SERVO_IDLE_ANGLE);
}

void PYD_Preferences::saveAll()
{
  mPreferences.putBytes("bottleContent", (byte*)(&bottleContent), sizeof(bottleContent));
  mPreferences.putBytes("bottleQuantity", (byte*)(&bottleQuantity), sizeof(bottleQuantity));
  mPreferences.putBytes("bottlePosition", (byte*)(&bottlePosition), sizeof(bottlePosition));
  mPreferences.putShort("pourRefillTime", pourRefillTime);
  mPreferences.putShort("pourDeadTime", pourDeadTime);
  mPreferences.putFloat("pourRate", pourRate);
  mPreferences.putShort("servoPourAngle", servoPourAngle);
  mPreferences.putShort("servoIdleAngle", servoIdleAngle);
}
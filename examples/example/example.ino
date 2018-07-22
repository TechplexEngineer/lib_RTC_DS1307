/* WRITE DOC
*/
#include <Wire.h>
#include "RTCDS1307.h"

void setup()
{
  Wire.begin();
  RTC.Begin();
  Serial.begin(9600);
  Serial.print("\n\n\n\n\n\n\n\n\n\n");
  Serial.print("\n\n\n\n\n\n\n\n\n\n");
  Serial.print("\n\n\n\n\n\n\n\n\n\n");
  Serial.println("Plexuino Starting Up!");
  delay(1000);
}

void loop()
{
  Serial.println("-------");
  Serial.println(RTC.getDateTime(TM_FMT_HR));
  Serial.println(RTC.getDateTime(TM_FMT_HRL));
  Serial.println("-------");
  Serial.println(RTC.getDateTime(TM_FMT_DATE));
  Serial.println(RTC.getDateTime(TM_FMT_DATE_GB));
  Serial.println("-------");
  Serial.println(RTC.getDateTime(TM_FMT_TIME_24));
  Serial.println(RTC.getDateTime(TM_FMT_TIME));
  Serial.println("-------");
  Serial.println(RTC.getDateTime(TM_FMT_T_HR));
  Serial.println(RTC.getDateTime(TM_FMT_T_MIN));
  Serial.println(RTC.getDateTime(TM_FMT_T_SEC));
  Serial.println("-------");
  Serial.println(RTC.getDateTime(TM_FMT_D_MONTH));
  Serial.println(RTC.getDateTime(TM_FMT_D_MONTHL));
  Serial.println(RTC.getDateTime(TM_FMT_D_DAY));
  Serial.println(RTC.getDateTime(TM_FMT_D_WKDAY));
  Serial.println(RTC.getDateTime(TM_FMT_D_YEAR));
  Serial.println(RTC.getDateTime(TM_FMT_STAMP));
  Serial.println("-------");
  delay(2500);
}


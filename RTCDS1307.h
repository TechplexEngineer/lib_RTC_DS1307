/*
  BarometricPressure.h - Library for BMP085 Barometric Pressure sensor.
	Created by Blake Bourque, 2/7/13
*/
#ifndef RealTimeClock_h
#define RealTimeClock_h

#include <Arduino.h>

typedef enum{
	TM_FMT_HR = 0, 	//Human Readable ie: (mm/dd/yy hh:mm:ss)
	TM_FMT_HRL,			//Human Readable Long (hh:mm:ss  Fri, dd Feb yyyy)
	TM_FMT_DATE,		//Slash Delimited. ie: (mm/dd/yy)
	TM_FMT_DATE_GB,	//Slash Delimited. ie: (yy/mm/dd)
	TM_FMT_TIME_24,	//Colon delimited. ie: (hh:mm:ss)
	TM_FMT_TIME,			//Colon delimited. ie: (hh:mm:ss (AM|PM))
	TM_FMT_T_HR,		//hour
	TM_FMT_T_MIN,		//minute
	TM_FMT_T_SEC,		//second
	TM_FMT_D_MONTH,	//month
	TM_FMT_D_MONTHL,//month long (Jan - Dec)
	TM_FMT_D_DAY,		//day
	TM_FMT_D_WKDAY, //weekday (Mon - Sun)
	TM_FMT_D_YEAR,	//year
	TM_FMT_STAMP,		//unix timestamp (seconds since epoch)
}TM_FMT;

class RealTimeClock
{
  public:
  	RealTimeClock(void);
  	void Begin(void);

  	//Forward Declarations
		void setDate(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);
		void setDateSerial(void);

		String getDateTime(TM_FMT format=TM_FMT_HR, bool leadingZero=false);

	private:
		static const String Day[];
		static const String Mon[];

};

extern RealTimeClock RTC;



#endif
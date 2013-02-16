
#include <Arduino.h>
#include <Wire.h>
#include "RTCDS1307.h"

// Arduino version compatibility Pre-Compiler Directives
#if defined(ARDUINO) && ARDUINO >= 100					// Arduino v1.0 and newer
	#define I2C_WRITE Wire.write
	#define I2C_READ Wire.read
#else																						// Arduino Prior to v1.0
	#define I2C_WRITE Wire.send
	#define I2C_READ Wire.receive
#endif

#define ZERO 0x00

#define DS1307_I2C_ADDRESS 0x68									// This is the I2C address

const String RealTimeClock::Day[] = {"","Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
const String RealTimeClock::Mon[] = {"","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

// byte RealTimeClock::second, RealTimeClock::minute, RealTimeClock::hour;
// byte RealTimeClock::dayOfWeek, RealTimeClock::dayOfMonth, RealTimeClock::month, RealTimeClock::year;

// Convert normal decimal numbers to binary coded decimal
inline byte decToBcd(byte val)
{
	return ( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
inline byte bcdToDec(byte val)
{
	return ( (val/16*10) + (val%16) );
}

RealTimeClock::RealTimeClock(void)
{
}

void RealTimeClock::Begin(void)
{
	Wire.begin(); //!@todo not sure if I should do this or not.
}

// Gets the date and time from the ds1307 and prints result
String RealTimeClock::getDateTime(TM_FMT format/*=TM_FMT_HR*/, bool leadingZero/*=false*/)
{
	byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

	// Reset the register pointer
	Wire.beginTransmission(DS1307_I2C_ADDRESS);
	I2C_WRITE(byte(ZERO));
	Wire.endTransmission();

	Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

	// A few of these need masks because certain bits are control bits
	second     = bcdToDec(I2C_READ() & 0x7f);
	minute     = bcdToDec(I2C_READ());
	hour       = bcdToDec(I2C_READ() & 0x3f);			// Need to change this if 12 hour am/pm
	dayOfWeek  = bcdToDec(I2C_READ());
	dayOfMonth = bcdToDec(I2C_READ());
	month      = bcdToDec(I2C_READ());
	year       = bcdToDec(I2C_READ());

	//////////////////////////////////////////////
	// TM_FMT_HR = 0, 	//Human Readable
	// TM_FMT_HRL,			//Human Readable Long
	// TM_FMT_DATE,			//Slash Delimited. ie: (mm/dd/yy)
	// TM_FMT_DATE_GB,	//Slash Delimited. ie: (yy/mm/dd)
	// TM_FMT_TIME_24,	//Colon delimited. ie: (hh:mm:ss)
	// TM_FMT_T_HR,			//hour
	// TM_FMT_T_MIN,		//minute
	// TM_FMT_T_SEC,		//second
	// TM_FMT_D_MONTH,	//month
	// TM_FMT_D_DAY,		//day
	// TM_FMT_D_YEAR,		//year
	//////////////////////////////////////////////

	String output = "";
	bool pm = false;

	if (format == TM_FMT_T_HR || format == TM_FMT_HRL || format == TM_FMT_HR || format == TM_FMT_TIME_24 || format == TM_FMT_TIME) {
		if(format == TM_FMT_TIME)
			if (hour > 12) {
				hour -= 12;
				pm = true;
			}

		if (hour < 10 && leadingZero)
			output += "0";
		output += String(hour, DEC);
	}


	if (format == TM_FMT_HRL || format == TM_FMT_HR || format == TM_FMT_TIME_24 || format == TM_FMT_TIME)
		output += ":";

	if (format == TM_FMT_T_MIN || format == TM_FMT_HRL || format == TM_FMT_HR || format == TM_FMT_TIME_24 || format == TM_FMT_TIME) {
		if (minute < 10 && leadingZero)
			output += "0";
		output += String(minute, DEC);
	}

	if (format == TM_FMT_HRL || format == TM_FMT_HR || format == TM_FMT_TIME_24 || format == TM_FMT_TIME)
		output += ":";

	if (format == TM_FMT_T_SEC || format == TM_FMT_HRL || format == TM_FMT_HR || format == TM_FMT_TIME_24 || format == TM_FMT_TIME) {
		if (second < 10 && leadingZero)
			output += "0";
		output += String(second, DEC);
	}
	if(format == TM_FMT_TIME) {
		if (pm)
			output += " PM";
		else
			output += " AM";
	}

	if (format == TM_FMT_HRL || format == TM_FMT_HR)
		output += "  ";

	if (format == TM_FMT_D_WKDAY || format == TM_FMT_HRL)
		output += String(Day[dayOfWeek]);
	if (format == TM_FMT_HRL)
		output += ", ";
	if (format == TM_FMT_D_DAY || format == TM_FMT_HRL)
		output += String(dayOfMonth, DEC);
	if (format == TM_FMT_HRL)
		output += " ";
	if (format == TM_FMT_D_MONTHL || format == TM_FMT_HRL)
		output += String(Mon[month]);
	if (format == TM_FMT_HRL)
		output += " ";
	if (format == TM_FMT_D_YEAR || format == TM_FMT_HRL) {
		output += "20";
		if (year < 10 && leadingZero)
			output += "0";
		output += String(year, DEC);
	}

	if (format == TM_FMT_D_MONTH)
		output += String(month);

	if (format == TM_FMT_HR || format == TM_FMT_DATE) {
		output += String(month);
		output += "/";
		output += String(dayOfMonth, DEC);
		output += "/";
		output += "20";
		if (year < 10 && leadingZero)
			output += "0";
		output += String(year, DEC);
	}
	if (format == TM_FMT_DATE_GB) {
		output += "20";
		if (year < 10 && leadingZero)
			output += "0";
		output += String(year, DEC);
		output += "/";
		output += String(month);
		output += "/";
		output += String(dayOfMonth, DEC);
	}
	if (format == TM_FMT_STAMP) {
		//long out = second + 60*minute +60*60*hour
		output += "Not Implimented";
	}

	return output;
}

// 1) Sets the date and time on the ds1307
// 2) Starts the clock
// 3) Sets hour mode to 24 hour clock
// Assumes you're passing in valid numbers,
// Probably need to put in checks for valid numbers.
void setDate(byte second, byte minute, byte hour,
	byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
	Wire.beginTransmission(DS1307_I2C_ADDRESS);
	I2C_WRITE(byte(ZERO));
	I2C_WRITE(decToBcd(second));  // 0 to bit 7 starts the clock
	I2C_WRITE(decToBcd(minute));
	I2C_WRITE(decToBcd(hour));    // If you want 12 hour am/pm you need to set
	// bit 6 (also need to change readDateDs1307)
	I2C_WRITE(decToBcd(dayOfWeek));
	I2C_WRITE(decToBcd(dayOfMonth));
	I2C_WRITE(decToBcd(month));
	I2C_WRITE(decToBcd(year));
	Wire.endTransmission();
}

void setDateSerial(void)
{
	byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

	// Use of (byte) type casting and ascii math to achieve result.
	second      = (byte) ((Serial.read() - 48) * 10 + (Serial.read() - 48));
	minute      = (byte) ((Serial.read() - 48) * 10 +  (Serial.read() - 48));
	hour        = (byte) ((Serial.read() - 48) * 10 +  (Serial.read() - 48));
	dayOfWeek   = (byte) (Serial.read() - 48);
	dayOfMonth  = (byte) ((Serial.read() - 48) * 10 +  (Serial.read() - 48));
	month       = (byte) ((Serial.read() - 48) * 10 +  (Serial.read() - 48));
	year        = (byte) ((Serial.read() - 48) * 10 +  (Serial.read() - 48));

	setDate(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
}

//! Preinstantiate class
RealTimeClock RTC;
/*
  TC74.h - Library for Microchip TC74 temperature sensors.
  Created by Paul Jenkins, November 17, 2011.
  Released into the public domain.
  http://forum.arduino.cc/index.php?topic=79016.0
*/

#ifndef TC74_h
#define TC74_h

// Allow for compilation in 0022 or 1.0
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Wire.h"

class TC74 {
	public:
		TC74(byte addr);
		TC74();
		int read();
	private:
		byte _addr;
};

#endif
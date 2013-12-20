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


#define TC74A0 0x48
#define TC74A1 0x49
#define TC74A2 0x4a
#define TC74A3 0x4b
#define TC74A4 0x4c
#define TC74A5 0x4d
#define TC74A6 0x4e
#define TC74A7 0x4f

// class TC74 {
// 	public:
// 		TC74(byte addr);
// 		// TC74();
// 		void begin();
// 		int read();
// 	private:
// 		byte _addr;
// };

#endif
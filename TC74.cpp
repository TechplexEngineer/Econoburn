// Allow for compilation in 0022 or 1.0
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "TC74.h"
#include "Wire.h"

//First, the constructor where an address is supplied
TC74::TC74(byte addr) {
//  byte _addr;
  if (addr == 0) _addr = 0x48;
  if (addr == 1) _addr = 0x49;
  if (addr == 2) _addr = 0x4a;
  if (addr == 3) _addr = 0x4b;
  if (addr == 4) _addr = 0x4c;
  if (addr == 5) _addr = 0x4d;
  if (addr == 6) _addr = 0x4e;
  if (addr == 7) {
  	  _addr = 0x4f;
  }
  else {
  	  _addr = 0x48;   //Set a default address
  }
}

//Second, a constructor where no address is specified
TC74::TC74(void) {
	byte _addr = 0x4f;
}

int TC74::read(void)
{
	int _temp = 255;
	// Get a reading from the temperature sensor
        Wire.beginTransmission(_addr);
        Wire.write((uint8_t) 0); 
        Wire.endTransmission();
    
        // request 1 byte from sensor
        Wire.requestFrom(_addr,1);
    
        _temp = Wire.read();
        
        if (_temp > 127) {
           _temp = 255 - _temp + 1;
        }
       
        return _temp;
}

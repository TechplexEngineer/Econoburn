#include <Wire.h>

// Test TC74 library
#include <TC74.h>

// TC74 sensor(3);  //Data object for sensor

byte _addr = 0x4b;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Startup Complete");
}

void loop() {
	int _temp = 255;
	// Get a reading from the temperature sensor
	Wire.beginTransmission(_addr);
	Wire.write((uint8_t) 0); 
	Wire.endTransmission();

	// request 1 byte from sensor
	Wire.requestFrom(_addr,1);

	_temp = Wire.read();
	
	if (_temp > 127) {
		_temp = 256 - _temp;
	}

	
	Serial.println("The temp is: ");
	Serial.println(_temp);
	delay(5000);
}

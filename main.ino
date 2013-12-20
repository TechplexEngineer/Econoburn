#include <Wire.h>

// Test TC74 library
#include <TC74.h>

// byte _addr = 0x4b;

#define SUPPLY_SENS TC74A1
#define RETURN_SENS TC74A0
#define THRESH 5 //minimum difference between supply and return in deg f
#define BOILER_CONTROL_PIN 8 //set pin to high to disable boiler
#define MINIMUM_CYCLE_TIME 60 //in sec

//fwd declarations
int getTempInC(byte addr);
float c2f(float f);
float getTempInF(byte addr);

void setup() {
  Serial.begin(9600);
  pinMode(BOILER_CONTROL_PIN, OUTPUT);
  Wire.begin();
  Serial.println("Startup Complete");
}

void loop() {
	float supplyTemp = getTempInF(SUPPLY_SENS);
	float returnTemp = getTempInF(RETURN_SENS);

	Serial.print(micros());
	Serial.print("  | ");
	Serial.print(supplyTemp);
	Serial.print(" F | ");
	Serial.print(returnTemp);
	Serial.print(" F | ");

	if (returnTemp > (supplyTemp+THRESH))
	{
		digitalWrite(BOILER_CONTROL_PIN, HIGH);
		Serial.print("HIGH");
	}
	else if (returnTemp < (supplyTemp-THRESH))
	{
		Serial.print("LOW");
		digitalWrite(BOILER_CONTROL_PIN, LOW);
	}
	Serial.println("");

	
	delay(1000);
}


int getTempInC(byte addr)
{
	int _temp = 255;
	// Get a reading from the temperature sensor
	Wire.beginTransmission(addr);
	Wire.write((uint8_t) 0); 
	Wire.endTransmission();

	// request 1 byte from sensor
	Wire.requestFrom(addr,1);

	_temp = Wire.read();
	
	if (_temp > 127) {
		_temp = 256 - _temp;
	}
	return _temp;
}

float c2f(float f)
{
	float _temp = f*9.0;
	_temp /= 5;
	_temp += 32;
	return _temp;
}

float getTempInF(byte addr)
{
	float _temp = getTempInC(addr);
	_temp = c2f(_temp);
	return _temp;
}
#include <Wire.h>

// Test TC74 library
#include <TC74.h>

// byte _addr = 0x4b;

#define SUPPLY_SENS TC74A1
#define RETURN_SENS TC74A0
#define THRESH_HOT 3 //minimum difference between supply and return in deg f
#define THRESH_COLD 1
#define BOILER_CONTROL_PIN 8 //set pin to high to disable boiler
// #define MINIMUM_CYCLE_TIME 60 //in sec
#define DELAY_BETWEEN_READS 1000 //in miliseconds

//fwd declarations
int getTempInC(byte addr);
float c2f(float f);
float getTempInF(byte addr);


const int numReadings = 10;
float supplyVals[numReadings];
int supplyIndex = 0;			// the index of the current reading
float supplyTotal = 0;			// the running total
float supplyAverage = 0;		// the average

float returnVals[numReadings];
int returnIndex = 0;			// the index of the current reading
float returnTotal = 0;			// the running total
float returnAverage = 0;		// the average

//lets throw away the first 10 cycles
int count = 0;

void setup() {
	Serial.begin(9600);
	pinMode(BOILER_CONTROL_PIN, OUTPUT);
	digitalWrite(BOILER_CONTROL_PIN, LOW);
	Wire.begin();

	// initialize all the readings to 0: 
	for (int i = 0; i < numReadings; i++)
	{
		supplyVals[i] = 0; 
		returnVals[i] = 0;
	}

	Serial.println("Startup Complete - Boiler Enabled");
}


void loop() {
	float supplyTemp = getTempInF(SUPPLY_SENS);
	float returnTemp = getTempInF(RETURN_SENS);
	//-----------------------------------------------
	// subtract the last reading:
	supplyTotal = supplyTotal - supplyVals[supplyIndex];         
	// read from the sensor:  
	supplyVals[supplyIndex] = supplyTemp;
	// add the reading to the supplyTotal:
	supplyTotal = supplyTotal + supplyVals[supplyIndex];       
	// advance to the next position in the array:  
	supplyIndex = supplyIndex + 1;                    

	// if we're at the end of the array wrap around to the beginning: 
	if (supplyIndex >= numReadings)            
		supplyIndex = 0;                           

	// calculate the average:
	float avgSupplyTemp = supplyTotal / numReadings;
	//-----------------------------------------------
	// subtract the last reading:
	returnTotal = returnTotal - returnVals[returnIndex];         
	// read from the sensor:  
	returnVals[returnIndex] = returnTemp;
	// add the reading to the returnTotal:
	returnTotal = returnTotal + returnVals[returnIndex];       
	// advance to the next position in the array:  
	returnIndex = returnIndex + 1;                    

	// if we're at the end of the array wrap around to the beginning: 
	if (returnIndex >= numReadings)            
		returnIndex = 0;                           

	// calculate the average:
	float avgReturnTemp = returnTotal / numReadings;
	//-----------------------------------------------

	

	if (count < numReadings)
	{
		count ++;
		Serial.print(micros());
		Serial.print("  | ");
		Serial.print("Junk read ");
		Serial.print(count);
		Serial.print(" of ");
		Serial.print(numReadings);
		Serial.println("");
	}
	else
	{
		Serial.print(micros());
		Serial.print("  | ");
		Serial.print(avgSupplyTemp);
		Serial.print(" (");
		Serial.print(supplyTemp);
		Serial.print(") F | ");
		Serial.print(avgReturnTemp);
		Serial.print(" (");
		Serial.print(returnTemp);
		Serial.print(") F | ");
		Serial.print(abs(avgSupplyTemp - avgReturnTemp));
		Serial.print(" F | ");
		if (avgReturnTemp > (avgSupplyTemp+THRESH_COLD))
		{
			digitalWrite(BOILER_CONTROL_PIN, HIGH);
			Serial.print("Boiler Disabled");
		}
		else if (avgReturnTemp < (avgSupplyTemp-THRESH_HOT))
		{
			Serial.print("Boiler Enabled");
			digitalWrite(BOILER_CONTROL_PIN, LOW);
		}
		Serial.println("");
	}

	delay(DELAY_BETWEEN_READS);
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
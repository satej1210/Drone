int Yaw = 0;
int Pitch = 0;
int Roll = 0;


#include <TinyGPS++.h>
#include <Wire.h>
#include <aREST.h>
#include "floatToString.h"
#include <string.h>
#include "SoftwareSerial.h"
#include "SerialData.h"
#include "UltraSonicSensor.h"

#include "HMCMPU.h"
#include "HMC5883L.h"
#include "MPU.h"

#include "Motor.h"
#include "Control.h"
#include "GPS.h"

/*Directions:
  0. Front
  1. Back
  2. Left
  3. Right
  4. Bottom
  5. Top
*/


long stayDistance[5];
long offset[] = { 0, 0, 0, 0, 0, 0 };



int UpSpeed = 0;
int RotationSpeed = 0;





aREST rest = aREST();



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  USSetup();
  Serial.println("Done");
  MotorSetup();
  Serial.println("Done");
  MPUSetup();
  Serial.println("Done");
  GPSSetup();
  Serial.println("Done");
  HMCsetup();
  Serial.println("Done");


  rest.set_id("001");
  rest.set_name("drone");

  rest.variable("X", &X);
  rest.variable("Y", &Y);
  rest.variable("Z", &Z);
  rest.variable("Yaw", &Yaw);
  rest.variable("Pitch", &Pitch);
  rest.variable("Roll", &Roll);


  serialData = "";



  Wire.begin();
}

void loop() {
  startSerialData();
  sendGPS();
  HMCloop();
  readDistances();
  //readIMU();
  MPULoop();
  runMotors();
  stabilize();
  gpsLoop();
  char test[20];
  String x = "\"T";
  x += "\": ";
  x += floatToString(test, float(0), 1, 3);
  appendSerialData(x);
  x = "\"A";
  x += "\": ";
  x += floatToString(test, float(0), 1, 3);
  appendSerialData(x);
  x = "\"Pa";
  x += "\": ";
  x += floatToString(test, float(0), 1, 3);
  appendSerialData(x);
  //test();
  //	stayStable();
  //	moveInDirection();
  endSerialData();
  Serial.println(serialData);
  serialData = "";
  //  int incomingByte;
  //   if (Serial.available() > 0) {
  //    // read the oldest byte in the serial buffer:
  //    incomingByte = Serial.read();
  //    // if it's a capital H (ASCII 72), turn on the LED:
  //    if (incomingByte == 'H') {
  //      digitalWrite(5, HIGH);
  //    }
  //    // if it's an L (ASCII 76) turn off the LED:
  //    if (incomingByte == 'L') {
  //      digitalWrite(5, LOW);
  //    }
  //    Serial.print(incomingByte);
  //  }
}

void readIMU() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  //delay(5000);           // wait 5 seconds for next scan
}

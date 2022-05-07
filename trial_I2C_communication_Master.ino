
#include <Wire.h>

//POTENTIAL PROBLEM IDK SLAVE ADDRESS FOR ARDUINO MEGA
#define SLAVE_ADDR 9 

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  // initialise I2C communication as master
  Wire.begin();
  
}

void loop() {
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5000);                       // wait for 5 secs

  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0);  //sends 1 to the slave
  Wire.endTransmission();

  delay(5000); //wait 5 seconds before starting the sequence where LED is off

  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(3);  //sends 0 to the slave
  Wire.endTransmission();

  delay(5000);
  
}

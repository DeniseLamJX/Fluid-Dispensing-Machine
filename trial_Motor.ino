//Encoder setup
#include <Encoder.h>
#include "U8glib.h"

//Encoder keys
Encoder myEnc(33, 31);
#define menuButt 41
#define encButt 35

U8GLIB_ST7920_128X64_1X u8g(23, 17, 16);  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17

//Stepper setup
#include <Arduino.h>
#include "BasicStepperDriver.h"

//Define steps for Motor
#define MOTOR_STEPS 400 //400 is one round
#define RPM 60 //Keep at 60 or above
#define MICROSTEPS 4

//Motor A: Using X-stepper (EN, DIR, STEP, GND); reminder that Enable is opposite dir.
#define DIR_A A1
#define STEP_A A0

//Motor B: Using Y-stepper (EN, DIR, STEP, GND);
#define DIR_B A7
#define STEP_B A6


BasicStepperDriver stepperA(MOTOR_STEPS, DIR_A, STEP_A); //For Motor A
BasicStepperDriver stepperB(MOTOR_STEPS, DIR_B, STEP_B); //For Motor B

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


//Positive direction
void stepperMove1(int steps){
  stepperA.move(steps);
}

//Negative direction
void stepperMove2(int steps){
  stepperA.move(-1*steps);
}

//Actuator setup; using Z-step and Z-dir
const int in1 = 46;
const int in2 = 48;

void extendActuator() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(3300);
}

void retractActuator() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(3300);
}

void stopActuator() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(3300);
}

int wheelMaxSpeed = 2000;

//movement integration
void work(int steps) {

  //extendActuator();
  stepperMove1(steps);
  //retractActuator();
  delay(500);
  //wheelMotor(wheelMaxSpeed);
  delay(500);
  stepperMove2(steps);
  //retractActuator();
  //wheelMotor(wheelMaxSpeed);
}

void wheelMotor(int Maxspeed) {
  for ( int i=0; i < Maxspeed; i++) {

    pwm.setPWM(1, 0, i);  //D1-A IN1 (high)    
    pwm.setPWM(4, 0, i);  //D1-B IN1 (high)
    pwm.setPWM(9, 0, i);  //D2-A IN1 (high)    
    pwm.setPWM(13, 0, i); //D2-B IN1 (high)
    
    pwm.setPWM(2,0,0);     //D1-A IN2 (supposed to be low)    
    pwm.setPWM(5,0,0);     //D1-B IN2 (supposed to be low)
    pwm.setPWM(10,0,0);    //D1-A IN2 (supposed to be low)    
    pwm.setPWM(14,0,0);    //D1-B IN2 (supposed to be low)
    
    pwm.setPWM(3,4096,0);  //D1-A ENA (high)
    pwm.setPWM(6,4096,0);  //D1-B ENB (high)
    pwm.setPWM(11,4096,0); //D1-A ENA (high)
    pwm.setPWM(15,4096,0); //D1-B ENB (high)
  }

  delay(1000);
  
   for ( int i=Maxspeed; i>0 ; i--) {

    pwm.setPWM(1, 0, i); //D1-A IN1 (high)    
    pwm.setPWM(4, 0, i); //D1-B IN1 (high)
    pwm.setPWM(9, 0, i); //D2-A IN1 (high)    
    pwm.setPWM(13, 0, i); //D2-B IN1 (high)
    
    pwm.setPWM(2,0,0);    //D1-A IN2 (supposed to be low)    
    pwm.setPWM(5,0,0);    //D1-B IN2 (supposed to be low)
    pwm.setPWM(10,0,0);   //D1-A IN2 (supposed to be low)    
    pwm.setPWM(14,0,0);   //D1-B IN2 (supposed to be low)
    
    pwm.setPWM(3,4096,0);  //D1-A ENA (high)
    pwm.setPWM(6,4096,0);  //D1-B ENB (high)
    pwm.setPWM(11,4096,0); //D1-A ENA (high)
    pwm.setPWM(15,4096,0); //D1-B ENB (high)
  }
}


void setup() {
  stepperA.begin(RPM, MICROSTEPS);
  stepperA.setEnableActiveState(LOW);

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);

  //pwm.begin();
  //pwm.setOscillatorFrequency(27000000);
  //pwm.setPWMFreq(1000);  
}

void loop(){
  //
 // u8g.firstPage();
 //do {
    //drawMenu();
  //} while (u8g.nextPage());

  work(600); //1.5round for now
  delay(1000);
  
  }

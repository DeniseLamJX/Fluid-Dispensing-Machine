#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
int Maxspeed = 750;

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1000);  
}

void loop() {
  for ( int i=0; i < Maxspeed; i+=3) {


    pwm.setPWM(1, 0, 0);  //D1-A IN1 (high)    
    pwm.setPWM(4, 0, 0);  //D1-B IN1 (high)
    pwm.setPWM(9, 0, 0);  //D2-A IN1 (high)    
    pwm.setPWM(13, 0, 0); //D2-B IN1 (high)
    
    pwm.setPWM(2,0,i);     //D1-A IN2 (supposed to be low)    
    pwm.setPWM(5,0,i);     //D1-B IN2 (supposed to be low)
    pwm.setPWM(10,0,i);    //D1-A IN2 (supposed to be low)    
    pwm.setPWM(14,0,i);    //D1-B IN2 (supposed to be low)
    
    pwm.setPWM(3,4096,0);  //D1-A ENA (high)
    pwm.setPWM(6,4096,0);  //D1-B ENB (high)
    pwm.setPWM(11,4096,0); //D1-A ENA (high)
    pwm.setPWM(15,4096,0); //D1-B ENB (high)

    
  }

  //delay(5000);
  
   for ( int i=Maxspeed; i>0 ; i-=3) {

    pwm.setPWM(1, 0, 0); //D1-A IN1 (high)    
    pwm.setPWM(4, 0, 0); //D1-B IN1 (high)
    pwm.setPWM(9, 0, 0); //D2-A IN1 (high)    
    pwm.setPWM(13, 0, 0); //D2-B IN1 (high)
    
    pwm.setPWM(2,0,i);    //D1-A IN2 (supposed to be low)    
    pwm.setPWM(5,0,i);    //D1-B IN2 (supposed to be low)
    pwm.setPWM(10,0,i);   //D1-A IN2 (supposed to be low)    
    pwm.setPWM(14,0,i);   //D1-B IN2 (supposed to be low)
    
    pwm.setPWM(3,4096,0);  //D1-A ENA (high)
    pwm.setPWM(6,4096,0);  //D1-B ENB (high)
    pwm.setPWM(11,4096,0); //D1-A ENA (high)
    pwm.setPWM(15,4096,0); //D1-B ENB (high)
  }
  
}

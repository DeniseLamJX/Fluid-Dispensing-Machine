// define Arduino Mega pin numbers
// ENABLE pins
#define A1_EN 42 // 52 on Arduino Mega only, 42 (AUX-2) on RAMPS
#define B1_EN 44 // 53 on Arduino Mega only, 44 (AUX-2) on RAMPS

// SIGNAL pins (PWM)
#define A1_IN1 4 // 5 on Arduino Mega only, 4 (SERVO) on RAMPS
#define A1_IN2 5 // 6 on Arduino Mega only, 5 (SERVO) on RAMPS

#define B1_IN1 6 // 8 on Arduino Mega only, 6 (SERVO) on RAMPS
#define B1_IN2 11 // 9 on Arduino Mega only, 11 (SERVO) on RAMPS

int PWM_MAX_RANGE = 100;

void PWM_write(int IN1_PWM, int IN2_PWM){
  // digitalWrite(A1_EN, LOW);
  // digitalWrite(B1_EN, LOW);
  
  if( IN1_PWM == 0 || IN2_PWM == 0 ) { //indicates supposed to run drivers A and B on the same driver
    analogWrite(A1_IN1, IN1_PWM);
    analogWrite(B1_IN1, IN2_PWM);
    analogWrite(A1_IN2, IN2_PWM);
    analogWrite(B1_IN2, IN1_PWM);
    
    Serial.print("(IN_1, IN_2) = (");
    Serial.print(IN1_PWM);
    Serial.print(", ");
    Serial.print(IN2_PWM);
    Serial.println(") ");

    delay(200);

    digitalWrite(A1_EN, HIGH);
    digitalWrite(B1_EN, HIGH);
  }
  else {
    Serial.println("WARNING! PWM ON BOTH PINS WILL DAMAGE DRIVER! ABORTING!");
    digitalWrite(A1_EN, LOW);
    digitalWrite(B1_EN, LOW);
  }
}

void setup() {
  // setup pins and pull all to LOW
  pinMode(A1_EN, OUTPUT);
  pinMode(B1_EN, OUTPUT);
  digitalWrite(A1_EN, LOW);
  digitalWrite(B1_EN, LOW);
  
  pinMode(A1_IN1, OUTPUT);
  pinMode(A1_IN2, OUTPUT);
  digitalWrite(A1_IN1, LOW);
  digitalWrite(A1_IN2, LOW);
  
  pinMode(B1_IN1, OUTPUT);
  pinMode(B1_IN2, OUTPUT);
  digitalWrite(B1_IN1, LOW);
  digitalWrite(B1_IN2, LOW);

  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < PWM_MAX_RANGE; i++){ //forwards
    PWM_write(i, 0);
    delay(10);
  }
  for(int i = PWM_MAX_RANGE; i > 0; i--){
    PWM_write(i, 0);
    delay(10);
  }
  PWM_write(0, 0);
  for(int i = 0; i < PWM_MAX_RANGE; i++){ //reverse
    PWM_write(0, i);
    delay(10);
  }
  for(int i = PWM_MAX_RANGE; i > 0; i--){
    PWM_write(0, i);
    delay(10);
  }
}

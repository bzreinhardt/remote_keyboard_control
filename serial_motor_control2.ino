//HERE BE #INCLUDES
#include <AccelStepper.h>

// Motors 1 and 2 face 'forward' , 3 and 4 face 'to the side'

//HERE BE CONSTANTS

//set the direction and enable pins for the motor controller
const int motor1L = 5;    // Motor 1 leg 1 (pin 2, 1A)
const int motor1R = 3;
const int mot1Ren = 2;
const int mot1Len = 4;  
const int V0pin = 0;
const int V1pin = 1;
int motor_speed = 255;   // Max value of PWM
 int button = 0;
 int lock = 0; // if lock is low, motors are independent
 int potMax = 1023;
 int pot1In = 0;
 int pot2In = 0;
 int mot1L = 0;
 int mot1R = 0;
 int mot2L = 0;
 int mot2R = 0;
 int ledPin = 13;
 int current = 0;
 long time = 0;

//set up speeds
float maxSpeed = 7000;


//HERE BE GLOBAL VARIABLES AND OBJECTS
// variables keeping track of the controller commands

int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
volatile boolean newCommand = false; // whether a valid command has been received
char command; // character recieved to be acted on
// set up motors

// 

void setup(){
	//initialize serial communication
	Serial.begin(9600);
	//set acceleration and initial speed for motors
  //analogReference(INTERNAL);
	float acceleration = 1000;
	float initSpeed = 0;
	int pulseWidth = 35; // this is the minimum pulse width recommended by the library

//start all the motors with zero speed
// set all the other pins you're using as outputs:
    pinMode(motor1L, OUTPUT); 
    pinMode(motor1R, OUTPUT);
    pinMode(mot1Ren, OUTPUT);
    pinMode(mot1Len, OUTPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(mot1Ren, HIGH);
    digitalWrite(mot1Len, HIGH);
}

void loop(){
	if (newCommand == true){
    Serial.print("command received: ");
    Serial.println(command);
    newCommand = false;
    switch(command){
      case 'w':{
        increment(mot1L, mot1R, 100);
        analogWrite(motor1L,mot1L);
        analogWrite(motor1R,mot1R);
        break;
      }
      case 's':{
        increment(mot1L, mot1R, -100);
        analogWrite(motor1L,mot1L);
        analogWrite(motor1R,mot1R);
        break;
      }
      
    }
    Serial.print(" mot1L = ");
      Serial.print(mot1L);
      Serial.print(" mot1R = ");
      Serial.println(mot1R);
	}
  if (millis() - time > 200){
    // Print data every 100 ms
    time = millis();
    int V0 = analogRead(V0pin);
    Serial.print(millis());Serial.print('\t');
    Serial.print("V0"); Serial.print('\t'); Serial.print(V0); 
    Serial.print('\n');
  }


}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
   while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    
    newCommand = true;
    command = inChar;
  }
}

void cmdMotor(int pinL, int pinR, int cmdL, int cmdR)
{
   if (cmdL != 0){
  analogWrite(pinL, cmdL);
  digitalWrite(pinR,LOW);
 }
 else{
  analogWrite(pinR, cmdR);
  digitalWrite(pinL, LOW);
 } 
}

void increment(int &motorL, int &motorR, int amt){
  // motorL and motorR are the current commands to the left and right directions of the motor
  int motorSpeed = motorR - motorL; //Right is positive and left is negative
  motorSpeed += amt;
  Serial.println(motorSpeed);
  if (motorSpeed >= 0){

    motorR = motorSpeed;
    motorL = 0;
    if (motorR > 255){
      motorR = 255;
    }
  } 
  else{
    motorR = 0;
    motorL = -motorSpeed;
    if (motorL > 255){
      motorL = 255;
    }
  }
}



#include <Arduino_FreeRTOS.h>
#include "semphr.h"

// motor one
int motor_left_pwm = 10;
int motor_left_in1 = 9;
int motor_left_in2 = 8;

// motor two
int motor_right_pwm = 5;
int motor_right_in1 = 7;
int motor_right_in2 = 6;

// led's
int red = 12;
int green = 13;

// button
int button = 2;
int toggle_on = false;

// initialize photoresistor variables
int light_threshold_pot_value = 50;
int light_threshold = 50;
int light_val = 100;

// initialize motor variables
int left_pot_value = 50;
int left_pwm_output = 50;
int right_pot_value = 50;
int right_pwm_output =50;

typedef int TaskProfiler;
TaskProfiler RedTaskProfiler;
TaskProfiler BlueTaskProfiler;
TaskProfiler  YellowTaskProfiler;

void setup()
{
    Serial.begin(9600);
  // set all the motor control pins to outputs
  pinMode(motor_left_pwm, OUTPUT);
  pinMode(motor_right_pwm, OUTPUT);
  pinMode(motor_left_in1, OUTPUT);
  pinMode(motor_left_in2, OUTPUT);
  pinMode(motor_right_in1, OUTPUT);
  pinMode(motor_right_in2, OUTPUT);
  pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);

}

void loop()
{
   light_threshold_pot_value = analogRead(A2); // Read potentiometer value
   light_threshold = map(light_threshold_pot_value, 0, 1023, 10 , 60);
   light_val = analogRead(A5); // Read light sensor value

   if (digitalRead(button) == true) {
    toggle_on = !toggle_on;
    delay(200);
  }
  
  while (toggle_on == false) {
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      delay(200);
      digitalWrite(green, HIGH);
      delay(200);
      digitalWrite(motor_left_in1, LOW);
      digitalWrite(motor_left_in2, LOW); 
      // right wheel move backward
      digitalWrite(motor_right_in1, LOW);
      digitalWrite(motor_right_in2, LOW);

     if (digitalRead(button) == true) {
        toggle_on = !toggle_on;
        delay(200);
      }
  }
  
  if (toggle_on == true and light_val > light_threshold) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
      // left wheel move forward
      digitalWrite(motor_left_in1, LOW);
      digitalWrite(motor_left_in2, HIGH); 
      left_pot_value = analogRead(A0); // Read potentiometer value
      left_pwm_output = map(left_pot_value, 0, 1023, 0 , 255); // Map the potentiometer value from 0 to 255
      analogWrite(motor_left_pwm, left_pwm_output); // Send PWM signal to L298N Enable pin
      
      // right wheel move forward
      digitalWrite(motor_right_in1, LOW);
      digitalWrite(motor_right_in2, HIGH); 
      right_pot_value = analogRead(A1); // Read potentiometer value
      right_pwm_output = map(right_pot_value, 0, 1023, 0 , 255); // Map the potentiometer value from 0 to 255
      analogWrite(motor_right_pwm, right_pwm_output); // Send PWM signal to L298N Enable pin
  } else {
    
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      
      
      // left wheel move backward
      digitalWrite(motor_left_in1, HIGH);
      digitalWrite(motor_left_in2, LOW); 
      // right wheel move backward
      digitalWrite(motor_right_in1, HIGH);
      digitalWrite(motor_right_in2, LOW); 
      analogWrite(motor_right_pwm, 120); // Send PWM signal to L298N Enable pin
      analogWrite(motor_left_pwm, 60); // Send PWM signal to L298N Enable pin

      delay(2000);
      
//      // left wheel stop
//      digitalWrite(in1, LOW);
//      digitalWrite(in2, LOW); 
//      // right wheel move backward
//      digitalWrite(in3, HIGH);
//      digitalWrite(in4, LOW); 
//      analogWrite(enB, 255); // Send PWM signal to L298N Enable pin
//      analogWrite(enA, 255); // Send PWM signal to L298N Enable pin
//      
//      delay(2000);

      
//      toggle_on = !toggle_on;
//      delay(200);
  }

}

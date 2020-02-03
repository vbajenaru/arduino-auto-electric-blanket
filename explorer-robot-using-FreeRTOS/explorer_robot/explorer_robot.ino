#include <Arduino_FreeRTOS.h>
#include "semphr.h"

// define arduino inputs/outputs
# define MOTOR_LEFT_PWM 10
# define MOTOR_LEFT_IN_1 9
# define MOTOR_LEFT_IN_2 8
# define MOTOR_RIGHT_PWM 5
# define MOTOR_RIGHT_IN_1 7
# define MOTOR_RIGHT_IN_2 6
# define LED_RED 12
# define LED_BLUE 13
# define BUTTON 2

// initialize photoresistor variables
int light_threshold_pot_value = 50;
int light_threshold = 50;
int light_val = 100;

// initialize motor variables
int left_pot_value = 50;
int left_pwm_output = 50;
int right_pot_value = 50;
int right_pwm_output = 50;

SemaphoreHandle_t xBinarySemaphore_motors_idle;
SemaphoreHandle_t xBinarySemaphore_motors_forward;
SemaphoreHandle_t xBinarySemaphore_motors_reverse;

void setup() {
  Serial.begin(9600);

  xBinarySemaphore_motors_idle = xSemaphoreCreateBinary();
  xBinarySemaphore_motors_forward = xSemaphoreCreateBinary();
  xBinarySemaphore_motors_reverse = xSemaphoreCreateBinary();

  xTaskCreate(polling_for_sensors_task,"polling_for_sensors_task", 100,NULL,1,NULL);
  xTaskCreate(motors_idle_task,"motors_idle_task", 100,NULL,1,NULL);
  xTaskCreate(motors_forward_task,"motors_forward_task", 100,NULL,1,NULL);
  xTaskCreate(motors_reverse_task,"motors_reverse_task", 100,NULL,1,NULL);
  
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);
  pinMode(MOTOR_LEFT_IN_1, OUTPUT);
  pinMode(MOTOR_LEFT_IN_2, OUTPUT);
  pinMode(MOTOR_RIGHT_IN_1, OUTPUT);
  pinMode(MOTOR_RIGHT_IN_2, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, HIGH);
}

void motors_idle_task(void *pvParameters) {
  while(1) {
    xSemaphoreTake(xBinarySemaphore_motors_idle, portMAX_DELAY);
    Serial.println("TASK: motors_idle_task");
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(MOTOR_LEFT_IN_1, LOW);
    digitalWrite(MOTOR_LEFT_IN_2, LOW); 
    digitalWrite(MOTOR_RIGHT_IN_1, LOW);
    digitalWrite(MOTOR_RIGHT_IN_2, LOW);
  }
}

void motors_forward_task(void *pvParameters) {
  while(1) {
    xSemaphoreTake(xBinarySemaphore_motors_forward, portMAX_DELAY);
    Serial.println("TASK: motors_forward_task");
    
    left_pot_value = analogRead(A0); // Read potentiometer value
    left_pwm_output = map(left_pot_value, 0, 1023, 0 , 255); // Map the potentiometer value from 0 to 255
    right_pot_value = analogRead(A1); // Read potentiometer value
    right_pwm_output = map(right_pot_value, 0, 1023, 0 , 255); // Map the potentiometer value from 0 to 255
//    Serial.print("left_pwm_output=");
//    Serial.println(left_pwm_output);
//    Serial.print("right_pwm_output=");
//    Serial.println(right_pwm_output);
    
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);
    // left wheel move forward
    digitalWrite(MOTOR_LEFT_IN_1, LOW);
    digitalWrite(MOTOR_LEFT_IN_2, HIGH); 
    analogWrite(MOTOR_LEFT_PWM, left_pwm_output); // Send PWM signal to L298N Enable pin
    // right wheel move forward
    digitalWrite(MOTOR_RIGHT_IN_1, LOW);
    digitalWrite(MOTOR_RIGHT_IN_2, HIGH); 
    analogWrite(MOTOR_RIGHT_PWM, right_pwm_output); // Send PWM signal to L298N Enable pin
  }
}

void motors_reverse_task(void *pvParameters) {
  while(1) {
    xSemaphoreTake(xBinarySemaphore_motors_reverse, portMAX_DELAY);
    Serial.println("TASK: motors_reverse_task");
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
    // left wheel move backward
    digitalWrite(MOTOR_LEFT_IN_1, HIGH);
    digitalWrite(MOTOR_LEFT_IN_2, LOW); 
    // right wheel move backward
    digitalWrite(MOTOR_RIGHT_IN_1, HIGH);
    digitalWrite(MOTOR_RIGHT_IN_2, LOW); 
    analogWrite(MOTOR_RIGHT_PWM, 120); // Send PWM signal to L298N Enable pin
    analogWrite(MOTOR_LEFT_PWM, 60); // Send PWM signal to L298N Enable pin
  }
}

# define STATE_LIGHT_OFF_TOGGLE_ON 0
# define STATE_LIGHT_ON_TOGGLE_ON 1
# define STATE_LIGHT_ON_TOGGLE_OFF 2
# define STATE_LIGHT_OFF_TOGGLE_OFF 3

void polling_for_sensors_task(void *pvParameters)
{
  int button_state = false;
  int toggle_on_state = false;
//  int photo_sensor_dark = false;
  int button_plus_light_state = STATE_LIGHT_ON_TOGGLE_OFF;

  while(1) {
     light_threshold_pot_value = analogRead(A2); // Read photoresistor value
     light_threshold = map(light_threshold_pot_value, 0, 1023, 10 , 60);
     light_val = analogRead(A5); // Read light sensor value

      if (button_state == false) {
        if (digitalRead(BUTTON) == true) {
            toggle_on_state = !toggle_on_state;
            button_state = true;
        } 
      } else {
        if (digitalRead(BUTTON) == false) { // button released
            button_state = false;
        }
      }    
    
//    Serial.print("light_val=");
//    Serial.println(light_val);
//    Serial.print("light_threshold=");
//    Serial.println(light_threshold);
//    delay(3000);

    switch (button_plus_light_state)
    {
      case STATE_LIGHT_OFF_TOGGLE_ON: 
        if (light_val > light_threshold) {  // check if light
          Serial.println("STATE_LIGHT_ON_TOGGLE_ON");
          xSemaphoreGive(xBinarySemaphore_motors_forward);
          button_plus_light_state = STATE_LIGHT_ON_TOGGLE_ON;
          break;
        }
        if (toggle_on_state == false) {
          Serial.println("STATE_LIGHT_OFF_TOGGLE_OFF");
          xSemaphoreGive(xBinarySemaphore_motors_idle);
          button_plus_light_state = STATE_LIGHT_OFF_TOGGLE_OFF;
          break;
        } 
        break;
      case STATE_LIGHT_ON_TOGGLE_ON: 
        if (light_val <= light_threshold) {  // check if dark
            Serial.println("STATE_LIGHT_OFF_TOGGLE_ON");
            xSemaphoreGive(xBinarySemaphore_motors_reverse);
            button_plus_light_state = STATE_LIGHT_OFF_TOGGLE_ON;
            break;
        }
        if (toggle_on_state == false) {
          Serial.println("STATE_LIGHT_ON_TOGGLE_OFF");
          xSemaphoreGive(xBinarySemaphore_motors_idle);
          button_plus_light_state = STATE_LIGHT_ON_TOGGLE_OFF;
          break;
        }
        break;
      case STATE_LIGHT_ON_TOGGLE_OFF: 
        if (light_val <= light_threshold) {  // check if dark
            Serial.println("STATE_LIGHT_OFF_TOGGLE_OFF");
            xSemaphoreGive(xBinarySemaphore_motors_idle);
            button_plus_light_state = STATE_LIGHT_OFF_TOGGLE_OFF;
            break;
        }
        if (toggle_on_state == true) {
          Serial.println("STATE_LIGHT_ON_TOGGLE_ON");
          xSemaphoreGive(xBinarySemaphore_motors_forward); 
          button_plus_light_state = STATE_LIGHT_ON_TOGGLE_ON;
          break;
        }
        break;
      case STATE_LIGHT_OFF_TOGGLE_OFF:
        if (light_val > light_threshold) {  // check if light
            Serial.println("STATE_LIGHT_ON_TOGGLE_OFF");
          xSemaphoreGive(xBinarySemaphore_motors_idle);
          button_plus_light_state = STATE_LIGHT_ON_TOGGLE_OFF;
            break;
        }
        if (toggle_on_state == true) {
          Serial.println("STATE_LIGHT_OFF_TOGGLE_ON");
          xSemaphoreGive(xBinarySemaphore_motors_reverse);
          button_plus_light_state = STATE_LIGHT_OFF_TOGGLE_ON;
          break;
        }
        break;
      default: 
        break;
    }
    vTaskDelay(1); // delay for 1 tick
  }
}

void loop() { }

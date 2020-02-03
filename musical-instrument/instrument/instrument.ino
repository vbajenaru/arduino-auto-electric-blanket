//#include <math.h>

const int button1Pin = 2;
const int button2Pin = 3; 
const int button3Pin = 4;
int sensor1Pin = 0;
int sensor2Pin = 1;
int led1Pin = 13;
int led2Pin = 6;   
const int buzzerPin = 8;

const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
int DISPLAY_TIME = 100;

int button3State;
int arpeggiator = 1;
int previous = LOW;
long time = 0;
long debounce= 200;
int color=0;

void setup() 
{
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void sound(int b, int sV, int sT, int iS);
void showSpectrum(int t);

void loop(){
 int button1State, button2State;
 int sensor1Value;
 int sensor2Value;
 
  //instrument
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);

  sensor1Value = analogRead(sensor1Pin);
  sensor2Value = analogRead(sensor2Pin);

  analogWrite(led2Pin, sensor1Value/4);
  
  
  //, (float)sensor1Value*767/1024
  if(button3State == HIGH && previous==LOW && millis()-time>debounce){
    if(arpeggiator==1)
      arpeggiator=2;
    else if(arpeggiator==2)
      arpeggiator=3;
    else
      arpeggiator=1;
      
    time = millis();
  }
  previous = button3State;  

if(arpeggiator==2){
  if(button1State==LOW&&button2State==LOW){
   
    sound(button2State, sensor1Value, (float)sensor2Value*3/4, 523);
    digitalWrite(led1Pin, HIGH);    
    delay(sensor2Value*3/4);             
    digitalWrite(led1Pin, LOW);      
    delay(sensor2Value*1/4);
    
    sound(button2State, sensor1Value, (float)sensor2Value*3/4, 262);
    digitalWrite(led1Pin, HIGH);    
    delay(sensor2Value*3/4);             
    digitalWrite(led1Pin, LOW);      
    delay(sensor2Value*1/4);
  }
    else{
      sound(button1State, sensor1Value, (float)sensor2Value*3/4, 523);
      sound(button2State, sensor1Value, (float)sensor2Value*3/4, 262);
      digitalWrite(led1Pin, HIGH);    
      delay(sensor2Value*3/4);             
      digitalWrite(led1Pin, LOW);      
      delay(sensor2Value*1/4);
    }
  }  
  
  if(arpeggiator==1){
    //add for looP:
       //showRGB(color);
       //color+=(float)sensor2Value/1024;
      //if(color>767)
      //color=0;
    float scale=3.0*256/sensor1Value;
    
    if(button1State==LOW){
    digitalWrite(led1Pin, HIGH);
    
      for(int x=0; x<sensor1Value; x++){
            tone(buzzerPin, sensor2Value+5*x, 40);
            showRGB((int)(x*scale));
      }
      for(int x=0; x<sensor1Value; x++){
        tone(buzzerPin, (sensor2Value+5*sensor1Value)-5*x, 40);
        showRGB((int)(x*scale));
    }
      digitalWrite(led1Pin, LOW);     
    }

    if(button2State==LOW){
    digitalWrite(led1Pin, HIGH);
    
    for(int x=0; x<sensor1Value; x++){
        tone(buzzerPin, sensor2Value+5*x, 200);
        //for(int color=0; color<767; color+=(float)5*sensor1Value/1024){
          showRGB((int)(x*scale));
        //delay(10);
        //tone(buzzerPin, (sensor2Value+5*sensor1Value)-5*x, 200);
    }
    digitalWrite(led1Pin, LOW);      
    }
    
  }

  if(arpeggiator==3){
    sound(button1State, sensor1Value, 10, 523);
    sound(button2State, sensor1Value, 10, 262);
  }
  
}

void sound(int bState, int sValue, int soundTime, int initSound){
  int buttonPitch;

  buttonPitch=initSound*(float)sValue/128;
  if(buttonPitch<50){
    buttonPitch=50;
  }
  if (bState == LOW){
    tone(buzzerPin, buttonPitch, soundTime);
  }

}

void showRGB(int color)
{
  int redIntensity;
  int greenIntensity;
  int blueIntensity;

  // Here we'll use an "if / else" statement to determine which
  // of the three (R,G,B) zones x falls into. Each of these zones
  // spans 255 because analogWrite() wants a number from 0 to 255.

  // In each of these zones, we'll calculate the brightness
  // for each of the red, green, and blue LEDs within the RGB LED.

  if (color <= 255)          // zone 1
  {
    redIntensity = 255 - color;    // red goes from on to off
    greenIntensity = color;        // green goes from off to on
    blueIntensity = 0;             // blue is always off
  }
  else if (color <= 511)     // zone 2
  {
    redIntensity = 0;                     // red is always off
    greenIntensity = 255 - (color - 256); // green on to off
    blueIntensity = (color - 256);        // blue off to on
  }
  else // color >= 512       // zone 3
  {
    redIntensity = (color - 512);         // red off to on
    greenIntensity = 0;                   // green is always off
    blueIntensity = 255 - (color - 512);  // blue on to off
  }

  // Now that the brightness values have been set, command the LED
  // to those values

  analogWrite(RED_PIN, redIntensity);
  analogWrite(BLUE_PIN, blueIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
}

void showSpectrum(int tm)
{
  //int x;  // define an integer variable called "x"
  
  // Now we'll use a for() loop to make x count from 0 to 767
  // (Note that there's no semicolon after this line!
  // That's because the for() loop will repeat the next
  // "statement", which in this case is everything within
  // the following brackets {} )
    
    showRGB(tm);  // Call RGBspectrum() with our new x
    
}


const int relayPin = 2;	    // use this pin to drive the transistor
float timeBlanketOn = 1.5*60*60*1000;
float timeSwitchRelay = 500;
float timeBlanketOff = ((float)24*60*60*1000)-(float)(timeBlanketOn)-(2*(float)timeSwitchRelay);

void setup()
{
  pinMode(relayPin, OUTPUT);  // set pin as an output
}


void loop()                    
{
  digitalWrite(relayPin, HIGH);  // turn on blanket
  delay(timeSwitchRelay);              
  digitalWrite(relayPin, LOW);   // stay on this long

  //Serial.print(now())
  delay(timeBlanketOn);              

  digitalWrite(relayPin, HIGH);  // turn off blanket
  delay(timeSwitchRelay);              
  digitalWrite(relayPin, LOW);   // stay off this long
  delay(timeBlanketOff);    
} 


#include <Arduino_FreeRTOS.h>

#define RED   6
#define BLUE  8
#define YELLOW 7

typedef int TaskProfiler;

TaskProfiler    RedLEDProfiler;
TaskProfiler    YellowLEDProfiler;
TaskProfiler    BlueLEDProfiler;

TaskHandle_t blue_Handle,red_Handle,yellow_Handle;

int yellowTaskPrio;
int blueTaskPrio;

void setup()
{
 Serial.begin(9600);
 xTaskCreate(redControllerTask, "RED LED Task",100,NULL,1,&red_Handle);
 xTaskCreate(blueControllerTask, "BLUE LED Task", 100,NULL,1,&blue_Handle); 
 xTaskCreate(yellowControllerTask, "YELLOW LED Task", 100,NULL,3,&yellow_Handle); 

}

void redControllerTask(void *pvParameters)
{
  while(1)
  {
//    RedLEDProfiler++;
//    Serial.print("RED Run Time : ");
//    Serial.println(RedLEDProfiler);

   // delay(300);
  }
}

void blueControllerTask(void *pvParameters)
{
  while(1)
  {
//    BlueLEDProfiler++;
//    Serial.print("BLUE Run Time : ");
//    Serial.println(BlueLEDProfiler);
  //   delay(300);

  }
}
void yellowControllerTask(void *pvParameters)
{
  while(1)
  {
   // YellowLEDProfiler++;
    yellowTaskPrio  = uxTaskPriorityGet(NULL);
    blueTaskPrio    = uxTaskPriorityGet(blue_Handle);
  
    Serial.print("BlueTaskPriority : ");
    Serial.println(blueTaskPrio);
    Serial.print("YellowTaskPriority : ");
    Serial.println(yellowTaskPrio);
    delay(300);

  }
}
void loop(){}

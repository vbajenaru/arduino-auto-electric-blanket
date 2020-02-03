#include <Arduino_FreeRTOS.h>
#include "event_groups.h"

#define       RED     6
#define       YELLOW  7
#define       BLUE    8

#define  TASKA_BIT  (1UL<<0UL)
#define  TASKB_BIT  (1UL<<1UL)
#define  TASKC_BIT  (1UL<<2UL)

EventGroupHandle_t  xEventGroup;
EventBits_t allSyncBits  =(TASKA_BIT|TASKB_BIT|TASKC_BIT );
void setup()
{
  pinMode(RED,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(BLUE,OUTPUT);

  xEventGroup  =  xEventGroupCreate();

  xTaskCreate(TaskA, "Task A", 100, NULL, 1,NULL);
  xTaskCreate(TaskB, " Task B", 100,NULL, 1,NULL);
  xTaskCreate(TaskC, "Task C", 100,NULL, 1, NULL);
  
}
void  TaskA(void *pvParameters)
{
  EventBits_t uxReturn;
  while(1)
  {
   uxReturn =  xEventGroupSync(xEventGroup,
                              TASKA_BIT,
                              allSyncBits,
                             portMAX_DELAY);
    if((uxReturn & allSyncBits)== allSyncBits)
    {
      digitalWrite(RED,digitalRead(RED)^1);
      vTaskDelay(pdMS_TO_TICKS(50));
    }
  }
}
void TaskB(void *pvParameters)
{
  EventBits_t uxReturn;
  while(1)
  {
    uxReturn =  xEventGroupSync(xEventGroup,
                               TASKB_BIT,
                               allSyncBits,
                               portMAX_DELAY);
  if((uxReturn & allSyncBits)==allSyncBits)
  {
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    vTaskDelay(pdMS_TO_TICKS(50));
  }
  }
}

void TaskC(void *pvParameters)
{
  EventBits_t uxReturn;
  while(1)
  {
    uxReturn =  xEventGroupSync(xEventGroup,
                                TASKC_BIT,
                                allSyncBits,
                                portMAX_DELAY);
                                
   if((uxReturn & allSyncBits) ==allSyncBits)
   {
    digitalWrite(BLUE,digitalRead(BLUE)^1);
    vTaskDelay(pdMS_TO_TICKS(50));
   }
    
  }
}
void loop(){}

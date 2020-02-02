#include <Arduino_FreeRTOS.h>
#include "semphr.h"


SemaphoreHandle_t  xMutex;

void setup()
{
  Serial.begin(9600);
  xMutex = xSemaphoreCreateMutex();

  xTaskCreate(OutputTask,"Printer Task 1", 100,"Task 1 #####################Task1 \r\n",1,NULL);
  xTaskCreate(OutputTask,"Printer Task 2", 100,"Task 2 ---------------------Task2 \r\n",2,NULL);
  
  
}

void OutputTask(void *pvParameters)
{
  char *pcStringToPrint;
  pcStringToPrint = (char *)pvParameters;
  while(1)
  {
    printer(pcStringToPrint);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void printer(const char* pcString)
{
  xSemaphoreTake(xMutex, portMAX_DELAY);
  Serial.println(pcString);
  xSemaphoreGive(xMutex);
}
void loop(){}


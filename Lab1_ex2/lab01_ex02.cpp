#include "tpl_os.h"
#include "Arduino.h"

void setup()
{
	// initialize digital pin 13 as an output.
	pinMode(13, OUTPUT);
}

//* The SystemCounter is the same as the systick used in Arduino, a tick each 1024us on a 16MHz arduino.
//* This task is periodic, with a period of 1024ms.
TASK(TaskA)
{
  static int counter_A = 0;
  digitalWrite(13, HIGH);
  counter_A+=500;
  printf("Counter A value: %d\r\n",counter_A);
  
  TerminateTask();
}

TASK(TaskB)
{
  static int counter_B = 1500;
  digitalWrite(13, LOW);
  counter_B+=750;
  printf("Counter B value: %d\r\n",counter_B);
   
  TerminateTask();
}

TASK(stop)
{
  CancelAlarm(a500msec);
  CancelAlarm(a750msec);
  printf("Shutdown\r\n");
  ShutdownOS(E_OK);
  TerminateTask();
}

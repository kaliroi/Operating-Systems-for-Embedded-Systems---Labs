#include "tpl_os.h"
#include "Arduino.h"

void setup()
{
	Serial.begin(115200); //115200 bps, 8N1
}

void do_things(int ms) {
	unsigned long mul=ms*504UL;
	unsigned long i;
	
	for (i=0;i<mul;i++) millis();
	Serial.println(millis());
}

TASK(TaskA)
{
	static int countA=-1;
	countA++;
	
	Serial.print("Task A execution # ");
	Serial.println(countA);
	
//	Serial.print("Task A response time: ");
//	Serial.println(millis());
	
	do_things(200);

//	Serial.print("Task A finish time: ");
//	Serial.println(millis());
	TerminateTask();
}

TASK(TaskB)
{	
	static int countB=-1;
	countB++;
	
	Serial.print("Task B execution # ");
	Serial.println(countB);
	
//	Serial.print("Task B activation time: ");
//	Serial.println(millis());
	
	do_things(600);

//	Serial.print("Task B finish time: ");
//	Serial.println(millis());	
	TerminateTask();
}

TASK(TaskC)
{
	static int countC=-1;
	countC++;
	
	Serial.print("Task C execution # ");
	Serial.println(countC);
	
//	Serial.print("Task C activation time: ");
//	Serial.println(millis());
	
	do_things(300);
	
//	Serial.print("Task C finish time: ");
//	Serial.println(millis());
	TerminateTask();
}

TASK(stop)
{
	CancelAlarm(A1200ms);
	CancelAlarm(B2000ms);
	CancelAlarm(C3000ms);

	printf("Shutdown\r\n");
	ShutdownOS(E_OK);
	TerminateTask();
}



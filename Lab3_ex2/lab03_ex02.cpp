#include "tpl_os.h"
#include "Arduino.h"
#define SEM 1

DeclareResource(Sem);

void setup()
{
	Serial.begin(115200); //115200 bps, 8N1
}

void do_things(int ms) {
	unsigned long mul=ms*504UL;
	unsigned long i;
	
	for (i=0;i<mul;i++) millis();

}

TASK(TaskA)
{
	static int countA=-1;
	countA++;
	
	Serial.print("Task A execution # ");
	Serial.println(countA);
	
	Serial.print("Task A activation time: ");
	Serial.println(millis());
	
	GetResource( Sem );
	Serial.print("Task A gets the resource\n");
	do_things(300); // A execution time
	ReleaseResource( Sem );
	
	Serial.print("Task A terminated at time: ");
	Serial.println(millis());
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
	
//	Serial.print("Task B terminated at time: ");
//	Serial.println(millis());
	TerminateTask();
}

TASK(TaskC)
{
	static int countC=-1;
	countC++;
	
	Serial.print("Task C execution # ");
	Serial.println(countC);
	
	Serial.print("Task C activation time: ");
	Serial.println(millis());
	
	do_things(200);
	
	GetResource( Sem );
	Serial.print("Task C gets the resource\n");
	do_things(300); // remaining C execution time
	ReleaseResource( Sem ); //release the semaphore
	
	Serial.print("Task C terminated at time: ");
	Serial.println(millis());
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

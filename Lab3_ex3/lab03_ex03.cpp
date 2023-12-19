#include "tpl_os.h"
#include "Arduino.h"

void setup()
{
	Serial.begin(115200); 		//Serial comunication initialization
}



void  do_things(int ms)
{
	unsigned long mul = ms * 504UL;
	unsigned long i;

	for(i=0; i<mul; i++) millis();
}

TASK (Init)
{
	int Sem=0;
	Serial.print("Task Init activation.\n");
	SendMessage(msgSend, &Sem); //Sends Sem=0
}

TASK(TaskA)
{	
	int Sem;
//	int Sem=1;
	Serial.print("Task A starts executing at ");
	Serial.println(millis());
	
//	Serial.println(Sem);
	
	ReceiveMessage(msgRec, &Sem);
	
	while(Sem==1){
//	Serial.println(Sem);
	ReceiveMessage(msgRec, &Sem);
//	Serial.println(Sem);
	}
	
	Sem=1;
	SendMessage(msgSend, &Sem);
	Serial.println(Sem);
	
	Serial.print("Task A gets the resource at ");
	Serial.println(millis());
	
	do_things(300);
		
	Sem=0;
	SendMessage(msgSend, &Sem);
	
	Serial.print("Task A releases the resource and terminates at ");
	Serial.println(millis());
	
	TerminateTask();
}

TASK(TaskB)
{
	Serial.print("Task B starts executing at ");
	Serial.println(millis());
	
	do_things(600);
	
	Serial.print("Task B terminates at ");
	Serial.println(millis());
	
	TerminateTask();
}

TASK(TaskC)
{
	int Sem;
//	int Sem=1;
	Serial.print("Task C starts executing at ");
	Serial.println(millis());

 	do_things(200);
 	
// 	Serial.println(Sem);
	
	while(Sem==1){
	ReceiveMessage(msgRec, &Sem); //exit from while loop if Sem=0
	}
	
	Sem=1;
	SendMessage(msgSend, &Sem);
	Serial.println(Sem);
	
	Serial.print("Task C gets the resource at ");
	Serial.println(millis());
	
	do_things(300);
	
	Sem=0;
	SendMessage(msgSend, &Sem);
	
	Serial.print("Task C exits CS and terminates at time ");
	Serial.println(millis());	
	
	TerminateTask();
}

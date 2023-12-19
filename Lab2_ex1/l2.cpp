#include "tpl_os.h"
#include "Arduino.h"

void setup()
{
	Serial.begin(115200);
	// initialize digital pin 13 as an output and pin 12 and A0 as inputs.
	pinMode(13, OUTPUT);
	pinMode(12, INPUT_PULLUP);
	pinMode(A0, INPUT);
	
	Serial.print("Setup OK");
}

TASK(TaskV)
{	
	Serial.print("Task V execution\n");

	int M_msg;
	
	ReceiveMessage(TaskV_receive, &M_msg);

	if (M_msg==0) {
		digitalWrite(13, LOW);
		Serial.print("The LED is turned off\n");
	}
	if (M_msg==1) {
		//slow blink
		digitalWrite(13,HIGH);
		delay(500); //1 Hz
		digitalWrite(13,LOW);
		delay(500);
	}
	if (M_msg==2) {
		//fast blink
		digitalWrite(13,HIGH);
		delay(125); //4 Hz
		digitalWrite(13,LOW);
		delay(125);
		digitalWrite(13,HIGH);
		delay(125);
		digitalWrite(13,LOW);
		delay(125);
	}
	if (M_msg==3) {
		digitalWrite(13, HIGH);
		Serial.print("The LED is turned on\n");
	}
	
	TerminateTask();
}

TASK(TaskM)
{
	Serial.print("Task M execution\n");
	
	static int M_msg;
	int bit;
	int SensorValue = analogRead(A0);
	static int R=0;
	static int set=0;
	static int X;

	ReceiveMessage(TaskM_receive, &bit);
	
	if (R!=SensorValue){
		X=abs(SensorValue-R);
		Serial.print("X: ");
		Serial.println(X);
	}

	if (bit!=12){
		if (set==0){
			M_msg=3;
		} else if (set==1){
			R=SensorValue;
			if(X<100) {
				M_msg=0;
			}
			if (X>=100 && X<200){
				M_msg=1;
			}
			if (X>=200){
				M_msg=2;
			}
		}
	}
	if (bit==12){
		R=SensorValue;
		
		Serial.print("SensorValue is:");
		Serial.println(SensorValue);
		
		set=1;
		X = abs(SensorValue-R);
	}
	
	Serial.print("M message: ");
	Serial.println(M_msg);
	
	SendMessage(from_M, &M_msg);
			
	TerminateTask();
}

TASK(TaskC)
{
	Serial.print("Task C execution\n");

	int Switch = digitalRead(12);
	int SensorValue=analogRead(A0);
	static int count=0;
	static int bit;

	if (SensorValue>=0 && SensorValue<=102){
		bit=0;
	} else if (SensorValue>102 && SensorValue<=204){
		bit=1;
	} else if (SensorValue>204 && SensorValue<=306){
		bit=2;
	} else if (SensorValue>306 && SensorValue<=408){
		bit=3;
	} else if (SensorValue>408 && SensorValue<=510){
		bit=4;
	} else if (SensorValue>510 && SensorValue<=612){
		bit=5;
	} else if (SensorValue>612 && SensorValue<=714){
		bit=6;
	} else if (SensorValue>714 && SensorValue<=816){
		bit=7;
	} else if (SensorValue>816 && SensorValue<=918){
		bit=8;
	} else if (SensorValue>918 && SensorValue<=1024){
		bit=9;
	}
	
	//Switch
	if (Switch==LOW){
		Serial.print("Button pressed\n");
		count++;
	} else if (Switch==HIGH){
		Serial.print("Button released\n");
		count=0;
	}
	
	if (count>=10){
		bit=12; //bitWrite(SensorValue,12)=1;
			//bit=SensorValue;
	}
	
	Serial.print("count:");
	Serial.println(count);
	
	Serial.print("bit:");
	Serial.println(bit);
	
	SendMessage(from_C, &bit);
			
	TerminateTask();
}

TASK(stop)
{
  CancelAlarm(TaskC_activation);
  CancelAlarm(TaskM_activation);
  printf("Shutdown\r\n");
  ShutdownOS(E_OK);
  TerminateTask();
}

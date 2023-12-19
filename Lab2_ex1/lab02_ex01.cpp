#include "tpl_os.h"
#include "Arduino.h"

void setup()
{
	Serial.begin(115200); //115200 bps, 8N1
	//initialize digital pin 13 as an output
	pinMode(13, OUTPUT);
	//initialize digital pin 12 and A0 as a inputs
	pinMode(12,INPUT_PULLUP);
	pinMode(A0,INPUT);
}

TASK(TaskV)
{
	int M_message;
	static int fact=0;
	static int sact=0;

	ReceiveMessage(msgMrec, &M_message);

	if (M_message==0){
	Serial.print("Task V: led off\n");
	digitalWrite(13, LOW);
	}

	if (M_message==1){
	//blink with 1 Hz frequency
	Serial.print("Task V: slow blink\n");
	sact++;
		if (sact<5){
		digitalWrite(13, HIGH);
		} else if (sact>4 && sact<9){
		digitalWrite(13, LOW);
		}
		if (sact>7){
		sact=0;
		}
	}
	
	if (M_message==2){
	//blink with 4 Hz frequency (period of 250 ms)
	Serial.print("Task V: fast blink\n");
	fact++;
		if (fact%2==0){
		digitalWrite(13, HIGH);
		} else {
		digitalWrite(13, LOW);
		}
		if (fact>3){
		fact=0;
		}
	}
  
	if (M_message==3){
	Serial.print("Task V: led on\n");
	digitalWrite(13,HIGH);
	}

	TerminateTask();
}


TASK(TaskM)
{
	static int M_message;
	int bit;
	int SensorValue=analogRead(A0);
	static int R=0;
	static int X;
	static int Set=0;
	  
	ReceiveMessage(msgCrec, &bit);
   
	if (R!=SensorValue) {
	X = abs(SensorValue-R);
	Serial.print("X is: ");
	Serial.println(X);
	}
	
	if (bit!=1) {       
		if (Set==0){
		M_message=3;
		} else if (Set==1) {
			R=SensorValue;
			if (X<100) {
			M_message=0;
			}
			if (X>=100 && X<200){
			M_message=1;
			}
			if (X>=200) {
			M_message=2;
			}
		}
	}
 
	if (bit==1) {
	R=SensorValue;

	Serial.print("Sensor value is: ");
	Serial.println(SensorValue);

	Set=1;
	X = abs(SensorValue-R);
	}

	Serial.print("M_message: ");
	Serial.println(M_message);

	SendMessage(msgMsend, &M_message);

	TerminateTask();
}

TASK(TaskC)
{
	static int bit;
	int SensorValue=analogRead(A0);
	int Switch=digitalRead(12);
	static int count=0;
	
	bitWrite(SensorValue,12,0);
	bit=bitRead(SensorValue,12);
	
	if (Switch==LOW) {
		count++;
	} else if (Switch==HIGH) {
		count=0;
	}

	if (count>=10) {
	bitWrite(SensorValue,12,1);
	bit=bitRead(SensorValue,12);
	}

	SendMessage(msgCsend, &bit);

	TerminateTask();
}

TASK(stop)
{
	CancelAlarm(Cperiod100ms);
	CancelAlarm(Mperiod500ms);
	CancelAlarm(Vperiod125ms);

	printf("Shutdown\r\n");
	ShutdownOS(E_OK);
	TerminateTask();
}

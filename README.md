# Operating Systems for Embedded Systems - Labs

## Lab 1 - Tasks and Alarms
This first lab is intended to get to know the basics of the Trampoline implementation of OSEK/VDX Operating System. In particular,tasks and alarms concepts were exploited and the system deployed firstly on POSIX target and then on ArduinoUno(SimulIde).

## Lab 2 - Messages
Lab 2 exploits the interaction of three basic periodic tasks representing a basic MVC system, by using message-based communication. 
- `Task C` samples a switch S connected to GPIO pin 12 and analog input voltage A0 every 100 ms. It then sends an int message to `Task M`.
- `Task M` performs some actions upon reception of the right messages from `Task C` and then sends appropriate messages to `Task V`.
- `Task V` drives a LED connected to GPIO pin 13 of the Arduino Uno. It makes the LED blink in four different ways depending on the int message it receives from `Task M`.

## Lab 3 - Scheduling, Priority Ceiling, Deadlock
Lab 3 exploits the concepts of scheduling, priority ceiling and deadlock. 

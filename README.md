# Operating Systems for Embedded Systems - Labs

## Lab 1 - Tasks and Alarms
This first lab is intended to get to know the basics of the Trampoline RTOS implementation of OSEK/VDX Operating System. In particular,tasks and alarms concepts were exploited and the system deployed firstly on POSIX target and then on ArduinoUno(SimulIde).

## Lab 2 - Messages
Lab 2 exploits the interaction of three basic periodic tasks representing a basic MVC system, by using message-based communication. 
- `Task C` samples a switch S connected to GPIO pin 12 and analog input voltage A0 every 100 ms. It then sends an int message to `Task M`.
- `Task M` performs some actions upon reception of the right messages from `Task C` and then sends appropriate messages to `Task V`.
- `Task V` drives a LED connected to GPIO pin 13 of the Arduino Uno. It makes the LED blink in four different ways depending on the int message it receives from `Task M`.

## Lab 3 - Scheduling, Priority Ceiling, Deadlock
Lab 3 exploits the concepts of scheduling, priority ceiling and deadlock by implementing .

## Lab 4 - Resources and task organization

# Setup and .c .cpp .oil files usage
Once Trampoline has been set up, the virtual peripheral simulator (`viper`) needs to be compiled by using the make command in the viper subfolder under the trampoline one. Viper is mandatory to run Trampoline applications using POSIX.

The next step is compiling the tool (`goil`) needed to configure the Trampoline OS based on the application needs. This is contained in a trampoline subfolder.

Each time a Trampoline application is to be run, the VIPER_PATH variable needs to be defined by using the command `export VIPER_PATH=/users/<user name>/trampoline/viper`.

Once the .c/.cpp files and the .oil file containing the OS setup have been written, some commands need to be run.

In order to configure the Trampoline OS to accomodate the needs of the application as defined in the .oil configuration file, the following command needs to be run. 
- POSIX target
`../../../goil/makefile-unix/goil --target=posix/linux --templates=../../../goil/templates/ <filename>.oil` 
Then, build the application. For posix, running the application will be enough.

- Arduino target
`../../../../goil/makefile-unix/goil --target=avr/arduino/uno --templates=../../../../goil/templates/ <filename>.oil` 
Then, make the application. If for posix running the application is enough, for an Arduino (SimulIde) target a .hex file is generated upon the completion of the make command execution. This file can be loaded as firmware in SimulIde.

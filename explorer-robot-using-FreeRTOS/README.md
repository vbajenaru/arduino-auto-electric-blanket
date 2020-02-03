# explorer-robot-using-FreeRTOS

Upload the explorer_robot.ino file to an Arduino, with the proper wiring, to produce this explorer robot!

See the following video for an overview of the components and workings: https://www.youtube.com/watch?v=4IsdUQJm-8M

I have not made wire diagrams, but it may be possible to track the wire locations with the following picture if you'd like to recreate it.  Note that the Arduino Uno controller was used, along with the L298N H-bridge motor controller module.
<br>
<br>
![image](https://raw.githubusercontent.com/vicb1/arduino-projects/master/explorer-robot-using-FreeRTOS/pic.jpg)
<br>
<br>
<br>

Also the following is the finite state diagram of the states, triggers, and tasks for this robot:
<br>
<br>
![image](https://raw.githubusercontent.com/vicb1/arduino-projects/master/explorer-robot-using-FreeRTOS/Real_time_explorer_finite_state_diagram.png)
<br>
<br>

Also the following is an example of the Arduino serial monitor output for this project, showing the state and task updates:
<br>
<br>
![image](https://github.com/vicb1/arduino-projects/blob/master/explorer-robot-using-FreeRTOS/serial_monitor_output.png?raw=true)

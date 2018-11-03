# arduino-auto-electric-blanket

Upload the .ino file to an Arduino, with the proper wiring, to produce this Sunbeam electric blanket addon that is able to automatically turn your blanket on and off at the prescribed times of day!

Some precautions:
- You'd have to unscrew apart your electric blanket controller, and sauder wires to the buttons to simulate button presses
   - This needs to be done for the power on button, and the plus (more heat) button
   - Each button bridges two electrical contacts.  Both of these contacts need to have an external wire saudered to them.  We will then simulate each button press with a relay, by invoking the relay to connect the button contacts, thus simulating a button press
- You'd also need a standard outlet timer to plug both the arduino and blanket to, which will serve as our method of timing.  The arduino internal clock is not accurate over long periods of time based on my experience with it, but you may find something different
- Using a transistor instead of the relay does not work for this application, since transistors at a low state will still trickle current which makes the Sunbeam button think there is contact
- A relay and a resistor is all that's really needed for this setup

I have not made wire diagrams, but it's possible to track the wire locations with this picture if you'd like to recreate it: 
![image](https://raw.githubusercontent.com/vbajenaru/arduino-auto-electric-blanket/master/pic2.jpg)

# arduino-auto-electric-blanket

Upload the .ino file to an Arduino, with the proper wiring, to produce this Sunbeam electric blanket addon that is able to automatically turn your blanket on and off at the prescribed times of day!

More information:
- You'd need a standard outlet timer to plug both the Arduino and blanket controller to, which will serve as our method of timing.  The Arduino doesn't have a battery powered clock that knows the time of day, so in that case you'd have to program the time of day when you enable the program.  Programming this in can be a challenge, especially when unplugging and replugging in the blanket for any reason, as you'd have to get your computer out and update the variables.  Working off a standard outlet timer seemed like a simpler approach
- When you plug in the controller you'll notice it does not turn on automatically.  You'll also notice it doesn't save its previous heat state, and starts of at its lowest state
   - Thus, we'll have to simulate the "On" button and the "Plus Heat" button
   - In this case, we'll have to unscrew apart the electric blanket controller, and sauder wires to the buttons to simulate button presses
   - When you open up the casing, you'll notice each button bridges two electrical contacts to invoke a button press.  Both of these contacts need to have an external wire saudered to them, so we can then invoke each button press with a relay, by programming the relay to connect the button contacts, thus simulating a button press
   - Using a transistor instead of the relay does not work for this application, since transistors at a low state will still trickle current which makes the controller think there is a button press
- A relay and a resistor is all that's really needed for this setup

I have not made wire diagrams, but it's possible to track the wire locations with this picture if you'd like to recreate it: 
![image](https://raw.githubusercontent.com/vbajenaru/arduino-auto-electric-blanket/master/pic3.jpg)

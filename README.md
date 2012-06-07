Lumix Intervalometer
====================

This project provides an arduino sketch and fritzing schematics to build a simple intervalometer controlling a Panasonic/Lumix camera via its remote port.

The breadboard houses four components (from left to right).

1. the on/off switch and the status LED
1. two push buttons (left focus, right shutter release)
1. three resistors that control the remote port
1. two optocouplers (left focus, right shutter release)

You can use the push buttons and the resistors to just manually remote control your camera. The on/off switch and the optocouplers are used to remote control the camera from the arduino.

After wiring the components, the interval can be specified by connection pins 0-7 to ground. The pins represent a byte whose value determines the amount of seconds between shutter releases. So use your binary magic to determine which pins to connect to ground.

When everything is setup, the far left button can be used to start stop the interval.

Sources
-------

Information on the various remote control ports can be found here:

http://www.doc-diy.net/photo/remote_pinout/#lumix

License
-------

Copyright © Thomas Jachmann. See LICENSE for details.

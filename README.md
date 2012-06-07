Lumix Intervalometer
====================

This project provides an arduino sketch and fritzing schematics to build a simple intervalometer controlling a Panasonic/Lumix camera via its remote port.

Setup
-----

You need an arduino, a breadboard plus some components and a remote control cable.

The cable is just a two wire cable connected to a 4 pole 2.5mm headphone jack. For details on how to connect the jack, see the remote pinout link below. - is connected to - and + is connected to + on the top bus strip.

Board Layout
------------

The bottom bus strip connects to the arduino, the top bus strip to the camera. The components on the breadboard consist of four major parts (from left to right).

1. the on/off switch and the status LED
1. two push buttons (left: focus, right: shutter release)
1. three resistors that control the remote port
1. two optocouplers (left: focus, right: shutter release)

You can use the push buttons and the resistors to just manually remote control your camera. The on/off switch and the optocouplers are used to remote control the camera from the arduino. The optocoupler for focus isn't used by the arduino sketch yet.

Interval Configuration
----------------------

The interval can be specified by connecting arduino's pins 0-7 to ground. The pins represent a byte whose value determines the amount of seconds between shutter releases. So use your binary magic to determine which pins to connect to ground.

When everything is setup, you can use the on/off switch to start/stop the interval.

Sources
-------

Information on the various remote control ports can be found here:

http://www.doc-diy.net/photo/remote_pinout/#lumix

License
-------

Copyright © Thomas Jachmann. See LICENSE for details.

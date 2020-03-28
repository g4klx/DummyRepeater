This is the Dummy Repeater. It allows a computer to appear as a himebrew repeater to interface with the ircDDB Gateway. It does require some form of vocoder to ranslate the audio from the computer's soundcard to AMBE. This is done via the original DV-Dongle, the NWDR Thumb-DV or similar devices.

They all build on 32-bit and 64-bit Linux as well as on Windows using Visual Studio 2017 on x86 and x64.

This software is licenced under the GPL v2.

# Linux Build
## Prerequisites

`sudo apt install libwxgtk3.0-dev libboost-all-dev wiringpi`
 WirinPi is only necessary if you want to build on Raspberry Pi and have GPIO or dRAWS support.
 
## Build
`make -j5`

## Know issues
Using DV3000 over serial connection makes the program freeze from time to time, recommended is to use through AMBEserver

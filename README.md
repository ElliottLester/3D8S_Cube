# A reimplementation of the 3D8S Cube microcontroller
This is a reimplementaion for the iCubeSmart 3D8S LED cube,
while it comes with software for programming your own patterns.

I wanted more control and more of a challenge.
This project exposes the onboard UART for input and output, with the goal of adding 
the abillity to upload patterns to the onboard EEPROM 

It's powered by a STC12C5A60S2
which is a modern clone of the 8051

Datasheet is avalible here:
http://www.stcmicro.com/datasheet/STC12C5A60S2-en.pdf

## Requirements
- sdcc compiler
- packihx
- stcgal: for flashing (https://github.com/grigorig/stcgal)

## Optional 
- minicom: for serial communication

## Interface
currently the serial interface responds to 3 keys that take two hex charaters to set the provided port.
- D : Sets the data line
- L : Enables latches 
- P : Sets the active vertical plane
- S : For auto (strobe) switching the planes on in seqence(Work in progress)


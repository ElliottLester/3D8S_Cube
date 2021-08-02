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
Simiple protocol for directly driving the LED Cube See play.sh
serial port needs to be configured for 115200 8n1



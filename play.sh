#!/bin/bash
tty='/dev/ttyUSB0'
while true; do
    echo "LFFD81L81DFFP81" > $tty
    sleep 0.1
    echo "LFFD00L7ED42L42D7EP42" > $tty
    sleep 0.1
    echo "LFFD00L3CD24L24D3CP24" > $tty
    sleep 0.1
    echo "LFFD00L18D18l18D18p18" > $tty
    sleep 0.1
    echo "LFFD00L3CD24L24D3CP24" > $tty
    sleep 0.1
    echo "LFFD00L7ED42L42D7EP42" > $tty
    sleep 0.1
    echo "LFFD81L81DFFP81" > $tty
    sleep 0.1
done

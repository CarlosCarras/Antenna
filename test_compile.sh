#!/bin/bash

gcc -c -std=c99 -o lsquaredc.o lsquaredc.c
g++ -c -std=c++0x -c -o I2C_Functions.o I2C_Functions.cpp
g++ -c -std=c++0x -c -o ISIS_Antenna.o ISIS_Antenna.cpp
g++ -c -std=c++0x -c -o main.o main.cpp
g++ -o testapp lsquaredc.o I2C_Functions.o ISIS_Antenna.o main.o

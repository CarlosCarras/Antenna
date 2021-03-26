CC= gcc
CCC= g++

CFLAGS= -Wall
CPPFLAGS= $(CFLAGS)
# BINS= imu_test i2clib.a


all: test

main.o: main.cpp
	$(CCC) $(CPPFLAGS) -c main.cpp -o main.o

ISIS_Antenna.o: ISIS_Antenna.h ISIS_Antenna.cpp
	$(CCC) $(CPPFLAGS) -c ISIS_Antenna.cpp -o ISIS_Antenna.o

I2C_Functions.o: I2C_Functions.h I2C_Functions.cpp
	$(CCC) $(CPPFLAGS) -c I2C_Functions.cpp -o I2C_Functions.o

lsquaredc.o: lsquaredc.h lsquaredc.c
	$(CC) $(CFLAGS) -c lsquaredc.c -o lsquaredc.o

test: lsquaredc.o I2C_Functions.o ISIS_Antenna.o main.o
	$(CCC) $(CPPFLAGS) -o test main.o ISIS_Antenna.o I2C_Functions.o lsquaredc.o

# i2clib.a: libi2c.o
#	 ar rcs i2clib.a libi2c.o lsquaredc.o

clean:
	rm -rf *.o test
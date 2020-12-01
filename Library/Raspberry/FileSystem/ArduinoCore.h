// file:    ArduinoCore.cpp
// Copyright 2020 D.E.Repolev
//
// This file is part of DeviceLib. DeviceLib is free software and you may distribute it under
// the terms of the GNU General Public License (version 3 or later) as published by the
// Free Software Foundation. The full license text you find at 'https://www.gnu.org/licenses'.
// Disclaimer: DeviceLib is distributed without any warranty.

/*
*  The following copyright notes only concern:
*  > Serial interface
*  > attachInterrupt / detachInterrupt
*  > analogRead / analogWrite
*  > the pwm and threading helper-routines
* 
*  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
*  http://www.libelium.com
*
*  Version 2.4 (For Raspberry Pi 2)
*  Author: Sergio Martinez, Ruben Martin
*
*  2020: Some minor changes have been made to meet the structure of the DeviceLib library.
*/


#ifndef ARDUINOCORE_H
#define ARDUINOCORE_H

#include <chrono>
#include "linkedlist.h"

extern bool GTK;

using namespace std;

// ARDUINO CORE

#define INPUT		0
#define OUTPUT		1
#define INPUT_PULLUP	2
#define INPUT_PULLDOWN	3

#define LOW 		0
#define HIGH		1
#define RISING		2
#define FALLING		3
#define CHANGE		4

extern void delay( uint32_t);
extern void delayMicroseconds( uint32_t);
extern long millis();
extern long micros();

extern void pinMode( uint8_t pin, uint8_t mode);
extern void digitalWrite( uint8_t pin, uint8_t data);
extern uint8_t digitalRead( uint8_t pin);
extern void analogWrite( uint8_t pin, uint16_t level);
// analogRead not defined yet

extern void attachInterrupt( uint8_t pin, void (*func)(), uint mode);
extern void detachInterrupt( uint8_t pin);

extern void bitWrite( uint8_t &data, uint8_t bit, uint8_t value);
extern void bitSet( uint8_t &data, uint8_t bit);
extern void bitClear( uint8_t &data, uint8_t bit);
extern uint8_t bitRead( uint8_t data, uint8_t bit, uint8_t value);
extern uint32_t bit( uint8_t bit);
extern uint8_t lowByte( uint16_t byte);
extern uint8_t highByte( uint16_t byte);

// ARDUINO SERIAL

#define SERIAL_5N1	0
#define SERIAL_6N1	1
#define SERIAL_7N1	2
#define SERIAL_8N1	3
#define SERIAL_5N2	4
#define SERIAL_6N2	5
#define SERIAL_7N2	6
#define SERIAL_8N2	7
#define SERIAL_5E1	8
#define SERIAL_6E1	9
#define SERIAL_7E1	10
#define SERIAL_8E1	11
#define SERIAL_5E2	12
#define SERIAL_6E2	13
#define SERIAL_7E2	14
#define SERIAL_8E2	15
#define SERIAL_5O1	16
#define SERIAL_6O1	17
#define SERIAL_7O1	18
#define SERIAL_8O1	19
#define SERIAL_5O2	20
#define SERIAL_6O2	21
#define SERIAL_7O2	22
#define SERIAL_8O2	23

class SerialRPi
{
public:

	SerialRPi( bool isconsole);

	uint available();
	uint availableForWrite();

	void begin( const ulong baud, const uint config = SERIAL_8N1);
	void end(); 

	bool find( const String search);
	bool findUntil( const String search, const String stop = "");

	void flush();

	double parseFloat();
	long   parseInt();

	int8_t peek();

	uint print( const int i, const NUMSYSTEM type = DEC);
	uint print( const double f, const int decimals = 2);
	uint print( const String s = "");
	uint println( const int i, const NUMSYSTEM type = DEC);
	uint println( const double f, const int decimals = 2);
	uint println( const String s = "");

	int8_t read();
	uint8_t   readBytes( uint8_t data[], const uint8_t len);
	uint8_t   readBytesUntil( const char stop, uint8_t data[], const uint8_t len);
	String readString();
	String readStringUntil( const char stop);

	void setTimeout( ulong millis);

	uint write( const uint8_t data);
	uint write( const String str);
	uint write( const uint8_t buf[], const uint len);

private:

	uint8_t readB( const char stop, uint8_t data[], const uint8_t len, bool dostop);
	String readS( const char stop, bool dostop);

	bool   m_console;
	bool   m_enabled;
	ulong  m_timeout;
	int    m_uart;
};

extern SerialRPi Serial;
extern SerialRPi Serial1;

// CONVENIENT

#define sprint		Serial.print
#define sprintln	Serial.println
#define sflush		Serial.flush

// HELPER

typedef void (*CALLBACK)();
typedef LinkedList<void*>  WidgetList;

typedef chrono::time_point<chrono::high_resolution_clock>	hirestime;
extern hirestime currentTime();
extern void localTime( tm &lt, uint32_t &msec);
extern ulong diffMillis( hirestime stop, hirestime start);
extern ulong diffMicros( hirestime stop, hirestime start);

#define DIRECTION_MAX 35
#define VALUE_MAX 30
#define MAXPINS 30

// GPIO

typedef struct tdGpioStatus {
    int code;
    String txt;
}tdGpioStatus;

typedef struct tdGpioPinData {
    int inUse;
    int dir;
    int fd;
    String path;
}tdGpioPinData;

class gpio
{
public:
    explicit gpio();
    ~gpio();
    int pinMode(uint8_t pin, uint8_t dir);
    void digitalWrite(uint8_t pin, uint8_t val);
    uint8_t digitalRead(uint8_t pin);
    void closeGpio();
    int openGpio(uint8_t pin);
    tdGpioStatus status;

private:
    int Export(uint8_t pin);
    int Unexport(uint8_t pin);
    int Direction(uint8_t pin, uint8_t dir);
    uint8_t Read(uint8_t pin);
    int Write(uint8_t pin, uint8_t value);
    tdGpioPinData pindata[MAXPINS];
};

/////////
// GTK //
/////////

#define tLabel	1
#define tImage	2
#define tButton	3
#define tCheck	4
#define tRadio	5
#define tEdit	6

extern void setTitle( String title);
extern void setSize( uint16_t width, uint16_t height);

extern void* create( uint8_t type, String name);
extern void* create( uint8_t type, String name, String param);
extern void appendDefaultStyle( uint8_t type, String style);
extern void setSize( void* widget, uint16_t width, uint16_t height);
extern void place( void* widget, uint16_t x, uint16_t y);
extern String name( void* widget);
extern void destroy( void* widget);
extern void show( void* widget);
extern void show( void* widget, bool show);
extern void hide( void* widget);
extern void drag( void* widget);
extern void drop();
extern void setDragField( uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);

extern void setText( void* widget, uint8_t type, String text);
extern String text( void* widget, uint8_t type);
extern void setCheck( void* widget, bool check);
extern bool isChecked( void* widget);

extern uint16_t mouseX();
extern uint16_t mouseY();
extern void mouse( uint16_t &x, uint16_t &y);
extern void *mouseWidget( String name = "");

extern void callOnMouseLClick( CALLBACK routine);
extern void callOnMouseRClick( CALLBACK routine);
extern void callOnMouseLRelease( CALLBACK routine);
extern void callOnMouseRRelease( CALLBACK routine);

uint8_t addStickyArea( uint16_t left, uint16_t top, uint16_t width, uint16_t height);
void removeStickyArea( uint16_t ix);
void clearStickyArea();

void addRow( WidgetList* widgets);
void setRowValues( uint8_t row, StringList &values, uint8_t type = tEdit);
void getRowValues( uint8_t row, StringList& values, uint8_t type = tEdit);

#endif // ARDUINOCORE_H

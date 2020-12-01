g++ -Wall -D RPI -shared -o libDeviceLib.so -fPIC \
	BcmCore.cpp \
	ArduinoCore.cpp \
	ArduinoString.cpp \
	Wire.cpp \
	SPI.cpp \
	device.cpp \
	actuator.cpp \
	sensor.cpp \
	a4988.cpp \
	beeper.cpp \
	buzzer.cpp \
	camera.cpp \
	dcmotor.cpp \
	dht.cpp \
	ds18.cpp \
	hcsr04.cpp \
	hcsr501.cpp \
	hx711.cpp \
	ibutton.cpp \
	led.cpp \
	mfrc522.cpp \
	nextion.cpp \
	pn532.cpp \
	rgbled.cpp \
	sound.cpp \
	sqlclient.cpp \
	switch.cpp \
	tcpclient.cpp \
	tcpserver.cpp \
	unistepper.cpp \
	`pkg-config --cflags --libs gtk+-3.0` \
	-L/usr/local/include -lbcm2835

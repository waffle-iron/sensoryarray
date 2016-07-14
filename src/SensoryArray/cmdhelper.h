#ifndef cmdhelper_h
#define cmdhelper_h

#include "arduino.h"

class cmdhelper{
public:	
	cmdhelper();
	void listenForCmd();
	String cleanseInput(String);
	void fireCmd(String);
};

#endif


/*
	listen for cmd  listenForCmd
	cleanse input  
	map input to possible commands
	exec command
	fire result msg
*/
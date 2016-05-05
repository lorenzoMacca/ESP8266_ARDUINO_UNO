#ifndef _ESP8266ARDUINO_H_
#define _ESP8266ARDUINO_H_

#include <SoftwareSerial.h>
/*
* The following libs are needed to use:
* - Stream
*/
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class ESP8266Arduino{

	private:
		SoftwareSerial *serial;
		Stream *serialDebug;
		bool isDebugEnabled;
		void debugMessage(String s);
        void clean();
        String* cleanString(String *s);
		bool find(String *s, String *occ);
	
	public:
		ESP8266Arduino(SoftwareSerial *serial);
		ESP8266Arduino(SoftwareSerial *serial, Stream *serialDebug);
		~ESP8266Arduino();
		bool testConnection();
};

#endif
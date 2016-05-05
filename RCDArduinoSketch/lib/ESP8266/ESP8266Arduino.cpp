#include "ESP8266Arduino.h"


ESP8266Arduino::ESP8266Arduino(SoftwareSerial *serial){
	this->serial = serial;
	this->isDebugEnabled = false;
}

ESP8266Arduino::ESP8266Arduino(SoftwareSerial *serial, Stream *serialDebug){
	this->serial = serial;
	this->serialDebug = serialDebug;
	this->isDebugEnabled = true;
}

ESP8266Arduino::~ESP8266Arduino(){
}

bool ESP8266Arduino::testConnection(){
	this->debugMessage("Test connection");
    this->clean();
    this->serial->println("AT");
    String response = this->serial->readString();
    response.trim();
	String rightResponse = "OK";
    if(this->find(&response, &rightResponse)){
        this->debugMessage("connection OK");
        return true;
    }else{
        this->debugMessage("fuck...");
        return false;
    }
}

void ESP8266Arduino::debugMessage(String s){
	if(this->isDebugEnabled){
		this->serialDebug->println(s);
	}
}

void ESP8266Arduino::clean(){
    this->serial->readString();
}

bool ESP8266Arduino::find(String *s, String *occ){
	unsigned occLen = occ->length();
	unsigned sLen = s->length();
	if(sLen < occLen) return false;
	for(unsigned i = 0; i<sLen; i++){
		if(s->charAt(i) == occ->charAt(0)){
			//this->debugMessage(s->substring(i,i+occLen));
			if(s->substring(i,i+occLen).equals(*occ)) return true;
		}
	}
}


String* ESP8266Arduino::cleanString(String *s){
    unsigned len = s->length();
    this->serialDebug->println(len);
    String res = "";
    for (unsigned i=0; i<len; i++) {
        if(s->charAt(i) != '\r' && s->charAt(i) != '\r' && s->charAt(i) != '\t'){
			this->serialDebug->println(s->charAt(i));
			res += s->charAt(i);
		}
    }
    return &res;
}
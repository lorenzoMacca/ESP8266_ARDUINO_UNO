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
	String message = "AT+RST";
	String neededResponse = "OK";
	String testName = "Test Connection";
	return this->sendAndreciveMessage(&message, &neededResponse, &testName);
}


bool ESP8266Arduino::sendAndreciveMessage(String *request, String *neededResponse, String *testName, bool iWannaMoreInfo, const int timeout){
	this->debugMessage(*testName);
    this->clean();
    this->serial->println(*request);

	long int time = millis();
	String response = "";
	while( (time+timeout) > millis() ){
		while( this->serial->available() ){
			response += this->serial->readString();
		}
	}
    response.trim();
	if(iWannaMoreInfo){
		this->debugMessage(response);
		//this->debugMessage(*neededResponse);
	}
	if(this->find(&response, neededResponse)){
        this->debugMessage("OK");
        return true;
    }else{
        this->debugMessage(response);
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

/**
* find a string in an other string
*/
bool ESP8266Arduino::find(String *s, String *occ){
	//this->debugMessage(*s);
	//this->debugMessage(*occ);
	unsigned occLen = occ->length();
	unsigned sLen = s->length();
	if(sLen < occLen) return false;
	for(unsigned i = 0; i<sLen; i++){
		if(s->charAt(i) == occ->charAt(0)){
			//this->debugMessage(s->substring(i,i+occLen));
			if(s->substring(i,i+occLen).equals(*occ)) return true;
		}
	}
	return false;	
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

bool ESP8266Arduino::connectToWifi(String *ssid, String *pass){
	bool isModuleInStationModeSet = this->setModeClient();
	if(isModuleInStationModeSet){
		//quitConnection();
		//String message = "AT+CWJAP=\"KDG-C1CFE\",\"F0Ey03x0YQU3\"";
		String message = "AT+CWJAP=";
		message += "\"";
		message += *ssid;
		message += "\",\"";
		message += *pass;
		message += "\"";
		String neededResponse = "WIFI CONNECTED";
		String testName = "Connect to wifi";
		return this->sendAndreciveMessage(&message, &neededResponse, &testName, true, 4000);
	}
	return false;
}

bool ESP8266Arduino::setModeClient(){
	String message = "AT+CWMODE=1";
	String neededResponse = "OK";
	String testName = "Set module in client mode";
	return this->sendAndreciveMessage(&message, &neededResponse, &testName);
}

bool ESP8266Arduino::quitConnection(){
	String message = "AT+CWQAP";
	String neededResponse = "OK";
	String testName = "Quit connection";
	return this->sendAndreciveMessage(&message, &neededResponse, &testName);
}

bool ESP8266Arduino::getIpAddress(){
	String message = "AT+CIFSR";
	String neededResponse = "OK";
	String testName = "Get ip address";
	return this->sendAndreciveMessage(&message, &neededResponse, &testName, true, 10000);
}


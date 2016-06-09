#include "lib/ESP8266/ESP8266Arduino.h"
#include <SoftwareSerial.h>

#define RX_PIN 10
#define TX_PIN 11

ESP8266Arduino *esp8266;
SoftwareSerial esp8266Serial(RX_PIN, TX_PIN); // RX, TX
String ssid = "";
String pass = "";

void setup() {
	pinMode(RX_PIN, INPUT);
	pinMode(TX_PIN, OUTPUT);
  esp8266Serial.begin(115200);
	Serial.begin(9600);
	esp8266 = new ESP8266Arduino(&esp8266Serial, &Serial);
	
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	//test connection
	bool isConnected = esp8266->testConnection();

  //connect to wif
  if(isConnected){
    esp8266->connectToWifi(&ssid, &pass);
    //esp8266->getIpAddress();
    esp8266->quitConnection();
  } 
}

void loop() {
  // put your main code here, to run repeatedly:

}

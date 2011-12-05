/*
 * A simple sketch that uses WiServer to get the hourly weather data from LAX and prints
 * it via the Serial API
 */

#include <WiServer.h>
#include "testertemp.h"
#define DEBUG


#define WIRELESS_MODE_INFRA	1
#define WIRELESS_MODE_ADHOC	2

// Wireless configuration parameters ----------------------------------------
unsigned char local_ip[] = {192,168,0,106};	// IP address of WiShield
unsigned char gateway_ip[] = {192,168,0,1};	// router or gateway IP address
unsigned char subnet_mask[] = {255,255,255,0};	// subnet mask for the local network
const prog_char ssid[] PROGMEM = {"boardcaster"};		// max 32 bytes

unsigned char security_type = 0;	// 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2

// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {"12345678"};	// max 64 characters

// WEP 128-bit keys
// sample HEX keys
prog_uchar wep_keys[] PROGMEM = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,	// Key 0
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 1
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 2
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Key 3
				};

// setup the wireless mode
// infrastructure - connect to AP
// adhoc - connect to another WiFi device
unsigned char wireless_mode = WIRELESS_MODE_INFRA;

unsigned char ssid_len;
unsigned char security_passphrase_len;
// End of wireless configuration parameters ----------------------------------------

boolean received = false;

// Function that prints data from the server
void printData(char* data, int len) {
  
  received = true;
  Serial.println("I was called");

  // Print the data returned by the server
  // Note that the data is not null-terminated, may be broken up into smaller packets, and 
  // includes the HTTP header. 
  while (len-- > 0) {
    Serial.print(*(data++));
  } 
}

String nextFEN = "";   
String endString = "***";

uint8 ip[] = {192,168,0,199};


void setup()
{



   // Initialize WiServer (we'll pass NULL for the page serving function since we don't need to serve web pages) 
 WiServer.init(NULL);
  Serial.begin(9600);  
  Serial.println("init");
  // Enable Serial output and ask WiServer to generate log messages (optional)
  WiServer.enableVerboseMode(true);

  setNextFEN("3k3r/8/8/8/8/8/1K6/RNBP4 w KQkq - 0 1");

  Serial.println("Donde setup");
}



int x = 0;

void loop(){



  do{
// IP Address for boardcaster website
  POSTrequest sendInfo(ip, 3000, "http://192.168.0.199", "/moves/", printPost);
  sendInfo.setReturnFunc(printData);  
  sendInfo.submit();
  WiServer.server_task();
  }while(!received);

  

  Serial.println("Got it baby");
  WiServer.server_task();
 }

void sendEndGamePost()
{
  setNextFEN(endString);
  sendData();
}

// This function generates the body of our POST request
void printPost() {
       WiServer.print("move_data=" + nextFEN);
}

void setNextFEN(String fen)
{
  nextFEN = fen;
}


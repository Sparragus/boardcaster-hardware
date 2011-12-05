// Chess Engine <START>
#include <bitboard.h>
#include <position.h>
#include <move.h>
#include <fen.h>
#include <attack.h>
#include <Chess.h>
// Chess Engine <END>
#include <WiServer.h>

#include "boardcaster.h"
#include "piece_detector.h"
#include "led_disp.h"
#include "utils.h"
#include "hw_signals.h"
#include "bitboard_ops.h"
#include "utils.h"

#include "MemoryFree.h"

#include <stdlib.h>
#include <avr/pgmspace.h>

#define NDEBUG
// Just in case.
#define assert(x) ;


int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};

void * operator new(size_t size)
{
  return malloc(size);
}

void operator delete(void * ptr)
{
  free(ptr);
}


// WiShield <START>


//#define DEBUG


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


volatile boolean received = false;
uint8 ip[] = {192,168,0,196};
// WiShield <END>
 POSTrequest sendInfo(ip, 3001, "http://192.168.0.197", "/moves/", printPost);
String fen = "3k3r/8/8/8/8/8/1K6/RNBP4 w KQkq - 0 1";
Chess chess;
uint64_t board = 0x0ULL;

// Main firmware setup call
void setup()
{
  delay(1000);
  Serial.end();
  // Set serial transmission rate for debug prints
  Serial.begin(9600);
  delay(1000);
  showString(PSTR(""));
  showBanner();
  showString(PSTR("\n"));
  showString(PSTR("\nInitializing Piece Detector..."));
    
  // Initialize the piece 
  initPieceDetector();
  showString(PSTR("done\n"));

  showString(PSTR("Initializing LED Array..."));
  // Initialize the LED array
  initLedDisp();
  showString(PSTR("done\n"));

  showString(PSTR("Cycling LED Array..."));
  // Run LED diagnostics
  //cycleArray();
  clearDisplay();

  showString(PSTR("done\n"));

  // Init chess engine

  //chess = Chess("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

  // chess = Chess("8/8/8/8/4Q3/8/8/k3K3 w KQkq - 0 1");
  int s = fen.length();
  char fen_arr[s];
  fen.toCharArray(fen_arr, s);
  chess = Chess(fen_arr);

  showString(PSTR("Expected starting board\n\n"));

  chess.printOwnPosition();

  showString(PSTR("Getting board state"));

  // Scan the board a few times first

   
  scanPieceArray(&board);
  showString(PSTR("\nMEM: "));
  Serial.println(freeMemory(), DEC);

  showString(PSTR("\nInitializing Wifi Shield...\n\n"));
    

  // Piece is placed, turn off leds
  clearDisplay();

  // Init web posting code
    
  // Initialize WiServer (we'll pass NULL for the page serving function since we don't need to serve web pages) 
  WiServer.init(NULL);
  showString(PSTR("WiServer Init done\n"));
  // Enable Serial output and ask WiServer to generate log messages (optional)
  //  WiServer.enableVerboseMode(true);

  //  setNextFEN("3k3r/8/8/8/8/8/1K6/RNBP4 w KQkq - 0 1");
  //  setNextFEN("Hello");
  /*
  do{
    // IP Address for boardcaster website
    POSTrequest sendInfo(ip, 3000, "http://192.168.0.197", "/moves/", printPost);
    sendInfo.setReturnFunc(printData);  
    sendInfo.submit();
    WiServer.server_task();
  }while(!received);

  */
 
 
  /*
  
  do{
    showString(PSTR("*"));
 // IP Address for boardcaster website
    sendInfo.setReturnFunc(printData);  
    
     sendInfo.submit();
    WiServer.server_task();
   
  }while(!received);
  */

  sendInfo.setBodyFunc(printPost);
  sendInfo.submit();  
while(sendInfo.isActive())
    {
      showString(PSTR("."));
      WiServer.server_task();
    }
//uip_close();

  showString(PSTR("MEM: "));
  Serial.println(freeMemory(), DEC);

  flashOK();



}

//------------ WiShield Functions -------------------


// This function generates the body of our POST request
void printPost() {
  

  WiServer.print("move_data=" + String(fen));
}

// Function that prints data from the server
void printData(char* data, int len) {
  
  received = true;

  showString(PSTR("recv data START---------------"));
  // Print the data returned by the server
  // Note that the data is not null-terminated, may be broken up into smaller packets, and 
  // includes the HTTP header. 
  while (len-- > 0) {
    Serial.print(*(data++));
  } 
  showString(PSTR("recv data END--------------"));

}

//---------------------------------------------------

// Main firmware loop
void loop()
{
  showString(PSTR("START---ITERATION----------------------------------------------\n"));
  // Get current position
   
  board  = chess.getCurrentPosition();

  showString(PSTR("CurrentPosition=\n"));
  chess.printBitboard(&board);
   
    
  // ---------------------------------------
  // LIFT PIECE
  //
  //

  scanPieceArray(&board);
   
  showString(PSTR("CurrentPosition= printBoard\n"));
  printBoard(&board,64);

 
  // Scan piece array until a change is detected
  // sq >= 0 if Board changed; Square that changed, sq = -1 = No change
  int sq_source = -1;
  do
    {
      showString(PSTR("^ "));
      sq_source = scanPieceArray(&board);
       
    }
  while(sq_source == -1 || 63-sq_source==27 || 63-sq_source==9);
  
  showString(PSTR("\n"));
  // sq_source = emulate_board(&board, 0);

  sq_source = 63 - sq_source;
  showString(PSTR("Found lifted piece: ")); Serial.println(sq_source, DEC);
  showString(PSTR("Current board\n"));
  // chess.printBitboard(&board); 
   
  // Obtain a bitboard with the legal moves for a piece on the square sq
  const uint64_t moves = chess.getPieceMoves( sq_source );
    
  showString(PSTR("Found the following moves\n"));
  chess.printBitboard(&moves);

  displayPositions(&moves);  

    

   
  //
  //
  // ---------------------------------------------------








  // --------------------------------------------------
  // SET PIECE
  //
  //

  // Scan piece array until a change is detected
  // sq_source >= 0 if Board changed; Square that changed, sq_source = -1 = No change
  int sq_dest = -1;
  do
    {
  
      showString(PSTR("v "));
      sq_dest = scanPieceArray(&board);
 
 
    }
  while(sq_dest == -1 || 63-sq_dest==27 || 63-sq_dest == 9);
  showString(PSTR("\n"));
    
  // sq_dest = emulate_board(&board, 1);
  sq_dest = 63 - sq_dest;
  showString(PSTR("Found placed piece: ")); Serial.println(sq_dest, DEC);
  clearDisplay();
   

  // Piece is placed, turn off leds
  
  // If sq_source == sq_dest, then piece was placed back to it's original pos
  // Don't play the move. Loop again.
  if(sq_source == sq_dest)
    {
      //TODO: check if empty return is safe.
      clearDisplay();
      showString(PSTR("Set piece at same position!\n"));
      showString(PSTR("END---ITERATION----------------------------------------------\n"));
      return;
    }
  chess.playPieceMove(sq_dest);

  // TODO: Confirn correct code logic
  /*
    uint64_t error_board = 0x0ULL;
    // legal == 0 if move is legal, else legal == 1, meaning move is illegal
    // while move is illegal...
    while(chess.playPieceMove(sq_dest) != 0)
    {
    if( sq_dest >= 0 )
    {
    showString(PSTR("Error board!\n"));
    error_board = chess.getMask(sq_dest);
    }
    uint16_t* parts  = getParts(&error_board);
    displayPositions(parts);
    delay(500);
    clearDisplay();
    // HACK
    sq_dest = scanPieceArray(&board);
    printBoard(&board, 64);
     
    sq_dest = 63 - sq_dest;

    //If the piece goes back to its original square...
    if(sq_dest == sq_source)
    {
    //TODO: check if empty return is safe.
    //return;
    }
    showString(PSTR("Waiting for a valid move\n"));
    }
  */

  // -------------------------------------------------
    


  //TODO: convert fen to an Arduino String
  // Send FEN to boardcaster.com
  showString(PSTR("Getting FEN from position\n"));
   char* chess_ret = chess.getFENFromPosition();
   fen = String(chess_ret);
   showString(PSTR("Got FEN from position\n"));
   
  showString(PSTR("Posting FEN\n"));
  Serial.println(fen);
  
  received = false;
  /*
  do{

    showString(PSTR("."));
    //showString(PSTR("MEM: "));
    //Serial.println(freeMemory(), DEC);
    sendInfo.setBodyFunc(printPost);
     sendInfo.setReturnFunc(printData);  
     sendInfo.submit();
    WiServer.server_task();
   
  }while(!received);
  */
  sendInfo.setBodyFunc(printPost);
  sendInfo.submit();  
while(sendInfo.isActive())
    {
      showString(PSTR("."));
      WiServer.server_task();
    }
 uip_close();
  showString(PSTR("END---ITERATION----------------------------------------------\n"));


  WiServer.server_task();
  delay(10);

}


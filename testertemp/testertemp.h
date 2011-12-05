#ifndef TESTERTEMP_H
#define TESTERTEMP_H
#include <WProgram.h>

void printData(char* data, int len);
void initPoster();
void printPost();
void sendData();
void setNextFEN(String fen);
void sendEndGamePost();

#endif //TESTERTEMP_H

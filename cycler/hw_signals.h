#ifndef HW_SIGNALS_H
#define HW_SIGNALS_H

void generateSig(uchar i, sig_t* s);
void setDecoder(sig_t* s);
void setMux(sig_t* s);
int readPieceArrayLine();

#endif // HW_SIGNALS_H

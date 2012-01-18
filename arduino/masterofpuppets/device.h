/*
 * DomoticHome branch
 *
 * DOMINO
 */

#ifndef Domino_h
#define Domino_h
#include <Arduino.h>

// #define DEBUG
// #define TEST


// Values for decode_type, the out= parameter in http request
#define NEC 1
#define SONY 2
#define IRCOMMANDER 3
#define UNKNOWN -1


// Some useful constants

#define USECPERTICK 50  // microseconds per clock interrupt tick
#define RAWBUF 100 // Length of raw duration buffer


// tutti i device sono questo
class Domino_device
{
protected:
  int _id;
public:
  Domino_device(int id);
  int sendCommand(int recvpin);
  int getId(){return _id;};
  //obbliga l'implementazione?
  //String getStatus();
  //int decode(decode_results *results);
  //void enableIRIn();
  //void resume();
private:
  //int _id;
  // These are called by decode
  /*int getRClevel(decode_results *results, int *offset, int *used, int t1);
  long decodeNEC(decode_results *results);
  long decodeSony(decode_results *results);
  long decodePanasonic(decode_results *results);
  long decodeRC5(decode_results *results);
  long decodeRC6(decode_results *results);*/
} 
;

// Only used for testing; can remove virtual for shorter code
#ifdef TEST
#define VIRTUAL virtual
#else
#define VIRTUAL
#endif

#endif

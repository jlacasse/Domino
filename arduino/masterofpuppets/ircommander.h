

#ifndef IR_commander_h
#define IR_commander_h

#include "device.h"

#define VELUX 3
#define AIRCONDITIONER 4
#define PANASONIC 5 


class IR_commander : public Domino_device
{
  public:
    String powerOnStereo();
    String getStatus();
    IR_commander():Domino_device(IRCOMMANDER){};
  private:
    void tuner();
    void cd();
    void aux();
     void testtuner();
     void testCd();
     void lowerVolume();
     void togglePower();
     void cdplay();
     void cdstop();
     void next();
     void prev();
     void increaseVolume();
};
  
#endif

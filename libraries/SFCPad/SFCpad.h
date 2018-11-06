#include "WProgram.h"


//Finally, it's common to wrap the whole header file up in a weird looking construct: 


#ifndef SFCpad_h
#define SFCpad_h

#include <inttypes.h>

#define SFCPAD_B_BTN	0x0001
#define SFCPAD_Y_BTN	0x0002
#define SFCPAD_SELECT	0x0004
#define SFCPAD_START	0x0008

#define SFCPAD_UP 	0x0010
#define SFCPAD_DOWN	0x0020
#define SFCPAD_LEFT	0x0040
#define SFCPAD_RIGHT	0x0080

#define SFCPAD_A_BTN	0x0100
#define SFCPAD_X_BTN	0x0200
#define SFCPAD_L_BTN	0x0400
#define SFCPAD_R_BTN	0x0800

#define SFCPAD_CUR_MASK	0x0f00
#define SFCPAD_ABXY_MASK 0x0303



class SFCpad{
public:
  SFCpad(uint8_t data, uint8_t clock, uint8_t latch);

  void init(uint8_t data, uint8_t clock, uint8_t latch);
  uint16_t readRaw();
private:
  uint8_t _data_pin; //Data send & RS LOW: command.  HIGH: character.
  uint8_t _clock_pin; 
  uint8_t _latch_pin; // activated by a HIGH pulse.

};

#endif

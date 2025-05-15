#ifndef PIN_MAPPING
#define PIN_MAPPING = 1
#include "MIDIUSB_Defs.h"


class Keyboard_;
class MIDI_;



class PinMapping
{
public:
    PinMapping (int pin, uint8_t key);
    void init();
    void runkeyboard(Keyboard_ &keyboard_out);
    void runmidi(midiEventPacket_t &midiport_out, uint8_t midi_channel);
private:
    int pin;
    uint8_t key;
    int button_state_val;
    const long unsigned key_down_debounce = 10;
    const long unsigned key_up_debounce = 10;
    enum key_state
    {
      Idle,
      KeyDown_Start,
      KeyDown_End,
      KeyUp_Start,
      KeyUp_End
    };
    key_state state;
    //state/
    //enum state

    unsigned long start_time;


};






#endif
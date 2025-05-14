#ifndef PIN_MAPPING
#define PIN_MAPPING = 1


class Keyboard_; //feex point to real


class PinMapping
{
public:
    PinMapping (int pin, int key);
    void init();
    void runkeyboard(Keyboard_ &keyboard_out);
    void runmidi(midiEventPacket_t &midiport_out, byte midi_channel);
private:
    int pin;
    int key;
    int button_state_val;
    int prev_button_state_val;
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
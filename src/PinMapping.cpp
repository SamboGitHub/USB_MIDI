#include <Arduino.h>

#include <Keyboard.h>
#include "PinMapping.h"
#include "MIDIUSB.h"


void PinMapping::init()
{
    //declare the buttons as input_pullup
    pinMode(pin, INPUT_PULLUP); 
    state = Idle;
}

void PinMapping::runkeyboard(Keyboard_ &keyboard_out)
{
    //checking the state of the button
    button_state_val = digitalRead(pin);
    
    //replaces button press with UP arrow
    if (button_state_val == LOW && state ==  Idle)
        {
            // and it's currently pressed:
            keyboard_out.press(key);
            state = KeyDown_Start;
            start_time = millis();
        }
    
    if (state == KeyDown_Start and millis()> start_time + key_down_debounce)
    {
        state = KeyDown_End;
    }
       
    if (button_state_val == HIGH && state ==  KeyDown_End)
    {
        // and it's currently released:
        keyboard_out.release(key);
        state = KeyUp_Start;
        start_time = millis();
    }
    
    if (state == KeyUp_Start and millis()> start_time + key_up_debounce)
    {
        state = Idle;
    }
}

void PinMapping::runmidi(midiEventPacket_t &midiport_out, byte midi_channel)
{
    byte velocity = 127;
    
    //checking the state of the button
    button_state_val = digitalRead(pin);
    
    //replaces button press with UP arrow
    if (button_state_val == LOW && state ==  Idle)
        {
            // and it's currently pressed:
            
            // THEIR SAMPLE CODE HERE!!
            // HOW TO USE midiportout?
            
            midiEventPacket_t noteOn = {0x09, 0x90 | midi_channel, key, velocity};
            
            //midiport_out = {0x09, 0x90 | midi_channel, key, velocity};
            // pick up here
            
            MidiUSB.sendMIDI(noteOn);

            state = KeyDown_Start;
            start_time = millis();
        }
    
    if (state == KeyDown_Start and millis()> start_time + key_down_debounce)
    {
        state = KeyDown_End;
    }
    
    
    if (button_state_val == HIGH && state ==  KeyDown_End)
    {
        // and it's currently released:
        
        // THEIR CODE!
        midiEventPacket_t noteOff = {0x08, 0x80 | midi_channel, key, velocity};
        MidiUSB.sendMIDI(noteOff);

        state = KeyUp_Start;
        start_time = millis();

    }
    
    if (state == KeyUp_Start and millis()> start_time + key_up_debounce)
    {
        state = Idle;
    }




}


PinMapping::PinMapping(int InitPin, int InitKey)
{
    pin = InitPin;
    key = InitKey;
    state = Idle;
    start_time = 0; 

}



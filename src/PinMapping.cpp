#include <Arduino.h>

#include <Keyboard.h>
#include "PinMapping.h"
#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>



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

void PinMapping::runmidi(MIDI_ &midiport_out, uint8_t midi_channel)
{
    uint8_t velocity = 127;
    
    //checking the state of the button
    button_state_val = digitalRead(pin);
    
    //replaces button press with UP arrow
    if (button_state_val == LOW && state ==  Idle)
        {
                          
            // First parameter is the event type (0x09 = note on, 0x08 = note off).
            // Second parameter is note-on/note-off, combined with the channel.
            // Channel can be anything between 0-15. Typically reported to the user as 1-16.
            // Third parameter is the note number (48 = middle C).
            // Fourth parameter is the velocity (64 = normal, 127 = fastest).

            // THEIR SAMPLE CODE HERE!!
            midiEventPacket_t noteOn = {0x09, 0x90 | midi_channel, key, velocity};
            // MidiUSB.sendMIDI(noteOn);
            
            // HOW TO USE midiportout?
           // noteOn = {0x09, 0x90 | midi_channel, key, velocity};
            midiport_out.sendMIDI(noteOn);
            // pick up here



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
        // MidiUSB.sendMIDI(noteOff);

        // My Code
        // noteOff = {0x08, 0x80 | midi_channel, key, velocity};
        midiport_out.sendMIDI(noteOff);

        state = KeyUp_Start;
        start_time = millis();

    }
    
    if (state == KeyUp_Start and millis()> start_time + key_up_debounce)
    {
        state = Idle;
    }




}


PinMapping::PinMapping(int InitPin, uint8_t InitKey)
{
    pin = InitPin;
    key = InitKey;
    state = Idle;
    start_time = 0; 

}



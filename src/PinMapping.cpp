#include <Arduino.h>

#include <Keyboard.h>
#include "PinMapping.h"

void PinMapping::init()
{
    //declare the buttons as input_pullup
    pinMode(pin, INPUT_PULLUP); 
    state = Idle;
}

void PinMapping::run(Keyboard_ &keyboard_out)
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

            // if (state == KeyDown_Start and millis() >= start_time + key_down_debounce)
            //     {
            //         state = Idle;
            //     }
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

            // if (state == KeyDown_Start and millis() >= start_time + key_down_debounce)
            //     {
            //         state = Idle;
            //     }
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



#include <Arduino.h>
#include <Keyboard.h>
#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>


#include "PinMapping.h"

enum USB_Mode
  {
    KYBD,
    MIDI
  };
  USB_Mode DeviceType = MIDI;

// MIDI Assignments 
uint8_t midi_channel = 0x05; //* MIDI channel to be used - channel 5
byte note = 36; //* Lowest note to be used; 36 = C2; 60 = Middle C
byte cc = 1; //* Lowest MIDI CC to be used

PinMapping keytable[] = { {2,54},{3,53},{4,52},{5,51},{6,50},{7,49},
                          {8,70},{9,69},{10,68},{14,67},{15,66},{16,65}};
const int keytablesize = sizeof(keytable)/sizeof(keytable[0]);

PinMapping miditable[] = { {2,54},{3,53},{4,52},{5,51},{6,50},{7,49},
                          {8,70},{9,69},{10,68},{14,67},{15,66},{16,65}};
const int miditablesize = sizeof(miditable)/sizeof(miditable[0]);

void setup() {

if(DeviceType == KYBD)
{for (int i=0; i<keytablesize; i++)
  {
      keytable[i].init();  
  }; 
  Keyboard.begin(); 
}

if(DeviceType == MIDI)
{
for (int i=0; i<miditablesize; i++)
  {
      miditable[i].init();  
  };
}
}

void loop()
{
if(DeviceType == KYBD)
{
  for (int i=0; i< keytablesize; i++)
  {
    keytable[i].runkeyboard(Keyboard);
  };
}

if(DeviceType == MIDI)
{
for (int i=0; i< miditablesize; i++)
  {
    miditable[i].runmidi(MidiUSB, midi_channel);
  };
}

}
#include <Arduino.h>
#include <Keyboard.h>


#include "PinMapping.h"


PinMapping pintable[] = { {2,54},{3,53},{4,52},{5,51},{6,50},{7,49},
                          {8,70},{9,69},{10,68},{14,67},{15,66},{16,65}};
const int pintablesize = sizeof(pintable)/sizeof(pintable[0]);


void setup() {

for (int i=0; i<pintablesize; i++)
  {
      pintable[i].init();  
  };

  
  Keyboard.begin(); 
}

void loop()
{
for (int i=0; i< pintablesize; i++)
  {
    pintable[i].run(Keyboard);
  };
}
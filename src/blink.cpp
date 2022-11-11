#include "Arduino.h"

const unsigned long TIME_ON  = 10;
const unsigned long TIME_OFF = 2000;

void setup()
{
    pinMode( LED_BUILTIN, OUTPUT );
}

void loop()
{
    digitalWrite( LED_BUILTIN, HIGH );
    delay( TIME_ON );
    digitalWrite( LED_BUILTIN, LOW );
    delay( TIME_OFF );
}

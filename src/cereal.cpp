#include "Arduino.h"

const unsigned long BAUD_RATE = 9600;

void setup()
{
    Serial.begin( BAUD_RATE );
    while ( !Serial ); // Wait to init
}

void loop()
{
    short available = Serial.available();
    unsigned char buffer[ 64 ];

    if ( available == 0 ) {
        return;
    }

    Serial.readBytes( buffer, available );

    // Transform into the lower case
    for ( short i = 0; i < available; ++i ) {
        if ( buffer[ i ] >= 'A' && buffer[ i ] <= 'Z' ) {
            buffer[ i ] -= 'A' - 'a';
        }
    }

    Serial.write( buffer, available );
}

#include "Arduino.h"
#include "Wire.h"

const unsigned long  SERIAL_BAUD_RATE     =  9600;
const long           SERIAL_TIMEOUT       = 30000;
const size_t         SERIAL_BUFFER_LENGTH =    64;

const uint8_t I2C_ADDR          = 0x40;
const size_t  I2C_BUFFER_LENGTH =   32;


int token( char *buffer, size_t length, size_t &head )
{
    while ( head < length && !isHexadecimalDigit( buffer[ head ] ) ) {
        ++head;
    }

    if ( head >= length ) {
        return -1;
    }

    int result = 0;
    for ( ; head < length && isHexadecimalDigit( buffer[ head ] ) ; ++head ) {
        result <<= 4;
        if ( buffer[ head ] <= '9' ) {
            result += buffer[ head ] - '0';
        } else if ( buffer[ head ] <= 'F' ) {
            result += buffer[ head ] - 'A' + 10;
        } else {
            result += buffer[ head ] - 'a' + 10;
        }
    }
    return result;
}


void setup()
{
    Serial.begin( SERIAL_BAUD_RATE );
    while ( !Serial ); // Wait to init
    Serial.setTimeout( SERIAL_TIMEOUT );

    Wire.begin();
}

void loop()
{
    char buffer[ SERIAL_BUFFER_LENGTH ];
    size_t length = Serial.readBytesUntil( '\n', buffer, SERIAL_BUFFER_LENGTH );
    if ( length == 0 ) {
        return;
    }

    size_t head = 1;
    if ( buffer[ 0 ] == 'r' ) {
        // Read N bytes: `r NN`

        int read_length = token( buffer, length, head );
        if ( read_length <= 0 ) {
            read_length = 1;
        }

        auto read = String();
        while ( read_length >= 0 ) {
            Wire.requestFrom( I2C_ADDR, min( read_length, I2C_BUFFER_LENGTH ) );
            read_length -= I2C_BUFFER_LENGTH;

            while ( Wire.available() )
            {
                unsigned char val = Wire.read();
                if ( val < 16 ) {
                    read += "0";
                }
                read += String( val, HEX ) + " ";
            }
        }

        read.trim();
        read += '\n';
        Serial.write( read.c_str() );

    } else if ( buffer[ 0 ] == 'w' ) {
        // Write bytes: `w XX YY ZZ ...`

        Wire.beginTransmission( I2C_ADDR );

        for ( int byte = token( buffer, length, head ); byte >= 0;
              byte = token( buffer, length, head ) )
        {
            do {
                Wire.write( byte );
                byte >>= 8;
            } while ( byte > 0 );
        }

        Wire.endTransmission( I2C_ADDR );
    }
}

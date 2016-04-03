#include <VirtualWire.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>

#define SENSOR_PIN       8
#define GARAGE          "0"
#define FIRST           "1"
#define SECOND          "2"
#define THIRD           "3"
#define RXPIN           2
#define TXPIN           3

TinyGPS gps;
SoftwareSerial nss( RXPIN, TXPIN );

char input[ 100 ];

void setup()
{   
    vw_set_ptt_inverted(true);   // Required for DR3100
    vw_set_tx_pin(SENSOR_PIN);
    vw_setup(2000);              // Bits per sec
    vw_rx_start();     // Start the receiver PLL running
    
    Serial.begin( 9600 );
}

void loop()
{    
    while( nss.avaliable() ) {
      int c = nss.read();
      if( gps.encode(c) ) {
          long lat, lon;
          unsigned long fix_age, time, date, speed, course;
          unsigned long chars;
          unsigned short sentences, failed_checksum;
           
          // retrieves +/- lat/long in 100000ths of a degree
          gps.get_position(&lat, &lon, &fix_age);
           
          // time in hhmmsscc, date in ddmmyy
          gps.get_datetime(&date, &time, &fix_age);
           
          // returns speed in 100ths of a knot
          speed = gps.speed();
           
          // course in 100ths of a degree
          course = gps.course();
          
          Serial.println( speed );
          Serial.println( course );
      }
    }
    
    while( Serial.available() > 0 ) {
      input[0] = Serial.parseInt() + '0';
      input[1] = '\0';
      Serial.print( "Sending coordinate: " );
      Serial.println( input );
      
      switch( input[0] ) {
             case '0': vw_send( (uint8_t *)GARAGE, strlen( GARAGE ) );
                       vw_wait_tx();
                       delay(1000);
                       break;
             case '1': vw_send( (uint8_t *)FIRST, strlen( FIRST ) );
                       vw_wait_tx();
                       delay(1000);
                       break; 
             case '2': vw_send( (uint8_t *)SECOND, strlen( SECOND ) );
                       vw_wait_tx();
                       delay(1000);
                       break; 
             case '3': vw_send( (uint8_t *)THIRD, strlen( THIRD ) );
                       vw_wait_tx();
                       delay(1000);
                       break; 
             default: Serial.println( "Wrong input" );
      }
  
      Serial.println( "Sending coordinate: " );
      Serial.print( input[0] );  
  }
    
    
}

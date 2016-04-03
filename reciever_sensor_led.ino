#include <VirtualWire.h>
#include <NewPing.h>

#define TRIGGER_PIN    12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN       11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE   70 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define LED_PIN        6
#define FULL_DISTANCE  5
#define STRING_SIZE    200
#define MESSAGE_FULL   "FULL"
#define MESSAGE_EMPTY  "EMPTY"

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  pinMode( LED_PIN, OUTPUT );
  vw_setup( 2000 );
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping_cm(); // Send ping, get ping time in microseconds (uS).
  
  // Print the distance out to the Serial
  Serial.print("Distance: " );
  Serial.print( uS );
  Serial.println( "cm" );
  
  if( uS == 0 ) {
    // This code is to handle the zero error
    pinMode(ECHO_PIN,OUTPUT);
    digitalWrite(ECHO_PIN,LOW);
    pinMode(ECHO_PIN,INPUT);
  } else if( uS < FULL_DISTANCE ) {
    // Set LED
    digitalWrite( LED_PIN, HIGH );
    
    // Transmit message
    Serial.print( "TRANSMITTING MESSAGE: " );
    Serial.println( MESSAGE_FULL );
    vw_send( (byte *)MESSAGE_FULL, strlen( MESSAGE_FULL ) );
    
  } else {
    // Set LED
    digitalWrite( LED_PIN, LOW );
    
    Serial.print( "Transmitting Message: " );
    Serial.println( MESSAGE_EMPTY );
    vw_send( (byte *)MESSAGE_EMPTY, strlen( MESSAGE_EMPTY ) );
  }
}

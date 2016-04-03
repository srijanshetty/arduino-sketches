#include <NewPing.h>

#define TRIGGER_PIN    12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN       11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE   200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define LED_PIN        6
#define FULL_DISTANCE  5

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  pinMode( LED_PIN, OUTPUT );
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping_cm(); // Send ping, get ping time in microseconds (uS).
  Serial.println(uS); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  
  if( uS == 0 ) {
    pinMode(ECHO_PIN,OUTPUT);
    digitalWrite(ECHO_PIN,LOW);
    pinMode(ECHO_PIN,INPUT);
  } else if( uS < FULL_DISTANCE ) {
    digitalWrite( LED_PIN, HIGH );
    Serial.println( "DUSTBIN FULL" );
  } else {
    digitalWrite( LED_PIN, LOW );
    Serial.println( "DUSTBIN EMPTY" );
  }
}

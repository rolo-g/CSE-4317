/*
 * Bit Bangers IR "Kill Switch" Receiver Library
 * github.com/Bit-Bangers-UTA/Senior-Design
 *
 * Authors: 
 * Rolando Rosales
 *
 * Hardware setup:
 * IR receiver data pin connected to GPIO 3
 * 
 * Requires crankyoldgit/IRremoteESP8266@^2.8.6 library
*/

// Libraries ------------------------------------------------------------------

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>

// Defines --------------------------------------------------------------------

#define IR_RX_PIN 3

// Variables & Constants ------------------------------------------------------

decode_results results;
const uint8_t unalive_code = 0xF;
bool LED_STATE = false;

// Structures & Classes -------------------------------------------------------

IRrecv irrecv(IR_RX_PIN);

// Functions ------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("Received IR code: ");
    Serial.println(results.value, HEX); // Print received code in hex

    if (results.value == IR_RX_PIN) { // Toggles LED if code is unalive code
      LED_STATE = !LED_STATE;
      digitalWrite(LED_BUILTIN, LED_STATE ? HIGH : LOW);
    }

    irrecv.resume(); // Receive the next value
  }
}
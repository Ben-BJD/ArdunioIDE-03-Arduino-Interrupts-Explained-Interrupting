#include <Arduino.h>
 
#define LED_PIN 6
#define BUTTON_PIN 2 // This must be an interrupt pin!
 
// These variables are shared with the ISR, so they MUST be 'volatile'
volatile int ledState = LOW;
volatile unsigned long lastStateChange = 0;
 
// This is our Interrupt Service Routine (ISR)
// It must be as fast as possible!
void onInterrupt() {
  // A simple way to debounce the button inside the ISR
  if (millis() - lastStateChange > 50) {
    ledState = !ledState; // Toggle the state
    digitalWrite(LED_PIN, ledState);
    lastStateChange = millis(); // Record the time of the change
  }
}
 
void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
 
  // Attach the interrupt
  // We're using pin 2, our ISR is named 'onInterrupt', and we trigger on a RISING edge
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onInterrupt, RISING);
 
  Serial.begin(9600);
}
 
// The same long, blocking task from before
void timeIntensiveTask() {
  Serial.println("Time intensive running ...");
  for (long i = 0; i < 100000; i++) {
    // Wasting time...
    Serial.println("Time intensive task still running ...");
  }
  Serial.println("Time intensive task finished.");
}
 
void loop() {
  // no button code needed in the loop anymore!
  // The main loop is free to do other things.
  timeIntensiveTask();
}
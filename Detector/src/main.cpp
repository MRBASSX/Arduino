
#include <Arduino.h>
#include "webserver.cpp"

#define LED 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  glow(LED,3,0);
  // put your main code here, to run repeatedly:
}




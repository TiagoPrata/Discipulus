//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ledPulseOn(int ledPin, int _delay) {
  for (int i = 0; i < 256; i++) {
    analogWrite(ledPin, i);
    delay(_delay);
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ledPulseOff(int ledPin, int _delay) {
  for (int i = 0; i < 256; i++) {
    analogWrite(ledPin, 255 - i);
    delay(_delay);
  }
}

void RGBled(byte R, byte G, byte B) {
  analogWrite(Led_RED, R);
  analogWrite(Led_GREEN, G);
  analogWrite(Led_BLUE, B);
}

void preTreino() {
  ledPulseOn(Led_RED, 5);
  ledPulseOff(Led_RED, 5);
  ledPulseOn(Led_GREEN, 5);
  ledPulseOff(Led_GREEN, 5);
  ledPulseOn(Led_BLUE, 5);
  ledPulseOff(Led_BLUE, 5);
}

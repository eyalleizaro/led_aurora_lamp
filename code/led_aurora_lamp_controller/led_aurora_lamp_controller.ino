/*
  LED Aurora Lamp Controller

  Hardware:
  - Arduino Uno R3
  - NeoPixel Ring 16
  - NeoPixel Ring 24
  - DC motor with encoder
  - H-bridge motor driver
  - External 5V power supply

  Install in Arduino IDE:
  - Adafruit NeoPixel library

  Important:
  - Test with low LED brightness first.
  - Use an external 5V supply for the LED rings.
  - Arduino GND and external supply GND must be connected together.
  - If your Tinkercad wiring is different, change the pin constants below.
*/

#include <Adafruit_NeoPixel.h>

// =========================
// NeoPixel pins
// =========================
const byte RING1_PIN = 7;     // RING1 DIN
const byte RING2_PIN = 12;    // RING2 DIN

const int RING1_LEDS = 16;
const int RING2_LEDS = 24;

// Low brightness for safer first tests.
// Increase later only after the circuit works.
const byte LED_BRIGHTNESS = 40;

// NeoPixels are usually GRB, 800 kHz.
Adafruit_NeoPixel ring1(RING1_LEDS, RING1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring2(RING2_LEDS, RING2_PIN, NEO_GRB + NEO_KHZ800);

// =========================
// H-bridge motor pins
// =========================
const byte MOTOR_ENABLE_PIN = 6;  // PWM pin, H-bridge 1-2EN
const byte MOTOR_IN1_PIN = 8;     // H-bridge 1A
const byte MOTOR_IN2_PIN = 9;     // H-bridge 2A

// =========================
// Encoder pins
// =========================
const byte ENCODER_A_PIN = 2;
const byte ENCODER_B_PIN = 3;

volatile long encoderTicks = 0;

// =========================
// Animation settings
// =========================
int motorSpeed = 90;       // 0-255. Start low.
int animationDelay = 35;   // Smaller = faster animation.

// =========================
// Encoder interrupt
// =========================
void encoderAChanged() {
  bool b = digitalRead(ENCODER_B_PIN);

  if (b) {
    encoderTicks++;
  } else {
    encoderTicks--;
  }
}

// =========================
// Color helper
// =========================
uint32_t colorWheel(Adafruit_NeoPixel &strip, byte position) {
  position = 255 - position;

  if (position < 85) {
    return strip.Color(255 - position * 3, 0, position * 3);
  }

  if (position < 170) {
    position -= 85;
    return strip.Color(0, position * 3, 255 - position * 3);
  }

  position -= 170;
  return strip.Color(position * 3, 255 - position * 3, 0);
}

// =========================
// LED helpers
// =========================
void clearRings() {
  ring1.clear();
  ring2.clear();
  ring1.show();
  ring2.show();
}

void setRingColor(Adafruit_NeoPixel &ring, uint32_t color) {
  for (int i = 0; i < ring.numPixels(); i++) {
    ring.setPixelColor(i, color);
  }

  ring.show();
}

void setBothRings(uint32_t color1, uint32_t color2) {
  setRingColor(ring1, color1);
  setRingColor(ring2, color2);
}

// =========================
// Motor helpers
// speed: -255 to 255
// positive = forward
// negative = reverse
// zero = stop
// =========================
void setMotor(int speedValue) {
  speedValue = constrain(speedValue, -255, 255);

  if (speedValue > 0) {
    digitalWrite(MOTOR_IN1_PIN, HIGH);
    digitalWrite(MOTOR_IN2_PIN, LOW);
    analogWrite(MOTOR_ENABLE_PIN, speedValue);
  } else if (speedValue < 0) {
    digitalWrite(MOTOR_IN1_PIN, LOW);
    digitalWrite(MOTOR_IN2_PIN, HIGH);
    analogWrite(MOTOR_ENABLE_PIN, -speedValue);
  } else {
    analogWrite(MOTOR_ENABLE_PIN, 0);
    digitalWrite(MOTOR_IN1_PIN, LOW);
    digitalWrite(MOTOR_IN2_PIN, LOW);
  }
}

// =========================
// Animations
// =========================
void auroraFlow(int loops) {
  for (int step = 0; step < loops * 256; step++) {
    for (int i = 0; i < ring1.numPixels(); i++) {
      byte colorPos = (i * 256 / ring1.numPixels() + step) & 255;
      ring1.setPixelColor(i, colorWheel(ring1, colorPos));
    }

    for (int i = 0; i < ring2.numPixels(); i++) {
      byte colorPos = (i * 256 / ring2.numPixels() + step + 80) & 255;
      ring2.setPixelColor(i, colorWheel(ring2, colorPos));
    }

    ring1.show();
    ring2.show();

    delay(animationDelay);
  }
}

void breathingGlow(uint32_t color1, uint32_t color2) {
  for (int brightness = 5; brightness <= LED_BRIGHTNESS; brightness += 2) {
    ring1.setBrightness(brightness);
    ring2.setBrightness(brightness);

    setBothRings(color1, color2);
    delay(25);
  }

  for (int brightness = LED_BRIGHTNESS; brightness >= 5; brightness -= 2) {
    ring1.setBrightness(brightness);
    ring2.setBrightness(brightness);

    setBothRings(color1, color2);
    delay(25);
  }

  ring1.setBrightness(LED_BRIGHTNESS);
  ring2.setBrightness(LED_BRIGHTNESS);
}

void sparkle(int count) {
  clearRings();

  for (int i = 0; i < count; i++) {
    int pixel1 = random(ring1.numPixels());
    int pixel2 = random(ring2.numPixels());

    ring1.clear();
    ring2.clear();

    ring1.setPixelColor(pixel1, ring1.Color(0, 80, 255));
    ring2.setPixelColor(pixel2, ring2.Color(0, 255, 120));

    ring1.show();
    ring2.show();

    delay(60);
  }

  clearRings();
}

void oppositeRotationEffect() {
  for (int step = 0; step < 120; step++) {
    ring1.clear();
    ring2.clear();

    int p1 = step % ring1.numPixels();
    int p2 = (ring2.numPixels() - 1) - (step % ring2.numPixels());

    ring1.setPixelColor(p1, ring1.Color(0, 100, 255));
    ring2.setPixelColor(p2, ring2.Color(0, 255, 80));

    ring1.show();
    ring2.show();

    delay(45);
  }
}

// =========================
// Setup
// =========================
void setup() {
  Serial.begin(9600);

  pinMode(MOTOR_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_IN1_PIN, OUTPUT);
  pinMode(MOTOR_IN2_PIN, OUTPUT);

  pinMode(ENCODER_A_PIN, INPUT_PULLUP);
  pinMode(ENCODER_B_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), encoderAChanged, RISING);

  ring1.begin();
  ring2.begin();

  ring1.setBrightness(LED_BRIGHTNESS);
  ring2.setBrightness(LED_BRIGHTNESS);

  clearRings();
  setMotor(0);

  randomSeed(analogRead(A0));

  Serial.println("LED Aurora Lamp started");
  Serial.println("Testing LEDs at low brightness");

  setBothRings(ring1.Color(0, 0, 80), ring2.Color(0, 80, 0));
  delay(800);
  clearRings();

  Serial.println("Starting motor at low speed");
  setMotor(motorSpeed);
}

// =========================
// Main loop
// =========================
void loop() {
  setMotor(motorSpeed);
  auroraFlow(1);

  breathingGlow(ring1.Color(0, 80, 255), ring2.Color(0, 255, 100));

  setMotor(-motorSpeed);
  oppositeRotationEffect();

  setMotor(motorSpeed);
  sparkle(40);

  Serial.print("Encoder ticks: ");
  Serial.println(encoderTicks);
}

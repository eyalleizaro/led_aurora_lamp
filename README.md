# LED Aurora Lamp

A programmable LED aurora lamp built with an Arduino Uno, two NeoPixel LED rings, a DC motor with encoder, an H-bridge motor driver, an external 5V power supply, and a 3D-printed lamp body.

## Tinkercad link

https://www.tinkercad.com/things/8Uebq5KBjwT-led-aurora-lamp


## Features

- Aurora-style LED animations
- Two NeoPixel rings: 16 LEDs and 24 LEDs
- Motor movement controlled by an H-bridge driver
- Encoder pins prepared for future speed/position feedback
- Modular electronics documentation
- Arduino-based control code

## Main Components

- Arduino Uno R3
- NeoPixel Ring 16
- NeoPixel Ring 24
- DC motor with encoder
- H-bridge motor driver
- 5V external power supply
- 1000 uF polarized capacitor
- Jumper wires
- Lamp body / 3D-printed parts

## Repository Structure

```text
led-aurora-lamp/
├── README.md
├── code/
│   └── led_aurora_lamp_controller/
│       └── led_aurora_lamp_controller.ino
├── docs/
│   ├── build_instructions.md
│   ├── safety.md
│   └── wiring.md
├── electronics/
│   ├── bom.csv
│   └── LED_AURORA_LAMP.pdf
└── 3d_models/
    └── README.md
```

## Getting Started

1. Open the schematic in `electronics/LED_AURORA_LAMP.pdf`.
2. Read `docs/wiring.md` and verify the pin map.
3. Install the **Adafruit NeoPixel** Arduino library.
4. Open `code/led_aurora_lamp_controller/led_aurora_lamp_controller.ino`.
5. Upload the code to the Arduino Uno.
6. Test the LED rings first.
7. Test the motor at low speed.
8. Only close the lamp body after all electronics work safely.

## Safety

This project uses bright LEDs and a moving motor. Do not look directly into bright LEDs at high brightness. Disconnect power before changing wires. Keep the motor and moving parts away from fingers, loose clothing, and cables.

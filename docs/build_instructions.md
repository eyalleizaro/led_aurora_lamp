# Build Instructions

This guide explains how to build the LED Aurora Lamp electronics and prepare the first working version of the project.

The project uses an Arduino Uno, two NeoPixel rings, a DC motor with encoder, an H-bridge motor driver, an external 5V supply, and a 1000 uF capacitor.

---

## 1. Parts Used

Main parts:

- 1 x Arduino Uno R3
- 1 x NeoPixel Ring 16
- 1 x NeoPixel Ring 24
- 1 x DC motor with encoder
- 1 x H-bridge motor driver
- 1 x 5V power supply
- 1 x 1000 uF polarized capacitor
- Jumper wires
- Lamp body / 3D-printed parts

---

## 2. Project Overview

The circuit has three main parts:

1. **Arduino Uno**  
   Controls the LED animations and sends direction/speed commands to the motor driver.

2. **NeoPixel rings**  
   Create the aurora light effect. Each ring has power, ground, data input, and data output.

3. **Motor + H-bridge driver**  
   The H-bridge lets the Arduino control motor speed and direction. The encoder pins can later be used for feedback.

---

## 3. Before Powering the Circuit

Before connecting power:

- Check that all grounds are connected together.
- Check the polarity of the 1000 uF capacitor.
- Check that the NeoPixel VDD pins are connected to 5V.
- Check that the NeoPixel VSS pins are connected to ground.
- Check that the motor power is connected through the H-bridge driver.
- Start with low LED brightness in code.
- Start with low motor speed in code.
- Disconnect power before moving wires.

---

## 4. Build Step 1: Prepare Power Rails

Create two main power rails:

- `P1+` = positive 5V rail
- `P1-` = ground / negative rail

Connect:

- Power supply `+` to `P1+`
- Power supply `-` to `P1-`
- Arduino `GND` to `P1-`
- H-bridge ground pins to `P1-`
- NeoPixel VSS pins to `P1-`

The Arduino, NeoPixel rings, H-bridge, and external power supply must share a common ground.

---

## 5. Build Step 2: Add the Capacitor

Place the 1000 uF capacitor across the power rail:

| Capacitor side | Connect to |
|---|---|
| Positive `+` | `P1+` |
| Negative `-` | `P1-` |

This helps reduce voltage drops when the LEDs change brightness.

Important: electrolytic capacitors are polarized. Do not reverse the positive and negative legs.

---

## 6. Build Step 3: Connect the NeoPixel Rings

Each NeoPixel ring has:

| NeoPixel Pin | Connect to |
|---|---|
| VDD | `P1+` / 5V |
| VSS | `P1-` / Ground |
| DIN | Arduino data pin |
| DOUT | Optional output to another NeoPixel strip/ring |

The default code assumes:

| Part | Arduino pin |
|---|---|
| RING1 DIN | D7 |
| RING2 DIN | D12 |

If your Tinkercad wiring is different, update the pin numbers at the top of the Arduino code.

---

## 7. Build Step 4: Connect the H-Bridge Motor Driver

The H-bridge has two sides. This project uses one side for one motor.

Default code pin map:

| H-bridge pin/function | Arduino pin |
|---|---|
| 1-2EN / motor enable / speed | D6 |
| 1A / direction input 1 | D8 |
| 2A / direction input 2 | D9 |

Motor output pins:

| H-bridge output | Motor |
|---|---|
| 1Y | Motor terminal 1 |
| 2Y | Motor terminal 2 |

Power pins:

| H-bridge pin | Connect to |
|---|---|
| VCC1 | Arduino 5V / logic 5V |
| VCC2 | `P1+` motor power |
| GND pins | `P1-` |

---

## 8. Build Step 5: Connect the Motor Encoder

The default code prepares these pins for the encoder:

| Encoder signal | Arduino pin |
|---|---|
| Encoder A | D2 |
| Encoder B | D3 |

The encoder is optional for the first version. The motor will still work without using encoder feedback.

---

## 9. Build Step 6: Upload the Code

1. Install the **Adafruit NeoPixel** library in the Arduino IDE.
2. Open `code/led_aurora_lamp_controller/led_aurora_lamp_controller.ino`.
3. Select board: **Arduino Uno**.
4. Select the correct COM port.
5. Upload the code.

---

## 10. Build Step 7: Test Gradually

Recommended test order:

1. Power the Arduino only.
2. Upload the code.
3. Test RING1 with low brightness.
4. Test RING2 with low brightness.
5. Connect the external 5V supply.
6. Test both rings together.
7. Test the motor at low speed.
8. Place the electronics inside the lamp body only after everything works.

---

## 11. Troubleshooting

### LEDs do not turn on

- Check VDD and VSS.
- Check that Arduino GND and external power supply ground are connected together.
- Check that the DIN pin number in the code matches the real wire.
- Check that the NeoPixel library is installed.

### LEDs flicker or reset

- Use the 1000 uF capacitor across 5V and ground.
- Lower the brightness in code.
- Use a stronger 5V supply.
- Keep LED power wires short.

### Motor does not spin

- Check H-bridge VCC1, VCC2, and GND.
- Check motor output wires.
- Check D6, D8, and D9.
- Try increasing the motor speed value in code.

### Arduino resets when motor starts

- The motor may draw too much current.
- Use a separate motor power rail through the H-bridge.
- Make sure all grounds are common.
- Add proper decoupling and keep motor wires away from signal wires.

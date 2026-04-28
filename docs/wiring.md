# Wiring Guide

This file documents the wiring for the LED Aurora Lamp.

The schematic is saved in:

```text
electronics/LED_AURORA_LAMP.pdf
```

The bill of materials is saved in:

```text
electronics/bom.csv
```

---

## Main Power

| Net / label | Meaning |
|---|---|
| `P1+` | 5V positive rail |
| `P1-` | Ground / negative rail |

Connect the Arduino ground, NeoPixel ground, H-bridge ground, motor supply ground, and power supply negative together.

---

## Power Supply and Capacitor

| Part | Pin | Connect to |
|---|---|---|
| P1 power supply | `+` | `P1+` |
| P1 power supply | `-` | `P1-` |
| C1 1000 uF capacitor | `+` | `P1+` |
| C1 1000 uF capacitor | `-` | `P1-` |

---

## NeoPixel Rings

| Part | Pin | Connect to |
|---|---|---|
| RING1 | VDD | `P1+` |
| RING1 | VSS | `P1-` |
| RING1 | DIN | Arduino D7 |
| RING1 | DOUT | Not required for default code |
| RING2 | VDD | `P1+` |
| RING2 | VSS | `P1-` |
| RING2 | DIN | Arduino D12 |
| RING2 | DOUT | Not required for default code |

If you connect RING1 DOUT into RING2 DIN, change the code to use one combined strip instead of two separate rings.

---

## H-Bridge Motor Driver

Default code pin map:

| H-bridge pin/function | Connect to |
|---|---|
| VCC1 | 5V logic |
| VCC2 | `P1+` motor power |
| GND1-GND4 | `P1-` |
| 1-2EN | Arduino D6 |
| 1A | Arduino D8 |
| 2A | Arduino D9 |
| 1Y | Motor terminal 1 |
| 2Y | Motor terminal 2 |
| 3-4EN, 3A, 4A, 3Y, 4Y | Not used in the default code |

---

## Motor With Encoder

The DC motor has motor terminals and encoder pins. The exact pin names depend on the motor part in Tinkercad.

Default code assumptions:

| Motor/encoder function | Connect to |
|---|---|
| Motor terminal 1 | H-bridge 1Y |
| Motor terminal 2 | H-bridge 2Y |
| Encoder A | Arduino D2 |
| Encoder B | Arduino D3 |
| Encoder VCC | 5V |
| Encoder GND | `P1-` |

The first version of the code does not require encoder feedback for the motor animation, but it counts encoder ticks so you can debug it later.

---

## Important Notes

- Keep LED brightness low during the first test.
- Do not power many LEDs from the Arduino 5V pin.
- Use the external 5V power supply for the LED rings.
- Always connect all grounds together.
- If a pin in your Tinkercad design is different, change the constants at the top of the Arduino code.

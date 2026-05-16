# 🔌 CIRCUIT DIAGRAM & HARDWARE CONNECTIONS

## Complete Hardware Wiring Guide

### Pin Configuration Summary

```
ARDUINO UNO CONNECTIONS:

Analog Pins (A0-A3) - Voltage Sensors:
├─ A0 → Voltage Sensor 1 (Signal)
├─ A1 → Voltage Sensor 2 (Signal)
├─ A2 → Voltage Sensor 3 (Signal)
└─ A3 → Voltage Sensor 4 (Signal)

Digital Pins:
├─ Pin 8 → Relay Module (Signal/IN)
└─ GND → Common Ground (All devices)

Power:
├─ 5V → Relay VCC, Sensor VCC
└─ GND → Relay GND, Sensor GND
```

---

## Detailed Wiring Instructions

### 1️⃣ VOLTAGE SENSORS (AC 0-300V)

#### Single Sensor Connection:

```
Voltage Sensor Module
├─ VCC (Red wire)     → Arduino 5V
├─ GND (Black wire)   → Arduino GND
└─ Signal (Yellow)    → Arduino A0/A1/A2/A3
```

#### All 4 Sensors:

```
SENSOR 1 (Cable A):
├─ VCC   → Arduino 5V
├─ GND   → Arduino GND
└─ SIG   → Arduino A0

SENSOR 2 (Cable B):
├─ VCC   → Arduino 5V
├─ GND   → Arduino GND
└─ SIG   → Arduino A1

SENSOR 3 (Cable C):
├─ VCC   → Arduino 5V
├─ GND   → Arduino GND
└─ SIG   → Arduino A2

SENSOR 4 (Ground/Neutral):
├─ VCC   → Arduino 5V
├─ GND   → Arduino GND
└─ SIG   → Arduino A3
```

⚠️ **Safety Warning**: 
- Always use proper voltage divider circuits
- Never connect high voltage (>250V) directly to Arduino
- Use isolation transformers if needed
- Test with multimeter before Arduino connection

---

### 2️⃣ RELAY MODULE (5V)

#### Pin Configuration:

```
Relay Module (Usually 4-pin):
├─ GND (Black)  → Arduino GND
├─ VCC (Red)    → Arduino 5V
├─ IN (Signal)  → Arduino Pin 8
└─ COM (Common) → Power Supply Input

Relay Switching:
├─ COM (Common)     → Power Supply
├─ NO (Normally Open) → Load/Alarm Circuit
└─ NC (Normally Closed) → Optional
```

#### Relay Operation:

```
IN Pin Logic:
├─ LOW (0V)  → Relay OFF  → Power disconnected
└─ HIGH (5V) → Relay ON   → Power connected

Arduino Code:
├─ digitalWrite(8, LOW)  → Turn relay off
└─ digitalWrite(8, HIGH) → Turn relay on
```

---

### 3️⃣ ARDUINO UNO PINOUT

```
                    ARDUINO UNO
        ┌─────────────────────────────┐
    5V  │ ■                           │ RX(0)
    3V  │ ■                           │ TX(1)
   GND  │ ■ ▼ GND                    │ 2
   AREF │ ■                           │ 3
    A0  │ ■                           │ 4
    A1  │ ■                           │ 5
    A2  │ ■                           │ 6
    A3  │ ■                           │ 7
    A4  │ ■                           │ 8 ◄─── RELAY
    A5  │ ■                           │ 9
       │ ■ ◄─── RESET              │ 10
       │ ■                           │ 11
       │ ■                           │ 12
       │ ■                           │ 13 (LED)
        └─────────────────────────────┘

▲ Voltage Sensors Connected Here
```

---

## Schematic Text Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                    SYSTEM ARCHITECTURE                          │
└─────────────────────────────────────────────────────────────────┘

                    UNDERGROUND CABLES
    ┌────────────┬────────────┬────────────┬────────────┐
    │  CABLE A   │  CABLE B   │  CABLE C   │  NEUTRAL   │
    │ (Phase 1)  │ (Phase 2)  │ (Phase 3)  │  (Ground)  │
    └────┬───────┴────┬───────┴────┬───────┴────┬───────┘
         │            │            │            │
    ┌────▼─┐     ┌────▼─┐     ┌────▼─┐     ┌────▼─┐
    │VOLT  │     │VOLT  │     │VOLT  │     │VOLT  │
    │SEN 1 │     │SEN 2 │     │SEN 3 │     │SEN 4 │
    │0-300V│     │0-300V│     │0-300V│     │0-300V│
    └──┬───┘     └──┬───┘     └──┬───┘     └──┬───┘
       │ SIG        │ SIG        │ SIG        │ SIG
       │            │            │            │
       └────┬───────┴───────┬────┴────────────┴─┐
            │               │                  │
         ┌──▼───────────────▼──────────────────▼──┐
         │                                        │
         │         ARDUINO UNO                   │
         │                                        │
         │  A0  A1  A2  A3       GND   5V        │
         │  ▼   ▼   ▼   ▼        ▼     ▼         │
         │ [SIG][SIG][SIG][SIG] [GND][PWR]       │
         │                                        │
         │  Pin 8 (RELAY CONTROL) ──────┐        │
         └────────────────────────────────┼───────┘
                                          │
                                       ┌──▼────┐
                                       │ RELAY  │
                                       │ MODULE │
                                       │ 5V TTL │
                                       └──┬─────┘
                                          │
                    ┌─────────────────────┴──────────────┐
                    │                                    │
                ┌───▼────┐                          ┌────▼────┐
                │ ALARM  │                          │  LOAD   │
                │ BUZZER │                          │ CIRCUIT │
                │ LED    │                          │ BREAKER │
                └────────┘                          └─────────┘
```

---

## Step-by-Step Assembly Guide

### Phase 1: Prepare Arduino
```
1. ✓ Get Arduino Uno board
2. ✓ Install Arduino IDE on computer
3. ✓ Connect USB cable
4. ✓ Test with blink sketch
```

### Phase 2: Connect Sensors
```
For each sensor (1-4):
1. ✓ Identify VCC, GND, Signal wires
2. ✓ Connect VCC to Arduino 5V rail
3. ✓ Connect GND to Arduino GND rail
4. ✓ Connect Signal to A0/A1/A2/A3
5. ✓ Use breadboard for organization
```

### Phase 3: Connect Relay
```
1. ✓ Connect Relay GND to Arduino GND
2. ✓ Connect Relay VCC to Arduino 5V
3. ✓ Connect Relay IN to Arduino Pin 8
4. ✓ Test relay click sound
```

### Phase 4: Upload Code
```
1. ✓ Open fault_detection.ino
2. ✓ Select Arduino Uno board
3. ✓ Select correct COM port
4. ✓ Click Upload
5. ✓ Watch TX/RX LEDs flash
```

### Phase 5: Test System
```
1. ✓ Open Serial Monitor
2. ✓ Check voltage readings
3. ✓ Verify relay activation
4. ✓ Test with known voltage sources
```

---

## Power Supply Requirements

```
Arduino Uno:
├─ Supply: 7-12V DC (USB or External)
├─ Current: ~100-200mA
└─ Recommendation: 5V/1A USB power

Relay Module:
├─ Supply: 5V DC
├─ Current: ~50-100mA
└─ Source: Arduino 5V pin

Voltage Sensors:
├─ Supply: 5V DC each
├─ Current: ~10-20mA each (×4 = 40-80mA)
└─ Source: Arduino 5V pin

Total Current Draw:
├─ Arduino: 100mA
├─ Relay: 80mA
├─ Sensors: 80mA
└─ TOTAL: ~260mA
```

**Recommendation**: Use external 5V/2A power supply connected to Arduino barrel jack

---

## Troubleshooting Connection Issues

### Problem: ADC reads 0
```
Solution:
├─ Check sensor wiring
├─ Verify 5V supply to sensor
├─ Test sensor with multimeter
├─ Check A0-A3 pin connection
└─ Use shorter jumper wires
```

### Problem: Relay not clicking
```
Solution:
├─ Check 5V supply to relay
├─ Test Pin 8 with LED
├─ Check relay IN connection
├─ Verify relay module power
└─ Test with digitalWrite(8,HIGH)
```

### Problem: Unstable readings
```
Solution:
├─ Add capacitor (100µF) across sensor power
├─ Use shielded cables
├─ Check for loose connections
├─ Reduce sampling speed
└─ Increase smoothing filter
```

---

## Advanced: Adding Capacitors for Stability

```
Add 100µF electrolytic capacitors:

SENSOR SIDE:
    5V ──┬──────────── VCC
         │
         C (100µF)
         │
        GND ─────────── GND

RELAY SIDE:
    5V ──┬──────────── VCC
         │
         C (100µF)
         │
        GND ─────────── GND
```

---

## Safety Checklist Before Power On

- [ ] All connections verified with multimeter
- [ ] No loose wires near power lines
- [ ] Sensors properly grounded
- [ ] Relay tested separately
- [ ] Code uploaded successfully
- [ ] Serial Monitor responding
- [ ] Emergency shutdown ready
- [ ] Proper ventilation
- [ ] No flammable materials nearby
- [ ] Adult supervision if high voltage

---

## Testing Procedure

```
TEST 1: Sensor Reading
├─ Connect known voltage to sensor 1
├─ Check Serial Monitor for reading
├─ Verify ±5% accuracy
└─ Repeat for sensors 2-4

TEST 2: Relay Control
├─ Manually trigger fault (lower voltage)
├─ Listen for relay click
├─ Verify relay activation
└─ Check relay output with multimeter

TEST 3: Threshold Response
├─ Set voltage below threshold
├─ Verify relay activates automatically
├─ Observe Serial Monitor
└─ Test recovery when voltage normalizes

TEST 4: Stability
├─ Run system for 1 hour
├─ Monitor for false triggers
├─ Check for calibration drift
└─ Adjust if needed
```

---

## Parts List & Where to Buy

| Component | Qty | Source | Cost |
|-----------|-----|--------|------|
| Arduino Uno | 1 | Amazon, Local | $25 |
| AC Voltage Sensor (0-300V) | 4 | AliExpress, Amazon | $40 |
| 5V Relay Module | 1 | Amazon, eBay | $5 |
| Jumper Wires (Pack) | 1 | Amazon | $5 |
| USB Cable | 1 | Amazon | $5 |
| Breadboard | 1 | Amazon | $5 |
| Capacitors (100µF) | 5 | Local Electronics | $2 |
| Resistors (1K, 10K) | 20 | Local Electronics | $2 |
| Buzzer (Optional) | 1 | Amazon | $3 |
| LEDs (Optional) | 5 | Amazon | $2 |
| **TOTAL** | | | **~$94** |

---

**Last Updated**: January 2025

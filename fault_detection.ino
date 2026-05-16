// Fault Detection in Underground Cables Using 4 Voltage Sensors and Relay
// Arduino Uno Code

// Pin definitions
const int sensor1Pin = A0;  // Analog pin for Voltage Sensor 1
const int sensor2Pin = A1;  // Analog pin for Voltage Sensor 2
const int sensor3Pin = A2;  // Analog pin for Voltage Sensor 3
const int sensor4Pin = A3;  // Analog pin for Voltage Sensor 4
const int relayPin = 8;     // Digital pin for Relay control

// Voltage threshold (in volts) - if voltage drops below this, fault is detected
const float voltageThreshold = 200.0;

// Reference voltage (Arduino works with 5V)
const float refVoltage = 5.0;

// ADC resolution (10-bit = 1024 levels)
const int adcResolution = 1024;

// Voltage divider calibration (adjust based on your voltage sensor)
const float calibrationFactor = 58.8;  // For typical 0-300V sensor (adjust accordingly)

// Variables to store sensor readings
float voltage1 = 0;
float voltage2 = 0;
float voltage3 = 0;
float voltage4 = 0;

// Fault detection variables
bool fault1 = false;
bool fault2 = false;
bool fault3 = false;
bool fault4 = false;
bool systemFault = false;

// Smoothing variables (for stable readings)
const int numReadings = 10;
float readings1[numReadings];
float readings2[numReadings];
float readings3[numReadings];
float readings4[numReadings];
int readIndex = 0;
float sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
float avg1 = 0, avg2 = 0, avg3 = 0, avg4 = 0;

void setup() {
  // Initialize Serial communication at 9600 baud
  Serial.begin(9600);
  
  // Set relay pin as output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Relay off initially
  
  // Initialize smoothing arrays
  for (int i = 0; i < numReadings; i++) {
    readings1[i] = 0;
    readings2[i] = 0;
    readings3[i] = 0;
    readings4[i] = 0;
  }
  
  delay(1000);  // Wait for sensors to stabilize
  
  Serial.println("=========================================");
  Serial.println("UNDERGROUND CABLE FAULT DETECTION SYSTEM");
  Serial.println("=========================================");
  Serial.println("System initialized successfully!");
  Serial.println();
}

void loop() {
  // Read analog values from all four sensors
  int rawValue1 = analogRead(sensor1Pin);
  int rawValue2 = analogRead(sensor2Pin);
  int rawValue3 = analogRead(sensor3Pin);
  int rawValue4 = analogRead(sensor4Pin);
  
  // Convert analog readings to voltage
  voltage1 = convertToVoltage(rawValue1);
  voltage2 = convertToVoltage(rawValue2);
  voltage3 = convertToVoltage(rawValue3);
  voltage4 = convertToVoltage(rawValue4);
  
  // Apply smoothing filter to get average values
  updateSmoothing(voltage1, voltage2, voltage3, voltage4);
  
  // Detect faults
  checkFaults();
  
  // Control relay based on fault detection
  controlRelay();
  
  // Display readings on Serial Monitor
  displayReadings();
  
  // Wait before next reading (sampling interval)
  delay(500);  // 500ms = 2 readings per second
}

// Function to convert ADC value to voltage
float convertToVoltage(int rawValue) {
  float voltage = (rawValue / (float)adcResolution) * refVoltage * calibrationFactor;
  return voltage;
}

// Function to apply smoothing filter (moving average)
void updateSmoothing(float val1, float val2, float val3, float val4) {
  // Subtract the last reading
  sum1 -= readings1[readIndex];
  sum2 -= readings2[readIndex];
  sum3 -= readings3[readIndex];
  sum4 -= readings4[readIndex];
  
  // Add new readings
  readings1[readIndex] = val1;
  readings2[readIndex] = val2;
  readings3[readIndex] = val3;
  readings4[readIndex] = val4;
  
  sum1 += readings1[readIndex];
  sum2 += readings2[readIndex];
  sum3 += readings3[readIndex];
  sum4 += readings4[readIndex];
  
  // Advance to next position
  readIndex = (readIndex + 1) % numReadings;
  
  // Calculate average
  avg1 = sum1 / numReadings;
  avg2 = sum2 / numReadings;
  avg3 = sum3 / numReadings;
  avg4 = sum4 / numReadings;
}

// Function to check for faults
void checkFaults() {
  // Check if any voltage is below threshold
  fault1 = (avg1 < voltageThreshold);
  fault2 = (avg2 < voltageThreshold);
  fault3 = (avg3 < voltageThreshold);
  fault4 = (avg4 < voltageThreshold);
  
  // System fault occurs if any cable has a fault
  systemFault = fault1 || fault2 || fault3 || fault4;
}

// Function to control relay
void controlRelay() {
  if (systemFault) {
    // Fault detected - activate relay (turn on)
    digitalWrite(relayPin, HIGH);
  } else {
    // No fault - deactivate relay (turn off)
    digitalWrite(relayPin, LOW);
  }
}

// Function to display readings on Serial Monitor
void displayReadings() {
  // Print timestamp
  Serial.print("Time: ");
  Serial.print(millis() / 1000);
  Serial.println("s");
  
  // Print voltage readings
  Serial.print("Sensor 1 (Cable A): ");
  Serial.print(avg1, 2);
  Serial.print("V - Status: ");
  Serial.println(fault1 ? "FAULT" : "OK");
  
  Serial.print("Sensor 2 (Cable B): ");
  Serial.print(avg2, 2);
  Serial.print("V - Status: ");
  Serial.println(fault2 ? "FAULT" : "OK");
  
  Serial.print("Sensor 3 (Cable C): ");
  Serial.print(avg3, 2);
  Serial.print("V - Status: ");
  Serial.println(fault3 ? "FAULT" : "OK");
  
  Serial.print("Sensor 4 (Ground): ");
  Serial.print(avg4, 2);
  Serial.print("V - Status: ");
  Serial.println(fault4 ? "FAULT" : "OK");
  
  // Print system status
  Serial.print("RELAY STATUS: ");
  Serial.println(systemFault ? "ACTIVATED (FAULT DETECTED!)" : "OFF (NORMAL)");
  
  Serial.println("=========================================");
}

// Optional: Function for advanced fault analysis
void analyzeFaultPattern() {
  // Calculate voltage differences between sensors
  float diff12 = abs(avg1 - avg2);
  float diff23 = abs(avg2 - avg3);
  float diff34 = abs(avg3 - avg4);
  
  // Detect type of fault
  if (diff12 > 20) {
    Serial.println("⚠ WARNING: Abnormal voltage difference between Sensor 1 and 2");
  }
  if (diff23 > 20) {
    Serial.println("⚠ WARNING: Abnormal voltage difference between Sensor 2 and 3");
  }
  if (diff34 > 20) {
    Serial.println("⚠ WARNING: Abnormal voltage difference between Sensor 3 and 4");
  }
}

/* 
CALIBRATION INSTRUCTIONS:
1. Measure actual voltage at each sensor point using a multimeter
2. Note the Arduino ADC reading and actual voltage
3. Calculate calibrationFactor = (Actual Voltage * 1024) / (ADC Reading * 5)
4. Update the calibrationFactor variable with your calculated value

HARDWARE CONNECTIONS:
- Voltage Sensor 1 → Arduino Analog Pin A0
- Voltage Sensor 2 → Arduino Analog Pin A1
- Voltage Sensor 3 → Arduino Analog Pin A2
- Voltage Sensor 4 → Arduino Analog Pin A3
- Relay Module Ground → Arduino Ground
- Relay Module VCC → Arduino 5V
- Relay Module Signal → Arduino Digital Pin 8
- Relay Module Common (C) → Power Supply
- Relay Module Normally Open (NO) → Alarm/Load
*/

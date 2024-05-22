#define BLYNK_TEMPLATE_ID "TMPL3_HOIloWD"
#define BLYNK_TEMPLATE_NAME "crop irrigation"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Blynk Auth Token
char auth[] = "T9T8Vc2xNrUquTAxgUc_u9BZ6OuX4Hka";

// Your WiFi credentials
char ssid[] = "Nithish";
char pass[] = "12345678";

// Define the analog pin connected to the soil moisture sensor
const int soilMoisturePin = 34;
// Define the digital pins connected to the motor driver
const int motorPin1 = 25;  // IN1 on the L298N
const int motorPin2 = 26;  // IN2 on the L298N
const int enablePin = 27;  // ENA on the L298N (PWM)

// Variables to store the sensor reading
int sensorValue = 0;
float soilMoisturePercent = 0.0;
bool manualControl = false;  // Flag to indicate manual control state

BlynkTimer timer;

// Function to read soil moisture and update Blynk
void readSoilMoisture() {
  // Read the analog value from the sensor
  sensorValue = analogRead(soilMoisturePin);
  
  // Convert the analog value to a percentage
  soilMoisturePercent = map(sensorValue, 4095, 0, 0, 100);

  // Print the values to the Serial Monitor
  Serial.print("Soil Moisture Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" - ");
  Serial.print(soilMoisturePercent);
  Serial.println("%");

  // Update the Blynk app with the soil moisture percentage
  Blynk.virtualWrite(V0, soilMoisturePercent);

  // Control the motor speed based on soil moisture percentage if not in manual control
  if (!manualControl) {
    if (soilMoisturePercent >= 50) {
      // Reduced speed before 80%
      ledcWrite(0, 0);  // 50% speed
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      Serial.println("Motor OFF");
    } else if (soilMoisturePercent >= 40) {
      // Full speed at or above 80%
      ledcWrite(0,80);  // Full speed
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      Serial.println("Motorn is ON");
    }
    else  {
      // Full speed at or above 80%
      ledcWrite(0, 150);  // Full speed
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      Serial.println("Motor ON: Full speed (100%)");
  }
}
}
// Blynk function to control the motor manually
BLYNK_WRITE(V1) {
  int motorState = param.asInt();
  manualControl = motorState == 1;

  if (motorState == 1) {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    ledcWrite(0, 255);  // Full speed when manually turned on
    Serial.println("Manual Control: Motor ON at full speed");
  } else {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    ledcWrite(0, 0);  // Turn off motor
    Serial.println("Manual Control: Motor OFF");
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Initialize PWM for motor speed control
  ledcSetup(0, 5000, 8);  // Channel 0, 5kHz, 8-bit resolution
  ledcAttachPin(enablePin, 0);

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);

  // Optionally, you can configure the analog resolution
  analogReadResolution(12);  // Default is 12 bits (0-4095)

  // Setup a function to be called every second
  timer.setInterval(1000L, readSoilMoisture);
}

void loop() {
  // Run Blynk
  Blynk.run();
  // Run timer
  timer.run();
}
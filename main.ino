include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 or 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Pin definitions
const int mqSensorPin = A0;  // Analog input pin from MQ sensor
const int buzzerPin = 8;     // Digital output pin for buzzer

// Threshold value for gas detection (adjust based on your calibration)
const int gasThreshold = 300; 

void setup() {
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize the I2C LCD
  lcd.init();
  lcd.backlight();
  
  // Optional: Serial monitor output for debugging/calibration
  Serial.begin(9600);
}

void loop() {
  // Read current analog gas level (0 to 1023)
  int gasLevel = analogRead(mqSensorPin);
  
  // Display the Gas Level on Row 1
  lcd.setCursor(0, 0);
  lcd.print("Gas Level: ");
  lcd.print(gasLevel);
  lcd.print("   "); // Clear trailing characters if value drops
  
  // Process threshold behavior and update Status on Row 2
  lcd.setCursor(0, 1);
  if (gasLevel > gasThreshold) {
    lcd.print("Status: ALERT  ");
    digitalWrite(buzzerPin, HIGH); // Turn buzzer ON
  } else {
    lcd.print("Status: NORMAL ");
    digitalWrite(buzzerPin, LOW);  // Turn buzzer OFF
  }
  
  // Print to computer serial monitor for debugging
  Serial.print("Current Gas Level: ");
  Serial.println(gasLevel);
  
  delay(500); // 0.5-second sampling rate
}

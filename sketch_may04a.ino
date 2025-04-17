#include <Wire.h>
#include <LiquidCrystal.h>

// Define the I2C address for the LCD
#define I2C_ADDR    0x27
#define BACKLIGHT_PIN -1 // Set to -1 to disable backlight control

// Define the LCD size (number of columns and rows)
#define LCD_COLUMNS 16
#define LCD_ROWS    2

// Define the pin for the soil moisture sensor
#define SOIL_MOISTURE_PIN A0

void setup() {
  Serial.begin(115200); // Initialize serial communication

  // Initialize the LCD
//  LiquidCrystal lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);
  lcd.init(); // Initialize the LCD without creating an instance

  // Turn on the backlight if the backlight control pin is defined
  #if BACKLIGHT_PIN >= 0
    pinMode(BACKLIGHT_PIN, OUTPUT);
    digitalWrite(BACKLIGHT_PIN, HIGH);
  #endif

  // Print initial message on the LCD
  lcd.print("Soil Moisture:");

  // Set up WiFi connection if needed
  // connectToWiFi();
}

void loop() {
 // LiquidCrystal lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS); // Create LCD instance in loop
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN); // Read soil moisture sensor
  int moisturePercentage = map(soilMoistureValue+100, 0, 1023, 0, 100); // Map sensor value to percentage

  printToSerial(moisturePercentage); // Print to serial monitor
  updateLCD(moisturePercentage, lcd); // Update LCD display

  delay(1000); // Delay for stability
}

void printToSerial(int moisturePercentage) {
  Serial.print("Soil Moisture Percentage: ");
  Serial.println(moisturePercentage);
}

void updateLCD(int moisturePercentage, LiquidCrystal &lcd) {
  lcd.setCursor(0, 1);
  lcd.print("Moisture: ");
  lcd.print(moisturePercentage);
  lcd.print("%");
}

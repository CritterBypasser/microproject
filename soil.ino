const int sensor_pin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  Serial.begin(9600);
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("System ready!");
}

void loop() {
  float moisture_percentage;

  moisture_percentage = ( ( (analogRead(sensor_pin)/5) *10) );
  Serial.print(analogRead(sensor_pin));
  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");

  delay(1000);
  lcd.clear(); 
  lcd.setCursor(0,0);
//  lcd.print("Moisture = ");
//  lcd.print(moisture_percentage);
//  lcd.println("%");
//  
  if (moisture_percentage >=600)
    lcd.print("Very wet");
  else if (moisture_percentage >=300)
    lcd.print("Not too wet");
  else if (moisture_percentage >=100)
    lcd.print("Dry");
  else if (moisture_percentage <100)
    lcd.print("Very Dry");
   
   
}

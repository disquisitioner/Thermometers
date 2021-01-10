/*
 * Read temperature from TMP36 sensor and display on LCD panel
 *
 * Author: David Bryant (david_bryant@yahoo.com)
 * January 29, 2012
 * 
 * Arduino Pinouts
 *    0 = TMP36 input (analog)
 *    3 = PCM control for red backlight LED -> LCD16
 *    7 = LCD RS -> LCD4
 *    8 = LCD EN -> LCD6
 *    9 = LCD DB4 (data) -> LCD11
 *   10 = LCD DB5 (data) -> LCD12
 *   11 = LCD DB6 (data) -> LCD13
 *   12 = LCD DB7 (data) -> LCD14
 *
 * Additional
 *    LCD1 = GND
 *    LCD2 = VCC
 *    LCD3 = Contrast voltage (wiper of contrast pot)
 *    LCD5 = GND
 *    LCD15 = VCC
 */
 
// include the library code:
#include <LiquidCrystal.h> 
 
#define REDLITE 3  // Pin that controls red display on LCD panel

boolean debugging = true;   /* If debugging, output via Serial monitor */
int sensorPin = 0;  /* Pin the TMP36 sensor output is connected to */
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
 
// you can change the overall brightness by range 0 -> 255. 100 is pretty good...
int brightness = 100;
 
void setup() {
  
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  
  // Set display brightness.  0 is max, 255 is min
  analogWrite(REDLITE,brightness);
  
  if(debugging) {
    // send debugging info via the Serial monitor
    Serial.begin(9600);
  }
}
 
void loop()
{
  int reading, displayTemp;
  float voltage, temperatureC, temperatureF;
  
  /* Read temperature sensor */
  reading = analogRead(sensorPin);
  
  /* Convert reading to voltage */
  voltage = (reading * 5.0);
  voltage /= 1024.0;
   
  /* Convert to temperature */
  temperatureC = (voltage - 0.5) * 100;  // 10mV per degree with 500mV offset
  temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  
  displayTemp = (int) (temperatureF + 0.5);
  
  if(debugging) {
    Serial.print(displayTemp); Serial.print(" degrees C [");
    Serial.print(temperatureC); Serial.print(" C, ");
    Serial.print(temperatureF); Serial.print(" F, (");
    Serial.print(voltage); Serial.println(" volts)]");
  }
  
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(displayTemp);
  lcd.print(" F");
  
  delay(1000);   /* Delay */
}

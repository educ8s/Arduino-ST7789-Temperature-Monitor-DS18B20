// In this sketch the temperature is displayed in degrees Celcius
//
//


#define TFT_DC    7
#define TFT_RST   8
#define SCR_WD   240
#define SCR_HT   240

#include <SPI.h>
#include <Adafruit_GFX.h>  //https://github.com/adafruit/Adafruit-GFX-Library
#include <OneWire.h>
#include <Arduino_ST7789_Fast.h>  //https://github.com/cbm80amiga/Arduino_ST7789_Fast
#include <DallasTemperature.h>   //https://github.com/milesburton/Arduino-Temperature-Control-Library
#define ONE_WIRE_BUS 2
#define TEMP_X  20
#define TEMP_Y  85

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float previousTemp = -100.0;
float tempC = 0;
float minTemp = 200;
float maxTemp = 0;

Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up ...");
  sensors.begin();
  
  tft.init(SCR_WD, SCR_HT);
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(RED);  
  tft.setTextSize(3);
  tft.println(" Temperature");
  tft.setCursor(160, TEMP_Y);
  tft.setTextSize(5);
  tft.setTextColor(WHITE);  
  tft.println((char)247 );
  tft.setCursor(200, TEMP_Y);
  tft.println("C");

  tft.setCursor(40, 180);
  tft.setTextSize(2);
  tft.setTextColor(CYAN); 
  tft.println("MIN");
  printMinTempDegreesSymbol();
  printMaxTempDegreesSymbol();


  tft.setCursor(170, 180);
  tft.setTextSize(2);
  tft.setTextColor(RED); 
  tft.println("MAX");

}

void loop() {
    delay(1000);
    sensors.requestTemperatures();
    Serial.print("Temperature for the device 1 (index 0) is: ");
    previousTemp = tempC;
    tempC = sensors.getTempCByIndex(0); 
    if(tempC<minTemp)
    {
      deleteMinTemp();
      minTemp = tempC; 
    }
    if(tempC>maxTemp)
    {
      deleteMaxTemp();
      maxTemp = tempC; 
    }
    if(previousTemp!=tempC)
    {
       deletePreviousTemp();
       printTemp();
       printMinTemp();
       printMaxTemp();
    }
}

void deletePreviousTemp()
{
  tft.setCursor(TEMP_X, TEMP_Y);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.println(previousTemp,1);
}

void printTemp()
{
  tft.setCursor(TEMP_X, TEMP_Y);
  tft.setTextSize(5);
  tft.setTextColor(WHITE);
  tft.println(tempC,1);
}

void printMinTemp()
{
  tft.setCursor(10, 210);
  tft.setTextSize(2);
  tft.setTextColor(CYAN);
  tft.println(minTemp,1);
}

void printMaxTemp()
{
  tft.setCursor(150, 210);
  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.println(maxTemp,1);
}

void deleteMaxTemp()
{
  tft.setCursor(150, 210);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println(maxTemp,1);
}

void deleteMinTemp()
{
  tft.setCursor(10, 210);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println(minTemp,1);
}

void printMinTempDegreesSymbol()
{
  tft.setCursor(70, 210);
  tft.setTextSize(2);
  tft.setTextColor(CYAN);
  tft.println((char)247 );
  tft.setCursor(85, 210);
  tft.println("C");
}

void printMaxTempDegreesSymbol()
{
  tft.setCursor(210, 210);
  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.println((char)247 );
  tft.setCursor(225, 210);
  tft.println("C");
}

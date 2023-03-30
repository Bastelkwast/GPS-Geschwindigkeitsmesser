/*Hier habe ich einen GPS-Geschwindigkeitsmesser gebaut.*/

#include <TM1637Display.h>  // Für die 7-Segment Anzeige
#include <TinyGPS++.h>      // Für das GPS
#include <SoftwareSerial.h> // Wird für den Serial für den GPS-Empfänger benötigt

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The serial connection to the GPS module 
SoftwareSerial GPS_serial(5, 6); // Es wird nur der 5=RX benötigt

// The TinyGPSPlus object
TinyGPSPlus gps;

int brightness = 0; // Hier kann die Helligkeit von 0 bis 7 eingestellt werden
int geschwindigkeit = 0;
int speed = 0;

float Next_Loop = 0; // Wird im LOOP zur Steuerung benötigt

TM1637Display display(CLK, DIO);

void ausgabe()
{

  if (gps.speed.isValid())
  {
    geschwindigkeit = (gps.speed.kmph());
  }
 
 display.showNumberDec(geschwindigkeit, false);
}

void setup()
{
  GPS_serial.begin(9600);
  display.setBrightness(brightness);
  
}

void loop()
{

  while (GPS_serial.available() > 0)
    gps.encode(GPS_serial.read());
  if (millis() >= Next_Loop)
  {
    Next_Loop = (millis() + 1000);
    ausgabe();
  }
}

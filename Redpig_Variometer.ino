// Project to do a simple to build avionic instrument based on Arduino IDE
// Projected to be used in REAL aircraft no guarantee or certification of correct use in flight is given.
// RedPig is a name refering manga pilot you know.
// Project using OTA, rotary encoder  , 4 digit and 1 sensor BMP280
// MCU ESP32-c2 used because OTA and i'm tired of speed and space of Arduino classic board. It is a shame but i'm lazy.
// Mission: easy to build and light (3d PetG printed), easy to solder (dupont wiring), easy to use (one measure).
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D

//WIFI
#include <WiFi.h>        // For connecting ESP32 to WiFi
const char* ssid = "Your SSID";  // Change to your WiFi Network name
const char* password = "You Password";  // Change to your password
//OTA
#include <ArduinoOTA.h>  // For enabling over-the-air updates
//Display  4 DIGIT LCD
#include <TM1637Display.h>
#define CLK 2
#define DIO 3
M1637Display display(CLK, DIO); // Create an instance of the TM1637Display
//Rotarry encoder 
//Defining pins
//Arduino interrupt pins: 2, 3.
const int RotaryCLK = PB3; //CLK pin on the rotary encoder
const int RotaryDT = PB4; //DT pin on the rotary encoder
const int PushButton = PB5; //Button to enter/exit menu
//Statuses for the rotary encoder
int CLKNow;
int CLKPrevious;
int DTNow;
int DTPrevious;
bool refreshLCD = true; //refreshes values
bool refreshSelection = false; //refreshes selection (> / X)
//Sensor Presión atmosférico
#include <Wire.h>
#include <ErriezBMX280.h>
#define SEA_LEVEL_PRESSURE_HPA      1026.25 //Adjust sea level for altitude calculation
ErriezBMX280 bmx280 = ErriezBMX280(0x76); ////Create BMX280 object I2C address 0x76 or 0x77

//___________SETUP
void setup() {
  display.clear();    
  display.setBrightness(5);  // Set the display brightness (0-7)
  for (int i=0; i <= 9999; i++){
     display.showNumberDec(i, true);  // i=value, true to padd the blank segments with 0
     delay(10);
  };
  uint8_t data[] = { // -REDPIG-ALTIMETER
      SEG_G,                                  // -
      SEG_G, SEG_G,                            // r
      SEG_A | SEG_F | SEG_G | SEG_E | SEG_D|,SEF_B,  // e
      SEG_G | SEG_B | SEG_C | SEG_E | SEG_D,   // d
      SEG_A | SEG_F | SEG_G | SEG_E | SEG_D,  // P
      SEG_F | SEG_E,                  // I
      SEG_A | SEG_F | SEG_G | SEG_E | SEG_D | SEG,  // G
      SEG_A | SEG_F | SEG_G | SEG_C | SEG_D | SEG_C, // S
      SEG_G,                                  // -
    
  WiFi.begin(ssid, password);  // Connect to WiFi - defaults to WiFi Station mode

  // Ensure WiFi is connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

  // Initialize serial
    delay(500);
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.println(F("\nErriez BMP280/BMX280 example"));
  }

  ArduinoOTA.begin();  // Starts OTA
}

void loop() {

  ArduinoOTA.handle();  // Handles a code update request

  // All loop you're code goes here.
}

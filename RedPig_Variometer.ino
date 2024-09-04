
#include <Adafruit_NeoPixel.h>
// Project to do a simple to build avionic instrument based on Arduino IDE
// Projected to be used in REAL aircraft BUT no guarantee or certification of correct use in flight is given.
// RedPig is a name refering anime pilot you know.
// Project using OTA, rotary encoder  , 4 digit and 1 sensor BMP280.
// MCU ESP32-c2 used because OTA and i'm tired of speed and memspace of Arduino classic board. It is a shame but i'm lazy.
// Mission: easy to build and light (3d PetG printed), easy to solder (dupont wiring), easy to use (one measure).
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D

//WIFI______________________________________________________________________________________
#include <WiFi.h>        // For connecting ESP32 to WiFi

const char* ssid = "AnDoMol";  // Change to your WiFi Network name
const char* password = "asdfg12345";  // Change to your password
IPAddress local_IP(192, 168, 2, 38);
// Set your Gateway IP address
IPAddress gateway(192, 168, 2, 1);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8); // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional
//OTA_______________________________________________________________________________________
#include <ArduinoOTA.h>  // For enabling over-the-air updates
#include <TelnetStream.h>jj
//Display  4 DIGIT LCD 7 SEGMENTS __________________________________________________________
#include <TM1637.h>

#define CLK 7
#define DIO 6
TM1637 display(CLK, DIO); // Create an instance of the TM1637Display
//Rotarry encoder __________________________________________________________________________
//Defining pins
//Arduino interrupt pins: 4, 5.
const int RotaryCLK = 38; //CLK pin on the rotary encoder
const int RotaryDT = 37; //DT pin on the rotary encoder
const int PushButton = 35; //Button to enter/exit menu
//Statuses for the rotary encoder
int CLKNow;
int CLKPrevious;
int DTNow;
int DTPrevious;
bool refreshLCD = true; //refreshes values
bool refreshSelection = false; //refreshes selection (> / X)
//Sensor Presión atmosférico ______________________________________________________________
#include <ErriezBMX280.h>
#define SEA_LEVEL_PRESSURE_HPA      1026.25 //Adjust sea level for altitude calculation
ErriezBMX280 bme = ErriezBMX280(0x76); ////Create BMX280 object I2C address 0x76 or 0x77
//#include <Adafruit_NeoPixel.h>
//____________________________________________________________________
#define NUM_LEDS 8   // Numero de leds
#define PIN  13      // PIN ARDUINO
// PALABRAS_______________________________________________________________________________
//const uint8_t celsius[] = {
 // SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
//  SEG_A | SEG_D | SEG_E | SEG_F   // C//
//};
//const uint8_t hPa[] = {
//  SEG_F | SEG_E | SEG_C | SEG_G,  // h
//  SEG_A | SEG_F | SEG_G | SEG_E | SEG_D,   // P
//  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G //A
//};



//######################SETUP##########################################################
void setup() {
  ArduinoOTA.begin();  // Starts OTA ________________por si upload firmware waiting at boot
  ArduinoOTA.handle();  // Handles a code update request
  Serial.begin(9600);
  Serial.println(F("SETUP Peripherals"));//____________________________________________
 // display.clear();    
//  display.setBrightness(5);  // Set the display brightness (0-7)
// for (int i=0; i <= 9999; i++){
//     display.showNumberDec(i, true);  // i=value, true to padd the blank segments with 0
//     delay(10);
//  };
//  for ( int i=0; i<(sizeof(hPa)-3); i++ ) {
//    display.setSegments(hPa+i); // Display the data
//    delay(500);
//  };
  ////// Blink String
//  for ( int i=0; i<5; i++ ) {
//    display.setSegments(hPa+4); // Display the data
//    delay(400);
//    display.clear();             // Clear the display
//    delay(250);
//  };
  //    SETUP WIFI ___________________________________________________________  
  //WiFi.begin(ssid, password);  // Connect to WiFi - defaults to WiFi Station mode
  // Ensure WiFi is connected
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
  Serial.println("STA Failed to configure");
   }
  //_ SETUP BMP280________________________________________________________________
    Serial.println("\nErriez BMP280 SETUP");
  bool status;
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin();  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  //FAST LEDS _____SETUP
  Serial.println("-- Default WP2812B led strip--");
  Serial.println();
  Adafruit_NeoPixel pixels(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  pixels.clear();
}
//####################################################################################################
//________________________LOOP########################################################################
void loop() {

  ArduinoOTA.handle();  // Handles a code update request

  // All loop you're code goes here.


  
}

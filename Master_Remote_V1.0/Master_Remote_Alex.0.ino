//Libraries to be included
#include <LiquidCrystal.h>
#include <SPI.h>
#include "RF24.h"


//Pin Definitions
#define XRight A0 //analog pin connected to X output
#define YRight A1 // analog pin connected to Y output
#define XLeft A2 // analog pin connected to X output
#define YLeft A3 // analog pin connected to Y output
#define LeftJoySw 0 //switch in left joystick
#define RightJoySw 1 //switch in left joystick
#define PAYLOADSIZE 32 //???from remote template .h file

//where LCD interface pins are connected to the Arduino
const int rs = 3, en = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

RF24 radio(7, 8);  // Set up the nRF24L01+ radio (CE pin, CSN pin)
int XRightNorm, XLeftNorm, YRightNorm, YLeftNorm;
uint8_t joystick[4];

byte rfAddresses[][6] = {"1NODE", "2NODE"}; //???from remote template .h file
byte rfPacket[PAYLOADSIZE]; //???from remote template .h file

void setup()
{

  lcd.begin(20, 4); //tells LCD library the size of our display
  lcd.clear(); //ensures LCD is clear
  lcd.print("Welcome to the");
  lcd.setCursor(0, 1); //Next text on 2nd line
  lcd.print("Duchess' Remote!");
  lcd.setCursor(0, 3); //Next text on 3rd line
  lcd.print("Press R JS to cont");

  radio.begin();                    // Start the radio module
  radio.setPALevel(RF24_PA_MAX);    // Set the transmission power to max
  radio.setDataRate(RF24_250KBPS);  // Set the speed to 250kbps
  //radio.setChannel(CHANNELNUMBER);  // Set the channel (set in header!)

  radio.openWritingPipe(rfAddresses[1]);    // Transmit to the remote address
  radio.openReadingPipe(1, rfAddresses[0]); // Recieve sensor addressed packets

  radio.setPayloadSize(PAYLOADSIZE); // Set the number of bytes for the data packet

  radio.startListening();

}

void loop()
{  
  if (radio.available())
  {
    radio.read(&rfPacket, PAYLOADSIZE); // rfPacket contains the recieved data as bytes
  }

  /* TODO -  add your own code to read the joystick data and transmit */
  
  radio.stopListening();  // Stop listening so we can transmit

  static int test = 0;   // Create some dummy data and transmit (be careful not to exceed the payload size)
  test++;
  radio.write(&test, sizeof(int));
  delay(1000);  // Allow time for the sensor board the receive and process

  radio.startListening(); // Start listening again
}

  void rout()
  {
    bool role = 1;
    if (role ==1)
    {
     radio.stopListening();                                    //stop listening so we can talk.
    Serial.println(F("Now sending"));                        
    radio.write(&joystick, sizeof(joysitck));               //sending joystick array
    Serial.println("command sent");
   
    }
  }

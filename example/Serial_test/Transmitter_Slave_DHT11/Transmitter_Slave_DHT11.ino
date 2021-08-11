/*
  Power Line Communication 
  Software serial Library

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>
#include<DHT.h>

DHT  dht(9,DHT11);


const int transmit_pin = 8;  //connect to data_in of TDA5051
const int receive_pin = 7;  //connect to data_out of TDA5051
#define tda5051_pd_pin  5
SoftwareSerial mySerial(receive_pin, transmit_pin); // RX, TX

#define TDA5051_ENABLE  digitalWrite(tda5051_pd_pin, LOW)   //wake up
#define TDA5051_DISABLE digitalWrite(tda5051_pd_pin, HIGH)  //power down

void setup()
{
    // Open serial communications and wait for port to open:
  Serial.begin(1200);
  //while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for Native USB only
  }

  pinMode(tda5051_pd_pin, OUTPUT);
  TDA5051_DISABLE;//  digitalWrite(tda5051_pd_pin, HIGH);
    
  Serial.println("Goodnight moon! This is slave!");

  dht.begin();

  // set the data rate for the SoftwareSerial port
  mySerial.begin(1200);
  
  TDA5051_ENABLE;
  //mySerial.println("Hello, world?");
}

uint32_t i=0;
void loop() // run over and over
{
  i++;
  if (mySerial.available())
  {
    delay(2);
    Serial.write(mySerial.read());
    //Serial.print(mySerial.readString());
  }
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  Serial.println(h,2);
  
  /**
  if (Serial.available())
  {
    delay(2);
    mySerial.write(Serial.read());
    //mySerial.print(Serial.readString());
  }
  **/
  mySerial.print("Hello, Makerfabs? #");
  mySerial.println(i);
  mySerial.print("T:");
  mySerial.print(t,2);
  mySerial.println("C");
    
  delay(1000);
}

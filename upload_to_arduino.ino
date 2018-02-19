//this code is for uno/nano
//for mega first press ctrl+F and 
//then replace Serial2 to Serial1
//you may delete the headers for mega
#include<SoftwareSerial.h>
SoftwareSerial mySerial(2,3);


void setup() {
  Serial.begin(9600);    // serial connection to processing app.
  mySerial.begin(9600);  // for communicating with the GT-511C3

}

byte rx_byte = 0;        // stores received byte

void loop() {
  if (Serial.available()) {

    rx_byte = Serial.read();
    mySerial.write(rx_byte);
  }
  if (mySerial.available()) {
    rx_byte = mySerial.read();
    Serial.write(rx_byte);
  }
}

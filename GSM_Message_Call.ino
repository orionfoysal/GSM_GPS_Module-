//#include <SoftwareSerial.h>
#include <String.h>
 
//SoftwareSerial mySerial(2, 3);
 
void setup()
{
  //mySerial.begin(19500);               
  Serial.begin(9600);    
  delay(1000);
  //deleteAll();

}
 
void loop()
{

  SendTextMessage();
  delay(1000);
}
 
void SendTextMessage()
{
  Serial.print("AT+CMGF=1\r");    
  delay(100);
  Serial.println("AT + CMGS = \"+8801680221766\"");
  delay(100);
  Serial.println("A test message!");
  delay(100);
  Serial.println((char)26);//ctrl+z
  delay(100);
  Serial.println();
}
 
 
void DialVoiceCall()
{
  Serial.println("ATD + +8801688933774;");//dial the number
  delay(100);
  Serial.println();
}

void deleteAll()
{
  Serial.print("AT+CMGF=1\r");    
  delay(100);
  Serial.println("AT+CMGD=ALL");
  delay(1000);
}


/* Code for GSM shield sim900 or sim908 for reading SMS and parsing data from the output String.
 * Created by Foysal on 17/05/2015
 * 
 *
 * Special thanks to Alejandro Gallelio
*/

#include <SoftwareSerial.h>
#include <String.h>
int8_t answer;
int x;
char message[300];
char number[50];
int onModulePin= 2;
char SMS[500];
String text = "";

//SoftwareSerial Serial2(2,3);

void setup(){
  
  Serial.begin(9600);
  Serial2.begin(19200);
  delay(3000);
 // sendATcommand("AT+CMGD=1,4", "OK", 1000); //DELETE ALL THE MESSAGES
  sendATcommand("AT+CMGF=1", "OK", 1000);    // sets the SMS mode to text
  sendATcommand("AT+CPMS=\"SM\",\"SM\",\"SM\"", "OK", 1000);    // selects the memory

  answer = sendATcommand("AT+CMGR=1", "+CMGR:", 2000);    // reads the first SMS
  
 // Serial.println("AT+CMGD=1");
  if (answer == 1)
  {
      answer = 0;
      while(Serial2.available() == 0);
      // this loop reads the data of the SMS
      do{
          // if there are data in the UART input buffer, reads it and checks for the asnwer
          if(Serial2.available() > 0){    
              SMS[x] = Serial2.read();
              x++;
              // check if the desired answer (OK) is in the response of the module
              if (strstr(SMS, "OK") != NULL)    
              {
                  answer = 1;
              }
          }
      }while(answer == 0);    // Waits for the asnwer with time out
      
      SMS[x] = '\0';
      
      Serial.print(SMS);
      
  }
  else
  {
      Serial.print("error ");
      Serial.println(answer, DEC);
  }
  gets(SMS);
  //Serial.println(SMS);
  stringParsing(SMS,message,number);
  //Serial.println(SMS);
  Serial.println(number);
  //messageParsing(message);
  Serial.println(message);

  if(strstr(message,"Block All") != NULL)
    digitalWrite(13, HIGH);

  
}
//
void loop(){

}

int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout){

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '\0', 100);    // Initialice the string

    delay(100);

    while( Serial2.available() > 0) Serial2.read();    // Clean the input buffer

    Serial2.println(ATcommand);    // Send the AT command 


        x = 0;
    previous = millis();

    // this loop waits for the answer
    do{
        // if there are data in the UART input buffer, reads it and checks for the asnwer
        if(Serial2.available() != 0){    
            response[x] = Serial2.read();
            x++;
            // check if the desired answer is in the response of the module
            if (strstr(response, expected_answer) != NULL)    
            {
                answer = 1;
            }
        }
        // Waits for the asnwer with time out
    }while((answer == 0) && ((millis() - previous) < timeout));    

    return answer;
} 


void stringParsing(char *p, char *q, char *r)
{
    int i;
    int n = strlen(p);
    for(i=n-1;p[i]!='"';i--);
    int j, k=0;
    for(j=i+1;j<n;j++) q[k++] = p[j];
    q[k] = '\0';
    for(i=0;p[i]!=',';i++);
    k = 0;
    for(j=i+2;p[j]!='"';j++) r[k++] = p[j];
    r[k] = '\0';
}






// Connect VIO to +5V
// Connect GND to Ground
// Connect RX (data into SIM800L) to Digital 7
// Connect TX (data out from SIM800L) to Digital 8
// Importation librairie
#include <SoftwareSerial.h>
SoftwareSerial sim800l(7, 8); // RX, TX
String ThankYouMessage = "Merci pour votre pensee!";
String HenriNumber = "+13472177389";


void setup() {
Serial.begin(9600);
sim800l.begin(9600);
delay(1000);

  //Set Debug mode
  sim800l.write("AT+CMEE=2\r\n");
  delay(1000);
  //Set SMS format to ASCII
  sim800l.write("AT+CMGF=1\r\n");
  delay(1000);
  deleteAllMessages();
  
    if (sim800l.available()) {
    
     while(sim800l.available())   {
    Serial.write(sim800l.read());
    delay(1); }
          Serial.println();

  }
  
  Serial.println("Setup Complete!");
  
  //Serial.println("Sending SMS...");
   
 // sendThankYouMessage(HenriNumber,"Program Starting yo");

}


void loop() {
 
  if (sim800l.available()) {
    
     while(sim800l.available())   {
    Serial.write(sim800l.read());
    delay(1); }
          Serial.println();

  }


//  if (Serial.available()) {
//
//    
//      while(Serial.available())   {
//        char c = Serial.read();
//        
//      sim800l.write(c);
//      }
//      
////  sim800l.println();
//  sim800l.println();
//  }
  
  while(lookForKeyword("+CMTI"))
    {
      Serial.println("SMS Recu");
      int mySms = lookForSmsNumber();
      Serial.print("smsNumber ");
      Serial.println(mySms);  
      
      if (mySms == 0)
        {break;}
      Serial.println("Retrieving message...");
      Serial.println(char(mySms));
//      sim800l.print("AT+CMGR=");
//      sim800l.print("AT+CMGR=");
//      sim800l.println(); 
      
      
      
    }

}



void deleteAllMessages()
{
sim800l.print("AT+CMGD=1,4");
sim800l.println(); 
delay(1000);
}

void sendThankYouMessage(String myNumber, String myMessage)
{
  //Send new SMS command and message number
  


sim800l.print("AT+CMGS=\"");
sim800l.print(myNumber);
sim800l.println("\"");

  delay(1000);
   
  //Send SMS content
  sim800l.println(myMessage);
  //delay(1000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
  sim800l.write((char)26);
 delay(1000);
     
  Serial.println("SMS Sent!");
}


bool lookForKeyword(String myKeyWord)
{
  int mySearch = 0;
  
if (Serial.available())

  {
    //Serial.println("Entering Function");

     while(Serial.available())   {
       
      char c = Serial.read();
      if (c == myKeyWord[mySearch])
         {
         mySearch = mySearch + 1;
         }
      else
         {
         mySearch = 0;
         }
      //Serial.print(c);   
      if (mySearch == myKeyWord.length())
         {
         //Serial.println("Keyword detected");
         mySearch = 0;
         return true;
         break;
         } 
         
    
    delay(2);   
  
    }
    return false;
    
    //Serial.println("On Attend");
  }
}

int lookForSmsNumber()
{
    if(lookForKeyword(","))
          {
            int smsNumber = 0;
            char c = Serial.read();
            while (c < 58 && c > 47)
              {
              //Serial.print(c);
              smsNumber = smsNumber * 10 + (c - 48);
              c = Serial.read();
              delay(2);
              }
              //Serial.println(c);
//            Serial.print("smsNumber ");
              return smsNumber;  
            }
}

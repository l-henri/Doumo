
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

/*
Waiting for an SMS Message
*/  
  while(lookForKeyword("+CMTI"))
    {
      /*
      An SMS has been received
      */ 
      Serial.println("SMS Recu");
      String mySms = "";
      if (lookForKeyword(","))
        {
          /*
          Retrieving this SMS number
          */ 
        //mySms = retrieveMessage('!');
        mySms = retrieveSmsNumber();
        
        }
      if (mySms == "")
        {Serial.println("Did not find SMS number");break;}
      else if (mySms[0] == '7')
        {deleteAllMessages();}
        
      Serial.print("My SMS number is ");
      Serial.println(mySms);  
      
      
      Serial.print("Retrieving message ");
      Serial.println(mySms);
      
//      sim800l.print("AT+CMGR=");
//      sim800l.print(mySms);
//      sim800l.println(); 
        int counter = 0;
        while(counter <3 && lookForKeyword(",") )
          {counter++;}
        if (counter < 2)
        {
        Serial.println("Did not find commas");
        break;}
      Serial.println("Retrieving phone number");
      mySms = "";
      mySms = retrieveMessage('!');
      if (mySms == "")
        {Serial.println("Did not find phone number");break;}
     Serial.print("My phone number is ");
      Serial.println(mySms); 
      
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
        // Serial.println("Keyword detected");
         mySearch = 0;
         return true;
         break;
         } 
         
    
    delay(2);   
  
    }
    //Serial.println("Keyword not detected");
    return false;
    
  }
}

String retrieveSmsNumber()
{
    
          
            String myMessage = "";
            int iter = 0;
            char c = Serial.read();
         
            //Serial.println("Looking for SMS number");
            while (c < 58 && c > 47 && iter < 20)
              {
              //Serial.print(c);
              myMessage += c;
              c = Serial.read();
              delay(2);
              iter = iter +1;
              //Serial.println("Looping");
              }
          
            return myMessage;
            
            
}

String retrieveMessage(char stopChar)
{
    
          
            String myMessage = "";
            int iter = 0;
            char c = Serial.read();
         
            //Serial.println("Looking for message");
            while (c != stopChar && iter < 20 && Serial.available())
              {
              //Serial.print(c);
              myMessage += c;
              c = Serial.read();
              delay(2);
              iter = iter +1;
              //Serial.println("Looping");
              }
            if (iter == 20)
              {myMessage = "";}
            return myMessage;
            
            
}

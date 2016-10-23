// Connect VIO to +5V
// Connect GND to Ground
// Connect RX (data into SIM800L) to Digital 7
// Connect TX (data out from SIM800L) to Digital 8
// Importation librairie
#include <SoftwareSerial.h>
SoftwareSerial sim800l(7, 8); // RX, TX

String myKeyWord = "+";



void setup() {
Serial.begin(9600);
//sim800l.begin(9600);

delay(1000);
  int myInt = sizeof(myKeyWord);
  Serial.println(myKeyWord);
  Serial.println(myKeyWord.length());
  Serial.println("Salut");
  //Serial.println(myKeyWord[sizeof(myKeyWord)-2]);
  Serial.println(myKeyWord[sizeof(myKeyWord)-1]);
  //Serial.println(String.length(myKeyWord));
  
}


void loop() {
  
  int mySearch = 0;

if (Serial.available())

  {

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
      if (mySearch == myKeyWord.length())
         {
         Serial.println("Le mot cle est ici");
         mySearch = 0;
         } 
         
    Serial.print(c);
    delay(2);   
  
    }
    
    Serial.println("On Attend");
}
}


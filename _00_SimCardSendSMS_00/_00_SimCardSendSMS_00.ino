// Connect VIO to +5V
// Connect GND to Ground
// Connect RX (data into SIM800L) to Digital 7
// Connect TX (data out from SIM800L) to Digital 8
// Importation librairie
#include <SoftwareSerial.h>
SoftwareSerial sim800l(7, 8); // RX, TX

void setup() {
Serial.begin(9600);
sim800l.begin(9600);

delay(1000);
   
  Serial.println("Setup Complete!");
  Serial.println("Sending SMS...");
   
  //Set Debug mode
  sim800l.write("AT+CMEE=2\r\n");
  delay(1000);
  
  //Set SMS format to ASCII
  sim800l.write("AT+CMGF=1\r\n");
  delay(1000);
 
  //Send new SMS command and message number
  sim800l.write("AT+CMGS=\"+13472177389\"\r\n");
  delay(1000);
   
  //Send SMS content
  sim800l.write("YO!");
  delay(1000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
  sim800l.write((char)26);
  delay(1000);
     
  Serial.println("SMS Sent!");



}


void loop() {
 
  if (sim800l.available()) {
    
     while(sim800l.available())   {
    Serial.write(sim800l.read());
    delay(1); }
          Serial.println();

  }


  if (Serial.available()) {

    
      while(Serial.available())   {
        char c = Serial.read();
        
      sim800l.write(c);
      }
      
//  sim800l.println();
  sim800l.println();
  }
}

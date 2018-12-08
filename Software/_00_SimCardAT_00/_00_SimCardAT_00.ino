// Connect VIO to +5V
// Connect GND to Ground
// Connect RX (data into SIM800L) to Digital 7
// Connect TX (data out from SIM800L) to Digital 8
// Importation librairie
#include <SoftwareSerial.h>
//SoftwareSerial sim800l(7,8); // RX, TX
SoftwareSerial sim800l(8,7); // RX, TX

void setup() {
Serial.begin(9600);
sim800l.begin(9600);
Serial.println("Initialisation done");



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


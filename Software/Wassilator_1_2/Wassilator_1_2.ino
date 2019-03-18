/*
 This is an example of how simple driving a Neopixel can be
 This code is optimized for understandability and changability rather than raw speed
 More info at http://wp.josh.com/2014/05/11/ws2812-neopixels-made-easy/
*/
#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
#define PIXELS 16  // Number of pixels in the string

// These values depend on which pin your string is connected to and what board you are using 
// More info on how to find these at http://www.arduino.cc/en/Reference/PortManipulation

// These values are for digital pin 8 on an Arduino Yun or digital pin 12 on a DueMilinove/UNO
// Note that you could also include the DigitalWriteFast header file to not need to to this lookup.

#define PIXEL_PORT  PORTD  // Port of the pin the pixels are connected to
#define PIXEL_DDR   DDRD  // Port of the pin the pixels are connected to
#define PIXEL_BIT   3      // Bit of the pin the pixels are connected to

// These are the timing constraints taken mostly from the WS2812 datasheets 
// These are chosen to be conservative and avoid problems rather than for maximum throughput 

#define T1H  900    // Width of a 1 bit in ns
#define T1L  600    // Width of a 1 bit in ns
#define T0H  400    // Width of a 0 bit in ns
#define T0L  900    // Width of a 0 bit in ns
#define RES 6000    // Width of the low gap between bits to cause a frame to latch

// Here are some convience defines for using nanoseconds specs to generate actual CPU delays

#define NS_PER_SEC (1000000000L)          // Note that this has to be SIGNED since we want to be able to check for negative values of derivatives
#define CYCLES_PER_SEC (F_CPU)
#define NS_PER_CYCLE ( NS_PER_SEC / CYCLES_PER_SEC )
#define NS_TO_CYCLES(n) ( (n) / NS_PER_CYCLE )


/*
Shooting star variables
int starNumber = how many stars are currently running
int myStarz[] = the relative position of each star to the one before it
byte myStarzR[STAR_MAX_NUMBER] = R value for shooting star
byte myStarzG[STAR_MAX_NUMBER] = G value for shooting star
byte myStarzB[STAR_MAX_NUMBER] = B value for shooting star
*/
#define STAR_MAX_NUMBER 10
unsigned long time;

int starNumber = 0;
int myStarz[STAR_MAX_NUMBER];
byte myStarzR[STAR_MAX_NUMBER];
byte myStarzG[STAR_MAX_NUMBER];
byte myStarzB[STAR_MAX_NUMBER];



/*
SIM800 variables

*/

// For PCB card
SoftwareSerial sim800l(7, 8); // RX, TX
// For tupperware card
//SoftwareSerial sim800l(8, 7); // RX, TX

String ThankYouMessage = "Merci pour votre message!";
String statisticsMessage = "Je t'ai reconnu!";
//String HenriNumber = "+13472177389";
String HenriNumber = "+33643950145";

bool isAnimating = false;
bool hasSmsToSend = false;




void setup() {
 ledsetup();
     cli();  
  for(int i=0;i<PIXELS;i++){    
       
  sendPixel(0,0,0);
 }
    sei();
    show();  
Serial.begin(9600);
Serial.println("Started serial communication");


sim800l.begin(9600);
delay(1000);

  //Set Debug mode
  sim800l.write("AT+CMEE=2\r\n");
  delay(5000);

  
    if (sim800l.available()) {
    
     while(sim800l.available())   {
    Serial.write(sim800l.read());
    delay(1); }
          Serial.println();
          //Set SMS format to ASCII
  }


          Serial.println();
          Serial.println("WSLT1.0");
          Serial.println("Ecrire PIN");

            sim800l.write("AT+CPIN=4321\r\n");
  delay(5000);
  while(!sim800l.available())   {delay(1);}
    if (sim800l.available()) {
    
     while(sim800l.available())   {
    Serial.write(sim800l.read());
    delay(1); }
    //Set SMS format to ASCII
  }
          Serial.println();
          Serial.println("Test CNUM");

            sim800l.write("AT+CNUM\r\n");
  delay(1000);
  
    if (sim800l.available()) {
    
     while(sim800l.available())   {
    Serial.write(sim800l.read());
    delay(1); }
          Serial.println();

  //Set SMS format to ASCII
  }
  
    //Set SMS format to ASCII
  sim800l.write("AT+CMGF=1\r\n");
  delay(5000);
//  emptyBuffer();
 deleteAllMessages();
  
  Serial.println("Setup Complete!");
  
  //Serial.println("Sending SMS...");
   
  sendThankYouMessage(HenriNumber,"Program Starting yo");

breath(100, 100, 100, 500);

}


void loop() {
 

//
//
//
//
//

/*
Waiting for an SMS Message
*/  
  while(lookForKeyword("+CMTI"))
    {
           String myMessage = processingSms();
//           Serial.print("*");
//           Serial.print(myMessage);
//           Serial.println("*");
//      int programNumber = random(0,5);
//      Serial.println(programNumber);
    if (myMessage == "")
      {continue;}
    else if (myMessage.substring(0,4) == "Hope")
          {
//            breath(0, 30, 6, 50);
//            breath(0, 60, 12, 100);
//            breath(0, 90, 18, 250);
            breath(0, 121, 24, 2500);
            }
    else if (myMessage.substring(0,5) == "Happy")
          {
//          breath(64, 55, 0, 50);
//          breath(128, 105, 0, 100);
//          breath(191, 155, 0, 250);
          breath(255, 210, 0, 2500);}
    else if (myMessage.substring(0,4) == "Love")
      {
//        breath(60, 5, 0, 50);
//      breath(120, 10, 0, 100);
//      breath(190, 15, 0, 250);
      breath(245, 20, 0, 2500);}
    else if (myMessage.substring(0,3) == "Hug" )
      {
//        breath(47, 14, 10, 50);
//      breath(95, 29, 21, 100);
//      breath(142, 43, 31, 250);
      breath(190, 58, 53, 2500);}
      else 
      {
//        breath(50, 50, 50,50);
//      breath(100, 100, 100,100);
//      breath(150, 150, 150,250);
      breath(200, 200, 200,2500);}


//      newStar();
    }
//Serial.println("a la fraiche");
//
//  if (millis() - time > 10 && isAnimating)
//      {
//        shootingStar(); 
//      time = millis();
//      }
}


/*

Modem library



*/

String processingSms()
{

   /*
      An SMS has been received
      */ 
      Serial.println("**********************************************");
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
        {Serial.println("Did not find SMS number");return "";}
        
      Serial.print("My SMS number is ");
      Serial.println(mySms);  
      
      
      Serial.print("Retrieving message ");
      Serial.println(mySms);
      
//        sim800l.println("AT+CMGR=1");

       sim800l.print("AT+CMGR=");
        sim800l.print(mySms);
        sim800l.println("\n\r");
        
        int counter = 0;
          delay(5);
          while(!sim800l.available())   {}
       // Serial.println("Reading answer now");
        // Empyting buffer because message comes in two steps
        emptyBuffer();
        delay(5);
          while(!sim800l.available())   {}
        //Serial.println("Finished reading") ;

        // Counting " to wait for phone number
        while(counter <3 && lookForKeyword(String(char(34)) ) ) //char(340 is "
          {
            //Serial.print("Loop ");
          //Serial.println(counter);
          counter++;
        }
        if (counter < 2)
        {
        Serial.println("Did not find \" symbol");
        return "";}
      Serial.println("Retrieving phone number");
      String mySmsNumber = "";
      mySmsNumber = retrieveMessage('\"');
      if (mySmsNumber == "")
        {Serial.println("Did not find phone number");return "";}
     Serial.print("My phone number is ");
      Serial.println(mySmsNumber); 

       lookForKeyword("\r");
      
//       String myMessageTest = retrieveMessage('\"');
//       Serial.println(myMessageTest);
//       while(counter <3 ) 
//          {
//            
//            
//            //Serial.print("Loop ");
//          
//          counter++;
//          Serial.println(counter);
//          myMessageTest = retrieveMessage('\"');
//          Serial.println(myMessageTest);
//        }
        //Serial.println("Out of counter loop 2");
         
//
//      // Looking for carriage return (ascii code 10) to read message
//      lookForKeyword(String(char(10)) );  //char(10) is return carriage
//    
        String myMessage = "";
        myMessage = retrieveMessage('\r');
      if (myMessage == "")
        {Serial.println("Did not find message");return "";}
       Serial.print("My message is ");
      Serial.println(myMessage); 
      

//      if (mySms==HenriNumber)
//       else if ((mySms.substring(0,4) == "+336" || mySms.substring(1,5) == "+337" ) && !isAnimating)
//      else if (isAnimating)

      if (mySmsNumber==HenriNumber)
        {
          Serial.println("Sending Statistics");
        sendThankYouMessage(HenriNumber,statisticsMessage);
        }
      else if (isAnimating)
        {
        Serial.println("Storing phone number");

        hasSmsToSend = true;
        sendThankYouMessage(mySms,ThankYouMessage);
        }
      else if ((mySmsNumber.substring(0,4) == "+336" || mySmsNumber.substring(0,4) == "+337") && !isAnimating )
        {
         Serial.println("Sending message");
       // isAnimating = true;
        sendThankYouMessage(mySmsNumber,ThankYouMessage);
        }
        else
        {
          Serial.println("Not sending anything");
          }  

      Serial.println("**********************************************");
      if (mySms[0] == '9')
        {deleteAllMessages();}
      return myMessage.substring(1,myMessage.length());
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
  
if (sim800l.available())

  {
//    Serial.print("Entering Function looking for :");
//    Serial.print(myKeyWord[0]);
//    Serial.print(" of length: ");
//    Serial.println(myKeyWord.length());

     while(sim800l.available())   {
       
      char c = sim800l.read();
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
    //Serial.println("Keyword not detected");
    return false;
    
  }
}

String retrieveSmsNumber()
{
    
          
            String myMessage = "";
            int iter = 0;
            char c = sim800l.read();
         
            //Serial.println("Looking for SMS number");
            while (c < 58 && c > 47 && iter < 20)
              {
              //Serial.print(c);
              myMessage += c;
              c = sim800l.read();
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
            char c = sim800l.read();
         
            //Serial.println("Looking for message");
            //Serial.print("stopCHar is :");
            //Serial.print(stopChar);
            //Serial.println("Stops here");
            while (c != stopChar && iter < 50 && sim800l.available())
              {
              //Serial.write(c);
              myMessage += c;
              c = sim800l.read();
              delay(2);
              iter = iter +1;
              //Serial.println("Looping");
              }
            if (iter == 20)
              {myMessage = "";}
            return myMessage;
            
            
}


void emptyBuffer()
 {

       while(sim800l.available())   {
      
//      Serial.write(sim800l.read());
      sim800l.read();
      delay(2); 
      }
      //Serial.println("Buffer emptied");
    }

/*

Led Animation Library

*/

void breath(int targetR, int targetG, int targetB, int riseDurationInMilliseconds) {
   Serial.println("Breathing");

//  int maxValue = max(max(targetR, targetG), targetB);
//
//  int rIncrementValue = targetR /100;
//  if (rIncrementValue == 0)
//    {rIncrementValue = 1;}
//  int gIncrementValue = targetG /100;
//  if (gIncrementValue == 0)
//    {gIncrementValue = 1;}
//      int bIncrementValue = targetB /100;
//  if (bIncrementValue == 0)
//    {bIncrementValue = 1;}
//    
   int stepCounter = 0;
    bool goingUp = true;

    while (stepCounter > 0 || goingUp )
    {

    int rValue = targetR * stepCounter/100;
    int gValue = targetG * stepCounter/100;
    int bValue = targetB * stepCounter/100;
//    Serial.print("stepCounter ");
//    Serial.print(stepCounter);
//    Serial.print(" targetR ");
//    Serial.print(rValue);
//    Serial.print(" targetG ");
//    Serial.print(gValue);
//    Serial.print(" targetB ");
//    Serial.println(bValue);

    if (goingUp)
    
    {stepCounter += 1;}
    else
    {stepCounter -=1;}
      if (stepCounter == 100)
    {
      goingUp = false;}
   cli();  
  for(int i=0;i<PIXELS;i++){    
       
  sendPixel(rValue,gValue,bValue);
 }
    sei();
    show();  
    if (goingUp)
      {delay(riseDurationInMilliseconds/100 * 3);}
    else
      {delay(riseDurationInMilliseconds/100 * 3);}
    
    }

    cli();  
  for(int i=0;i<PIXELS;i++){    
       
  sendPixel(0,0,0);
 }
    sei();
    show();  
   Serial.println("Stopped");

}


void shootingStar() {
  
  
      
      
      unsigned int myCounter=0;
      unsigned int step=0;
      cli();
      
      
      for (int i=0; i < PIXELS ; i++) {
        
        
        if (step==myStarz[myCounter] && myCounter < STAR_MAX_NUMBER) {
          
          sendPixel( myStarzR[myCounter] , myStarzG[myCounter] , myStarzB[myCounter] );
          myCounter++;
          step=0;
          } 
        else {
          step++;
          sendPixel( 0 , 0 , 0 );
          
        }
       
        
      }
      
      sei();
      
      show();
      //Serial.println(myCounter);
      if (myCounter == 0)
      {
        Serial.println("Stop Animation");
        isAnimating = false;
      }
      myStarz[0]++;
      //delay(wait);
      //starIncrement();
     
    
    
  
  
}
void newStar()
{
  isAnimating = true;
  Serial.println("New Star");
for (int i = STAR_MAX_NUMBER-1; i >0;i--)
  {
  myStarz[i] = myStarz[i-1];
  myStarzR[i] = myStarzR[i-1];
  myStarzG[i] = myStarzG[i-1];
  myStarzB[i] = myStarzB[i-1];
  //Serial.println(myStarz[i-1]);
  }
  myStarz[0]=0;
  myStarzR[0] = random(0,120);
  myStarzG[0] = random(0,120);
  myStarzB[0] = random(0,120);
    
  }









/*

LED Strip library



*/

// Actually send a bit to the string. We must to drop to asm to enusre that the complier does
// not reorder things and make it so the delay happens in the wrong place.

void sendBit( bool bitVal ) {
  
    if (  bitVal ) {				// 0 bit
      
		asm volatile (
			"sbi %[port], %[bit] \n\t"				// Set the output bit
			".rept %[onCycles] \n\t"                                // Execute NOPs to delay exactly the specified number of cycles
			"nop \n\t"
			".endr \n\t"
			"cbi %[port], %[bit] \n\t"                              // Clear the output bit
			".rept %[offCycles] \n\t"                               // Execute NOPs to delay exactly the specified number of cycles
			"nop \n\t"
			".endr \n\t"
			::
			[port]		"I" (_SFR_IO_ADDR(PIXEL_PORT)),
			[bit]		"I" (PIXEL_BIT),
			[onCycles]	"I" (NS_TO_CYCLES(T1H) - 2),		// 1-bit width less overhead  for the actual bit setting, note that this delay could be longer and everything would still work
			[offCycles] 	"I" (NS_TO_CYCLES(T1L) - 2)			// Minimum interbit delay. Note that we probably don't need this at all since the loop overhead will be enough, but here for correctness

		);
                                  
    } else {					// 1 bit

		// **************************************************************************
		// This line is really the only tight goldilocks timing in the whole program!
		// **************************************************************************


		asm volatile (
			"sbi %[port], %[bit] \n\t"				// Set the output bit
			".rept %[onCycles] \n\t"				// Now timing actually matters. The 0-bit must be long enough to be detected but not too long or it will be a 1-bit
			"nop \n\t"                                              // Execute NOPs to delay exactly the specified number of cycles
			".endr \n\t"
			"cbi %[port], %[bit] \n\t"                              // Clear the output bit
			".rept %[offCycles] \n\t"                               // Execute NOPs to delay exactly the specified number of cycles
			"nop \n\t"
			".endr \n\t"
			::
			[port]		"I" (_SFR_IO_ADDR(PIXEL_PORT)),
			[bit]		"I" (PIXEL_BIT),
			[onCycles]	"I" (NS_TO_CYCLES(T0H) - 2),
			[offCycles]	"I" (NS_TO_CYCLES(T0L) - 2)

		);
      
    }
    
    // Note that the inter-bit gap can be as long as you want as long as it doesn't exceed the 5us reset timeout (which is A long time)
    // Here I have been generous and not tried to squeeze the gap tight but instead erred on the side of lots of extra time.
    // This has thenice side effect of avoid glitches on very long strings becuase 

    
}  

  
void sendByte( unsigned char byte ) {
    
    for( unsigned char bit = 0 ; bit < 8 ; bit++ ) {
      
      sendBit( bitRead( byte , 7 ) );                // Neopixel wants bit in highest-to-lowest order
                                                     // so send highest bit (bit #7 in an 8-bit byte since they start at 0)
      byte <<= 1;                                    // and then shift left so bit 6 moves into 7, 5 moves into 6, etc
      
    }           
} 

/*
  The following three functions are the public API:
  
  ledSetup() - set up the pin that is connected to the string. Call once at the begining of the program.  
  sendPixel( r g , b ) - send a single pixel to the string. Call this once for each pixel in a frame.
  show() - show the recently sent pixel on the LEDs . Call once per frame. 
  
*/


// Set the specified pin up as digital out

void ledsetup() {
  
  bitSet( PIXEL_DDR , PIXEL_BIT );
  
}

void sendPixel( unsigned char r, unsigned char g , unsigned char b )  {  
  
  sendByte(g);          // Neopixel wants colors in green then red then blue order
  sendByte(r);
  sendByte(b);
  
}


// Just wait long enough without sending any bots to cause the pixels to latch and display the last sent frame

void show() {
	_delay_us( (RES / 1000UL) + 1);				// Round up since the delay must be _at_least_ this long (too short might not work, too long not a problem)
}


/*
  That is the whole API. What follows are some demo functions rewriten from the AdaFruit strandtest code...
  
  https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/strandtest/strandtest.ino
  
  Note that we always turn off interrupts while we are sending pixels becuase an interupt
  could happen just when we were in the middle of somehting time sensitive.
  
  If we wanted to minimize the time interrupts were off, we could instead 
  could get away with only turning off interrupts just for the very brief moment 
  when we are actually sending a 0 bit (~1us), as long as we were sure that the total time 
  taken by any interrupts + the time in our pixel generation code never exceeded the reset time (5us).
  
*/

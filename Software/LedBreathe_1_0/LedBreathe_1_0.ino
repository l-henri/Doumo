/*
 This is an example of how simple driving a Neopixel can be
 This code is optimized for understandability and changability rather than raw speed
 More info at http://wp.josh.com/2014/05/11/ws2812-neopixels-made-easy/
*/
#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
#define PIXELS 225  // Number of pixels in the string

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






void setup() {
 ledsetup();
     cli();  
  for(int i=0;i<225;i++){    
       
  sendPixel(0,0,0);
 }
    sei();
    show();  
Serial.begin(9600);
Serial.println("Started serial communication");
 
  Serial.println("Setup Complete!");
  

//breath();

}


void loop() {
 

/*
Waiting for an SMS Message
*/  

cli();  
        for(int i=0;i<50;i++)
              {    
               sendPixel(0,121,24); // HOPE     
               // Tests verts
              // sendPixel(93,184,96); // Pantone 362
              //sendPixel(0,121,52); // Pantone 356
              // sendPixel(114,180,49); // Pantone 369

              // Jaune
              // sendPixel(255,210,0); // Happy
              
              // Rouge
              //sendPixel(245, 20, 0); // Love

              // Orange
              // sendPixel(245, 41, 0); // Hugs, orange
              // sendPixel(190, 58, 53); // Hugs, rose
             }
          sei();
          show();  
delay(5000);
cli();  
        for(int i=0;i<50;i++)
              {    
               //sendPixel(0,121,24); // HOPE     
               // Tests verts
              // sendPixel(93,184,96); // Pantone 362
              //sendPixel(0,121,52); // Pantone 356
              // sendPixel(114,180,49); // Pantone 369

              // Jaune
               sendPixel(255,210,0); // Happy
              
              // Rouge
              //sendPixel(245, 20, 0); // Love

              // Orange
              // sendPixel(245, 41, 0); // Hugs, orange
              // sendPixel(190, 58, 53); // Hugs, rose
             }
          sei();
          show();  
delay(5000);
cli();  
        for(int i=0;i<50;i++)
              {    
               //sendPixel(0,121,24); // HOPE     
               // Tests verts
              // sendPixel(93,184,96); // Pantone 362
              //sendPixel(0,121,52); // Pantone 356
              // sendPixel(114,180,49); // Pantone 369

              // Jaune
              // sendPixel(255,210,0); // Happy
              
              // Rouge
              sendPixel(245, 20, 0); // Love

              // Orange
              // sendPixel(245, 41, 0); // Hugs, orange
              // sendPixel(190, 58, 53); // Hugs, rose
             }
          sei();
          show();  
delay(5000);
cli();  
        for(int i=0;i<50;i++)
              {    
               //sendPixel(0,121,24); // HOPE     
               // Tests verts
              // sendPixel(93,184,96); // Pantone 362
              //sendPixel(0,121,52); // Pantone 356
              // sendPixel(114,180,49); // Pantone 369

              // Jaune
              // sendPixel(255,210,0); // Happy
              
              // Rouge
              //sendPixel(245, 20, 0); // Love

              // Orange
              // sendPixel(245, 41, 0); // Hugs, orange
              sendPixel(190, 58, 53); // Hugs, rose
             }
          sei();
          show();  
delay(5000);
 

}



/*

Led Animation Library

*/

void breath() {
   Serial.println("Breathing");

   int isLitUp = 1;
    bool goingUp = true;
  Serial.println("Turning all leds up to 25% power");
    while (isLitUp > 0 )
    {

 
  if (isLitUp == 60)
    {
      goingUp = false;}
    if (goingUp)
    {isLitUp += 1;}
    else
    {isLitUp -=1;}
    
   cli();  
  for(int i=0;i<PIXELS;i++){    
       
  sendPixel(isLitUp,isLitUp,isLitUp);
 }
    sei();
    show();  
    delay(50);
    }
   Serial.println("Finished");
   Serial.println("Turning 50 leds up to 100% power");
    isLitUp = 1;
    goingUp = true;
    while (isLitUp > 0 )
    {

       
        if (isLitUp == 250)
          {
            goingUp = false;}
          if (goingUp)
            {isLitUp += 1;}
          else
            {isLitUp -=1;}
          
         cli();  
        for(int i=0;i<50;i++)
              {    
                   
              sendPixel(isLitUp,isLitUp,isLitUp);
             }
          sei();
          show();  
          delay(50);
    }

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


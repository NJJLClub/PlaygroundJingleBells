#include <Adafruit_CircuitPlayground.h>

/*
 Jingle Bells, the music

 E E E2 E E E2 E G C3/4 D/4
 E4 F F F3/4 F/4 F E E E/4 E/4
 E D D E D2 G2 E E E2 E E E2
 E G C3/4 D/4 E4 F F F F 
 F E E E/2 E/2 G G F D C4

 C,262
 D,294
 E,330
 F,349
 G,392
 A,440
 B,494
 C,523
*/

uint16_t beat = 250;
uint16_t jingle_bells[102] = {
  330, beat,   //E
  330, beat,   //E
  330, beat*2, //E
  330, beat,   //E
  330, beat,   //E
  330, beat*2,        //E
  330, beat,          //E
  392, beat,          //G
  262, beat * 1.5,    //C
  294, beat * 0.5,  //D
  
  330, beat*4,        //E
  349, beat,          //F
  349, beat,          //F
  349, beat * 1.5,     //F
  349, beat * 0.5,        //F
  349, beat,          //F
  330, beat,          //E
  330, beat,          //E
  330, beat/4,        //E
  330, beat/4,        //E

  330, beat, //E
  294, beat, //D
  294, beat, //D
  330, beat, //E
  294, beat *2, //D 2
  392, beat * 2, //G 2
  330, beat, //E
  330, beat, //E
  330, beat*2 ,//E 2
  330, beat, //E
  330, beat, //E
  330, beat*2, //E 2

  330, beat, //E
  392, beat, //G
  262, beat * 1.5 , //C 3/4
  294, beat / 2, //D /4
  330, beat * 4, //E 4
  349, beat, //F
  349, beat, //F
  349, beat, //F
  349, beat, //F
  
  349,beat, //F
  330,beat, //E
  330,beat, //E
  330,beat /2, //E /2
  330,beat/2, //E/2
  392,beat,   //G
  392,beat,   //G
  349,beat,   //F
  294,beat,   //D
  262,beat*4, //C 4
};
uint16_t jingle_bells_size = 102;
uint16_t songHead = 0;  // beginning of the song

#define BRIGHTNESS 20

uint16_t pixelHead=0;
uint16_t pixelMax=9;
bool isGreen;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(BRIGHTNESS);
  CircuitPlayground.clearPixels();
  CircuitPlayground.redLED(false);
 
}

void loop() {
  
  bool slideSwitchOnLeft = CircuitPlayground.slideSwitch();  // true==left  false=right


  // 
  // if somebody slides the switch to the Left it will cause
  // the device to play Jingle Bells.
  //
  if ( slideSwitchOnLeft )
  {
      uint16_t notevalue = jingle_bells[songHead]; songHead++;
      uint16_t holdfor = jingle_bells[songHead];
      
      CircuitPlayground.playTone( notevalue, holdfor);      
      delay( holdfor );  // let the note play
      delay( beat );     // delay a beat
    
      songHead++;
      if ( songHead > (jingle_bells_size-1)) songHead=0; // start over


  }


  /*
   *  Make a christmas wreath (red and green lights)
   */
  CircuitPlayground.clearPixels(); // erase all 
  isGreen = false;
  
  for ( uint16_t ith = pixelHead; ith <= pixelMax ; ith++)
  {
    if ( isGreen)  CircuitPlayground.setPixelColor( ith, 0, 255, 0);
    if ( !isGreen) CircuitPlayground.setPixelColor( ith, 255, 0, 0);
    isGreen = ! isGreen;
  }

  for (uint16_t ith = 0; ith < pixelHead; ith++)
  {
    if ( isGreen)  CircuitPlayground.setPixelColor( ith, 0, 255, 0);
    if ( !isGreen) CircuitPlayground.setPixelColor( ith, 255, 0, 0);
    isGreen = ! isGreen;
     
  }

  pixelHead++;
  if (pixelHead > pixelMax) pixelHead=0;

  if ( ! slideSwitchOnLeft ) delay(200);

}


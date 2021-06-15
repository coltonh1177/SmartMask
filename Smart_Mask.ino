//Team Smart Mask
//Colton Henderson,Mostak Ahmed,Derek Grey,Jason Umali, Brandon Namphong
//CSCE 483 Spring 2021
//Instructors: Dr.Paul Taele, Larry Powell
//Code for the led grid functionality

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

#define lengthof(A) ((sizeof((A))/sizeof((A)[0])))
#define button 12
 

const PROGMEM uint8_t ourSmile[8][8] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {3,0,0,0,0,0,0,3},
    {3,3,0,0,0,0,3,3},
    {3,3,0,0,0,0,3,3},
    {0,3,3,3,3,3,3,0},
    {0,0,3,3,3,3,0,0},
    {0,0,0,0,0,0,0,0}
};

const PROGMEM uint8_t ourFrown[8][8] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,0},
    {1,1,0,0,0,0,1,1},
    {1,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};

const PROGMEM uint8_t loudMouth[8][8] = {
    {0,0,0,0,0,0,0,0},
    {0,0,7,7,7,7,0,0},
    {0,7,0,0,0,0,7,0},
    {7,0,0,0,0,0,0,7},
    {7,0,0,0,0,0,0,7},
    {0,7,0,0,0,0,7,0},
    {0,0,7,7,7,7,0,0},
    {0,0,0,0,0,0,0,0}
};

const PROGMEM uint8_t mediumMouth[8][8] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,7,7,7,7,7,7,0},
    {7,0,0,0,0,0,0,7},
    {7,0,0,0,0,0,0,7},
    {0,7,7,7,7,7,7,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};

const PROGMEM uint8_t quietMouth[8][8] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,7,7,0,0,0},
    {7,7,7,0,0,7,7,7},
    {7,7,7,0,0,7,7,7},
    {0,0,0,7,7,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};



uint16_t palette[8] = {};
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 0,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
Adafruit_NeoMatrix matrix1 = Adafruit_NeoMatrix(8, 8, 6,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
Adafruit_NeoMatrix matrix2 = Adafruit_NeoMatrix(8, 8, 7,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

Adafruit_NeoMatrix matrix3 = Adafruit_NeoMatrix(8, 8, 2,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800); 
Adafruit_NeoMatrix matrix4 = Adafruit_NeoMatrix(8, 8, 0,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800); 
  

void drawImage(short image_addr){
    for(int x = 0; x<8; x++){
        for(int y = 0; y<8; y++){
            uint8_t index = pgm_read_byte(image_addr+x+y*8);
            matrix.drawPixel(x,y, palette[index]);
            matrix1.drawPixel(x, y, palette[index]); 
            matrix2.drawPixel(x, y, palette[index]); 
            matrix3.drawPixel(x, y, palette[index]);  
            matrix4.drawPixel(x, y, palette[index]);
        }
    }

    matrix.show();
    matrix1.show();
    matrix2.show();
    matrix3.show();
    matrix4.show();
}

void setup() {

    Serial.begin(9600);
    matrix.begin();
    matrix1.begin();
    matrix2.begin();
    matrix3.begin();
    matrix4.begin();

    //numbers out of order because we took out the other colors
    palette[3] = matrix.Color(0,0,255);       //blue
    palette[1] = matrix.Color(0,255,0);       //green
    palette[7] = matrix2.Color(255,255,0);    //cyan
    
   
   pinMode(button,INPUT_PULLUP);
}


void loop() {
    
    int newstate=digitalRead(button);
      if(newstate == LOW){
        
      int test = analogRead(A7);
      //515 was found based off of testing the mic input range
      if(test < 515){
        drawImage((short int)ourSmile);
      }
      else if(test >= 515){
        drawImage((short int)loudMouth);
        delay(100);
        drawImage((short int)mediumMouth);
        delay(100);
        drawImage((short int)quietMouth);
        delay(100);
      }
}//if button is in other position do sad face
else{
       int test = analogRead(A7);
       if(test < 515){
        drawImage((short int)ourFrown);
      }
      else if(test >= 515){
        drawImage((short int)loudMouth);
        delay(100);
        drawImage((short int)mediumMouth);
        delay(100);
        drawImage((short int)quietMouth);
        delay(100);
      }
}
}
   
    
    
        

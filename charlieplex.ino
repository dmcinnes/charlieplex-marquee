// Row       1---2---3---4---5---
#define _A 0b01101001111110011001
#define _B 0b11101001111010011110
#define _C 0b01111000100010000111
#define _D 0b11101001100110011110
#define _E 0b11111000111010001111
#define _F 0b11111000111010001000
#define _G 0b01111000101110010110
#define _H 0b10011001111110011001
#define _I 0b01110010001000100111
#define _J 0b01110010001010100100
// Row       1---2---3---4---5---
#define _K 0b10011010110010101001
#define _L 0b10001000100010001111
#define _M 0b10011111111110011001
#define _N 0b10011101101110011001
#define _O 0b01101001100110010110
#define _P 0b11101001111010001000
#define _Q 0b01101001101101100001
#define _R 0b11101001111010101001
// Row       1---2---3---4---5---
#define _S 0b11111000111100011111
#define _T 0b01110010001000100010
#define _U 0b10011001100110010110
#define _V 0b10011001100110100100
#define _W 0b10011001111111110110
#define _X 0b10011001011010011001
#define _Y 0b10011001011000101100
#define _Z 0b11110001001001001111

int offset = 0;
unsigned long lastMillis = 0;
unsigned long currentMillis = 0;

unsigned long characterMap[] = {_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,_N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,_X,_Y,_Z};

char myString[] = "HELLOWORLD";

void setup() {
}

void loop() {
  currentMillis = millis();

  renderString(myString, offset);

  if (currentMillis - lastMillis > 300) {
    lastMillis = currentMillis;
    offset++;
    if (offset > 50) {
      offset = -4;
    }
  }
}

void renderString(char *theString, int offset) {
  int index = 0;
  while (theString[index]) {
    renderCharacter(theString[index], offset - index * 5);
    index++;
  }
}

void renderCharacter(char theChar, int charOffset) {
  if (charOffset < -3 || charOffset > 4) {
    // off the 'screen' nothing to do
    return;
  }

  unsigned long graphic = characterMap[theChar - 65];

  for (byte y = 0; y < 5; y++) {
    for (byte x = 0; x < 4; x++) {
      if (graphic & 0x1) {
        // 3 - x to reverse order
        lightPixel(3 - x - charOffset, y);
      }
      graphic = graphic >> 1;
    }
  }
}

void lightPixel(byte x, byte y) {
  if (x >= 0 && x < 4) {
    if (y <= x) {
      x++;
    }
    LEDon(y, x);
  }
}

void LEDon(byte vin, byte gnd) {
  delay(1);
  pinMode(0, INPUT); 
  pinMode(1, INPUT); 
  pinMode(2, INPUT); 
  pinMode(3, INPUT); 
  pinMode(4, INPUT); 
  pinMode(5, INPUT); 

  pinMode(vin, OUTPUT);   
  pinMode(gnd, OUTPUT); 
  digitalWrite(vin, HIGH);
  digitalWrite(gnd, LOW); 
}

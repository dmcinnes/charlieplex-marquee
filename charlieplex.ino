#define MAP_START 32

// maps characters to their 4x5 grid 
unsigned long characterMap[58];

void Chr(char theChar, unsigned long value) {
  characterMap[theChar - MAP_START] = value;
}

int offset = 0;
unsigned long lastMillis = 0;
unsigned long currentMillis = 0;

char myString[] = "HELLO WORLD!";

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

  unsigned long graphic = characterMap[theChar - MAP_START];

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

  pinMode(vin, OUTPUT);   
  pinMode(gnd, OUTPUT); 
  digitalWrite(vin, HIGH);
  digitalWrite(gnd, LOW); 
}

void setup() {
  // set up render map

  // Rows:   1---2---3---4---5---
  Chr('A', 0b01101001111110011001);
  Chr('B', 0b11101001111010011110);
  Chr('C', 0b01111000100010000111);
  Chr('D', 0b11101001100110011110);
  Chr('E', 0b11111000111010001111);
  Chr('F', 0b11111000111010001000);
  Chr('G', 0b01111000101110010110);
  Chr('H', 0b10011001111110011001);
  Chr('I', 0b01110010001000100111);
  Chr('J', 0b01110010001010100100);
  Chr('K', 0b10011010110010101001);
  Chr('L', 0b10001000100010001111);
  Chr('M', 0b10011111111110011001);
  Chr('N', 0b10011101101110011001);
  Chr('O', 0b01101001100110010110);
  Chr('P', 0b11101001111010001000);
  Chr('Q', 0b01101001101101100001);
  Chr('R', 0b11101001111010101001);
  Chr('S', 0b11111000111100011111);
  Chr('T', 0b01110010001000100010);
  Chr('U', 0b10011001100110010110);
  Chr('V', 0b10011001100110100100);
  Chr('W', 0b10011001111111110110);
  Chr('X', 0b10011001011010011001);
  Chr('Y', 0b10011001011000101100);
  Chr('Z', 0b11110001001001001111);
  Chr(' ', 0b00000000000000000000);
  Chr('!', 0b01000100010000000100);
}

void loop() {
  currentMillis = millis();

  renderString(myString, offset);

  if (currentMillis - lastMillis > 100) {
    lastMillis = currentMillis;
    offset++;
    if (offset > 60) {
      offset = -4;
    }
  }
}

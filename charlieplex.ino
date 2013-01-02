#define A 0b01101001111110011001
#define B 0b11101001111010011110

int offset = 0;
unsigned long lastMillis = 0;
unsigned long currentMillis = 0;

void setup() {
}

void loop() {
  currentMillis = millis();

  character(B);

  if (currentMillis - lastMillis > 300) {
    lastMillis = currentMillis;
    offset++;
    if (offset > 4) {
      offset = -4;
    }
  }
}

void character(unsigned long cha) {
  for (byte y = 0; y < 5; y++) {
    for (byte x = 0; x < 4; x++) {
      if (cha & 1) {
        // 3 - x to reverse order
        light(3 - x - offset, y);
      }
      cha = cha >> 1;
    }
  }
}

void light(byte x, byte y) {
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

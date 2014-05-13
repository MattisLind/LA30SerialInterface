/*

  Pins
  LA30 interface board      Arduino pin    AVR port 
  -------------------------------------------------
  B1     PDEM              10              PB2
  D1     PBIT1             A0              PC0
  E1     PBIT2             A1              PC1
  H1     PBIT3             A2              PC2
  J1     PBIT4             A3              PC3
  K2     PBIT5             A4              PC4
  L1     PBIT6             A5              PC5
  P1     PBIT7             12              PB4
  V2     PINIL              9              PB1
  E2     PSTBL             13              PB5
  S1     KBIT1L             2              PD2
  D2     KBIT2L             3              PD3
  H2     KBIT3L             4              PD4
  M2     KBIT4L             5              PD5
  P2     KBIT5L             6              PD6
  S2     KBIT6L             7              PD7
  T2     KBIT7L             8              PB0
  M1     KSTBL             11              PB3
*/

#define PBIT1 A0
#define PBIT2 A1
#define PBIT3 A2
#define PBIT4 A3
#define PBIT5 A4
#define PBIT6 A5
#define PBIT7 12

#define PDEM 10
#define PSTBL 13
#define PINIL 9

#define KBIT1L 11
#define KBIT2L 3
#define KBIT3L 4
#define KBIT4L 5
#define KBIT5L 6
#define KBIT6L 7
#define KBIT7L 8

#define KSTBL 2

void setup () {
//DDRA = DDRA | B
//DDRB = DDRB | B00101011; // PB0, PB1, PB3 and PB5 is outputs  PB2 and PB4 inputs  
//DDRB = DDRC | B00111111; // Port C is all outputs except 6 and 7.
//DDRD = DDRD | B00000000; // Port D is all input while leving RX/TX untouched
pinMode (KBIT1L, INPUT_PULLUP);
pinMode (KBIT2L, INPUT_PULLUP);
pinMode (KBIT3L, INPUT_PULLUP);
pinMode (KBIT4L, INPUT_PULLUP);
pinMode (KBIT5L, INPUT_PULLUP);
pinMode (KBIT6L, INPUT_PULLUP);
pinMode (KBIT7L, INPUT_PULLUP);

pinMode (KSTBL, INPUT);

pinMode (PBIT1, OUTPUT);
pinMode (PBIT2, OUTPUT);
pinMode (PBIT3, OUTPUT);
pinMode (PBIT4, OUTPUT);
pinMode (PBIT5, OUTPUT);
pinMode (PBIT6, OUTPUT);
pinMode (PBIT7, OUTPUT);

pinMode (PINIL, OUTPUT);
pinMode (PSTBL, OUTPUT);
pinMode (PDEM, INPUT);
Serial.begin (9600);
digitalWrite(PINIL, 0);
delay(1);
digitalWrite(PINIL, 1);
attachInterrupt(0,keyInt, FALLING);
}



char buf[1024];
int readIndex=0;
int writeIndex=0;
int bufferFull=0;
int bufferEmpty=1;

volatile int keyboardReady=0;
volatile int keyboardData;

void keyInt () {
    keyboardData = (0x03e & PIND) >> 2;
    keyboardData |= digitalRead(KBIT1L);
    keyboardData |= (digitalRead(KBIT7L)<<6);
    keyboardReady=1;  
}

void loop () {
  char ch;
  if (keyboardReady==1) {
    // Now read the keyboad inputs and send it over serial line
    // I think that the data is active low.
    Serial.write(~keyboardData);
    keyboardReady=0;
  }
  if (!bufferFull && (Serial.available() > 0)) {
    // at least one serial char available
    ch = Serial.read();
    if (digitalRead (PDEM) == 1) {
      // write directly to printer
      PORTC = ch;
      digitalWrite(PBIT7, ch>>6);
      digitalWrite(PSTBL, 0);
      digitalWrite(PSTBL, 1);  
    }
    else if (!bufferFull) {
      // store it in buffer
      buf[writeIndex++] = ch;
      bufferEmpty = 0;
      if (writeIndex == 1024) {
        writeIndex = 0;
      }
      if (writeIndex == readIndex) {
        bufferFull = 1;
      }     
    }   
  }
  if ( ( (!bufferEmpty) || (bufferFull)) && (digitalRead(PDEM) == 1) ) {
    // The printer is ready to accept a character
    ch = buf[readIndex++];
    bufferFull = 0;
    PORTC = ch;
    digitalWrite(PBIT7, ch>>6);
    digitalWrite(PSTBL, 0);
    delay(1);
    digitalWrite(PSTBL, 1);  
    if (readIndex == 1024) {
      readIndex = 0;
    }
    if (readIndex == writeIndex) {
      bufferEmpty = 1;
    }
  }
}




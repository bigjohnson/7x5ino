//#define DEBUG
//#define NOZERO
#define a 2
#define b 3
#define c 4
#define d 5
#define e 6
#define f 7
#define g 8
#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A4
#define PU A5

#define BLANK 10

/*
  0 63
  1 6
  2 91
  3 79
  4 102
  5 109
  6 125
  7 7
  8 127
  9 103
*/
unsigned char numeri[] = { 63, 6, 91, 79, 102, 109, 125, 7,  127, 103, 0 };

unsigned long displayvalue = 0;
unsigned int olddisplayvalue = 0;
unsigned char displaypos = 0;
unsigned char cifrashow[] = { BLANK, BLANK, BLANK, BLANK, BLANK, 4 };
unsigned char led[] = { S5, S4, S3, S2, S1, PU };

unsigned char secondi = 0;
unsigned char minuti = 0;
unsigned char ore = 1;

unsigned long time0;
unsigned long time1;

boolean light = true;

void mostra() {
#ifdef DEBUG
  Serial.print("P:");
  Serial.print(displaypos);
  Serial.print(" N:");
  Serial.print(cifrashow[displaypos]);
  Serial.print(" C:");
  Serial.print(numeri[cifrashow[displaypos]]);

  if ( numeri[displaypos] < 10) {
    Serial.print(" ");
  }
  if ( numeri[displaypos] < 100) {
    Serial.print(" ");
  }
#endif

  if ( displayvalue != olddisplayvalue ) {
#ifdef DEBUG
    Serial.println(displayvalue);
#endif
    setdisplayled(displayvalue);
    olddisplayvalue = displayvalue;
  }

  if ( displaypos == 0 ) {
    digitalWrite(led[5], LOW);
  } else {
    digitalWrite(led[displaypos - 1], LOW);
  }

#ifdef DEBUG
  Serial.print(" g:");
#endif
  if (  numeri[cifrashow[displaypos]] & 64) {
#ifdef DEBUG
    Serial.print("ON ");
#endif
    digitalWrite(g, LOW);
  } else {
#ifdef DEBUG
    Serial.print("OFF");
#endif
    digitalWrite(g, HIGH);
  }
#ifdef DEBUG
  Serial.print(" f:");
#endif
  if (  numeri[cifrashow[displaypos]] & 32 ) {
#ifdef DEBUG
    Serial.print("ON ");
#endif
    digitalWrite(f, LOW);
  } else {
#ifdef DEBUG
    Serial.print("OFF");
#endif
    digitalWrite(f, HIGH);
  }
#ifdef DEBUG
  Serial.print(" e:");
#endif
  if (  numeri[cifrashow[displaypos]] & 16 ) {
#ifdef DEBUG
    Serial.print("ON ");
#endif
    digitalWrite(e, LOW);
  } else {
#ifdef DEBUG
    Serial.print("OFF");
#endif
    digitalWrite(e, HIGH);
  }
#ifdef DEBUG
  Serial.print(" d:");
#endif
  if (  numeri[cifrashow[displaypos]] & 8 ) {
#ifdef DEBUG
    Serial.print("ON ");
#endif
    digitalWrite(d, LOW);
  } else {
#ifdef DEBUG
    Serial.print("OFF");
#endif
    digitalWrite(d, HIGH);
  }
#ifdef DEBUG
  Serial.print(" c:");
#endif
  if (  numeri[cifrashow[displaypos]] & 4 ) {
#ifdef DEBUG
    Serial.print("ON ");
#endif
    digitalWrite(c, LOW);
  } else {
#ifdef DEBUG
    Serial.print("OFF");
#endif
    digitalWrite(c, HIGH);
  }
#ifdef DEBUG
  Serial.print(" b:");
#endif
  if (  numeri[cifrashow[displaypos]] & 2) {

#ifdef DEBUG
    Serial.print("ON ");
#endif
    digitalWrite(b, LOW);
  } else {
#ifdef DEBUG
    Serial.print("OFF");
#endif
    digitalWrite(b, HIGH);
  }

#ifdef DEBUG
  Serial.print(" a:");
#endif
  if (  numeri[cifrashow[displaypos]] & 1 ) {
#ifdef DEBUG
    Serial.print("ON ");
#endif
    digitalWrite(a, LOW);
  } else {
#ifdef DEBUG
    Serial.print("OFF");
#endif
    digitalWrite(a, HIGH);
  }
#ifdef DEBUG
  Serial.println();
#endif
  if (light) {
    digitalWrite(led[displaypos], HIGH);
  }
  displaypos++;
  if (displaypos > 5)
  {
    displaypos = 0;
  }
}

void setdisplayled ( unsigned long numero ) {
  numero = numero % 100000;
  unsigned char cifra  = numero / 10000;

  if ( cifra ) {
    numero = numero % 10000;
    cifrashow[4] = cifra;
  } else {
#ifdef NOZERO
    cifrashow[4] = BLANK;
#else
    cifrashow[4] = 0;
#endif
  }
  cifra = numero / 1000;
  if ( cifra ) {
    numero = numero % 1000;
    cifrashow[3] = cifra;
  } else {
#ifdef NOZERO
    if ( cifrashow[4] == BLANK ) {
      cifrashow[3] = BLANK;
    } else {
      cifrashow[3] = 0;
    }
#else
    cifrashow[3] = 0;
#endif
  }
  cifra = numero / 100;
  if ( cifra ) {
    numero = numero % 100;
    cifrashow[2] = cifra;
  } else {
#ifdef NOZERO
    if ( cifrashow[3] == BLANK ) {
      cifrashow[2] = BLANK;
    } else {
      cifrashow[2] = 0;
    }
#else
    cifrashow[2] = 0;
#endif
  }
  cifra = numero / 10;
  if ( cifra ) {
    numero = numero % 10;
    cifrashow[1] = cifra;
  } else {
#ifdef NOZERO
    if ( cifrashow[2] == BLANK ) {
      cifrashow[1] = BLANK;
    } else {
      cifrashow[1] = 0;
    }
#else
    cifrashow[1] = 0;
#endif
  }
  if ( numero ) {
    cifrashow[0] = numero;
  } else {
#ifdef NOZERO
    if ( cifrashow[1] == BLANK ) {
      cifrashow[0] = BLANK;
    } else {
      cifrashow[0] = 0;
    }
#else
    cifrashow[0] = 0;
#endif
  }
}

void blinkpoint() {
  if (cifrashow[5] != 10) {
    cifrashow[5] = 10;
  } else {
#ifdef NOZERO
    if ( ore > 0 ) {
      cifrashow[5] = 8;
    } else {
      cifrashow[5] = 4;
    }
#else
    cifrashow[5] = 8;
#endif
  }
}

ISR(TIMER1_OVF_vect)
{
  mostra();
}

void setup() {
  // put your setup code here, to run once:
#ifdef DEBUG
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#endif
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S4, OUTPUT);
  pinMode(S5, OUTPUT);
  pinMode(PU, OUTPUT);
  time1 = millis();
  time0 = time1 + 250;
  TIMSK1 |= (1 << TOIE1);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long newtime = millis();
  if ( (newtime - time0) > 500 || time0 > newtime) {
    time0 = newtime;
    blinkpoint();
  }

  if ( (newtime - time1) >= 1000 || time1 > newtime) {
    time1 = newtime;

    if ( secondi > 0 ) {
      secondi--;
    }

    if (secondi == 0) {
      if ( minuti > 0 ) {
        minuti--;
      }
    }

    if ( secondi == 0 && minuti == 0 && ore == 0)
    {
      displayvalue = (unsigned long)secondi + ( (unsigned long)minuti * 100 ) + ((unsigned long)ore * 10000);
      while (true) {
          delay(500);
          light = false;
          mostra();
          delay(500);
          light = true;
          mostra();
      }
    } else if (  secondi == 0 && minuti == 0 ) {
      secondi = 59;
      minuti = 59;
      if ( ore != 0 ) {
        ore--;
      }
    } else if ( secondi == 0) {
      secondi = 59;
    }
    displayvalue = (unsigned long)secondi + ( (unsigned long)minuti * 100 ) + ((unsigned long)ore * 10000);
  }
}

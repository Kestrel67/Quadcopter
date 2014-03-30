// ARDUIN PRO (Atmel328)
#define ECHO 8
#define TRIG 13

// IMU pin D8

// F_CPU : cpu frequency

// prescale factor (each tick 0.5 us @16MHz, 0.5µs = 1/ (16000000 / 8))
const int prescale = 8;
const long precision = (1000000/ (16000000 / 1000) ) * 8; // <=> 1/ (16000000 / 8) * 10^9 (in nanosecond ns)
const byte prescaleBits = B010;    // see Table 18-1 or data sheet (binary = 0000 0010 (b)
const int sample_period = 300; // fréquence d'échantillonage en ms

unsigned int duration;

void setup()
{  
  Serial.begin(115200);
  
  //pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  
  capture();
}

void loop()
{
  delay(2000);
  Serial.println("------------------------");
  Serial.println("debut");
  capture();
  Serial.println("fin");
}

// Timer 1 interrupt vector
ISR(TIMER1_CAPT_vect)
{ 
  // rising
  if (bitRead(TCCR1B ,ICES1))
  {
    // reset counter
    TCNT1 = 0;
  
    TCCR1B &= ~_BV(ICES1);
  }
  else // falling
  {
    duration = ICR1;
    
    // on masque l'interruption capture
    bitClear(TIMSK1, ICIE1);
    
    TCCR1B = 0;
    
    // masque overflow
    //TIMSK1 &= ~_BV(TOIE1);
    
    Serial.print("durée : ");
    Serial.println(duration);
  }
  
  
}

void capture(void)
{
  TCCR1A = 0 ; // Normal counting mode
  
  // flag interruption à 0
  bitClear(TIFR1, ICF1);
  
   // flag overflow à 0
  TIFR1 &= ~_BV(TOV1);
  
  
  TCCR1B = prescaleBits ; // set prescale bits
  
  // Bit 6 – ICES1: Input Capture Edge Select (enable input capture on rising)
  TCCR1B |= _BV(ICES1);
  
  
  // enable overflow
  TIMSK1 |= _BV(TOIE1);
  
  // démarre la capture
  bitSet(TIMSK1, ICIE1);
  
  
  
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(500);
  digitalWrite(TRIG, LOW);
}


ISR(TIMER1_OVF_vect) // here if no input pulse detected
{  
  // masque
  //TIMSK1 &= ~_BV(TOIE1);
  
  Serial.print("overflow");
}


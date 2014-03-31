void setup()
{
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  bitSet(TCCR0A, WGM00);  
  bitClear(TCCR0A, WGM01);
  bitClear(TCCR0B, WGM02);
}

void loop()
{
  byte p = analogRead(0) >> 2;
  analogWrite(5, p);
  analogWrite(6, p);
}

void setup()
{
   Serial.begin(115200);
   Serial1.begin(115200); 
}

void loop()
{
  if (Serial1.available() > 0)
  {
    Serial.write(Serial1.read());
  } 
}

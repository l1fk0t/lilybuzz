/* Circuit for lylipad composed of:
- a LED
- a light sensor
- a buzzer
*/

#define sensorPin A5
#define ledPin 5
#define buzzerPin 11

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  scale();
}
  
  
void loop(){
  delay(500);
}

void beep(int frequencyInHertz, long timeInMilliseconds)
{
  int x;
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));

  for (x=0; x<loopTime; x++){
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(buzzerPin, LOW);
  }
}

void scale()
{
  digitalWrite(ledPin, HIGH);
  beep(2093,500);	//C: play the note C (C7 from the chart linked to above) for 500ms
  digitalWrite(ledPin,LOW);
}


/* Circuit for lylipad composed of:
- a LED
- a light sensor
- a buzzer
*/

#define DEBUG 1

#define sensorPin A5
#define ledPin A2
#define buzzerPin 11

#define fadeAmount 50

int sensorValue = 0;
int frequency = 0;
int wait = 0;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
}

  
void loop(){
  scale();
  sensorValue = analogRead(sensorPin);
  frequency = map(sensorValue, 0, 1024, 1, 10);
  wait = 100 * frequency;
  #ifdef DEBUG
    Serial.print(sensorValue);
    Serial.print(" => ");
    Serial.println(frequency);
  #endif
  delay(wait);
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


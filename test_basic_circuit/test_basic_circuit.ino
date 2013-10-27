/* Circuit for lylipad composed of:
- a LED
- a light sensor
- a buzzer
*/

#define DEBUG 1

#define redPin 9
#define greenPin 6
#define bluePin 5
#define buzzerPin 11

#define bledPin A2 //right
#define wled1Pin A3 //right
#define wled2Pin A4 //left
#define pledPin A5 //left


void setup(){
  pinMode(bledPin, OUTPUT);
  pinMode(wled1Pin, OUTPUT);
  pinMode(wled2Pin, OUTPUT);
  pinMode(pledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
}

  
void loop(){
  testBuzzer();
  
  testLed(bledPin);
  testLed(wled1Pin);
  testLed(wled2Pin);
  testLed(pledPin);
  
  testRGB();

 // off();
  
}

void off(){
  digitalWrite(bledPin, LOW);
  digitalWrite(wled1Pin, LOW);
  digitalWrite(wled2Pin, LOW);
  digitalWrite(pledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  color(0,0,0);
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

void testBuzzer()
{
  beep(2093,500);	//C: play the note C (C7 from the chart linked to above) for 500ms
  delay(500);
}

void testLed(int led){
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}

void testRGB(){
  // Basic colors:
  color(255, 0, 0); // turn the RGB LED red
  delay(1000);
  color(0,255, 0); // turn the RGB LED green
  delay(1000);
  color(0, 0, 255); // turn the RGB LED blue
  delay(1000);

  // Example blended colors:
  color(255,255,0); // turn the RGB LED yellow (more orange than yellow)
  delay(1000);
  color(255,255,255); // turn the RGB LED white (should be white but it is not)
  delay(1000);
  color(128,0,255); // turn the RGB LED purple
  delay(1000);
  color(0,0,0);	// turn the RGB LED off
  delay(1000);
}

void color (unsigned char red, unsigned char green, unsigned char blue) // the color generating function
{	 
  analogWrite(redPin, 255-red);	 
  analogWrite(bluePin, 255-blue);
  analogWrite(greenPin, 255-green);
}	 


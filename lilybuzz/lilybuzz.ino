//#define DEBUG 0

#define bluetoothTx 2
#define bluetoothRx 3

#define redPin 9
#define greenPin 5
#define bluePin 6
#define buzzerPin 11

#define bledPin A2 //right
#define wled1Pin A3 //right
#define wled2Pin A4 //left
#define pledPin A5 //left

int rgb_value = 0;
int intValue = 0;
int loop_count = 0;

void setup(){
  pinMode(bledPin, OUTPUT);
  pinMode(wled1Pin, OUTPUT);
  pinMode(wled2Pin, OUTPUT);
  pinMode(pledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT);

  
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  delay(100);
  
  off();
}

  
void loop(){
  
  if (Serial.available()){ //if bluetooth sent any characters
    // send ay character the bluetooth prints to the serial monitor
    int intValue = (int)Serial.read();
  #ifdef DEBUG
    Serial.print("Received integer value: ");
    Serial.println(intValue);
  #endif
  }
  
  #ifdef DEBUG
    intValue = (loop_count % 10) + 1;
    Serial.print("Received integer value: ");
    Serial.println(intValue);
  #endif
  
  switch (intValue){
    case 1: // connection ON
      rgb_green();
      break;
    case 2:  // notification
      buzz_rgb_blue();
      break;
     case 3: // system error
       rgb_red();
       break;
     case 4: // all off
       off();
       break;
     case 5:  // go straight
       digitalWrite(wled1Pin, HIGH);
       digitalWrite(wled2Pin, HIGH);
       break;
     case 6: // turn left
       digitalWrite(bledPin, LOW);
       digitalWrite(wled1Pin, LOW);
       digitalWrite(wled2Pin, HIGH);
       digitalWrite(pledPin, HIGH);
       break;
     case 7: // turn right
       digitalWrite(bledPin, HIGH);
       digitalWrite(wled1Pin, HIGH);
       digitalWrite(wled2Pin, LOW);
       digitalWrite(pledPin, LOW);
       break;
     case 8: // wrong path
       for (int i=0; i<10; i++){
         flicker_blue_pink();
       }
       break;
     case 9: //arrived
       all_leds_flash();
       off();
       break;
     case 10: // navigation off
       nav_off();
       break;
  }
  
  #ifdef DEBUG
    ++loop_count;
    delay(11000);
  #endif
  
}

void nav_off(){
  digitalWrite(bledPin, LOW);
  digitalWrite(wled1Pin, LOW);
  digitalWrite(wled2Pin, LOW);
  digitalWrite(pledPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void all_leds_flash(){
  for (int x=0; x<20; x++){
    digitalWrite(wled1Pin, HIGH);
    digitalWrite(wled2Pin, HIGH);
    digitalWrite(bledPin, HIGH);
    digitalWrite(pledPin, HIGH);
    delay(500);
    digitalWrite(wled1Pin, LOW);
    digitalWrite(wled2Pin, LOW);
    digitalWrite(bledPin, LOW);
    digitalWrite(pledPin, LOW);
  }
}

void flicker_blue_pink(){
  digitalWrite(wled1Pin, LOW);
  digitalWrite(wled2Pin, LOW);
  
  digitalWrite(bledPin, HIGH);
  digitalWrite(pledPin, HIGH);
  delay(300);
  digitalWrite(bledPin, LOW);
  digitalWrite(pledPin, LOW);
}

void off(){
  nav_off();
  rgb_off();
}
  
  
void beep(int frequencyInHertz, long timeInMilliseconds)
{
  int x;
  long delayAmount = (long)(1000000/frequencyInHertz);
  int loops = 3;

  for (x=0; x<loops; x++){
    digitalWrite(buzzerPin, HIGH);
    rgb_blue();
    delay(timeInMilliseconds);
    digitalWrite(buzzerPin, LOW);
    rgb_off();
  }
}

void buzz_rgb_blue()
{
  int bkp_rgb = rgb_value;
  beep(2093,500);	//C: play the note C (C7 from the chart linked to above)
  
  switch (bkp_rgb){
    case 0:
      rgb_red();
      break;
    case 1:
      rgb_green();
      break;
    case 2:
      rgb_blue();
      break;
  }
}


void rgb_red(){
  rgb_value = 0;
  color(255, 0, 0);
}

void rgb_green(){
  rgb_value = 1;
  color(0,255,0);
}

void rgb_blue(){
  rgb_value = 2;
  color(0,0,255);
}

void rgb_off(){
  color(0,0,0);
}

void color (unsigned char red, unsigned char green, unsigned char blue) // the color generating function
{	 
  analogWrite(redPin, 255-red);	 
  analogWrite(bluePin, 255-blue);
  analogWrite(greenPin, 255-green);
}	 


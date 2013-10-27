/* Circuit for lylipad composed of:
- a LED
- a light sensor
- a buzzer
*/
#include <SoftwareSerial.h>

#define DEBUG 1

#define bluetoothTx 2
#define bluetoothRx 3

#define redPin 9
#define greenPin 6
#define bluePin 5
#define buzzerPin 11

#define bledPin A2 //right
#define wled1Pin A3 //right
#define wled2Pin A4 //left
#define pledPin A5 //left


SoftwareSerial bluetooth(bluetoothTx,bluetoothRx);

int rgb_value = 0;
int intValue = 0;

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

  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$$$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  
  off();
}

  
void loop(){
  
  if (bluetooth.available()){ //if bluetooth sent any characters
    // send ay character the bluetooth prints to the serial monitor
    int intValue = (int)bluetooth.read();
  #ifdef DEBUG
    Serial.print("Received integer value: ");
    Serial.println(intValue);
  #endif
  }
  
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
       flicker_blue_pink();
       break;
     case 9: //arrived
       all_leds_flash();
       off();
       break;
     case 10: // navigation off
       nav_off();
       break;
  }
  
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
    digitalWrite(wled1Pin, LOW);
    digitalWrite(wled2Pin, LOW);
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
  
  do {
    digitalWrite(bledPin, HIGH);
    digitalWrite(pledPin, HIGH);
    delay(100);
    digitalWrite(bledPin, LOW);
    digitalWrite(pledPin, LOW);
  } while (intValue == 8);
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


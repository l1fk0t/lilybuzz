#define DEBUG
#define buzzerPin 11

#define bledPin A2 //right
#define wled1Pin A3 //right
#define wled2Pin A4 //left
#define pledPin A5 //left

int intValue = 0;
int loop_count = 0;

void setup(){
  pinMode(bledPin, OUTPUT);
  pinMode(wled1Pin, OUTPUT);
  pinMode(wled2Pin, OUTPUT);
  pinMode(pledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);


  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  delay(100);

  off();
}


void loop() {
  all_leds_flash();
  
  delay(1000);
  
//  digitalWrite(bledPin, LOW);
//  digitalWrite(wled1Pin, HIGH);
//  digitalWrite(wled2Pin, HIGH);
//  digitalWrite(pledPin, LOW);
//  
//  delay(1000);
  
//  digitalWrite(bledPin, LOW);
//  digitalWrite(wled1Pin, LOW);
//  digitalWrite(wled2Pin, HIGH);
//  digitalWrite(pledPin, HIGH);
//  
//  delay(1000);
  
//  digitalWrite(bledPin, HIGH);
//  digitalWrite(wled1Pin, HIGH);
//  digitalWrite(wled2Pin, LOW);
//  digitalWrite(pledPin, LOW);
//  
//  delay(1000);
//  
  digitalWrite(wled1Pin, LOW);
  digitalWrite(wled2Pin, LOW);
  digitalWrite(bledPin, HIGH);
  digitalWrite(pledPin, HIGH);
  
  delay(1000);

}

void nav_off(){
  digitalWrite(bledPin, LOW);
  digitalWrite(wled1Pin, LOW);
  digitalWrite(wled2Pin, LOW);
  digitalWrite(pledPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void all_leds_flash(){
  for (int x=0; x<5; x++){
    digitalWrite(wled1Pin, HIGH);
    digitalWrite(wled2Pin, HIGH);
    digitalWrite(bledPin, HIGH);
    digitalWrite(pledPin, HIGH);
    delay(500);
    digitalWrite(wled1Pin, LOW);
    digitalWrite(wled2Pin, LOW);
    digitalWrite(bledPin, LOW);
    digitalWrite(pledPin, LOW);
    delay(500);
  }
}


void off(){
  nav_off();
}


void beep(long timeInMilliseconds)
{
  int x;
  int loops = 3;

  for (x=0; x<loops; x++){
    digitalWrite(buzzerPin, HIGH);
    delay(timeInMilliseconds);
    digitalWrite(buzzerPin, LOW);
  }
}


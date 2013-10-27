#define DEBUG
#define redPin 9
#define greenPin 5
#define bluePin 6
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
  //pinMode(redPin, OUTPUT); 
  //pinMode(greenPin, OUTPUT); 
  //pinMode(bluePin, OUTPUT);


  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  delay(100);

  off();
}


void loop() {

  if (Serial.available()){ //if bluetooth sent any characters
    // send ay character the bluetooth prints to the serial monitor
    int intValue = (int)Serial.read();
#ifdef DEBUG
    Serial.print("Received integer value: ");
    Serial.println(intValue);
#endif

    switch (intValue){
    case  1: // connection ON
    case 49:
      break;
    case  2:  // notification
    case 50:
      Serial.println("beep");
      beep(500);
      break;
    case  3: // system error
    case 51:
      break;
    case  4: // all off
    case 52:
      off();
      break;
    case 5:  // go straight
    case 53:
      digitalWrite(bledPin, LOW);
      digitalWrite(wled1Pin, HIGH);
      digitalWrite(wled2Pin, HIGH);
      digitalWrite(pledPin, LOW);
      break;
    case 6: // turn left
    case 54:
      digitalWrite(bledPin, LOW);
      digitalWrite(wled1Pin, LOW);
      digitalWrite(wled2Pin, HIGH);
      digitalWrite(pledPin, HIGH);
      break;
    case 7: // turn right
    case 55:
      digitalWrite(bledPin, HIGH);
      digitalWrite(wled1Pin, HIGH);
      digitalWrite(wled2Pin, LOW);
      digitalWrite(pledPin, LOW);
      break;
    case 8: // wrong path
    case 56:
      digitalWrite(wled1Pin, LOW);
      digitalWrite(wled2Pin, LOW);
      digitalWrite(bledPin, HIGH);
      digitalWrite(pledPin, HIGH);
      break;
    case 9: //arrived
    case 57:
      all_leds_flash();
      off();
      break;
    case 10: // navigation off
    case 58:
      nav_off();
      break;
    }
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


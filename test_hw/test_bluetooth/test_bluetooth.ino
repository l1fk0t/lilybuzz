#include <SoftwareSerial.h>

#define bluetoothTx 2
#define bluetoothRx 3

SoftwareSerial bluetooth(bluetoothTx,bluetoothRx);

void setup(){
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  
  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$$$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
}

void loop(){
  if (bluetooth.available()){ //if bluetooth sent any characters
    // send ay character the bluetooth prints to the serial monitor
    Serial.print((char)bluetooth.read());
  }
  if (Serial.available()){ // if stuff was typed in the serial monitor
    bluetooth.print((char)Serial.read());
  }
  
  //and loop forever
}

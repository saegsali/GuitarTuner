#include <Arduino.h>


void setup() {
  // put your setup code here, to run once:
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(PD2, OUTPUT);

  const E = 82;
  
// put your main code here, to run repeatedly:
  static const uint8_t pins[] = {PD2, A5, A4, A3, A2, A1, 10, 9, 8, 7, 6 };
  for(int i = 0; i<11; i++){
    digitalWrite(pins[i], HIGH);
    delay(40);
    digitalWrite(pins[i], LOW);
    delay(40);
  }

  //for(int i = 9; i>1; i--){
  //  digitalWrite(pins[i], HIGH);
  //  delay(40);
  //  digitalWrite(pins[i], LOW);
  //  delay(40);
  //}
 
}

void loop() {
  // put your main code here, to run repeatedly:
  static const uint8_t pins[] = {PD2, A5, A4, A3, A2, A1, 10, 9, 8, 7, 6 };
  for(int i = 0; i<11; i++){
    digitalWrite(pins[i], HIGH);
    delay(40);
    digitalWrite(pins[i], LOW);
    delay(40);
  }

  //for(int i = 9; i>1; i--){
  //  digitalWrite(pins[i], HIGH);
  //  delay(40);
  //  digitalWrite(pins[i], LOW);
  //  delay(40);
  //}

}
#include <Keypad.h>
const byte rows=4;
const byte cols=4;
char layout[rows][cols]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
byte rowPins[rows]={9,8,7,6};
byte colPins[cols]={5,4,3,2};
Keypad mykeypad = Keypad(makeKeymap(layout),rowPins,colPins,rows,cols);

void setup(){
  Serial.begin(9600);
  for(int i=10; i<=13; i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
}

void loop(){
  char getkey = mykeypad.getKey();
  if (getkey == '1') {digitalWrite(10,HIGH);}
  if (getkey == '2') {digitalWrite(11,HIGH);}
  if (getkey == '3') {digitalWrite(12,HIGH);}
  if (getkey == '4') {digitalWrite(13,HIGH);}
  if (getkey == 'A') {digitalWrite(10,LOW);}
  if (getkey == 'B') {digitalWrite(11,LOW);}
  if (getkey == 'C') {digitalWrite(12,LOW);}
  if (getkey == 'D') {digitalWrite(13,LOW);}
}


/*by Kishan
keypad safe 
components used:
Keypad
Blue Led- on-System engaged
          blink-unlocked/locked
          off-safe open
Red Led- blink- Wrong password

Buzzer- 2times beep-unlocked
        2times reverse beep-Locked
        multiple beep- Wrong password

Servo motor    */
#include <Keypad.h>
#include <Servo.h>

Servo lock;


String input = "";
String password = "1234";
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3,2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
const int buzzer=11;

void setup(){
  Serial.begin(9600);
  lock.attach(10);
  lock.write(100);
  pinMode(12,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  digitalWrite(A1,LOW);
  digitalWrite(12, HIGH);
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
    input=input+key;
    tone(buzzer, 4500); delay(100); noTone(buzzer);
    Serial.println(input);
    if(key=='D'){
      Serial.println("Locked"); 
      lock.write(90);
      digitalWrite(12,LOW);  tone(buzzer, 2800);
      delay(200);
      digitalWrite(12,HIGH);   noTone(buzzer);
      delay(100);
      digitalWrite(12,LOW);  tone(buzzer,2300);
      delay(200);
      digitalWrite(12,HIGH);   noTone(buzzer);
      input = "";
    }
  }
  
  if(input.length()==4){
    if(input==password){
      Serial.println("Unlocked");
      lock.write(180);
      digitalWrite(12,HIGH);  tone(buzzer, 2300);
      delay(200);
      digitalWrite(12,LOW);   noTone(buzzer);
      delay(100);
      digitalWrite(12,HIGH);  tone(buzzer,2800);
      delay(200);
      digitalWrite(12,LOW);   noTone(buzzer);
      input = "";
    }
    else{
      Serial.println(" Wrong Password ");
      digitalWrite(A0,HIGH);
      tone(buzzer,5000);
      delay(100);
      digitalWrite(A0,LOW);
      noTone(buzzer);
      delay(100);
      digitalWrite(A0,HIGH);
      tone(buzzer,4000);
      delay(100);
      digitalWrite(A0,LOW);
      noTone(buzzer);
      delay(100);
      digitalWrite(A0,HIGH);
      tone(buzzer,3000);
      delay(100);
      digitalWrite(A0,LOW);
      noTone(buzzer);
      delay(100);
      digitalWrite(A0,HIGH);
      tone(buzzer,2000);
      delay(100);
      digitalWrite(A0,HIGH);
      noTone(buzzer);
      delay(100);
      digitalWrite(A0,LOW);
      input="";
      
    }
  }
      
}

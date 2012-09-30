#include <Servo.h>

Servo servo1, servo2;
int photo_led = A0;
int led = 7;
int start_angle = 30;
int max_angle = 175;
int jump_step = 90;
int j =0;
int mode = 1; //automatic by default
int dish_no = 0; 
int pause_time = 1000; //time in ms
int pos[3] = {10, 100, 175};

void setup() {
  
   servo1.attach(3); 
   servo2.attach(5);
   Serial.begin(9600);
   servo1.write(start_angle);
   servo2.write(start_angle);
   wait_for_number();
   wait_for_mode();
   pinMode(led, OUTPUT);
}

void loop() {
   digitalWrite(led, HIGH);  
  if (mode == 0) {manual(dish_no);}
  else  { automatic(dish_no);}
  
}
void wait_for_mode() {
 dataComing("mode", 'z');
}

void wait_for_number() {
  dataComing("number", 'n'); 
}

void manual(int loaded) {
  int i;
  for (i = 1; i <= loaded; i++){
    dataComing("manual", 'y');
  
    Serial.print("number is : ");
    Serial.println(i);
    Serial.print("light data is : ");
    Serial.println(analogRead(photo_led));
    Serial.flush();
    if (i == loaded){
      go_to(1);
    }
    else {
      int y = i+1;
      go_to(y);
    }
    
  }
}

void automatic(int loaded) {
  int i;
  for (i = 1; i <=loaded; i++){
    go_to(i);
    Serial.print("number is : ");
    Serial.println(i);
    Serial.print("light data is : ");
    Serial.println(analogRead(photo_led));
    Serial.flush();
    delay(pause_time);
  }
  dataComing("stop", 'b');
}

void go_to(int loc){
  if (loc == 1) {
     servo1.write(10);
     servo2.write(10); 
  }
  if (loc == 2){
     servo1.write(100);
     servo2.write(10); 
  }
  if (loc == 3) {
     servo1.write(175);
     servo2.write(35); 
  }
  if (loc == 4) {
     servo1.write(175);
     servo2.write(130); 
  }
}

void dataComing(String var, char c){
 
  String content = "";
  char character;
  while(content.indexOf(c) <0){
     // Serial.println('content');
      if(Serial.available() >0){
        character = Serial.read();
        content.concat(character);
      }
  }
 
  String sub = content.substring(0, content.length()-1);
  char buf[100];
  sub.toCharArray(buf, 100);
  int a = atoi(buf);
  if (var == "mode"){
    mode = a;
    if (mode == 0 ) {Serial.println("Mode is manual");}
    if (mode == 1 ) {Serial.println("Mode is automatic");}
  }
  
  if (var == "number"){
    dish_no = a;
     Serial.print("Total Dishes loaded is ");
     Serial.println(a);
  }
    
}

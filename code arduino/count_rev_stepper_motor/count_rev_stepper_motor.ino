#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int MS1 = 7;            // MS1 MS2 MS3 pin to set state
int MS2 = 6;
int MS3 = 5;
int dirPin = 3;         // pin direction
int stepPin = 4;        // pin control step
int set_up = 8;         // Pin UP
int set_down = 9;       
int rota_UCK = 10;
int rota_CK= 11;
int start = 12;
int _stop = 2;
int count;
int perStep = 400;                       // STEP

int dirr = 1;
LiquidCrystal_I2C lcd(0x27,20,4);
void setup()
{
  Serial.begin(9600);
 count = 0;
 Wire.begin();
 lcd.init();
 lcd.backlight();
 pinMode(stepPin, OUTPUT);
 pinMode(dirPin, OUTPUT);
 pinMode(set_up, INPUT);
 pinMode(set_down, INPUT);
 pinMode(start, INPUT);
 pinMode(_stop, INPUT);
 pinMode(rota_CK, INPUT);
 pinMode(rota_UCK, INPUT);
 pinMode(MS1, OUTPUT);
 pinMode(MS2, OUTPUT);
 pinMode(MS3, OUTPUT);

 // SET STATE                                  MS1  MS2  MS3
 digitalWrite(MS1, HIGH);                   // LOW  LOW  LOW  => 200 STEP
 digitalWrite(MS2, LOW );                   // HIGH LOW  LOW  => 400 STEP
 digitalWrite(MS3, LOW);                    // LOW  HIGH LOW  => 800 STEP
                                            // HIGH HIGH LOW  => 1600 STEP
                                            // HIGH HIGH HIGH => 3200 STEP
  }
void loop(){
  lcd.setCursor(0,0);
  lcd.print("Rev: ");
  lcd.setCursor(5,0);
  lcd.print(count);
  lcd.setCursor(0,1);
  lcd.print("Dir: ");
  
  int press_up = digitalRead(set_up);
  Serial.print("set up: ");
  Serial.println(press_up);
  
  int press_down = digitalRead(set_down);
  int press_CK = digitalRead(rota_CK);
  int press_UCK = digitalRead(rota_UCK);
  int press_start = digitalRead(start);
  int press_stop = digitalRead(_stop);
 

  delay(150);
  Serial.println();
  if(press_UCK == 1 & press_CK ==1 ){
     lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("Dir: ");
  }
  else{                                                   // you have to choose direction to make motor rotation
    start_state(perStep);
    }
  count_up();
  count_down();
  clockRota();
  clockUnRota();

  }

  // PRESS UP BUTTON
  void count_up(){
    int press_up = digitalRead(set_up);
    int press_CK = digitalRead(rota_CK); 
    int press_UCK = digitalRead(rota_UCK); 
    if(press_up == 0){
      count++;
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print(count);
      if (press_UCK == 0){
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print(count);
      lcd.setCursor(5,1);
      lcd.print("Counter CW");
      }
      if(press_CK == 0){
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print(count);
      lcd.setCursor(5,1);
      lcd.print("Clockwise");
      }
      
    }
  }

  // Press down button
  void count_down(){
     int press_down = digitalRead(set_down);
     int press_CK = digitalRead(rota_CK); 
     int press_UCK = digitalRead(rota_UCK); 
     if(press_down == 0){
      count--;
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print(count);
      if (press_UCK == 0){
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print(count);
      lcd.setCursor(5,1);
      lcd.print("Counter CW");
      }
      if(press_CK == 0){
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print(count);
      lcd.setCursor(5,1);
      lcd.print("Clockwise");
      }
      
    }
  }

  // CLOCKWISE
  void clockRota(){  
    int press_CK = digitalRead(rota_CK);  
    if(press_CK == 0){
      digitalWrite(dirPin, LOW);
      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Clockwise");
      }
  }

   // COUNTER CLOCKWISE
   void clockUnRota(){
    int press_UCK = digitalRead(rota_UCK);
    if(press_UCK == 0){
      digitalWrite(dirPin, HIGH);                           // đưa tín hiệu điều khiển đco quay ngược chiều
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print(count);
      lcd.setCursor(5,1);
      lcd.print("Counter CW");
    }
  }

  // PRESS START BUTTON
  void start_state( int perStep){
  int count_1 = count;
  int press_start = digitalRead(start);
  int press_stop = digitalRead(_stop);                    
  int press_CK = digitalRead(rota_CK); 
  int press_UCK = digitalRead(rota_UCK); 
  if(press_start == 0){                                   // press Start, motor rotate  
      for (int i = 0; i < count_1*perStep; i++) {
        if ((i+1) % perStep == 0){
         count--;
        }
        int press_stop = digitalRead(_stop);              // when you turn off button, step motor will stop immediately
        if(press_stop == 0){
            i = count_1*perStep;
        }
      // These four lines result in 1 step:
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
      }
    }
  }


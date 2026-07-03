// initialize the library with the numbers of the interface pins
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte ghost[8] = {
  B01110,
  B10001,
  B11011,
  B10001,
  B10001,
  B10101,
  B01010,
  B00000,
};

byte apple[8] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B10001,
  B10001,
  B01110,
  B00000,
};

byte sword[8] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B00100,
  B01110,
  B00100,
  B00000,
};

int sword_row;
int laser_row;
int ghost_row;
int ghost_x;
int laser_x;
int lose_cnt;
int win_cnt;

void setup(){
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
  // Print a message to the  LCD.
  lcd.print(" Welcome to poop");
  lcd.setCursor(0,1); //Display position
  lcd.print(" and pipi world  ");

  lcd.createChar(0, ghost);
  lcd.createChar(1, apple);
  lcd.createChar(2, sword);
  
  lcd.display();

  sword_row = 0;
  laser_row = 0;
  laser_x = 0;
  lose_cnt = 0;
  win_cnt = 0;
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
}



void loop(){
  
  delay(150);  
  lcd.clear();
  
  // Read joystick
  int joy = analogRead(A5);
  if(joy<1023/4) sword_row=0;
  if(joy>1023*3/4) sword_row=1;
  // Read Switch
   pinMode(A4, OUTPUT);
   digitalWrite(A4, HIGH);
   pinMode(A4, INPUT);
  int joy2 = analogRead(A4);
  if(joy2<(1023/2) && laser_x < 1){
    laser_row = sword_row;
    laser_x = 14;
  }
  // Move ghost
  if(ghost_x < 14) ghost_x++;
  else {
    ghost_x = 0;
    lose_cnt = 3;
  }
  // Draw Sword
  lcd.setCursor(15, sword_row);
  lcd.write(byte(2));
  // Draw Ghost
  lcd.setCursor(ghost_x, ghost_row);
  lcd.write(byte(0));
  //Draw Laser
  if(laser_x > 0){
    for(int k=14 ; k>=laser_x ; k--){
      lcd.setCursor(k, laser_row);
      lcd.print("-");
      if((laser_row == ghost_row) && (laser_x == (ghost_x + 1))){
        ghost_x = 0;
        laser_x = 1;
        ghost_row = random(0,2);
        win_cnt = 3;
        break;
      }
    }
    laser_x--;    
  }
  /*
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  lcd.setCursor(3,1);
  lcd.write(byte(0));
  lcd.setCursor(10,1);
  lcd.write(byte(1));
  
  delay(150);
  for(int k=15 ; k>=0 ; k--){    
    lcd.setCursor(k,0);
    lcd.print("-");
    delay(150);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("*");
  lcd.setCursor(1,0);
  lcd.print("*");
  lcd.setCursor(0,1);
  lcd.print("*");
  lcd.setCursor(1,1);
  lcd.print("*");
  delay(500);*/
}  

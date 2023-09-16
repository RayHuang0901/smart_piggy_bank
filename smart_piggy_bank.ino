#include "HX711.h"
#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫

// LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int t_weight = 0;
float weight = 0;
int money = 0;
// 接線設定
const int DT_PIN = 9;
const int SCK_PIN = 10;

const int scale_factor = 419; //比例參數，從校正程式中取得

HX711 scale;


void setup() {
  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);
  scale.begin(DT_PIN, SCK_PIN);

  scale.set_scale(scale_factor);       // 設定比例參數
  scale.tare();				        // 歸零
  
  Serial.println("Readings:");  //在這個訊息之前都不要放東西在電子稱上
  lcd.clear();
  lcd.setCursor(0, 0); // (colum, row)從第一排的第三個位置開始顯示
  lcd.print(money); 
}
void loop() {
  while(true){
    while(weight <=1 && weight >= -1){
      delay(1000);
      weight = scale.get_units(3);
      Serial.println(weight); 
    }
    Serial.println(weight);
    delay(2000);
    weight = scale.get_units(3);
    delay(2000);
    weight = scale.get_units(3);
    if(weight <3.7 && weight >2){
      money+=1;
    }
    else if(weight<5){
      money+=5;
    }
    else if(weight<8){
      money+=10;
    }
    else {
      money+=50;
    }
    if(weight > 2){
      
      lcd.clear();
      scale.tare();
      lcd.setCursor(0, 0); // (colum, row)從第一排的第三個位置開始顯示
      lcd.print(money);
      delay(2000);
    }
  }
}

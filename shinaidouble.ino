#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int zpin = A2;
double z;
double zVal;
double acceleration;
double max = 0;

float aList[500] = {0};

void setup() {

    //lcd setup
    lcd.init();
    lcd.backlight();

    //means start in Japanese
    lcd.print("   Hajime!!!!");
    
    Serial.begin(9600);
}

void loop() {
    
    
    for (int i=1; i<500; i++){
      aList[i] = accCalc();
      
      
      if (aList[i] > max){
        max = aList[i];
      }
      
    }
    
    Serial.print(max);
    Serial.print("\t");
    
    lcd.setCursor(0,1);
    lcd.print("   Z:  ");
    lcd.print(max);
    lcd.print("g");
    lcd.print("    ");
    
    delay(250);
}

//calculations to determine acceleration
double accCalc(){
    z = analogRead(zpin);
    //convert reading to voltage
    zVal = (z/1024)*5;
    //convert voltage to acceleration (g)
    acceleration = (zVal - 1.7)/0.3;
      
    return acceleration;

    }  

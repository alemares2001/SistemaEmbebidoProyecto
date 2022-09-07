#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>                
#include <DallasTemperature.h>
#define Pin 3


LiquidCrystal_I2C lcd(0x3F,16,2);  //
OneWire ourWire(Pin);
DallasTemperature sensors(&ourWire);
float calibration_value = 21.34 - 0.7;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
float ph_act;


void setup() 
{
  Wire.begin();
  sensors.begin();
 Serial.begin(115200);
 
  lcd.init();
  lcd.backlight();
  
  
}
void loop() {
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6; 
  ph_act = -5.70 * volt + calibration_value;
sensors.requestTemperatures();   
float temp= sensors.getTempCByIndex(0);

// Serial.print("Temperatura = ");
// Serial.print(temp);
// Serial.println(" C");
//  Serial.println("pH = ");
//  Serial.print(ph_act);



 lcd.setCursor(0, 0);
 lcd.print("Temp = ");
 lcd.print(temp);
 lcd.print(" C");
 lcd.setCursor(0, 1);
 lcd.print("pH = ");
 lcd.print(ph_act);
 
Serial.println(String("PH,")+ph_act);
delay(1000);
Serial.println(String("Temp,")+temp);
delay(1000);
}

 

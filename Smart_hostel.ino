#include<Wire.h>
#include "TSL2561.h"
#include<Adafruit_SSD1306.h>
#include<Adafruit_GFX.h>
#define OLED_ADDR 0x3C
#include "dht.h"
#define DHT11_PIN D7
#define LED D3
TSL2561 tsl(TSL2561_ADDR_FLOAT); 
dht DHT11;
Adafruit_SSD1306 display(-1);
#define trigPin D6
#define echoPin D5
long duration;
float distance;
char data;
#define MOTORG D0
#define BUZ D4
#define FAN D8
void setup() {
  //Display
  Serial.begin(9600);//baud min-rate
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);   // initialize and clear display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,20);
  display.print("ASUS TEAM");
  display.display();
  //UltraSonic Sensor
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  digitalWrite(trigPin,LOW);
  if (tsl.begin()) {
  tsl.setGain(TSL2561_GAIN_16X);      // 16x gain (for dim situations)
  
  tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);  // shortest integration time (bright light)
  //tsl.setTiming(TSL2561_INTEGRATIONTIME_101MS);  // medium integration time (medium light)
  //tsl.setTiming(TSL2561_INTEGRATIONTIME_402MS);  // longest integration time (dim light)
  }
}

void loop() {
  //UltraSonic Sensor
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance=duration*0.034/2;
  if(distance<5){
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Enter the pass code ");
    delay(10000);
    display.display();
    //Bluetooth read data
    if(Serial.available() > 0)      // Send data only when you receive data:
   {
      display.clearDisplay();
      display.print("Bluetooth");
      display.display();
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor       
      if(data == 'a')      {
       
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("WELCOME");
        display.display();
        delay(3000);
      }
      else{
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("PASS CODE ENTERED IS WRONG");
        display.display();
        digitalWrite(BUZ,HIGH);
        delay(3000);
        digitalWrite(BUZ,LOW);
      }
  
   }
   else{
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Please Enter the pass code");
    delay(5000);
    display.display();
   }
   
  }
  int temp=DHT11.read11(DHT11_PIN);
  if(temp==0){
    if (DHT11.temperature>25){
      
      digitalWrite(FAN,HIGH);
      }
    else{
      digitalWrite(FAN,LOW);
      delay(2000);
    }
  }
  uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE);
  if(x<40){
    analogWrite(LED,255);
  }
  else if(x<360){
    analogWrite(LED,127);
  }
  else if(x<460){
    analogWrite(LED,77);
  }
  else if(x<1000){
    analogWrite(LED,52);
  }
  else{
    analogWrite(LED,0);
  }
 

}

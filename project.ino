#include<Servo.h>
#include<LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN 5     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
Servo myServo;
int servoPin=9;
int RGB_LED[] = {13,12,11};//13번 RED, 12번 GREEN, 11번 BLUE
LiquidCrystal lcd(44,45,46,47,48,49);
DHT dht(DHTPIN, DHTTYPE);
float hum;  //Stores humidity value
float temp; //Stores temperature value
int flag=1;
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
   dht.begin();
   myServo.attach(servoPin);
   for (int i=0; i<3; i++){
    pinMode(RGB_LED[i],OUTPUT);
  }
}

void RGBLED(float R) //불쾌지수 표현
{

if(R>=85){//빨간불
digitalWrite(RGB_LED[0],LOW);
digitalWrite(RGB_LED[1],HIGH);
digitalWrite(RGB_LED[2],HIGH);

}else if(R<85 && R>=75){ //노란불
analogWrite(RGB_LED[0],150);
analogWrite(RGB_LED[1],150);
digitalWrite(RGB_LED[2],HIGH);

}else if (R<75 && R>=68){//파란불
digitalWrite(RGB_LED[0],HIGH);
digitalWrite(RGB_LED[1],HIGH);
digitalWrite(RGB_LED[2],LOW);
}
else{ //초록불
digitalWrite(RGB_LED[0],HIGH);
digitalWrite(RGB_LED[1],LOW);
digitalWrite(RGB_LED[2],HIGH);

}}
  
void Servomotor(int a){
 /*int angle;       // 축 제어 값
  for (angle = 0; angle < 180; angle++) { // 0도에서 180도로
    myServo.write(angle);
    delay(5);
  }
  delay(1000);*/
  
 if(a<=500){  //블라인드 닫힘
    if(flag==0){
  int angle=180;
   myServo.write(angle);
   flag=1;
  }}
  else{     //블라인드 열림
    if(flag==1){
    int angle=0;
  myServo.write(angle);
  flag=0;
  
}}}
void TextLCD(float a,float b){
  lcd.begin(16,2);
  lcd.print("Temp: "+String(a));
  lcd.setCursor(0,1);
  lcd.print("Hum: "+String(b));
   //delay(1000);
   //lcd.clear() ;
   lcd.setCursor(0,0);
  }
void loop() { 
 char temp1[3];
  if(Serial1.available()>0){
 for(int i=0;i<3;i++){
  char a= Serial1.read();
  temp1[i]=a;}   
  int pos = atoi(temp1);
  Serial.println(pos);
  delay(1000);
 
hum = dht.readHumidity();//온도 읽기
temp= dht.readTemperature();//습도 읽기
  
  //Serial.print("Humidity: ");
  //Serial.print(hum,0);// 소수 이하 자리 없음
 // Serial.print(" %, Temp: ");
 // Serial.print(temp, 1);//소수 이하 1자리 허용
 // Serial.println(" Celsius");
  //delay(2000);// 샘플링 간격 2초 부여
  float a =hum/100;
  float b =temp;
float V = 1.8*b-0.55*(1-a)*(1.8*b-26)+32;//불쾌지수 구하는 식
Serial.println(V);
RGBLED(V);
TextLCD(temp,hum);
 Servomotor(500);}
 

}

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address to 0x27 with 16 chars and 2 lines

int trigerpin = 3;
int echo = 2;
long duration;
int distance;

int trigerpin1 = 4;
int echo1 = 5;
long duration1;
int distance1;
int threshold1 =8;
int threshold2 =8;
int irSensor=7;
#include <Servo.h>

Servo servo;  // create servo object to control a servo

void setup() {
  pinMode(irSensor,INPUT);

  servo.attach(9);  // attaches the servo on pin 9 to the servo objectư
  //servo.write(0);   // rotate slowly servo to 0 degrees immediately
  Serial.begin(9600);
  pinMode(trigerpin, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trigerpin1, OUTPUT);
  pinMode(echo1, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("VEHICLE PARKING  ");
  lcd.setCursor(0, 1);
  lcd.print("   MANAGEMENT    ");
  delay(3000);
  lcd.clear();
}

void loop() {

  ultrasonic1();
  ultrasonic2();
  if ((distance>= threshold1) && (distance1 >= threshold2)) {
    lcd.setCursor(0, 0);
    lcd.print("SLOT 1 AVAILABLE ");
    lcd.setCursor(0, 1);
    lcd.print("SLOT 2 AVAILABLE ");
    delay(2000);
  }
    if ((distance < threshold1) && (distance1 >= threshold2)) {
    lcd.setCursor(0, 0);
    lcd.print("SLOT 1 OCCUPIED  ");
    lcd.setCursor(0, 1);
    lcd.print("SLOT 2 AVAILABLE ");
     delay(2000);
  }
   if ((distance >= threshold1) && (distance1 < threshold2)) {
    lcd.setCursor(0, 0);
    lcd.print("SLOT 1 AVAILABLE ");
    lcd.setCursor(0, 1);
    lcd.print("SLOT 2 OCCUPIED  ");
     delay(2000);
  }
  if ((distance <= threshold1) && (distance1 <= threshold2)) {
    lcd.setCursor(0, 0);
    lcd.print("NO SLOT AVAILABLE ");
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    servo.write(0);
     delay(2000);
  }
if(digitalRead(irSensor)==LOW){
   
    servo.write(0);  // control servo to go to position in variable 'pos'
           // waits 10ms for the servo to reach the position
     
  }
  else{
     // rotate from 180 degrees to 0 degrees, one by one degree
    servo.write(180);                     // control servo to go to position in variable 'pos'
                               // waits 10ms for the servo to reach the position
     
  }  
}

void ultrasonic1() {
  digitalWrite(trigerpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerpin, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * .034 / 2;
  Serial.println("distance");
  Serial.println(distance);
  delay(500);
}

void ultrasonic2() {
  digitalWrite(trigerpin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerpin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerpin1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = duration1 * .034 / 2;
  Serial.println("distance1");
  Serial.println(distance1);
  delay(500);
}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/**********************************************************/
#define MQ_7 A0
#define buzzer 13
#define PIN_RELAY_1  2 // the Arduino pin, which connects to the IN1 pin of relay module
#define PIN_RELAY_2  3 // the Arduino pin, which connects to the IN2 pin of relay module
#define PIN_RELAY_3  4 // the Arduino pin, which connects to the IN3 pin of relay module
#define PIN_RELAY_4  5 // the Arduino pin, which connects to the IN4 pin of relay module

float analysis(int);
//float Rs;
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight
   // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Cmon=");
  pinMode(buzzer, OUTPUT);
  pinMode(PIN_RELAY_1, OUTPUT);
  pinMode(PIN_RELAY_2, OUTPUT);
  pinMode(PIN_RELAY_3, OUTPUT);
  pinMode(PIN_RELAY_4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float Cmon;
  float rs;
  int sensorValue = analogRead(MQ_7);
  Serial.print("adc : ");
  Serial.print(sensorValue);
  Serial.print("\t");
  Serial.print("Carbon monoxide : ");
  Serial.print(analysis(sensorValue));
  Serial.print("ppm");
  Serial.print("\t");
  Serial.print("Sensor resistance : ");
  Serial.println(rs);
  Cmon=analysis(sensorValue);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Cmon=");
  lcd.setCursor(8,0);
  lcd.print(Cmon);
   if((Cmon>=50)&&(Cmon<200))
  {
    digitalWrite(buzzer,LOW);
   // Serial.println("Low Carbon monoxide");
     Serial.println("Turn on all");
    digitalWrite(PIN_RELAY_1, HIGH);
    digitalWrite(PIN_RELAY_2, HIGH);
    digitalWrite(PIN_RELAY_3, HIGH);
    digitalWrite(PIN_RELAY_4, HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(buzzer,HIGH);
      Serial.println("Turn off all");
    digitalWrite(PIN_RELAY_1, LOW);
    digitalWrite(PIN_RELAY_2, LOW);
    digitalWrite(PIN_RELAY_3, LOW);
    digitalWrite(PIN_RELAY_4, LOW);
   // Serial.println("High Carbon monoxide");
    delay(500);
  }
  delay(500);
}

float analysis(int adc){
  float rs;
  float slope = -0.7516072988;
  float A = 45.87510694;
  float Rseries = 1000;
  float V_Rseries = ((float)adc*5)/1023;
  rs = ((5-V_Rseries)/V_Rseries)*Rseries;
  float R0 = 400;
  float Y = rs/R0;
  float CO_ppm = pow(10,(log10(Y/A)/slope));
  return CO_ppm;
}

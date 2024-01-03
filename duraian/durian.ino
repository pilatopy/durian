/********************************
LCD Run
********************************/
//Boytu_13@gmail.com
/********************************/
// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//int abc = 500;
int adcPin = 0;
int adcValue = 0;
int test=0;
float v;
float rs;
int A[7];
int B[7];
int y[7];
int i;
int d;
int beep = 13;
int ledRaw = 9;
int ledMed = 10;
int ledRip = 11;
int adc2;
/**********************************************************/
LiquidCrystal_I2C lcd(0x3F,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display 0x3F(Booooy)
/*********************************************************/
void setup()
{
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  lcd.begin(16, 3);    // set up the LCD's number of columns and rows: 
  lcd.setCursor(3, 0);
  lcd.print("ADC=");
  Serial.begin (9600);
  pinMode(beep, OUTPUT);
  pinMode(ledRaw, OUTPUT);
  pinMode(ledMed, OUTPUT);
  pinMode(ledRip, OUTPUT);
  delay (2000);
}
/*********************************************************/
void loop() 
{  delay(500);
////////////////////////////////////////////////////////////////////////////
   int n=7;
   float slopeM;
   int nxy;
   int sigmaX=210;
   int sigmaY;
   int mxy;
   int dnxy;
   float c;
   float data;
   int sigmaXY;
   for(i=0;i<7;i++)
   {   y[i] = analogRead(adcPin);
            Serial.print("ADC=");       
            Serial.println (y[i]);
            lcd.clear();
            lcd.setCursor(3,0);
            lcd.print("ADC=");
            lcd.setCursor(7,0);
            lcd.print(y[i]);
            //digitalWrite(beep,HIGH);
            delay(5000);
   }
   sigmaY=(y[0])+(y[1])+(y[2])+(y[3])+(y[4])+(y[5])+(y[6]);
   sigmaXY=(0*y[0])+(5*y[1])+(10*y[2])+(15*y[3])+(20*y[4])+(25*y[5])+(30*y[6]);
   nxy=7*sigmaXY;
   mxy=105*sigmaY;
   dnxy=nxy-mxy;
   slopeM=dnxy/4900;
   c=(sigmaY-(105*slopeM))/7;
   data=(600*slopeM)+c;

///////////////////////////////////////////////////////////////////////////

    digitalWrite(beep,HIGH);
    delay(50);
    digitalWrite(beep,LOW);
    delay(50);
    digitalWrite(beep,HIGH);
    delay(50);
    digitalWrite(beep,LOW);
    delay(50);
    digitalWrite(beep,HIGH);
    digitalWrite(ledRaw,LOW);
    digitalWrite(ledMed,LOW);
    digitalWrite(ledRip,LOW);


    if(data<100){
              lcd.setCursor(0,1); 
              //lcd.print("yh=");
             //lcd.print(data);
              lcd.setCursor(9,1);             
              //lcd.print("=>");
              lcd.print("Raw");                                                                    
              Serial.println ("Raw");
              Serial.println ("Raw");
              digitalWrite(ledRaw,HIGH);
              digitalWrite(ledMed,LOW);
              digitalWrite(ledRip,LOW);
              }
    else if(data>=100&&data<=154){
              lcd.setCursor(0,1); 
              //lcd.print("yh=");
              //lcd.print(data);
              lcd.setCursor(9,1);             
               //lcd.print("=>");
              lcd.print("Med");  
                                                                                                                           
              Serial.println ("Med");
              Serial.println ("Med");
              digitalWrite(ledRaw,LOW);
              digitalWrite(ledMed,HIGH);
              digitalWrite(ledRip,LOW);
              }
    else if(data>154){
              lcd.setCursor(0,1); 
              //lcd.print("yh=");
              //lcd.print(data);
              lcd.setCursor(9,1);             
               //lcd.print("=>");
              lcd.print("Rip"); 
              Serial.println ("Rip");
               Serial.println ("Rip");
              digitalWrite(ledRaw,LOW);
              digitalWrite(ledMed,LOW);
              digitalWrite(ledRip,HIGH);
             }
      delay(5000);
      digitalWrite(beep,HIGH);
      delay(50);
      digitalWrite(beep,LOW);
      delay(50);
      digitalWrite(beep,HIGH);
      delay(50);
      digitalWrite(beep,LOW);
      delay(50);
      digitalWrite(beep,HIGH);
      digitalWrite(ledRaw,LOW);
      digitalWrite(ledMed,LOW);
      digitalWrite(ledRip,LOW);
      test=adcValue;
}

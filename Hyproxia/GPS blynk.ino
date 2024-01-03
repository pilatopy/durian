#include <TinyGPS.h>

#include <Blynk.h>

#define BLYNK_PRINT Serial
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_TEMPLATE_ID "TMPL6N4lr5cJ1"
#define BLYNK_TEMPLATE_NAME "gpsssss"

static const int RXPin = 4, TXPin = 5;   
static const uint32_t GPSBaud = 9600; 

TinyGPSPlus gps;
WidgetMap myMap(V0);  

SoftwareSerial ss(RXPin, TXPin);

BlynkTimer timer;

float speeding;       
float state;      

char auth[] = "vS1nJs1CvLuc0BjD2h3aXGTrqQC-6GOh";  
char ssid[] = "Hypoxia"; 
char pass[] = "10001111";                                     
      
unsigned int move_index = 1;       
  
int smokeA0 = A0;
int data = 0;
int sensorThres = 100;
void setup()
{
  Serial.begin(115200);
  Serial.println();
  ss.begin(GPSBaud);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, checkGPS); 
  pinMode(smokeA0, INPUT);
  //dht.begin();
  timer.setInterval(2500L, sendSensor);
}

void checkGPS(){
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
     Blynk.virtualWrite(V4, "GPS ERROR");  // Value Display widget  on V4 if GPS not detected
      }
}
void sendSensor(){
 
 int data = analogRead(smokeA0);
 Blynk.virtualWrite(V0, data);
  Serial.print("Pin A0: ");
  Serial.println(data);


  if(50< data <200 ){
    //Blynk.email("test@gmail.com", "Alert", "Gas Leakage Detected!");
    Blynk.logEvent("CO danger level");
  }
}
void loop()
{
    while (ss.available() > 0) 
    {
      if (gps.encode(ss.read()))
        displayInfo();
  }
  Blynk.run();
  timer.run();
}

void displayInfo()
{ 
  if (gps.location.isValid() ) 
  {    
    float latitude = (gps.location.lat());     
    float longitude = (gps.location.lng()); 
    
    Serial.print("LAT:  ");
    Serial.println(latitude, 6); 
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
    Blynk.virtualWrite(V13, String(latitude, 6));   
    Blynk.virtualWrite(V14, String(longitude, 6));  
    myMap.location(move_index, latitude, longitude, "รถของฉัน");
    speeding = gps.speed.kmph();        
       Blynk.virtualWrite(V15, speeding);
       state = gps.satellites.value();    
       Blynk.virtualWrite(V16, state);               
  }
  
}

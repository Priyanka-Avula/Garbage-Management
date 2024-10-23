#define BLYNK_TEMPLATE_ID "TMPL3JeRJ4Wg5"
#define BLYNK_TEMPLATE_NAME "ultrasonic"
#define BLYNK_AUTH_TOKEN "Eq1582lERNzPuZA4bQqcSdGFRGgNt_hT"
#define BLYNK_PRINT Serial

#include<WiFi.h>
#include<BlynkSimpleEsp32.h>

const char ssid[]="CHINNI";
const char password[]="priyanka";
int moistureSensor = 35;
int ultrasonicTrigger = 4;
int ultrasonicEcho = 5;
int moistureThreshold = 2800;
long duration;
int distance;
String distanceState;
String distanceAction;

void setup() {
  pinMode(moistureSensor, INPUT);
  pinMode(ultrasonicTrigger, OUTPUT);
  pinMode(ultrasonicEcho, INPUT);
   Blynk.begin(BLYNK_AUTH_TOKEN,ssid,password);
  Serial.begin(115200);
}

void loop() {
  Blynk.run();
  int moistureValue = analogRead(moistureSensor);

  // Read ultrasonic distance
  digitalWrite(ultrasonicTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigger, LOW);
  duration = pulseIn(ultrasonicEcho, HIGH);
  distance = duration * 0.034 / 2;
  Blynk.virtualWrite(V0,distance);
  if(distance<30)
  {
     distanceState = "bin is full";
    distanceAction = "motor on";
    Blynk.logEvent("dust_bin","garbage bin is filled");

  }
  else
  {
    distanceState = "bin is not full";
    distanceAction = "motor on";
  }

  // Print values
  Serial.print("#"); 
  Serial.print(","); 
  Serial.print(moistureValue); 
  Serial.print(","); 
  Serial.print(distance); 
  Serial.print(","); 
  Serial.print(distanceState); 
  Serial.print(",");
  Serial.print(distanceAction);
  Serial.print(",");
  Serial.println("~"); 
  delay(2000);
}

#include <HCSR04.h>

// defines pins numbers / definition des broches du capteur
const int L1 = 7;
const int trigPin = 2;
const int echoPin = 3;
float mesure;
float mesure2;
float mesure3;
float vitesse;
float mesure4;
float distancesecu = 30;

float restedistance;
float tempsvehicule;

UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);
void setup() {
  pinMode (L1, OUTPUT);
  Serial.begin(9600); 
}
void loop() {

  mesure4 = distanceSensor.measureDistanceCm();
  Serial.println("distance totale :");
  Serial.println(mesure4);
  delay(5000);
   
   mesure = distanceSensor.measureDistanceCm();
   Serial.println("mesure 1 est de : ");
   Serial.println(mesure);
    delay(1000);
   
    mesure2 = distanceSensor.measureDistanceCm();
  Serial.println("mesure 2 est de : ");
  Serial.println (mesure2);
delay(1000);

mesure3 = mesure - mesure2;
abs(mesure3);

vitesse = mesure3 * 3,6;
vitesse = vitesse / 3,6;

Serial.println("la vitesse est de :");
Serial.println(vitesse);
Serial.println ("cm/s");
delay(1000);

restedistance = mesure4 - distancesecu;
tempsvehicule = (restedistance * 1)/ vitesse;

Serial.println ( " le temps que le vehicule prendra sera de :  ");
Serial.println (tempsvehicule);
delay(50000000);



}

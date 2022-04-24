
#include <OneWire.h>
#include <DallasTemperature.h> 
#include <SPI.h>
#include <Ethernet.h>


int signalIdEssai = 2;

//capteur de température et humidité

OneWire oneWire (7); 
DallasTemperature sensors(&oneWire); 
DeviceAddress sensorDeviceAddress; 

int frequencyTemp = 1024;

//Nombre de cycle
unsigned long nbcycle = 0;

//fréquence du modulo
int frequency = 40;

// seuil de conformité
const int seuil = 0;


//Nombre de cateurs
int nbCap=15;
int list[15];

// id de l'essai
int idEssai = 0;
int pos = 1;

// variables des photorésistances
int led0 = 0;
int led1 = 0;
int led2 = 0;
int led3 = 0;
int led4 = 0;
int led5 = 0;
int led6 = 0;
int led7 = 0;
int led8 = 0;
int led9 = 0;
int led10 = 0;
int led11= 0;
int led12= 0;
int led13= 0;
int led14= 0;
int idCap1 = -1;
int idCap2 = -1;
int idCap3 = -1;
int idCap4 = -1;
int idCap5 = -1;
int idCap6 = -1;
int idCap7 = -1;
int idCap8 = -1;
int idCap9 = -1;
int idCap10 = -1;
int idCap11= -1;
int idCap12= -1;
int idCap13= -1;
int idCap14= -1;
int idCap15= -1;


// variables du démarage des acquisitions de données
int cinqv = 8;
int val = 0;
int ret = 0;

// parametrage du micro controlleur
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "dev.epl.local";

IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

EthernetClient client;

// Variables de mesure de la vitesse
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = false;

/**
 * Méthode permettant de créer un essai dans la base de données, et de retourner son ID
 *
 */
void createEssai() {

    if (client.connect(server, 80)) {
       Serial.println("connected");
       client.println("GET /php/test/createEssai.php HTTP/1.0");
       client.println();

    } else {
      Serial.println("connection failed");
    }
    String c;

    while (client.connected()){
      if(client.available()){
        char letter = client.read();
        String myString = String(letter);
        c += myString;
      }
    }
    int index = c.indexOf("<p>")+3;
    int index2 = c.indexOf("</p>");

    String ret = "";

    for (int i =index; i<index2; i++) ret += c[i];
    idEssai = ret.toInt();

}

/**
 * Méthode permettant de créer les capteurs dans la base de données, et de retourner leurs ID sous forme de liste
 *
 * @param EthernetClient
 * @param int
 * @param int
 */
void createCap() {

  for(int i = 0; i<nbCap; i++) {
    if (client.connect(server, 80)) {
       Serial.println("connected");
       int posi = pos+i;
       client.println("GET /php/test/createCap.php?idessai="+ String(idEssai) +"&position="+ String(posi) +" HTTP/1.0");
       client.println();

    } else {
      Serial.println("connection failed");
    }
    String c;

    while (client.connected()){
      if(client.available()){
        char letter = client.read();
        String myString = String(letter);
        c += myString;
      }
    }
    int index = c.indexOf("<p>")+3;
    int index2 = c.indexOf("</p>");

    String ret = "";

    for (int i =index; i<index2; i++) ret += c[i];
    list[i] = ret.toInt();

  }
}


/**
 * Méthode permettant d'insérer les données d'une température
 *
 * @param int
 * @param int
 * @param int
 *
 */

void push(int idessai, unsigned long time, float value){
  int valid = 1;
    if (led0 <= seuil) valid = 0;
    String data = "idessai=" + String(idessai) + "&time=" + String(time) + "&value=" + String(value);
    if (client.connect("dev.epl.local",80) ) {
      client.println("POST /php/test/pushTemp.php HTTP/1.1");
      client.println("Host: dev.epl.local");
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.println(data.length());
      client.println();
      client.print(data);
    } else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }
}

/**
 * Méthode permettant d'insérer les données d'un capteur
 *
 * @param int
 * @param int
 * @param int
 *
 */

void push(int value, int idCap, unsigned long time){
  int valid = 1;
    if (led0 <= seuil) valid = 0;
    String data = "value=" + String(value) + "&time=" + String(time) + "&valid=" + String(valid) + "&idCap=" + String(idCap);
    if (client.connect("dev.epl.local",80) ) {
      client.println("POST /php/test/pushValue.php HTTP/1.1");
      client.println("Host: dev.epl.local");
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.println(data.length());
      client.println();
      client.print(data);
    } else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }
}

/**
 * Méthode permettant d'insérer les données d'un capteur avec une valeur à zero mais valide
 *
 * @param int
 * @param int
 * @param int
 *
 */

void pushzero(int idCap, unsigned long time){
    String data = "value=0&time=" + String(time) + "&valid=1&idCap=" + String(idCap);
    if (client.connect("dev.epl.local",80) ) {
      client.println("POST /php/test/testArduino1.php HTTP/1.1");
      client.println("Host: dev.epl.local");
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.println(data.length());
      client.println();
      client.print(data);
    } else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }
}



void setup() {
 
 pinMode(signalIdEssai, OUTPUT);
  
 
 /**
  * Configuration de l'acquisition du capteur de temperature DS18B20
  */
  sensors.begin(); 
  sensors.getAddress(sensorDeviceAddress, 0); //Demande l'adresse du capteur à l'index 0 du busn
  sensors.setResolution(sensorDeviceAddress, 12); //Résolutions possibles: 9,10,11,12n}


  /**
   * Designation de l'entrée 5v en tant qu'entrée
   */
  pinMode(cinqv, INPUT);
  unsigned long(millis());


/**
 * Lancement du port série
 */
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  /**
   * Parametrage DHCP
   */
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1);
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");



  beginMicros = micros();

sensors.requestTemperatures();

  //Création de l'essai
  createEssai();
  Serial.println(idEssai);
  //Création et affactation des capteurs
  createCap();
  idCap1 = list[0];
  Serial.println(idCap1);
  idCap2 = list[1];
  idCap3 = list[2];
  idCap4 = list[3];
  idCap5 = list[4];
  idCap6 = list[5];
  idCap7 = list[6];
  idCap8 = list[7];
  idCap9 = list[8];
  idCap10 = list[9];
  idCap11= list[10];
  idCap12= list[11];
  idCap13= list[12];
  idCap14= list[13];
  idCap15= list[14];
  

/**
 * Envoie un signal aux Arduino esclave comme quoi l'essai a été crée
 */
digitalWrite(signalIdEssai, HIGH);
  
}


void loop() {

  if ( nbcycle%frequencyTemp==0) {
      float temp = sensors.getTempCByIndex(0);
      push(idEssai,(unsigned long) millis() ,temp);
      Serial.println(temp);
  }

  //Récuperation des valeurs des photoresistances
  led0 = analogRead(A2);
  led1 = analogRead(A3);
  led2 = analogRead(A0);
  led3 = analogRead(A1);
  led4 = analogRead(A4);
   led5 = analogRead(A5);
 led6 = analogRead(A6);
   led7 = analogRead(A7);
   led8 = analogRead(A8);
  led9= analogRead(A9);
   led10 = analogRead(A10);
   led11= analogRead(A11);
 led12= analogRead(A12);
 led13= analogRead(A13);
 led14= analogRead(A14);
  //Recupération d'une tension d'entrée de 5V
  val = digitalRead(cinqv);

  //Variables de récupération du temps
  String t2 = String((unsigned long) millis());


  //Envoie d'une donnée 0 quand il reçoit un changement d'état de la tension d'entrée
  if (val != ret) {
      Serial.println("attention c'est débranché");
      pushzero(idCap1, (unsigned long) millis());
      pushzero(idCap2, (unsigned long) millis());
      pushzero(idCap3, (unsigned long) millis());
       pushzero(idCap4, (unsigned long) millis());
      pushzero(idCap5, (unsigned long) millis());
      pushzero(idCap6, (unsigned long) millis());
      pushzero(idCap7, (unsigned long) millis());
       pushzero(idCap8, (unsigned long) millis());
      pushzero(idCap9, (unsigned long) millis());
      pushzero(idCap10, (unsigned long) millis());
      pushzero(idCap11, (unsigned long) millis());
      pushzero(idCap12, (unsigned long) millis());
      pushzero(idCap13, (unsigned long) millis());
      pushzero(idCap14, (unsigned long) millis());
       pushzero(idCap15, (unsigned long) millis());
  }


  //Simplification de l'affichage et de la vitesse de traitement du port série
  int len = client.available();
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len);
    }
    byteCount = byteCount + len;
  }

  //Envoie les valeurs des photoresistances lorsque la tension d'entrée est à 5V
  if (/*val == HIGH*/true){
    if ( nbcycle%frequency==0 || led0<seuil ) {
      push(led0, idCap1, (unsigned long) millis());
    }
    if ( nbcycle%frequency==0 || led1<seuil ) {
      push(led1, idCap2, (unsigned long) millis());
    }
    if ( nbcycle%frequency==0 || led2<seuil ) {
      push(led2, idCap3, (unsigned long) millis());
    }
    if ( nbcycle%frequency==0 || led3<seuil ) {
      push(led3, idCap4, (unsigned long) millis());
    }
  
  
  if ( nbcycle%frequency==0 || led0<seuil ) {
      push(led4, idCap5, (unsigned long) millis());
    }
    if ( nbcycle%frequency==0 || led1<seuil ) {
      push(led5, idCap6, (unsigned long) millis());
    }
    if ( nbcycle%frequency==0 || led2<seuil ) {
      push(led6, idCap7, (unsigned long) millis());
    }
    if ( nbcycle%frequency==0 || led3<seuil ) {
      push(led7, idCap8, (unsigned long) millis());
    }
  
  if ( nbcycle%frequency==0 || led0<seuil ) {
      push(led8, idCap9, (unsigned long) millis());
    }
    if ( nbcycle%frequency==0 || led1<seuil ) {
      push(led9, idCap10, (unsigned long) millis());
    }
    if ( nbcycle%frequency==0 || led2<seuil ) {
      push(led10, idCap11, (unsigned long) millis());
    }
    if ( nbcycle%frequency==0 || led3<seuil ) {
      push(led11, idCap12, (unsigned long) millis());
    }
  
  if ( nbcycle%frequency==0 || led0<seuil ) {
      push(led12, idCap13, (unsigned long) millis());
    }
    if ( nbcycle%frequency==0 || led1<seuil ) {
      push(led13, idCap14, (unsigned long) millis());
    }
    if ( nbcycle%frequency==0 || led2<seuil ) {
      push(led14, idCap15, (unsigned long) millis());
    }
  
  }


  ret = val;
  nbcycle++;
}
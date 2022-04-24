#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
char ssid [ ] = "Enter your ssid";
char pass [ ] = "Pass of ssid";

const char *host = "www.google.fr"; //Domain to Server
String path = "/search?q=arduino"; //Path of Server
const int httpsPort = 443; //HTTPS PORT (default: 443)
int refreshtime = 15; //Make new HTTPS request after x seconds
String datarx; //Received data as string
long crontimer;

void setup()
{
  Serial.begin(9600);
  Serial.println();


  WiFi.begin(ssid, pass);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if(crontimer < millis()/1000){
    crontimer = (millis()/1000)+refreshtime;
    callhttps(); //
  }
}

  
  void callhttps(){
    
     WiFiClientSecure httpsClient;
  httpsClient.setTimeout(15000);
  delay(1000);
  int retry = 0;
 
  while ((!httpsClient.connect(host, httpsPort)) && (retry < 50)) {
    delay(100);
    Serial.print(".");
    retry++;
  }
  if (retry == 50) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected to Server");
  }
 
  if (httpsClient.available()) {
  Serial.println("connected");
  /* httpsClient.print("GET /search?q=arduino HTTP/1.0");
   httpsClient.println();
   */
  }else{
    Serial.println("connection failed");
  }

  
  if (httpsClient.available()) {
    char c = httpsClient.read();
    Serial.print(c);
  }
  
  }

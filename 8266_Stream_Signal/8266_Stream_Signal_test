#include <ESP8266WiFi.h> //Inclou la biblioteca per connectar-se a WiFi
#include <WiFiClient.h> //Inclou la biblioteca per crear un client WiFi
#include <ESP8266WebServer.h> //Inclou la biblioteca per crear un servidor web
#include <ESP8266HTTPClient.h> //Inclou la biblioteca per fer peticions HTTP

const char* ssid = "your_WiFi_SSID"; //Nom de la xarxa WiFi
const char* password = "your_WiFi_password"; //Contrasenya de la xarxa WiFi

const char* host = "www.google.com"; //L'host al qual es farà ping per comprovar connexió a Internet
const int port = 80; //El port utilitzat per fer el ping

const char* twitch_channel = "4Xsample"; //Nom del canal de Twitch
const char* twitch_api = "https://api.twitch.tv/kraken/streams/"; //URL de l'API de Twitch

int led = 2; //Pin del LED
bool internetConnected = false; //Variable per indicar si hi ha connexió a Internet

void setup() {
  pinMode(led, OUTPUT); //Configura el pin del LED com a sortida
  digitalWrite(led, LOW); //Apaga el LED
  Serial.begin(115200); //Inicia el port sèrie
  WiFi.begin(ssid, password); //Inicia la connexió a WiFi amb el nom de la xarxa i la contrasenya especificats
  while (WiFi.status() != WL_CONNECTED) { //Espera fins que s'estableixi la connexió a WiFi
    delay(1000);
    Serial.println("Connectant-se a WiFi...");
  }
  Serial.println("Connectat a WiFi");
  internetConnected = true; //Indica que hi ha connexió a Internet
  Serial.println("Iniciat");
}

void loop() {
  if (ping(host)) { //Comprova si hi ha connexió a Internet connectant-se a l'host especificat
    if (!internetConnected) {
      internetConnected = true;
      Serial.println("Internet Connected");
    }
    String url = String(twitch_api) + String(twitch_channel); //Crea l'URL per fer la petició a l'API de Twitch
    WiFiClient client;
    HTTPClient http;
    http.begin(client, url); //Inicia la petició a l'API de Twitch
    int httpCode = http.GET(); //Fa la petició GET i guarda el codi de resposta
    if (httpCode == 200) { //Si la resposta és 200 (OK)
      String payload = http.getString(); //Guarda la resposta en una variable
      Serial.println("API response: " + payload);
      if (payload.indexOf("\"stream\":null") >= 0) { //Comprova si el canal està en directe o no
        digitalWrite(led, LOW); //Apaga el LED
delay(5000); //Espera 5 segons
digitalWrite(led, HIGH); //Fa un breu flash d'una desena de segon
delay(100);
digitalWrite(led, LOW); //Espera 5 segons
delay(5000);
} else {
digitalWrite(led, HIGH); //Encendre el LED si el canal està en directe
}
} else {
digitalWrite(led, LOW); //Apaga el LED
delay(100);
digitalWrite(led, HIGH); //Fa un parpadeig cada desena de segon
delay(100);
}
http.end(); //Finalitza la petició
} else {
if (internetConnected) {
internetConnected = false;
Serial.println("No Internet Connection");
}
digitalWrite(led, LOW); //Apaga el LED
delay(300);
digitalWrite(led, HIGH); //Fa el patró SOS (---...---)
delay(300);
digitalWrite(led, LOW);
delay(300);
digitalWrite(led, HIGH);
delay(300);
digitalWrite(led, LOW);
delay(900);
}
delay(60000); //Espera 60 segons abans de fer una nova comprovació
}

bool ping(const char* host) { //Funció per fer ping a l'host especificat
WiFiClient client;
if (client.connect(host, port)) {
Serial.println("Ping successful");
return true;
} else {
Serial.println("Pingfailed");
return false;
}
}

#include <WiFi.h>
#include <WebServer.h>

// Configuració de la xarxa WiFi
const char* ssid = "4Xtest";
const char* password = "1234567890";

// Configuració de la xarxa IP (si no es defineix el valor serà assignat per DHCP)
// const char* local_ip = "192.168.1.10"; // IP estàtica de la placa
// const char* gateway = "192.168.1.1"; // Adreça de la porta d'enllaç (encara no esta integrat)
// const char* subnet = "255.255.255.0"; // Màscara de subxarxa (encara no esta integrat)

// Variables per al comptador de radiació
// volatile int comptadorRadiacio = 0;
int comptadorRadiacio = 0;
unsigned long tempsRadiacio = 0;
float cpm = 0.0;

// Configuració del servidor web
WebServer servidor(80);
// WebServer servidor(local_ip, 80, gateway, subnet); // en cas de voler especificar la configuració

// Funció per gestionar la pàgina principal
void gestionaPrincipal() {
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Medidor CPM</title><style>body { font-family: Futura, sans-serif; font-size: 100px; text-align: center; }</style></head><body>";
  html += "<h1>" + String(cpm) + " CPM</h1>";
  html += "</body></html>";
  servidor.send(200, "text/html", html);
}

// Funció per gestionar peticions de pàgines no existents
void gestionaNoTrobat() {
  String missatge = "Fitxer no trobat\n\n";
  servidor.send(404, "text/plain", missatge);
}

// Funció que s'executa quan es detecta un impuls de radiació
void gestionaRadiacio() {
  comptadorRadiacio++;
}

#define SENSOR_PIN 10

int sensorState = LOW;
int lastSensorState = LOW;
unsigned long lastPulseTime = 0;


void setup() {
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);

// pinMode(SENSOR_PIN, INPUT_PULLUP);
  pinMode(SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), gestionaRadiacio, FALLING);

  WiFi.begin(ssid, password);
  Serial.println("Connectant a la xarxa WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connectant a la xarxa WiFi...");
  }

  Serial.println("Connectat a la xarxa WiFi");
  Serial.print("Adreça IP: ");
  Serial.println(WiFi.localIP());

  servidor.on("/", gestionaPrincipal);
  servidor.onNotFound(gestionaNoTrobat);

  servidor.begin();
}

void loop() {
  sensorState = digitalRead(SENSOR_PIN);
  if (sensorState != lastSensorState) {
    if (sensorState == HIGH) {
      if (millis() - tempsRadiacio >= 60000) {
    cpm = comptadorRadiacio / 1.0;
    comptadorRadiacio = 0;
    tempsRadiacio = millis();
    Serial.print("CPM: ");
    Serial.println(cpm);
  }
    }
    lastPulseTime = millis();
  }
  lastSensorState = sensorState;
  servidor.handleClient(); // Gestió de les peticions dels clients
}
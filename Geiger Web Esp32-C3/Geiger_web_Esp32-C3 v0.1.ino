#include <WiFi.h>
#include <WebServer.h>

// Configurar la xarxa Wi-Fi, hardcodejada directament perquè no ens agrada la privacitat ni la seguretat, mare de deu, amb lo senzill que es posar aquestes coses en una llibreria externa rollo "#include <credentials-h>"
const char* ssid = "4Xtest";
const char* password = "1234567890";

// Configuració de la xarxa IP (si no es defineix el valor serà assignat per DHCP)
// const char* local_ip = "192.168.1.10"; // IP estàtica de la placa
// const char* gateway = "192.168.1.1"; // Adreça de la porta d'enllaç (encara no esta integrat)
// const char* subnet = "255.255.255.0"; // Màscara de subxarxa (encara no esta integrat)

// Sí, deixem-ho en DHCP, perquè qui necessita controlar la seva pròpia xarxa, veritat?

// Variables per al comptador de radiació
int comptadorRadiacio = 0; // Genial, només estem mesurant la radiació... què podria anar malament?
unsigned long tempsRadiacio = 0;
float cpm = 0.0;

// Configuració del servidor web
WebServer servidor(80);
// WebServer servidor(local_ip, 80, gateway, subnet); // en cas de voler especificar la configuració

// Wiiiii, estem configurant un servidor web, perquè el món necessita més pàgines web sobre la radiació!!!

// Funció per gestionar la pàgina principal
void gestionaPrincipal() {
  String html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Radiació llegida en temps real a Palafrugell</title><style>body { font-family: Futura, sans-serif; font-size: 50px; text-align: center; background-color: #35373f; color: white; } #alert{color: red;} footer{font-size: smaller; color: #ccc;}</style></head><body>";
  html += "<h1>Radiació a Palafrugell</h1>";
  if((cpm / 151) < 0.1142){
    html += "<h2>" + String(cpm / 151) + " &mu;Sv/h</h2>";
  }
  else{
    html += "<h2  id=alert>" + String(cpm / 151) + " &mu;Sv/h</h2>";
  }
  html += "<footer><p>Aquesta és una pàgina de recerca personal, creada amb recursos molt limitats, i les dades poden no ser del tot exactes. Podeu trobar el projecte al meu GitHub <a href=\"https://github.com/4Xsample/Idees-per-Arduino/tree/main/Geiger%20Web%20Esp32-C3\">aquí</a>.</p></footer>";
  html += "</body></html>";
  servidor.send(200, "text/html", html);
}

// Funció per gestionar peticions de pàgines no existents, com la quantitat de politics independentistes que hi ha al parlament.
void gestionaNoTrobat() {
  String missatge = "Fitxer no trobat\n\n";
  servidor.send(404, "text/plain", missatge);
}

// Funció que s'executa quan es detecta un impuls de radiació, perquè és tan divertit mesurar radiació... oi?
void gestionaRadiacio() {
  comptadorRadiacio++;
}

#define SENSOR_PIN 10

int sensorState = LOW;
int lastSensorState = LOW;
unsigned long lastPulseTime = 0;

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(115200);

// Configurem el detector de polsos.
  pinMode(SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), gestionaRadiacio, FALLING);

// Configurem la xara fent servir els parametres definits previament.
  WiFi.begin(ssid, password);
  Serial.println("Connectant a la xarxa WiFi");

  // Posem una mica de codis d'error pel port de serie (el normal seria treure això del codi final però si voleu jugar-hi millor tenir-ho que no ocupa tant)
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

  // comprovar si la connexió Wi-Fi està activa
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Merda! connexió Wi-Fi perduda, intentant reconnectar...");
    WiFi.begin(ssid, password);
    // esperar fins que es torni a connectar
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Segueixo intentant connectar però aquesta merda no funciona encara...");
    }
    Serial.println("Al final he pogut connectar a la p*** xarxa Wi-Fi.");
  }

  sensorState = digitalRead(SENSOR_PIN);
  if (sensorState != lastSensorState) {
      if (millis() - tempsRadiacio >= 60000) {
    cpm = comptadorRadiacio / 1.0;
    comptadorRadiacio = 0;
    tempsRadiacio = millis();
    Serial.print("µSv/h: ");
    Serial.println(cpm / 151 );
    }
    lastPulseTime = millis();
  }
  lastSensorState = sensorState;
  servidor.handleClient(); // Gestió de les peticions dels clients
}
// message.txt
// 3 KB
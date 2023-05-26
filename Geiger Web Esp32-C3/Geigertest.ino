// Llibreria per la conexió wifi
#include <WiFi.h>
 // Llibreria per muntar un servidor web
#include <WebServer.h>
 // Llibreries per muntar el client de NTP
#include "time.h"
//#include <esp_sntp.h>
//#include <TimeLib.h>
 // Llibreria per poder enviar missatges de debug al discord 
#include <Discord_WebHook.h>
 // Llibreria que conté les credencials per configurar la nostre ESPE
#include "credentials.h"

// Configurar la xarxa Wi-Fi, al final, un mes despres hem decidit agafar les dades del puto credentials.h
const char * ssid = WIFI_SSID;
const char * password = WIFI_PASSWORD;

// Configuració de la xarxa IP (si no es defineix el valor serà assignat per DHCP)

// const char* local_ip = "192.168.1.10"; // IP estàtica de la placa
// const char* gateway = "192.168.1.1"; // Adreça de la porta d'enllaç (encara no esta integrat)
// const char* subnet = "255.255.255.0"; // Màscara de subxarxa (encara no esta integrat)
// Sí, deixem-ho en DHCP, perquè qui necessita controlar la seva pròpia xarxa, veritat?

// Configuració del servidor web
WebServer servidor(80); // En cas d'usar DHCP
// WebServer servidor(local_ip, 80, gateway, subnet); // en cas de no usar DHCP
// Wiiiii, estem configurant un servidor web, perquè el món necessita més pàgines web sobre la radiació!!!

//Aqui començem a merdejar amb l'NTC
void setTimezone(String timezone){
  Serial.printf("  Setting Timezone to %s\n",timezone.c_str());
  setenv("TZ",timezone.c_str(),1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();
}

void initTime(String timezone){
  struct tm timeinfo;

  Serial.println("Setting up time");
  configTime(0, 0, "pool.ntp.org");    // First connect to NTP server, with 0 TZ offset
  if(!getLocalTime(&timeinfo)){
    Serial.println("  Failed to obtain time");
    return;
  }
  Serial.println("  Got the time from NTP");
  // Now we can set the real timezone
  setTimezone(timezone);
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time 1");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S zone %Z %z ");
}

void setTime(int yr, int month, int mday, int hr, int minute, int sec, int isDst){
  struct tm tm;

  tm.tm_year = yr - 1900;   // Set date
  tm.tm_mon = month-1;
  tm.tm_mday = mday;
  tm.tm_hour = hr;      // Set time
  tm.tm_min = minute;
  tm.tm_sec = sec;
  tm.tm_isdst = isDst;  // 1 or 0
  time_t t = mktime(&tm);
  Serial.printf("Setting time: %s", asctime(&tm));
  struct timeval now = { .tv_sec = t };
  settimeofday(&now, NULL);
}

String getFormattedTime() {
  tm currentTime; // crea una estructura tm
  getLocalTime(&currentTime, 1000); // passa el punter i el temps màxim
  char timeStringBuff[50]; //50 chars should be enough
  strftime(timeStringBuff, sizeof(timeStringBuff), "%A, %B %d %Y %H:%M:%S", &currentTime);
  return String(timeStringBuff);
}


  String currentDateTime = getFormattedTime();

// Variables per al comptador de radiació
int comptadorRadiacio = 0; // Genial, només estem mesurant la radiació... què podria anar malament?
unsigned long tempsRadiacio = 0;
float cpm = 0.0;

// Funció per gestionar la pàgina principal
void gestionaPrincipal() {
  String html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Radiació llegida en temps real a Palafrugell</title><style>body { font-family: Futura, sans-serif; font-size: 50px; text-align: center; background-color: #35373f; color: white; } #alert{color: red;} footer{font-size: smaller; color: #ccc;}</style></head><body>";
  html += "<h1>Radiació a Palafrugell</h1>";
  if ((cpm / 151) < 0.1142) {
    html += "<h2>" + String(cpm / 151) + " &mu;Sv/h</h2>";
  } else {
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
  Serial.println("Pita que la cosa es radioactiva!");
}

#define SENSOR_PIN 10

int sensorState = LOW;
int lastSensorState = LOW;
unsigned long lastPulseTime = 0;

// Declarem el link del webhook de discord
Discord_Webhook discord;
String DISCORD_WEBHOOK = WEBHOOK_LINK;

void setup() {

  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);

//Seguim configurant NTC
  initTime("WET0WEST,M3.5.0/1,M10.5.0");   // Set for Melbourne/AU
  printLocalTime();

  // Inicialitzem el webhook de discord
  discord.begin(DISCORD_WEBHOOK);

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
  discord.send("M'acabo de reiniciar.");

  servidor.on("/", gestionaPrincipal);
  servidor.onNotFound(gestionaNoTrobat);
  servidor.begin();

}

void loop() {
  int i;
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
      String dts = getFormattedTime(); // guarda la data i hora actuals
      Serial.print("µSv/h: ");
 //     discord.send("µSv/h: ");
      Serial.println(cpm / 151);
//      discord.send(String(cpm / 151));
      discord.send("µSv/h: " + String(cpm / 151));

      // Imprimeix la data i hora al port de serie
      Serial.print("Data: ");
      Serial.print(dts);
      discord.send("Data: ");
      discord.send(dts);

    }
    lastPulseTime = millis();
  }
  lastSensorState = sensorState;
  servidor.handleClient(); // Gestió de les peticions dels clients
}
// message.txt
// 3 KB
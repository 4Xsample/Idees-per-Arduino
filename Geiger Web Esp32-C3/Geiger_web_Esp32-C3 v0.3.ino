// Llibreria per la conexió wifi
#include <WiFi.h>
// Llibreria per muntar un servidor web
#include <WebServer.h>
// Llibreries per muntar el client de NTP
#include <esp_sntp.h>
#include <TimeLib.h>
// Llibreria per poder enviar missatges de debug al discord
#include <Discord_WebHook.h>
// Llibreria que conté les credencials per configurar la nostre ESPE
#include "credentials.h"
// Llibreria per al watchdog
#include "ApplicationMonitor.h"

// Configurar la xarxa Wi-Fi, al final, un mes despres hem decidit agafar les dades del puto credentials.h
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

// Configuració de la xarxa IP (si no es defineix el valor serà assignat per DHCP)

// const char* local_ip = "192.168.1.10"; // IP estàtica de la placa
// const char* gateway = "192.168.1.1"; // Adreça de la porta d'enllaç (encara no esta integrat)
// const char* subnet = "255.255.255.0"; // Màscara de subxarxa (encara no esta integrat)
// Sí, deixem-ho en DHCP, perquè qui necessita controlar la seva pròpia xarxa, veritat?

// Configuració del servidor web
WebServer servidor(80); // En cas d'usar DHCP
// WebServer servidor(local_ip, 80, gateway, subnet); // en cas de no usar DHCP
// Wiiiii, estem configurant un servidor web, perquè el món necessita més pàgines web sobre la radiació!!!

// Variables per al comptador de radiació
int comptadorRadiacio = 0; // Genial, només estem mesurant la radiació... què podria anar malament?
unsigned long tempsRadiacio = 0;
float cpm = 0.0;

// Funció per gestionar la pàgina principal
void gestionaPrincipal()
{
  String html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Radiació llegida en temps real a Palafrugell</title><style>body { font-family: Futura, sans-serif; font-size: 50px; text-align: center; background-color: #35373f; color: white; } #alert{color: red;} footer{font-size: smaller; color: #ccc;}</style></head><body>";
  html += "<h1>Radiació a Palafrugell</h1>";
  if ((cpm / 151) < 0.1142)
  {
    html += "<h2>" + String(cpm / 151) + " &mu;Sv/h</h2>";
  }
  else
  {
    html += "<h2  id=alert>" + String(cpm / 151) + " &mu;Sv/h</h2>";
  }
  html += "<footer><p>Aquesta és una pàgina de recerca personal, creada amb recursos molt limitats, i les dades poden no ser del tot exactes. Podeu trobar el projecte al meu GitHub <a href=\"https://github.com/4Xsample/Idees-per-Arduino/tree/main/Geiger%20Web%20Esp32-C3\">aquí</a>.</p></footer>";
  html += "</body></html>";
  servidor.send(200, "text/html", html);
}

// Funció per gestionar peticions de pàgines no existents, com la quantitat de politics independentistes que hi ha al parlament.
void gestionaNoTrobat()
{
  String missatge = "Fitxer no trobat\n\n";
  servidor.send(404, "text/plain", missatge);
}

// Funció que s'executa quan es detecta un impuls de radiació, perquè és tan divertit mesurar radiació... oi?
void gestionaRadiacio()
{
  comptadorRadiacio++;
  Serial.println("Pita que la cosa es radioactiva!");
}

#define SENSOR_PIN 10

int sensorState = LOW;
int lastSensorState = LOW;
unsigned long lastPulseTime = 0;

// Declaracions de variables per NTP
struct tm *tm;
int d_year;
int d_mon;
int d_mday;
int d_hour;
int d_min;
int d_sec;
int d_wday;
static const char *weekStr[7] = {
    "Sun",
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat"};

const char *ntpServer = "fr.pool.ntp.org";
const long gmtOffset_sec = 7200;
const int daylightOffset_sec = 0;

// Cridem la funció que obté la data i hora del servidor NTP
void wifisyncjst()
{
  // Sincronització de l’rellotge intern amb CEST
  // Obté CEST a traves de NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  delay(500);
  // Espera fins que l’hora de l’rellotge intern coincideixi amb l’hora NTP
  while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET)
  {
    delay(500);
  }
}

// Declarem el link del webhook de discord
Discord_Webhook discord;
String DISCORD_WEBHOOK = WEBHOOK_LINK;

Watchdog::CApplicationMonitor ApplicationMonitor;

void setup()
{

  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);

  void comandaReset()
  {
    if (Serial.available() > 0)
    {
      String command = Serial.readStringUntil('\n'); // Llegim tota l'entrada per serial fins al primer canvi de linia
      command.trim();                                // Eliminem espais en blanc

      if (command.equals("resetEspe"))
      { // Definim la comanda per a reset
        Serial.println("Reiniciant la ESPE...");
        delay(1000);   // Petiti delay per a poder veure el missatge
        ESP.restart(); // Reinici de la ESPE
      }
    }
    
  }

  ApplicationMonitor.Dump(Serial);
  ApplicationMonitor.EnableWatchdog(Watchdog::CApplicationMonitor::Timeout_4s);

  // Inicialitzem el webhook de discord
  discord.begin(DISCORD_WEBHOOK);

  // Configurem el detector de polsos.
  pinMode(SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), gestionaRadiacio, FALLING);

  // Configurem la xara fent servir els parametres definits previament.
  WiFi.begin(ssid, password);
  Serial.println("Connectant a la xarxa WiFi");

  // Posem una mica de codis d'error pel port de serie (el normal seria treure això del codi final però si voleu jugar-hi millor tenir-ho que no ocupa tant)
  while (WiFi.status() != WL_CONNECTED)
  {
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

void loop()
{

  ApplicationMonitor.IAmAlive();

  comandaReset(); // Comprovem si s'ha introduit la comanda de reset

  // comprovar si la connexió Wi-Fi està activa
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Merda! connexió Wi-Fi perduda, intentant reconnectar...");
    WiFi.begin(ssid, password);
    // esperar fins que es torni a connectar
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(1000);
      Serial.println("Segueixo intentant connectar però aquesta merda no funciona encara...");
    }
    Serial.println("Al final he pogut connectar a la p*** xarxa Wi-Fi.");
  }

  sensorState = digitalRead(SENSOR_PIN);
  if (sensorState != lastSensorState)
  {
    if (millis() - tempsRadiacio >= 60000)
    {
      cpm = comptadorRadiacio / 1.0;
      comptadorRadiacio = 0;
      tempsRadiacio = millis();
      Serial.print("µSv/h: ");
      //     discord.send("µSv/h: ");
      Serial.println(cpm / 151);
      //      discord.send(String(cpm / 151));
      discord.send("µSv/h: " + String(cpm / 151));
      // Obté el temps actual en format time_t
      time_t t = time(NULL);
      // Converteix el temps time_t a una estructura tm
      tm = localtime(&t);
      // Assigna els valors dels components de la data i hora a les variables corresponents
      d_mon = tm->tm_mon + 1;
      d_mday = tm->tm_mday;
      d_hour = tm->tm_hour;
      d_min = tm->tm_min;
      d_sec = tm->tm_sec;
      d_wday = tm->tm_wday;
      d_year = timeinfo.tm_year + 1900;
      // Formata els valors de la data i hora en cadenes de text
      char ts[80];
      char ds[80];
      char dts[80];
      //     sprintf(ds, "%02d-%02d %s", d_mon, d_mday, weekStr[d_wday]);
      //     sprintf(ts, "%02d:%02d:%02d", d_hour, d_min, d_sec);
      sprintf(dts, "%02d/%02d/%02d %02d:%02d:%02d", d_mday, d_mon, d_year, d_hour, d_min, d_sec);
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
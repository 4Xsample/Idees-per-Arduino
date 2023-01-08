#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Pins per al RFIO-RC522
const int SS_PIN = D8;
const int RST_PIN = D4;

// Creem un objecte MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Definim els paràmetres per al WiFi
const char *ssid = "";
const char *password = "";

// Creem un objecte ESP8266WebServer
ESP8266WebServer server(80);

// Definim la variable per a l'ID de la targeta
String cardID;

// Definim la variable per a l'idioma
String language = "catalan";

// Creem les variables per al webhook de Discord
const char *webhook_name = "";
const char *webhook_url = "";

// Configurem l'OTA
void setupOTA() {

// Definim el SSID i la contrasenya per al WiFi
  ArduinoOTA.setHostname("rfid-reader");
  ArduinoOTA.setPassword("password");

// Comencem l'OTA
  ArduinoOTA.begin();
}

// Configurem el WiFi
void setupWiFi() {

// Comencem a connectar-nos al WiFi
  WiFi.begin(ssid, password);

// Esperem fins que ens connectem
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

// Un cop connectats, imprimim la nostra IP local
  Serial.print("IP local: ");
  Serial.println(WiFi.localIP());

// Enviem la nostra IP local al webhook de Discord
  String content = "S'ha connectat un dispositiu amb l'IP " + WiFi.localIP().toString();
  sendDiscordWebhook(webhook_name, webhook_url, content);
}

// Enviem un missatge al webhook de Discord
void sendDiscordWebhook(const char *name, const#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Pins per al RFIO-RC522
const int SS_PIN = D8;
const int RST_PIN = D4;

// Creem un objecte MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Definim els paràmetres per al WiFi
const char *ssid = "";
const char *password = "";

// Creem un objecte ESP8266WebServer
ESP8266WebServer server(80);

// Definim la variable per a l'ID de la targeta
String cardID;

// Definim la variable per a l'idioma
String language = "catalan";

// Creem les variables per al webhook de Discord
const char *webhook_name = "";
const char *webhook_url = "";

// Configurem l'OTA
void setupOTA() {

// Definim el SSID i la contrasenya per al WiFi
  ArduinoOTA.setHostname("rfid-reader");
  ArduinoOTA.setPassword("password");

// Comencem l'OTA
  ArduinoOTA.begin();
}

// Configurem el WiFi
void setupWiFi() {

// Comencem a connectar-nos al WiFi
  WiFi.begin(ssid, password);

// Esperem fins que ens connectem
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

// Un cop connectats, imprimim la nostra IP local
  Serial.print("IP local: ");
  Serial.println(WiFi.localIP());

// Enviem la nostra IP local al webhook de Discord
  String content = "S'ha connectat un dispositiu amb l'IP " + WiFi.localIP().toString();
  sendDiscordWebhook(webhook_name, webhook_url, content);
}

// Enviem un missatge al webhook de Discord
void sendDiscordWebhook(const char *name, constchar *url, String content) {

// Creem un client HTTP
WiFiClient client;

// Connectem al servidor del webhook
if (!client.connect(url, 80)) {
Serial.println("No es pot connectar al servidor");
return;
}

// Creem el missatge a enviar
String json = "{"username": "" + String(name) + "", "content": "" + content + ""}";

// Enviem el missatge
client.print("POST " + String(url) + " HTTP/1.1\r\n" +
"Host: " + String(url) + "\r\n" +
"Content-Type: application/json\r\n" +
"Content-Length: " + json.length() + "\r\n" +
"Connection: close\r\n" +
"\r\n" +
json);

// Esperem la resposta del servidor
while (client.available()) {
String line = client.readStringUntil('\r');
Serial.print(line);
}
}

// Funció que s'executa quan s'envia una petició al servidor web
void handleRoot() {

// Creem la pàgina HTML
String page = "<html><head><title>Lector RFID</title></head><body>";

// Afegim el títol
if (language == "catalan") {
page += "<h1>Lector RFID</h1>";
} else {
page += "<h1>RFID Reader</h1>";
}

// Afegim la targeta llegida
if (language == "catalan") {
page += "<p>Targeta llegida: " + cardID + "</p>";
} else {
page += "<p>Read card: " + cardID + "</p>";
}

// Afegim el menú per triar l'idioma
page += "<form action='/set_language' method='POST'><label for='language'>Idioma:</label><select name='language' id='language'>";
if (language == "catalan") {
page += "<option value='catalan' selected>Català</option><option value='english'>Anglès</option>";
} else {
page += "<option value='catalan'>Català</option><option value='english' selected>Anglès</option>";
}
page += "</select><br><br><input type='submit' value='Canviar idioma'></form>";

// Afegim el tancament de la pàgina HTML
page += "</body></html>";

// Enviem la pàgina al client
server.send(200, "text/html", page);
}

// Funció que s'executa quan s'envia una petició POST per canviar l'idioma
void handleSetLanguage() {

// Llegim l'idioma seleccionat
language = server.arg("language");

// Redirigim al client a la pàgina principal
server.sendHeader("Location", "/", true);
server.send(302, "text/plain", "");
}

// Funció que s'executa quan s'envia una petició a la pàgina OTA
void handleOTA() {

// Creem la pàgina HTML
String page = "<html><head><title>Actualització OTA</title></head><body>";

// Afegim el títol
if (language == "catalan") {
page += "<h1>Actualització OTA</h1>";
} else {
page += "<h1>OTA Update</h1>";
}

// Afegim el formulari per configurar el WiFi
page += "<form action='/set_wifi' method='POST'>";
if (language == "catalan") {
page += "<label for='ssid'>SSID:</label><input type='text' name='ssid' id='ssid' value='" + String(ssid) + "'><br>";
page += "<label for='password'>Contrasenya:</label><input type='password' name='password' id='password' value='" + String(password) + "'><br><br>";
page += "<input type='submit' value='Desar paràmetres WiFi'>";
} else {
page += "<label for='ssid'>SSID:</label><input type='text' name='ssid' id='ssid' value='" + String(ssid) + "'><br>";
page += "<label for='password'>Password:</label><input type='password' name='password' id='password' value='" + String(password) + "'><br><br>";
page += "<input type='submit' value='Save WiFi settings'>";
}
page += "</form>";

// Afegim el formulari per configurar el webhook de Discord
page += "<br><br><form action='/set_webhook' method='POST'>";
if (language == "catalan") {
page += "<label for='webhook_name'>Nom del webhook:</label><input type='text' name='webhook_name' id='webhook_name' value='" + String(webhook_name) + "'><br>";
page += "<label for='webhook_url'>URL del webhook:</label><input type='text' name='webhook_url' id='webhook_url' value='" + String(webhook_url) + "'><br><br>";
page += "<input type='submit' value='Desar paràmetres webhook'>";
} else {
page += "<label for='webhook_name'>Webhook name:</label><input type='text' name='webhook_name' id='webhook_name' value='" + String(webhook_name) + "'><br>";
page += "<label for='webhook_url'>Webhook URL:</label><input type='text' name='webhook_url' id='webhook_url' value='" + String(webhook_url) + "'><br><br>";
page += "<input type='submit' value='Save webhook settings'>";
}
page += "</form>";

// Afegim el tancament de la pàgina HTML
page += "</body></html>";

// Enviem la pàgina al client
server.send(200, "text/html", page);
}

// Funció que s'executa quan s'envia una petició POST per configurar el WiFi
void handleSetWiFi() {

// Llegim els paràmetres del WiFi
ssid = server.arg("ssid").c_str();
password = server.arg("password").c_str();

// Desconnectem del WiFi actual
WiFi.disconnect();

// Connectem al nou WiFi
setupWiFi();

// Redirigim al client a la pàgina OTA
server.sendHeader("Location", "/ota", true);
server.send(302, "text/plain", "");
}

// Funció que s'executa quan s'envia una petició POST per configurar el webhook de Discord
void handleSetWebhook() {

// Llegim els paràmetres del webhook
webhook_name = server.arg("webhook_name").c_str();
webhook_url = server.arg("webhook_url").c_str();

// Redirigim al client a la pàgina OTA
server.sendHeader("Location", "/ota", true);
server.send(302, "text/plain", "");
}

void setup() {

// Iniciem la consola sèria
Serial.begin(9600);

// Iniciem el RFIO-RC522
mfrc522.PCD_Init();

// Iniciem l'OTA
setupOTA();

// Iniciem el WiFi
setupWiFi();

// Definim les funcions a cridar quan s'envia una petició al servidor web
server.on("/", handleRoot);
server.on("/set_language", handleSetLanguage);
server.on("/ota", handleOTA);
server.on("/set_wifi", handleSetWiFi);
server.on("/set_webhook", handleSetWebhook);

// Iniciem el servidor web
server.begin();
Serial.println("Servidor web iniciat");
}

void loop() {

// Gestionem l'OTA
ArduinoOTA.handle();

// Gestionem les peticions al servidor web
server.handleClient();

// Miram si hi ha una targeta RFID disponible
if (mfrc522.PICC_IsNewCardPresent()) {

// Llegim la targeta
MFRC522::PICC_Type piccType = mfrc522.PICC_ReadCardSerial();

// Creem una cadena amb l'ID de la targeta
cardID = "";
for (byte i= 0; i < mfrc522.uid.size; i++) {
cardID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
cardID += String(mfrc522.uid.uidByte[i], HEX);
}

// Esperem un segon per evitar llegir la mateixa targeta de nou
delay(1000);
}
}
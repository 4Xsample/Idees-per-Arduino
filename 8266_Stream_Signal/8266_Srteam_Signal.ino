#include <ArduinoJson.h>       //Inclou la llibreria per treballar amb JSON
#include <ESP8266WiFi.h>       //Inclou la llibreria per treballar amb WiFi
#include <ESP8266HTTPClient.h> //Inclou la llibreria per fer peticions HTTP

const char *ssid = "YOUR_SSID";         // Nom de la xarxa WiFi
const char *password = "YOUR_PASSWORD"; // Contrasenya de la xarxa WiFi
const char *channel = "4Xsample";       // Nom del canal de Twitch
const int ledPin = D0;                  // Pin al que està connectat la tira LED

void setup()
{
    pinMode(ledPin, OUTPUT);    // Configura el pin com a sortida
    digitalWrite(ledPin, LOW);  // Inicialment, apaga la tira LED
    WiFi.begin(ssid, password); // Connecta a la xarxa WiFi
    while (WiFi.status() != WL_CONNECTED)
    { // Espera a connectar-se a la xarxa
        delay(1000);
        Serial.println("Connectant a WiFi...");
    }
    Serial.println("Connectat a WiFi");
}

void loop()
{
    HTTPClient http;                                                        // Crea una instancia de la classe HTTPClient
    String url = "https://api.twitch.tv/kraken/streams/" + String(channel); // Crea l'URL de la petició
    WiFiClient client;
    http.begin(client, url);   // Inicia la petició HTTP
    int httpCode = http.GET(); // Envia la petició GET i obté el codi de resposta
    if (httpCode == 200)
    {                                                                    // Si la resposta és correcta (200 OK)
        String response = http.getString();                              // Obté la resposta en forma de String
        DynamicJsonDocument jsonDoc(500);                                // Crea una instancia del buffer JSON
        DeserializationError error = deserializeJson(jsonDoc, response); // Analitza el JSON
        if (!error)
        { // Si no hi ha hagut cap error en l'anàlisi
            if (!jsonDoc["stream"].isNull())
            {                               // Si hi ha un stream en directe
                digitalWrite(ledPin, HIGH); // Enciu la tira LED
                Serial.println("El stream esta en directe");
            }
            else
            {
                digitalWrite(ledPin, LOW); // Apaga la tira LED
                Serial.println("El stream no esta en directe");
            }
        }
        else
        {
            Serial.println("Error analitzant el JSON: " + String(error.c_str()));
        }
    }
    else
    {
        Serial.println("Error connectant a l'API de Twitch");
    }
    http.end();   // Finalitza la petició HTTP
    delay(60000); // Espera 60 segons abans de fer una nova petició
}

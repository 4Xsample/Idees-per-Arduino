#include <WiFiClient.h>        //Inclou la biblioteca per crear un client WiFi
#include <ESP8266HTTPClient.h> //Inclou la biblioteca per fer peticions HTTP

const char *ssid = "iHome";                                       // Nom de la xarxa WiFi
const char *password = "1234567890";                              // Contrasenya de la xarxa WiFi
const char *client_id = "YOUR_CLIENT_ID";                         // Replace with your own client ID
const char *channel_name = "4Xsample";                            // Nom del canal de Twitch
const char *twitch_api = "https://api.twitch.tv/kraken/streams/"; // URL de l'API de Twitch

int led = 2; // Pin del LED

void setup()
{
    pinMode(led, OUTPUT);       // Configura el pin del LED com a sortida
    digitalWrite(led, LOW);     // Apaga el LED
    Serial.begin(115200);       // Inicia el port sèrie
    WiFi.begin(ssid, password); // Inicia la connexió a WiFi amb el nom de la xarxa i la contrasenya especificats
    while (WiFi.status() != WL_CONNECTED)
    { // Espera fins que s'estableixi la connexió a WiFi
        delay(1000);
        Serial.println("Connectant-se a WiFi...");
    }
    Serial.println("Connectat a WiFi");
}

void loop()
{
    String url = String(twitch_api) + String(channel_name); // Crea l'URL per fer la petició a l'API de Twitch
    WiFiClient client;
    HTTPClient http;
    http.begin(client, url); // Inicia la petició a l'API de Twitch
    http.addHeader("Client-ID", client_id);
    int httpCode = http.GET(); // Fa la petició GET i guarda el codi de resposta
    if (httpCode == 200)
    {                                      // Si la resposta és 200 (OK)
        String payload = http.getString(); // Guarda la resposta en una variable
        Serial.println("API response: " + payload);
        if (payload.indexOf("\"stream\":null") >= 0)
        {                           // Comprova si el canal està en directe o no
            digitalWrite(led, LOW); // Apaga el LED
        }
        else
        {
            Serial.println("El canal esta en directe");
            digitalWrite(led, HIGH); // Encendre el LED si el canal està en directe
        }
    }
    else
    {
        Serial.println("Error en la petició a l'API de Twitch: " + String(httpCode));
    }
    http.end();  // Finalitza la petició
    delay(5000); // Espera 5 segons abans de fer una nova petició
}

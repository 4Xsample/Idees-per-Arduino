#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "your_WiFi_SSID";
const char *password = "your_WiFi_password";

const char *host = "www.google.com";
const int port = 80;

const char *twitch_channel = "4Xsample";
const char *twitch_api = "https://api.twitch.tv/kraken/streams/";

int led = 2;
bool internetConnected = false;

void setup()
{
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  internetConnected = true;
}

void loop()
{
  if (ping(host))
  {
    if (!internetConnected)
    {
      internetConnected = true;
    }
    String url = String(twitch_api) + String(twitch_channel);
    WiFiClient client;
    HTTPClient http;
    http.begin(client, url);
    int httpCode = http.GET();
    if (httpCode == 200)
    {
      String payload = http.getString();
      if (payload.indexOf("\"stream\":null") >= 0)
      {
        digitalWrite(led, LOW);
        delay(5000);
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        delay(5000);
      }
      else
      {
        digitalWrite(led, HIGH);
      }
    }
    else
    {
      digitalWrite(led, LOW);
      delay(100);
      digitalWrite(led, HIGH);
      delay(100);
    }
    http.end();
  }
  else
  {
    if (internetConnected)
    {
      internetConnected = false;
    }
    digitalWrite(led, LOW);
    delay(300);
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(300);
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(900);
  }
  delay(60000);
}

bool ping(const char *host)
{
  WiFiClient client;
  if (client.connect(host, port))
  {
    return true;
  }
  else
  {
    return false;
  }
}

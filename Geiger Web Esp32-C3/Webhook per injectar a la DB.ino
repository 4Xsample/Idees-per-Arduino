#include <HTTPClient.h>

void sendData(float dataValue) {
  HTTPClient http;
  String url = "http://<IP_DE_LA_TEVA_RASPBERRY>:<PORT>/api/data"; // Canvia-ho per la URL del teu webhook
  String payload = "value=" + String(dataValue); // Aquí pots canviar la forma en què envies les dades
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(payload);
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error on sending data: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
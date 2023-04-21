// Aquí tenim un codi increïblement complex i sofisticat que fa res més que llegir un senyal d'un pin i encendre un LED. Com ho hauríem aconseguit sense aquest codi?

// Definim els pins que utilitzarem, perquè això no és obvi per a ningú que treballa amb aquest codi.
#define SENSOR_PIN 10
#define LED_PIN 4

// Aquí tenim un conjunt de variables que probablement són totalment innecessàries, perquè aquest codi és tan simple que podríem fer-ho sense cap variable.
int sensorState = LOW;
int lastSensorState = LOW;
unsigned long lastPulseTime = 0;

// Configurem el codi. Aquesta és la part més avorrida, ja que no fem res realment emocionant.
void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sensor de radiació Geiger iniciat.");
}

// Aquí és on les coses comencen a posar-se emocionants! Llegim l'estat del pin del sensor, i això és el màxim que podem fer en aquest codi senzill.
void loop() {
  sensorState = digitalRead(SENSOR_PIN);
// I aquí és on tota l'emoció es desencadena! Comprovem si l'estat del sensor ha canviat i fem alguna cosa amb això (en aquest cas, encenem un LED i mostrem un missatge perquè tothom estigui content).
  if (sensorState != lastSensorState) {
    if (sensorState == HIGH) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("Radiació detectada.");
    }
    else {
      digitalWrite(LED_PIN, LOW);
    }
    lastPulseTime = millis();
  }
// Actualitzem l'estat del sensor perquè no ens oblidem de fer-ho i creem una catàstrofe nuclear.
  lastSensorState = sensorState;
// Comprovem si ha passat temps suficient sense cap pols del sensor i apaguem el LED. Wow, quina emoció.
  if (millis() - lastPulseTime > 1000) {
    digitalWrite(LED_PIN, LOW);
  }
}
// I aquí acaba el codi, un vertader exemple de la complexitat dels dispositius electrònics moderns.
// Com a mínim fa la feina, que ja és molt. 
// Aquest codi es simplement un pas intermig per veure si podiem fer que la esp32c3 llegis i reacciones als pulsos de radiació detectats pel medidor geiger.
// llegeix els pulsos del pin 10 i encen un led al pin 4

#define SENSOR_PIN 10
#define LED_PIN 4

int sensorState = LOW;
int lastSensorState = LOW;
unsigned long lastPulseTime = 0;

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sensor de radiació Geiger iniciat.");
}

void loop() {
  sensorState = digitalRead(SENSOR_PIN);
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
  lastSensorState = sensorState;
  if (millis() - lastPulseTime > 1000) {
    digitalWrite(LED_PIN, LOW);
  }
}
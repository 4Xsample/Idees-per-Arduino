#include <WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Configurar la conexión Wi-Fi y la dirección IP de la base de datos
const char* ssid = "mi_red_wifi";
const char* password = "mi_clave_wifi";
IPAddress server_addr(192, 168, 0, 100); // dirección IP de la base de datos
const char* user = "mi_usuario";
const char* password_bd = "mi_clave_bd";
const char* database = "mi_base_de_datos";

// Crear una instancia de la conexión Wi-Fi y de la conexión de la base de datos
WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red Wi-Fi...");
  }

  Serial.println("Conexión Wi-Fi establecida");

  if (conn.connect(server_addr, 3306, user, password_bd, database)) {
    Serial.println("Conexión a la base de datos establecida");
  } else {
    Serial.println("Error al conectar a la base de datos");
  }
}

void loop() {
  // Leer el valor de medición de radiación
  float cpm = leer_medicion();

  // Crear una consulta SQL para insertar el valor de medición en la base de datos
  char query[128];
  sprintf(query, "INSERT INTO mediciones (fecha, valor) VALUES (NOW(), %.2f)", cpm);

  // Crear un objeto MySQL_Cursor para ejecutar la consulta
  MySQL_Cursor* cursor = new MySQL_Cursor(&conn);

  // Ejecutar la consulta y verificar si se realizó correctamente
  if (cursor->execute(query)) {
    Serial.println("Medición enviada a la base de datos");
  } else {
    Serial.println("Error al enviar la medición a la base de datos");
  }

  // Liberar la memoria utilizada por el objeto MySQL_Cursor
  delete cursor;

  // Esperar un tiempo antes de tomar otra medición
  delay(10000);
}

// Función para leer el valor de medición de radiación
float leer_medicion() {
  // Aquí deberías poner el código para leer el valor de medición de radiación
  // que actualmente
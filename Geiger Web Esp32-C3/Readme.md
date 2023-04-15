|               |               |               |               |               |               |
|:-------------:|:-------------:|:-------------:|-------------:|-------------:|-------------:|
| ![Hack the planet](https://img.shields.io/badge/Hack-The%20Planet-orange) | [![Discord](https://img.shields.io/discord/667340023829626920?logo=discord)](https://discord.gg/ahVq54p) | [![Twitter](https://img.shields.io/twitter/follow/4xsample?style=social&logo=twitter)](https://twitter.com/4xsample/follow?screen_name=shields_io) | [![4Xsample@mastodon.social](https://img.shields.io/badge/Mastodon-@4Xsample-blueviolet?style=for-the-badge&logo=mastodon)](https://mastodon.social/@4Xsample) | [![4Xsample](https://img.shields.io/badge/Twitch-4Xsample-6441A4?style=for-the-badge&logo=twitch)](https://twitch.tv/4Xsample) | [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.com/donate/?hosted_button_id=EFVMSRHVBNJP4) |

# Medidor Geiger amb ESP32 i placa de radiació

Aquest projecte proporciona una pàgina web que mostra la quantitat de radiació llegida en temps real a Palafrugell.

Per realitzar aquesta tasca, s'ha utilitzat una placa ESP32-C3 i un sensor de radiació, que envia impulsos cada vegada que es detecta una partícula radiactiva.

El codi ha estat escrit en C++ i s'ha utilitzat l'IDE d'Arduino per programar la placa.

Per a l'enviament de les dades, s'ha utilitzat una connexió WiFi, que ha estat configurada amb les següents credencials:

```
const char* ssid = "4Xtest";
const char* password = "1234567890";
```


## Informació important

Aquest projecte ha estat desenvolupat en directe a [Twitch.tv/4Xsample](https://www.twitch.tv/4Xsample). 

-  Fase 1: Muntatge d’un medidor Geiger (RadiationD v1.1) per mesurar la radiació.
-  Fase 2: Muntatge d’un servidor web en una ESP32 C3 per llegir les dades del medidor Geiger i fer-les accessibles a través d’Internet.
- Fase 3: Muntatge d’una bateria i una placa solar per alimentar tot el sistema i deixar-lo connectat permanentment de forma autònoma. Requisit: connexió WiFi.

La fase 1 ha sigut un exit (per sorpresa de tots) i el medidor de radiació funciona perfectament.

Actualment, estem ja en la fase 2, es a dir treballant en connectar el sensor a una arduino ESP32 C3 per muntar un servidor web que ens mostri les dades obtingudes pel sensor. L'objectiu final de la fase és mostrar la radiació en milisieverts per hora (mSv/h) i incloure un historial de les mesures realitzades i totes les funcions que poguem empaquetar en un servidor que pugui correr en una placa arduino ESP32 C3.

La versió actual del codi és la v0.1, la qual inclou el servidor web i mostra el nombre de pulsos per minut (CPM) en pantalla. No obstant, encara no funciona correctament perquè la placa no compta els pulsos adequadament. No sabem si això és perquè el sensor no està ben connectat o perquè hi ha un problema en el codi, però continuarem investigant per solucionar-ho.

## Materials necessaris

* [Sensor GM RadiationD v1.1 (CAJOE)](https://s.click.aliexpress.com/e/_Dn4AUID)
* [Placa Arduino ESP32 C3](https://s.click.aliexpress.com/e/_DEWtkDJ)
* [Breadboard](https://s.click.aliexpress.com/e/_DEWtkDJ) (Opcional) i cables
* Bateria o font d'alimentació

## Esquema de connexions

Les connexions són les següents:

| Sensor GM  | Placa Arduino |
| ---------- | ------------- |
| Pin 1 (GND) | GND           |
| Pin 2 (HV)  | 5v        |
| Pin 3 (SIGNAL)  | GPIO 10    |

## Codi
El codi amb el que hem treballat s'ha desenvolupat en varies fases:

1. El primer codi que va funcionar es `Geiger led esp32c3.ino`, aquest codi es tremendament senzill però va servir per comprovar la forma mes practica de detectar els polsos de senyal.

Per fer funcionar aquest codi simplement vam conectar la esp32 c3 al medidor Geiger-Müller conectant la senyal al GPIO 10 i vam conectar un led al GPIO 4 per fer mes facil veure cada cop que tenem una detecció

Es pot conectar al port de serie conectant al port COM de torn a una velositat de 115200.

La gracia del codi està en comprovar l'estat del pin de senyal del Geiger-Müller i nomes saltar quan es detecta un cambi fent servir el seguent codi:

```
  sensorState = digitalRead(SENSOR_PIN);
  if (sensorState != lastSensorState) {
```

2. El codi final projecte es pot trobar al fitxer `Geiger_web_Esp32-C3.ino`. Aquest codi utilitza la llibreria `WiFi.h` per connectar-se a una xarxa WiFi i la llibreria `WebServer.h` per servir una pàgina web que mostra la radiació detectada.

El codi permet l'ús de xarxes IP estàtiques i dinàmiques, però per defecte està configurat per utilitzar DHCP. Per canviar la configuració de la xarxa, es pot modificar el següent bloc de codi:

```
// const char* local_ip = "192.168.1.10"; // IP estàtica de la placa
// const char* gateway = "192.168.1.1"; // Adreça de la porta d'enllaç (encara no esta integrat)
// const char* subnet = "255.255.255.0"; // Màscara de subxarxa (encara no esta integrat) 
```

Configuració del servidor web
El codi també inclou la configuració del servidor web, que s'inicia a l'inici del programa i s'encarrega de gestionar les peticions HTTP que arriben a la placa.

```
WebServer servidor(80);
```

Però si es vol definir la configuració de xarxa cal cambiar aquesta linea per la seguent. (que esta comentada just a sota)

```
WebServer servidor(local_ip, 80, gateway, subnet);
```

Per definir el pin al que conectarem la senyal del medidor geiger ho fem a la linea seguent:

```
#define SENSOR_PIN 10
```

Aquest programa es basa en comparar l'estat del sensor amb l'estat anterior per detectar impulsos de radiació. Això es fa a través de la funció gestionaRadiacio(), que s'executa cada vegada que es detecta un impuls.

```
  if (sensorState != lastSensorState) {
    if (sensorState == HIGH) {
```

## Resultat

Amb aquest aparell, es pot mesurar la radiació ionitzant en temps real i mostrar-la en una pàgina web. Això permet tenir un control més precís de la radiació ambiental i detectar variacions inesperades.

## Disclaimer: 
*Aquest codi s'ofereix tal com és i no es garanteix que funcioni correctament en totes les condicions. No em faig responsable dels danys que puguin resultar de l'ús d'aquesta informació. Utilitzeu-lo sota la vostra pròpia responsabilitat. Si teniu dubtes pregunteu i respondré al que pugui. Si voleu obrir proposar cambis podeu obrir fork i i voleu seguir-me, al panel del principi d'aquest readme podeu trobar links a les meves xarxes socials, Twitch i PayPal per si també voleu donar suport al meu treball.*
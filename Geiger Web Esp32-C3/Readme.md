| | | | | | |
|:-------------:|:-------------:|:-------------:|-------------:|-------------:|-------------:|
| ![Hack the planet](https://img.shields.io/badge/Hack-The%20Planet-orange) | [![Discord](https://img.shields.io/discord/667340023829626920?logo=discord)](https://discord.gg/ahVq54p) | [![Twitter](https://img.shields.io/twitter/follow/4xsample?style=social&logo=twitter)](https://twitter.com/4xsample/follow?screen_name=shields_io) | [![4Xsample@mastodon.social](https://img.shields.io/badge/Mastodon-@4Xsample-blueviolet?style=for-the-badge&logo=mastodon)](https://mastodon.social/@4Xsample) | [![4Xsample](https://img.shields.io/badge/Twitch-4Xsample-6441A4?style=for-the-badge&logo=twitch)](https://twitch.tv/4Xsample) | [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.com/donate/?hosted_button_id=EFVMSRHVBNJP4) |

# Medidor Geiger amb ESP32 i placa de radiació

Aquest projecte proporciona una pàgina web que mostra la quantitat de radiació llegida en temps real.

Per executar aquesta tasca, s'ha utilitzat una placa ESP32-C3 i un sensor de radiació, que envia impulsos cada vegada que es detecta una partícula radioactiva.

El codi ha estat escrit en C++ i s'ha fet servir l'IDE d'Arduino per programar la placa.

Per a l'enviament de les dades, s'ha utilitzat una connexió WiFi, que ha estat configurada amb les següents credencials:

```c++
const char* ssid = "4Xtest";
const char* password = "1234567890";
```

## Informació important

Aquest projecte ha estat desenvolupat en directe a [Twitch.tv/4Xsample](https://www.twitch.tv/4Xsample).

- Fase 1: Muntatge d'un medidor Geiger (RadiationD v1.1) per mesurar la radiació.
- Fase 2: Muntatge d'un servidor web en una ESP32 C3 per llegir les dades del medidor Geiger i fer-les accessibles a través d'Internet.
- Fase 3: Muntatge d'una bateria i una placa solar per alimentar tot el sistema i deixar-lo connectat permanentment de forma autònoma. Requisit: connexió WiFi.
- Fase 4: Crear un suport motoritzat que apunti cap al sol perquè la placa solar rebi el màxim d'energia possible del sol que hi hagi.
- Fase 5: Millorar la seguretat informàtica del projecte per poder assumir l'entrada de dades de fonts de dades externes i així començar a acumular informació estadística des d'altres punts de recollida de dades que hagin fet aficionats d'arreu.

## Fase 1.

La fase 1 ha sigut un èxit (per sorpresa de tots) i el medidor de radiació funciona perfectament.

Actualment, estem ja en la fase 2, és a dir treballant a connectar el sensor a una arduino ESP32 C3 per muntar un servidor web que ens mostri les dades obtingudes pel sensor. L'objectiu final de la fase és mostrar la radiació en mili sieverts per hora (mSv/h) i incloure un historial de les mesures realitzades i totes les funcions que puguem empaquetar en un servidor que pugui córrer en una placa Arduino ESP32 C3.

### Materials necessaris

- [Sensor GM RadiationD v1.1 (CAJOE)](https://s.click.aliexpress.com/e/_Dn4AUID)
- [Placa Arduino ESP32 C3](https://s.click.aliexpress.com/e/_DEWtkDJ)
- [Breadboard](https://s.click.aliexpress.com/e/_DEWtkDJ) (Opcional) i cables
- Bateria o font d'alimentació

### Esquema de connexions

Les connexions són les següents:

| Sensor GM | Placa Arduino |
| ---------- | ------------- |
| Pin 1 (GND) | GND |
| Pin 2 (HV) | 5v |
| Pin 3 (SIGNAL) | GPIO 10 |

### Codi
El codi en què hem treballat s'ha desenvolupat en varies fases:

1. El primer codi que va funcionar és 'Geiger led esp32c3.ino', aquest codi és tremendament senzill, però va servir per comprovar la forma més pràctica de detectar els polsos de senyal.

Per fer funcionar aquest codi simplement vam connectar l'esp32 c3 al medidor Geiger-Müller connectant el senyal al GPIO 10 i vam connectar un led al GPIO 4 per fer més fàcil veure cada cop que tenim una detecció.

Es pot connectar al port de sèrie connectant al port COM de torn a una velocitat de 9600.

La gràcia del codi està a comprovar l'estat del pin de senyal del Geiger-Müller i només saltar quan es detecta un canvi fent servir el següent fragment:

```c++
sensorState = digitalRead(SENSOR_PIN);
if (sensorState != lastSensorState) {
```

2. El codi del projecte es pot trobar al fitxer 'Geiger_web_Esp32-C3 v0.1.ino'. Aquest codi utilitza la llibreria 'WiFi.h' per connectar-se a una xarxa WiFi i la llibreria 'WebServer.h' per servir una pàgina web que mostra la radiació detectada.

El codi permet l'ús de xarxes IP estàtiques i dinàmiques, però per defecte està configurat per utilitzar DHCP. Per canviar la configuració de la xarxa, es pot modificar el següent bloc de codi:

```c++
const char* local_ip = "192.168.1.10"; // IP estàtica de la placa
const char* gateway = "192.168.1.1"; // Adreça de la porta d'enllaç
const char* subnet = "255.255.255.0"; // Màscara de subxarxa
```

Configuració del servidor web
El codi també inclou la configuració del servidor web, que s'inicia a l'inici del programa i s'encarrega de gestionar les peticions HTTP que arriben a la placa.

```c++
WebServer servidor(80);
```

Però si es vol definir la configuració de xarxa cal canviar aquesta línia per la següent. (que està comentada just a sota)

```c++
WebServer servidor(local_ip, 80, gateway, subnet);
```

Per definir el pin a què connectarem el senyal del medidor geiger ho fem a la línia següent:

```c++
#define SENSOR_PIN 10
```

Aquest programa es basa en comparar l'estat del sensor amb l'estat anterior per detectar impulsos de radiació. Això es fa a través de la funció gestionaRadiacio(), que s'executa cada vegada que es detecta un impuls.

```c++
if (sensorState != lastSensorState) {
if (sensorState == HIGH) {
```

## Fase 2.

El desenvolupament de la fase 2 està resultant més lenta del que esperàvem, però continua avançant de mica en mica.

### Materials necessaris

- Un ordinador on fer córrer tots els contenidors necessaris.
- Un ordinador diferent on fer córrer la còpia de seguretat.

Aquests ordinadors poden estar a la mateixa xarxa, poden ser ordinadors físics dedicats, poden ser contenidors que comparteixin hardware (excepte el de còpies de seguretat que ha d'estar en un lloc físicament diferent) o poden ser ordinadors virtuals contractats en serveis d'internet.

## Resultat

- En la fase 1 aquest aparell, pot mesurar la radiació ionitzant en temps real i mostrar-la en una pàgina web. Això permet tenir un control més precís de la radiació ambiental i detectar variacions inesperades.
- A la fase 2 aquest aparell pot generar dades estadístiques de radiació i històrics per poder obtenir informació útil.
- A la fase 3 aquest dispositiu passa a ser energèticament autònom i a més afegeix molta informació estadística que acompanyaria la informació de radiació que ens permetria fer anàlisis més interessants.
- A la fase 4 aquest aparell millora el seu rendiment energètic i la seva autonomia (a més que robotitzar coses sempre es maco)

## Disclaimer:
*Aquest codi s'ofereix tal com és i no es garanteix que funcioni correctament en totes les condicions. No em faig responsable dels danys que puguin resultar de l'ús d'aquesta informació. Utilitzeu-lo sota la vostra pròpia responsabilitat. Si teniu dubtes pregunteu i respondré al que pugui. Si voleu obrir proposar canvis podeu obrir fork i i voleu seguir-me, al panel del principi d'aquest readme podeu trobar links a les meves xarxes socials, Twitch i PayPal per si també voleu donar suport al meu treball.*
|               |               |               |               |               |               |
|:-------------:|:-------------:|:-------------:|-------------:|-------------:|-------------:|
| ![Hack the planet](https://img.shields.io/badge/Hack-The%20Planet-orange) | [![Discord](https://img.shields.io/discord/667340023829626920?logo=discord)](https://discord.gg/ahVq54p) | [![Twitter](https://img.shields.io/twitter/follow/4xsample?style=social&logo=twitter)](https://twitter.com/4xsample/follow?screen_name=shields_io) | [![4Xsample@mastodon.social](https://img.shields.io/badge/Mastodon-@4Xsample-blueviolet?style=for-the-badge&logo=mastodon)](https://mastodon.social/@4Xsample) | [![4Xsample](https://img.shields.io/badge/Twitch-4Xsample-6441A4?style=for-the-badge&logo=twitch)](https://twitch.tv/4Xsample) | [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.com/donate/?hosted_button_id=EFVMSRHVBNJP4) |

# Medidor Geiger amb ESP32 i placa de radiació

Aquest projecte consisteix en la creació d'un aparell per mesurar la radiació ionitzant, utilitzant un sensor Geiger-Müller (GM) i una placa Arduino.

## Informació important

Aquest projecte ha estat desenvolupat en directe a [Twitch.tv/4Xsample](https://www.twitch.tv/4Xsample). 

-  Fase 1: Muntatge d’un medidor Geiger (RadiationD v1.1) per mesurar la radiació.
-  Fase 2: Muntatge d’un servidor web en una ESP32 C3 per llegir les dades del medidor Geiger i fer-les accessibles a través d’Internet.
- Fase 3: Muntatge d’una bateria i una placa solar per alimentar tot el sistema i deixar-lo connectat permanentment de forma autònoma. Requisit: connexió WiFi.

La fase 1 ha sigut un exit (per sorpresa de tots) i el medidor de radiació funciona perfectament.

Actualment, estem ja en la fase 2, es a dir treballant en connectar el sensor a una arduino ESP32 C3 per muntar un servidor web que ens mostri les dades obtingudes pel sensor. L'objectiu final de la fase és mostrar la radiació en milisieverts per hora (mSv/h) i incloure un historial de les mesures realitzades i totes les funcions que poguem empaquetar en un servidor que pugui correr en una placa arduino ESP32 C3.

La versió actual del codi és la v0.1, la qual inclou el servidor web i mostra el nombre de pulsos per minut (CPM) en pantalla. No obstant, encara no funciona correctament perquè la placa no compta els pulsos adequadament. No sabem si això és perquè el sensor no està ben connectat o perquè hi ha un problema en el codi, però continuarem investigant per solucionar-ho.

## Materials necessaris

* Sensor GM RadiationD v1.1 (CAJOE)
* Placa Arduino ESP32 C3
* Breadboard (Opcional) i cables
* Bateria o font d'alimentació

## Esquema de connexions

Les connexions són les següents:

| Sensor GM  | Placa Arduino |
| ---------- | ------------- |
| Pin 1 (GND) | GND           |
| Pin 2 (HV)  | GPIO 27       |
| Pin 3 (SIGNAL)  | GPIO 2    |

## Codi

El codi necessari per aquest projecte es pot trobar al fitxer `Geiger_web_Esp32-C3.ino`. Aquest codi utilitza la llibreria `WiFi.h` per connectar-se a una xarxa WiFi i la llibreria `WebServer.h` per servir una pàgina web que mostra la radiació detectada.

El codi es pot resumir en els següents passos:

1. Es defineixen les variables necessàries, com ara el nom de la xarxa WiFi, la contrasenya, les connexions del sensor GM, etc.
2. Es defineixen les funcions per gestionar les peticions HTTP, com ara la pàgina principal i les peticions fallides.
3. Es defineix la funció per gestionar les interrupcions del sensor GM, que incrementa un comptador cada vegada que es detecta radiació.
4. A la funció `setup`, s'inicialitzen les connexions dels pins i es connecta la placa a la xarxa WiFi.
5. A la funció `loop`, es calcula la radiació detectada en el darrer minut i s'actualitza el valor a la pàgina web.

## Resultat

Amb aquest aparell, es pot mesurar la radiació ionitzant en temps real i mostrar-la en una pàgina web. Això permet tenir un control més precís de la radiació ambiental i detectar variacions inesperades.

## Disclaimer: 
*Aquest codi s'ofereix tal com és i no es garanteix que funcioni correctament en totes les condicions. No em faig responsable dels danys que puguin resultar de l'ús d'aquesta informació. Utilitzeu-lo sota la vostra pròpia responsabilitat. Si teniu dubtes pregunteu i respondré al que pugui. Si voleu obrir proposar cambis podeu obrir fork i i voleu seguir-me, al panel del principi d'aquest readme podeu trobar links a les meves xarxes socials, Twitch i PayPal per si també voleu donar suport al meu treball.*
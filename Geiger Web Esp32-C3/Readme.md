| | | | | | |
|:-------------:|:-------------:|:-------------:|-------------:|-------------:|-------------:|
| ![Hack the planet](https://img.shields.io/badge/Hack-The%20Planet-orange) | [![Discord](https://img.shields.io/discord/667340023829626920?logo=discord)](https://discord.gg/ahVq54p) | [![Twitter](https://img.shields.io/twitter/follow/4xsample?style=social&logo=twitter)](https://twitter.com/4xsample/follow?screen_name=shields_io) | [![4Xsample@mastodon.social](https://img.shields.io/badge/Mastodon-@4Xsample-blueviolet?style=for-the-badge&logo=mastodon)](https://mastodon.social/@4Xsample) | [![4Xsample](https://img.shields.io/badge/Twitch-4Xsample-6441A4?style=for-the-badge&logo=twitch)](https://twitch.tv/4Xsample) | [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.com/donate/?hosted_button_id=EFVMSRHVBNJP4) |

# Geiger Web Esp32-C3

## Descripció

Aquest projecte consisteix en un comptador Geiger que mesura la radiació ambiental i l'envia a una pàgina web mitjançant un mòdul ESP32-C3. El projecte va néixer de la meva curiositat per la física nuclear i el desig de crear un dispositiu útil i educatiu. Amb aquest projecte he après a utilitzar l'ESP32-C3, el protocol MQTT i la llibreria Chart.js. El projecte destaca per la seva simplicitat, funcionalitat i disseny.

## Informació important

Aquest projecte ha estat desenvolupat en directe a [Twitch.tv/4Xsample](https://www.twitch.tv/4Xsample).

- Fase 1: Muntatge d'un medidor Geiger (RadiationD v1.1) per mesurar la radiació.
- Fase 2: Muntatge d'un servidor web en una ESP32 C3 per llegir les dades del medidor Geiger i fer-les accessibles a través d'Internet.
- Fase 3: Muntatge d'una bateria i una placa solar per alimentar tot el sistema i deixar-lo connectat permanentment de forma autònoma. Requisit: connexió WiFi.
- Fase 4: Crear un suport motoritzat que apunti cap al sol perquè la placa solar rebi el màxim d'energia possible del sol que hi hagi.
- Fase 5: Millorar la seguretat informàtica del projecte per poder assumir l'entrada de dades de fonts de dades externes i així començar a acumular informació estadística des d'altres punts de recollida de dades que hagin fet aficionats d'arreu.

## Taula de continguts

- [Geiger Web Esp32-C3](#geiger-web-esp32-c3)
  - [Descripció](#descripció)
  - [Informació important](#informació-important)
  - [Taula de continguts](#taula-de-continguts)
  - [Instal·lació i ús](#installació-i-ús)
  - [Llicència](#llicència)
  - [Agraïments](#agraïments)
  - [Disclaimer:](#disclaimer)

## Instal·lació i ús

Per a instal·lar i executar el projecte necessites els següents components:

- Un comptador Geiger (per exemple el [Sensor GM RadiationD v1.1 (CAJOE)](https://s.click.aliexpress.com/e/_Dn4AUID))
- Un mòdul ESP32-C3 (per exemple, [Placa Arduino ESP32 C3](https://s.click.aliexpress.com/e/_DEWtkDJ))
- Un cable USB per a connectar l'ESP32-C3 al teu ordinador (en el cas de la placa que he recomanat seria interessant provar un cable usb c, va millor que els altres)
- Un editor de codi (per exemple, l'Arduino IDE)

Els passos per a instal·lar i executar el projecte són els següents:

1. Descarrega el codi font del projecte des d'aquest repositori de GitHub.
2. Descomprimir el codi en una carpeta i triar la versió que volem intentar implementar, (ara mateix el codi amb mes funcions es el `Geiger_web_Esp32-C3 v0.3.ino`) i cambiar el nom de l'arxiu triat per que coincideixin amb el nom de la carpeta.
3. Obre el fitxer `credentials.h` amb l'editor de codi que prefereixis.
4. Modifica les variables que vulguis usar amb les teves dades de connexió a la xarxa Wi-Fi webhook de discord i mes.
5. Assegura't de tenir instalades totes les llibreries necessaries (`WiFi.h`, `WebServer.h`, `esp_sntp.h`. `TimeLib.h` i `Discord_WebHook.h`)
6. Connecta l'ESP32-C3 al teu ordinador mitjançant el cable micro USB.
7. Selecciona la placa ESP32-C3 i el port COM corresponent des del menú Eines de l'editor de codi. (Obviament cal tenir instalada)
8. Carrega el codi a l'ESP32-C3 fent clic al botó Pujar.
9. Connecta el comptador Geiger a l'ESP32-C3 segons el següent esquema:
   
| Sensor GM | Placa Arduino |
| ---------- | ------------- |
| Pin 1 (GND) | GND |
| Pin 2 (HV) | 5v |
| Pin 3 (SIGNAL) | GPIO 10 |

10. Obre la ip de la placa ESP32C3 amb el teu navegador preferit.
11.  Gaudeix del teu comptador Geiger web!

## Llicència

Aquest projecte està sota la llicència MIT Consulta el fitxer [LICENSE](https://github.com/4Xsample/Idees-per-Arduino/blob/main/Geiger%20Web%20Esp32-C3/LICENSE) per a més detalls.

## Agraïments

Vull agrair a les següents fonts i persones que m'han inspirat o ajudat a crear aquest projecte:

- El tutorial de [Random Nerd Tutorials](https://randomnerdtutorials.com/) sobre com utilitzar l'ESP32-C3 amb l'Arduino IDE.
- El video d'[Andreas Spiess](https://www.youtube.com/watch?v=K28Az3-gV7E) que ha inspirat aquest projecte
- A l'esclau que ha picat la meitat del codi i una mica mes (encara que no ha enviat la recepta del tiramisú que deu des de fa un any) [Omirzar](https://github.com/Omirzar1337)

## Disclaimer:
*Aquest codi s'ofereix tal com és i no es garanteix que funcioni correctament en totes les condicions. No em faig responsable dels danys que puguin resultar de l'ús d'aquesta informació. Utilitzeu-lo sota la vostra pròpia responsabilitat. Si teniu dubtes pregunteu i respondré al que pugui. Si voleu obrir proposar canvis podeu obrir fork i i voleu seguir-me, al panel del principi d'aquest readme podeu trobar links a les meves xarxes socials, Twitch i PayPal per si també voleu donar suport al meu treball.*
|               |               |               |               |               |               |
|:-------------:|:-------------:|:-------------:|-------------:|-------------:|-------------:|
| ![Hack the planet](https://img.shields.io/badge/Hack-The%20Planet-orange) | [![Discord](https://img.shields.io/discord/667340023829626920?logo=discord)](https://discord.gg/ahVq54p) | [![Twitter](https://img.shields.io/twitter/follow/4xsample?style=social&logo=twitter)](https://twitter.com/4xsample/follow?screen_name=shields_io) | [![4Xsample@mastodon.social](https://img.shields.io/badge/Mastodon-@4Xsample-blueviolet?style=for-the-badge&logo=mastodon)](https://mastodon.social/@4Xsample) | [![4Xsample](https://img.shields.io/badge/Twitch-4Xsample-6441A4?style=for-the-badge&logo=twitch)](https://twitch.tv/4Xsample) | [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.com/donate/?hosted_button_id=EFVMSRHVBNJP4) |

# Senyal de directe
Aquest codi permet connectar un Arduino ESP8266 NodeMCU v3 a internet a través de WiFi, fer un ping a google.com per comprovar si hi ha accés a internet i després consultar l'API de Twitch per veure si el canal especificat està en directe.

## Funcionament
1. Connecta l'Arduino a la xarxa WiFi especificada amb el nom i contrasenya.
2. Fa un ping a google.com per comprovar si hi ha connexió a internet.
3. Si hi ha connexió a internet, fa una petició GET a l'API de Twitch per obtenir informació sobre el canal especificat.
4. Si el canal està en directe, enciu el LED de forma fixa.
5. Si el canal no està en directe, fa un breu flash cada 5 segons.
6. Si no hi ha connexió a internet, fa el patró del SOS amb el LED (---...---).
7. Si l'API de Twitch no respon o dóna error, fa un parpadeig cada desena de segon amb el LED.
8. Comprova la informació cada 60 segons.

## Requeriments
- Arduino ESP8266 NodeMCU v3
- Connexió a una xarxa WiFi amb accés a internet
- Biblioteques ESP8266WiFi, WiFiClient, ESP8266WebServer i ESP8266HTTPClient

## Configuració
Abans de carregar el codi a l'Arduino, assegureu-vos de configurar les següents variables amb les dades de la vostra xarxa WiFi i el nom del vostre canal de Twitch:
- `ssid`: Nom de la xarxa WiFi
- `password`: Contrasenya de la xarxa WiFi
- `twitch_channel`: Nom del canal de Twitch

## Depuració
Es pot utilitzar el port sèrie per veure els missatges de depuració i comprovar l'estat del programa en tot moment.


## Disclaimer: 
*Aquest codi s'ofereix tal com és i no es garanteix que funcioni correctament en totes les condicions. Utilitzeu-lo sota la vostra pròpia responsabilitat. Si voleu seguir-me, al panel del principi d'aquest readme podeu trobar links a les meves xarxes socials, Twitch i PayPal per si voleu donar suport al meu treball.*

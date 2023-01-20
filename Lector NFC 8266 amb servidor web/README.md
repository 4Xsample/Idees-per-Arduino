
|               |               |               |               |               |               |
|:-------------:|:-------------:|:-------------:|-------------:|-------------:|-------------:|
| ![Hack the planet](https://img.shields.io/badge/Hack-The%20Planet-orange) | [![Discord](https://img.shields.io/discord/667340023829626920?logo=discord)](https://discord.gg/ahVq54p) | [![Twitter](https://img.shields.io/twitter/follow/4xsample?style=social&logo=twitter)](https://twitter.com/4xsample/follow?screen_name=shields_io) | [![4Xsample@mastodon.social](https://img.shields.io/badge/Mastodon-@4Xsample-blueviolet?style=for-the-badge&logo=mastodon)](https://mastodon.social/@4Xsample) | [![4Xsample](https://img.shields.io/badge/Twitch-4Xsample-6441A4?style=for-the-badge&logo=twitch)](https://twitch.tv/4Xsample) | [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.com/donate/?hosted_button_id=EFVMSRHVBNJP4) |

# Lector RFID amb ESP8266 i RFIO-RC522
Aquest projecte és un dispositiu que llegeix targetes RFID amb un RFIO-RC522 i les mostra en un servidor web a un ESP8266. També té una pàgina OTA per configurar l'SSID i la contrasenya del WiFi al qual es connecta aquest dispositiu i enviar la IP local del dispositiu al webhook de Discord quan es connecta. El webhook de Discord també es pot configurar a la pàgina OTA. La pàgina OTA i la pàgina principal tenen un menú per triar l'idioma, que permet triar entre català i anglès. L'idioma per defecte és el català.

## Al tanto!!!
Aquest codi i el readme que estas llegint ha sigut generat directament amb ChatGPT i encara no ha sigut ni compilat ni revisat aixi que segur que donarà uns quants errors i s'ha d'arreglar un fotimer de coses però em sembla interessant veure fins on arriba sol aquest trasto.

El prompt que li he donat a ChatGPT ha sigut el seguent.

`Write an arduino code to read an rfid card uisng an RFIO-RC522 and show it in a web server on an ESP8266 
Add a OTA page to configure the SSID and pass of the wifi where to conect this device and send to a discord webhook the local ip of the device when is conected
Add a place to config the webhook on the OTA page.
Add a menu on the OTA page and on the main page to choose language and let me choose between catalan and english. The default language is catalan
And comment it in CATALAN`

P.D. Aquest readme també ha sigut generat pel ChatGPT simplement demanant el seguent promt despres d'obtenir el codi del projecte.

`Mostra el codi d'un Readme.md per github explicant aquest projecte en català.`

## Requisits
Per fer servir aquest dispositiu necessitaràs:
- Un ESP8266
- Un RFIO-RC522
- Una targeta RFID o un mòdul RFID amb targetes de prova
- Una font d'alimentació per a l'ESP8266 (ex. una bateria de 5V o un adaptador de corrent)
- Una placa de desenvolupament per a l'ESP8266 (ex. una placa NodeMCU o una placa WeMos)
- Un cable micro-USB per connectar l'ESP8266 a l'ordinador
- Un ordinador amb l'IDE d'Arduino instal·lat

## Llibreries necessàries
Per poder compilar aquest codi necessitaràs les següents llibreries:
- MFRC522 (per comunicar-se amb el RFIO-RC522)
- ESP8266WiFi (per connectar-se al WiFi amb l'ESP8266)
- WiFiClient (per enviar i rebre dades a través del WiFi)
- ESP8266WebServer (per crear un servidor web a l'ESP8266)
- ESP8266mDNS (per poder accedir al servidor web amb un nom de host)
- ArduinoOTA (per fer actualitzacions per over-the-air)

## Configuració
1. Instal·la les llibreries necessàries a l'IDE d'Arduino.
2. Connecta el RFIO-RC522 a la placa de desenvolupament de l'ESP8266 de la següent manera:
   - RFIO-RC522 | Placa de desenvolupament de l'ESP8266
   - SDA        | D2
   - SCK        | D5
   - MOSI       | D7
   - MISO       | D6
   - IRQ        | No connectat
   - GND        | GND
   - RST        | D3
   - 3.3V       | 3.3V
3. Connecta la placa de desenvolupament de l'ESP8266 a l'ordinador amb un cable micro-USB.
4. Obre el codi a l'IDE d'Arduino i modifica les constants següents perquè coincideixin amb les teves pròpies configuracions de WiFi i webhook de Discord:
   - `ssid`: l'SSID de la xarxa WiFi a la qual es vol connectar
   - `password`: la contrasenya de la xarxa WiFi a la qual es vol connectar
   - `webhook_name`: el nom del webhook de Discord
   - `webhook_url`: l'URL del webhook de Discord
5. Puja el codi a la placa de desenvolupament de l'ESP8266.
6. Un cop finalitzada la pujada, el dispositiu es connectarà automàticament a la xarxa WiFi i iniciarà el servidor web.
7. Per accedir al servidor web, obre un navegador web i ves a `http://ESP8266.local`, substituint `ESP8266` pel nom de host de la teva placa de desenvolupament de l'ESP8266. També pots trobar l'adreça IP del dispositiu al monitor de sèrie de l'IDE d'Arduino.
8. Per accedir a la pàgina OTA, ves a `http://ESP8266.local/ota`, substituint `ESP8266` pel nom de host de la teva placa de desenvolupament de l'ESP8266.

## Ús
Una vegada que hagis accedit al servidor web, podràs llegir targetes RFID amb el RFIO-RC522 i veure-les mostrades a la pàgina principal. Si vols canviar l'idioma, pots fer-ho a través del menú situat a la part superior de la pàgina. Si vols fer canvis a la configuració del WiFi o del webhook de Discord, pots fer-ho a través de la pàgina OTA.

## Actualitzacions
Per fer actualitzacions per over-the-air, connecta't a la pàgina OTA com s'ha descrit anteriorment i segueix les instruccions per pujar un nou fitxer de programa.

## Atenció
Aquest dispositiu només està destinat a ús personal i no s'ha de fer servir amb finalitats comercials sense l'autorització prèvia del propietari. L'autor no es fa responsable dels danys causats per l'ús indegut d'aquest dispositiu.

## Disclaimer: 
*Aquest codi s'ofereix tal com és i no es garanteix que funcioni correctament en totes les condicions. No em faig responsable dels danys que puguin resultar de l'ús d'aquesta informació. Utilitzeu-lo sota la vostra pròpia responsabilitat. Si teniu dubtes pregunteu i respondré al que pugui. Si voleu obrir proposar cambis podeu obrir fork i i voleu seguir-me, al panel del principi d'aquest readme podeu trobar links a les meves xarxes socials, Twitch i PayPal per si també voleu donar suport al meu treball.*
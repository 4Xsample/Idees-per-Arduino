# Roadmap
## Funcions de la ESPE.
- ✓ Registrar un canvi d'estat al pin 10. 
- ✓ Encendre un led quan es registra un canvi d'estat al pin 10 (deprecated).
- ✓ Comptar el número de canvis d'estat en els últims 60 segons i posar-ho al port de sèrie. 
- ✓ Connectar a una xarxa wifi usant la llibreria WiFi.h 
- ✓ Crear un servidor web usant WebServer.h
- ✓ Fer que la pàgina web mostri el CPM en pantalla.
- ✓ Convertir el CPM a Mili Sieverts hora.
- ✓ Mostrar per port de sèrie l'estat de connexió a wifi, i la IP en el moment que es connecta a la wifi a més del valor de radiació en Mili Sieverts hora.
- ✓ Donar cert format a la pàgina.
- ☐ Incloure algun mitjà perquè l'ESPE enviï dades a una base de dades de forma activa. 

  Dades a enviar (En cas de no tenir dades enviar N/A):
  
    - Número d'identificació de la font de dades (per si en un futur s'inclouen més punts de recollida de dades).
    
    - Data i hora de la recollida de dades.
    
    - Mili sieverts/hora.
    
    - Valor del voltatge de la bateria.
    
    - Valor del voltatge de la placa solar.
    
    - Valor de la intensitat de llum.

- ☐ Incloure algun mecanisme per que la ESPE pugui saber la hora que es i tenir-ho en una variable.(hem optat per ntp)
- ~ Incloure una comanda per poder reiniciar la ESPE usant una comanda per Serial
- ☐ Incloure una memòria que reculli cada valor i el guardi si no pot enviar les dades a la base de dades per poder enviar les dades tan bon punt tingui accés a la base de dades.
- ~ Incloure un watchdog que revisi que el codi no s'ha bloquejat i si s'ha bloquejat reiniciar el codi.
- ✓ Afegir un bloc de codi al bucle principal que comprovi l'estat de la connexió Wi-Fi i, en cas de pèrdua de senyal, intenti reconnectar-se.
- ☐ Afegir una pàgina d'administració on poder reiniciar l'ESPE manualment.
- ✓ Enviar missatges de debug amb el serial al discord a un canal dedicat pel tema.

## Funcions del Data Collector
- ✓ Aixecar una base de dades en un contenidor per recollir les dades.
- ✓ Incloure les següents columnes a la base de dades:
  
    - Número d'identificació de la font de dades (per si en un futur s'inclouen més punts de recollida de dades).
    
    - Data i hora de la recollida de dades.
    
    - Mili sieverts/hora.
    
    - Valor del voltatge de la bateria.
    
    - Valor del voltatge de la placa solar.
    
    - Valor de la intensitat de llum.
  
- ✓ Aixecar un contenidor amb Grafana per connectar-lo a la base de dades, jugar una mica i mirar quines són les gràfiques més interessants que es poden aconseguir a partir d'aquestes dades.
- ☐ Crear un servidor web que mostri gràficament de forma molt bonica informació estadística de la base de dades.

## Sistema d'energia

- ✓ Aconseguir una bateria decent de 3,7v (Al final he escollit una bateria [Huawei HB3X1](https://s.click.aliexpress.com/e/_Ddd0FeV) simplement per que n'he pogut reciclar una, encara estic dubtant si usar la bateria sencera o separar una cel·la per usar-la per separat)
- ✓ Aconseguir un gestor de carrega i descarrega per bateries de 3.7v compatible amb plaques solars de 6v com per exemple una [Placa d'alimentació mòbil UPS de 5V, 2.1A](https://s.click.aliexpress.com/e/_DCTR7EV)
- ✓ aconseguir una placa solar de 6V de mes de 10W (Necesstem una placa prou sobrada per poder seguir alimentant el projecte en dies plujosos i curts) Al final la escollida es una placa de [6V 20W 170x230mm](https://s.click.aliexpress.com/e/_DBCjdDF)
- ✓ Muntar els divisors de voltatge per poder reduir el voltatge a uns valors registrables pels pins analogics de la ESP32C3
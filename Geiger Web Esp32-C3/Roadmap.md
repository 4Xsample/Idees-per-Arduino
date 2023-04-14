# Roadmap
## Funcions de la ESPE.
- ✓ Registrar un canvi d'estat al pin 10. 
- ✓ Encendre un led quan es registra un canvi d'estat al pin 10 
- ✓ Comptar el número de canvis d'estat en els últims 60 segons i posar-ho al port de sèrie. 
- ✓ Connectar a una xarxa wifi usant la llibreria WiFi.h 
- ✓ Crear un servidor web usant WebServer.h
- ✓ Fer que la pàgina web mostri el CPM en pantalla.
- ✓ Convertir el CPM a Mili Sieverts hora.
- ✓ Mostrar per port de sèrie l'estat de connexió a wifi, i la IP en el moment que es connecta a la wifi a més del valor de radiació en Mili Sieverts hora.
- ✓ Donar cert format a la pàgina.
- ☐ Incloure algun mitjà perquè l'ESPE enviï dades a una base de dades de forma activa.
        Dades a enviar (En cas de no tenir dades enviar N/A):
            Número d'identificació de la font de dades (per si en un futur s'inclouen més punts de recollida de dades).
            Data i hora de la recollida de dades.
            Mili sieverts/hora.
            Valor del voltatge de la bateria.
            Valor del voltatge de la placa solar.
            Valor de la intensitat de llum.
- ☐ Afegir un bloc de codi al bucle principal que comprovi l'estat de la connexió Wi-Fi i, en cas de pèrdua, intenti reconnectar-se.
- ☐ Incloure una comanda per poder reiniciar la ESPE usant una comanda per Serial
- ☐ Incloure una memòria que reculli cada valor i el guardi si no pot enviar les dades a la base de dades per poder enviar les dades tan bon punt tingui accés a la base de dades.
- ☐ Incloure un watchdog que revisi que el codi no s'ha bloquejat i si s'ha bloquejat reiniciar el codi.
- ☐ Afegir un bloc de codi al bucle principal que comprovi l'estat de la connexió Wi-Fi i, en cas de pèrdua, intenti reconnectar-se.
- ☐ Afegir una pàgina d'administració on poder reiniciar l'ESPE manualment.

## Funcions del Data Collector
- ☐ Aixecar una base de dades en un contenidor per recollir les dades.
- ☐ Incloure les següents columnes a la base de dades:
        Número d'identificació de la font de dades (per si en un futur s'inclouen més punts de recollida de dades).
        Data i hora de la recollida de dades
        Mili sieverts/hora
        Valor del voltatge de la bateria.
        Valor del voltatge de la placa solar.
        Valor de la intensitat de llum.
- ✓ Aixecar un contenidor amb Grafana per connectar-lo a la base de dades, jugar una mica i mirar quines són les gràfiques més interessants que es poden aconseguir a partir d'aquestes dades.
- ☐ Crear un servidor web que mostri gràficament de forma molt bonica informació estadística de la base de dades.
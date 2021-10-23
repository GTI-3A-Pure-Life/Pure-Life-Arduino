# GTI-3A-Arduino

## Descripción general
Código c++/arduino para el funcionamiento de un componente electrónico que obtiene datos de un sensor de CO2 y son emitidos vía blutooth

## Instalación y puesta en funcionamiento
Con el IDE Arduino seguir estos pasos de instalación:
1. Arduino -> Preferencias -> Gestor de Placas Adicionales. Pegar https://www.adafruit.com/package_adafruit_index.json
2. Herramientas -> Placa -> Gestor de Placas. Buscar nRF52 e instalar "Adafruit nRF52 by Adafruit"
3. Herramientas -> Puerto. Ver qué placa ha detectado y elegirla (Por ejemplo: "Adafruit Feather nRF52840 Express")
4. Herramientas -> Placa. Elegir la misma que en el paso anterior

## Test
Instalar en el teléfono la aplicación “nRF Connect”. Con ella podremos comprobar
si nuestra placa arduino emite iBeacons

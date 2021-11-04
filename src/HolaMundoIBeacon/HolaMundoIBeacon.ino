// -*-c++-*-

// --------------------------------------------------------------
//
// Rubén Pardo Casanova
// 2021-09-14
//
// --------------------------------------------------------------

// https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython

// https://stackoverflow.com/questions/29246805/can-an-ibeacon-have-a-data-payload

// --------------------------------------------------------------
// --------------------------------------------------------------
#include <bluefruit.h>

#undef min // vaya tela, están definidos en bluefruit.h y  !
#undef max // colisionan con los de la biblioteca estándar

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "LED.h"
#include "PuertoSerie.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {
  
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

  PuertoSerie elPuerto ( /* velocidad = */ 115200 ); // 115200 o 9600 o ...

  // Serial1 en el ejemplo de Curro creo que es la conexión placa-sensor 
};

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "Publicador.h"
#include "Medidor.h"


// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

  Publicador elPublicador;

  Medidor elMedidor;

}; // namespace

// --------------------------------------------------------------
/**
 * inicializarPlaquita()
 *  Función que inicializa el micro y los pines
 */
// --------------------------------------------------------------
void inicializarPlaquita () {

  // de momento nada

} // ()

//--------------------------------------------------------------

//------------------------------------------------------------------

// --------------------------------------------------------------
// setup()
// --------------------------------------------------------------
void setup() {

  Globales::elPuerto.esperarDisponible();

  inicializarPlaquita();
  // Suspend Loop() to save power
  // suspendLoop();

  Globales::elPublicador.encenderEmisora();

  Globales::elMedidor.iniciarMedidor();

  esperar( 1000 );

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

} // setup ()

// --------------------------------------------------------------
/**
 * lucecitas()
 * Función que enciende 4 veces el LED con esperas entre medio
 */
// --------------------------------------------------------------
inline void lucecitas() {
  using namespace Globales;

  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 1000 ); // 1000 encendido
  esperar ( 1000 ); //  100 apagado
} // ()



// --------------------------------------------------------------
// loop ()
// --------------------------------------------------------------
namespace Loop {
  uint8_t cont = 0;
  int bateria = 100;
  int esperaEntreMedicionesMs = 3000; //1360
  int esperaEntreBateria = esperaEntreMedicionesMs * 2;
};

/**
 * modificado: Lorena-Ioana Florescu
 * @version 04/11/2021
 */
void loop () {

  using namespace Loop;
  using namespace Globales;

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );


  lucecitas();

  // 
  // mido y publico
  // 
  int valorCO = 0;
  int valorNO2 = 0;
  int valorSO2 = 0;
  int valorO3 = 0;
 
  valorCO = elMedidor.medirCO();
  valorSO2 = elMedidor.medirSO2();
  valorNO2 = elMedidor.medirNO2();
  valorO3 = elMedidor.medirO3();

  //valor random de CO
  elPublicador.publicarCO(random(0,18),1000);

  //valor medido de CO
//  elPublicador.publicarCO( valorCO,
//							1000 // intervalo de emisión
//							);

//mediciones con valores random
  elPublicador.publicarSO2( valorSO2,
             1000 // intervalo de emisión
              );
  elPublicador.publicarNO2( valorNO2,
              1000 // intervalo de emisión
              );
  elPublicador.publicarO3( valorO3,
              1000 // intervalo de emisión
              );
 //mandar bateria
  if (esperaEntreBateria == 0){
        elPublicador.publicarBateria(bateria,
              1000 // intervalo de emisión
              );
        if(bateria==0) bateria = 100;
        else bateria = bateria - 10;
 }
/*  elPublicador.publicarBateria(bateria,
              1000 // intervalo de emisión
              );
        if(bateria==0) bateria = 100;
       else bateria = bateria - 10;*/


//mediciones controladas
  /*
  if(cont ==0) elPublicador.publicarCO(1,1000);
  if(cont ==1) elPublicador.publicarO3(20,1000);
  if(cont ==2) elPublicador.publicarSO2(100,1000);
  if(cont ==3) elPublicador.publicarNO2(60,1000);
  if(cont ==4) elPublicador.publicarCO(10,1000);
  if(cont ==5) elPublicador.publicarSO2(10,1000);
  */
  
  esperar(esperaEntreMedicionesMs);

  esperaEntreBateria -= esperaEntreMedicionesMs;
  if (esperaEntreBateria <0) esperaEntreBateria = esperaEntreMedicionesMs * 2;

  elPublicador.laEmisora.detenerAnuncio();
  
  // 
  // 
  // 
  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );

  cont++;
  if (cont>5) cont = 0;
  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------

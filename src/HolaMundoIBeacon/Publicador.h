// -*- mode: c++ -*-

// ----------------------------------------------------------
// Rubén Pardo Casanova
// 2021-09-14
// ----------------------------------------------------------

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// --------------------------------------------------------------
// --------------------------------------------------------------
class Publicador {

  // ............................................................
  // ............................................................
private:

  uint8_t beaconUUID[16] = { 
	'G', 'T', 'I', '-', '3', 'A', '-', '1',
	'%', '%', '%', '%', '%', '%', '%', '%'
	};

  // ............................................................
  // ............................................................
public:


  EmisoraBLE laEmisora {
	"GTI-3A-1", //  nombre emisora
	  0x004c, // fabricanteID (Apple)
	  4 // txPower
	  };
  
  const int RSSI = -53; // por poner algo, de momento no lo uso

  // ............................................................
  // ............................................................
public:

  // ............................................................
  // ............................................................
  enum MedicionesID  {
    SO2 = 3,
    O3 = 4,
    NO2 = 2,
    CO = 1,
  	BATERIA = 1000
  };

  // ............................................................
  // ............................................................
  /**
   * Constructor para la clase Publicador
   *
   */
  Publicador( ) {
	// ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
	// Pondremos un método para llamarlo desde el setup() más tarde
  } // ()

  // ............................................................
  // ............................................................
  /**
   * encenderEmisora()
   *
   */
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  } // ()

  // ............................................................
  // ............................................................
  /**
   * 
   * N,N,N -> publicarCO()
   *
   * @param valorCO
   * @param tiempoEspera ms en el que el anuncio se esta emitiendo
   *
   */
  void publicarCO( int16_t valorCO, long tiempoEspera ) {

	//
	// 1. empezamos anuncio
	//
	uint16_t major = MedicionesID::CO;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											major,
											valorCO, // minor
											(*this).RSSI // rssi
									);
	//
	// 2. esperamos el tiempo que nos digan
	//
	esperar( tiempoEspera );

	//
	// 3. paramos anuncio
	//
	(*this).laEmisora.detenerAnuncio();
  } // ()


   /**
   * @author Lorena-Ioana Florescu
   * @version 04/11/2021
   * N,N,N -> publicarSO()
   *
   * @param valorSO 
   * @param tiempoEspera ms en el que el anuncio se esta emitiendo
   *
   */
  void publicarSO2( int16_t valorSO2, long tiempoEspera ) {

  uint16_t major = MedicionesID::SO2;
  (*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
                      major,
                      valorSO2, // minor
                      (*this).RSSI // rssi
                  );
  esperar(tiempoEspera);

  (*this).laEmisora.detenerAnuncio();
  } 

   /**
   * @author Lorena-Ioana Florescu
   * @version 04/11/2021
   * N,N,N -> publicarNO2()
   *
   * @param valorNO2
   * @param tiempoEspera ms en el que el anuncio se esta emitiendo
   *
   */
  void publicarNO2( int16_t valorNO2, long tiempoEspera ) {

  uint16_t major = MedicionesID::NO2;
  (*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
                      major,
                      valorNO2, // minor
                      (*this).RSSI // rssi
                  );
  esperar(tiempoEspera);

  (*this).laEmisora.detenerAnuncio();
  } 

   /**
   * @author Lorena-Ioana Florescu
   * @version 04/11/2021
   * N,N,N -> publicarO3()
   *
   * @param valorO3
   * @param tiempoEspera ms en el que el anuncio se esta emitiendo
   *
   */
  void publicarO3( int16_t valorO3, long tiempoEspera ) {

  uint16_t major = MedicionesID::O3;
  (*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
                      major,
                      valorO3, // minor
                      (*this).RSSI // rssi
                  );
  esperar(tiempoEspera);

  (*this).laEmisora.detenerAnuncio();
  } 

  // ............................................................
  // ............................................................
   /**
   * @author Lorena-Ioana Florescu
   * @version 04/11/2021
   * N,N,N -> publicarBateria()
   *
   * @param valorBateria 
   * @param contador numero para el calculo del valor del major del beacon
   * @param tiempoEspera ms en el que el anuncio se esta emitiendo
   *
   */
  void publicarBateria( int16_t valorBateria, long tiempoEspera ) {

	uint16_t major = MedicionesID::BATERIA;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											major,
											valorBateria, // minor
											(*this).RSSI // rssi
									);
	esperar(tiempoEspera);

	(*this).laEmisora.detenerAnuncio();
  } 
	
}; // class

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif

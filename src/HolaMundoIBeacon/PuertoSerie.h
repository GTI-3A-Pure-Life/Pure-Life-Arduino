
// -*- mode: c++ -*-

// ----------------------------------------------------------
// Rubén Pardo Casanova
// 2021-09-14
// ----------------------------------------------------------

#ifndef PUERTO_SERIE_H_INCLUIDO
#define PUERTO_SERIE_H_INCLUIDO

// ----------------------------------------------------------
// ----------------------------------------------------------
class PuertoSerie  {

public:
  // .........................................................
  // .........................................................
  /**
   * Constructor para la clase PuertoSerie
   *
   * @param baudios velocidad del puerto serie 
   *
   */
  PuertoSerie (long baudios) {
  	Serial.begin( baudios );
  	// mejor no poner esto aquí: while ( !Serial ) delay(10);   
  } // ()

  // .........................................................
  // .........................................................
  /**
   * esperarDisponible()
   * Bucle infinito hasta que el puerto serie este disponible
   *
   */
  void esperarDisponible() {

  	while ( !Serial ) {
  	  delay(10);   
  	}

  } // ()

  // .........................................................
  // .........................................................
   /**
   * T -> escribir()
   *
   * @param mensaje contenido a escribir por el puerte serie
   *
   */
  template<typename T>
  void escribir (T mensaje) {
	  Serial.print( mensaje );
  } // ()
  
}; // class PuertoSerie

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif

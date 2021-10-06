// -*- mode: c++ -*-

// ----------------------------------------------------------
// Rubén Pardo Casanova
// 2021-09-14
// ----------------------------------------------------------
#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO

// ----------------------------------------------------
// ----------------------------------------------------
#include <vector>

// ----------------------------------------------------
// alReves() utilidad
// pone al revés el contenido de una array en el mismo array
// ----------------------------------------------------
template< typename T >
T *  alReves( T * p, int n ) {
  T aux;

  for( int i=0; i < n/2; i++ ) {
	aux = p[i];
	p[i] = p[n-i-1];
	p[n-i-1] = aux;
  }
  return p;
} // ()

// ----------------------------------------------------
// ----------------------------------------------------
/**
 * Texto -> stringAUint8AlReves() -> Lista<N>, Lista<N>
 *
 * @param pString texto a girar y convertir.
 * @param param2 Descripcion de param2.
 *
 * @return Descripcion del valor devuelto.
 */
uint8_t * stringAUint8AlReves( const char * pString, uint8_t * pUint, int tamMax ) {

	int longitudString =  strlen( pString );
	int longitudCopiar = ( longitudString > tamMax ? tamMax : longitudString );
	// copio nombreServicio -> uuidServicio pero al revés
	for( int i=0; i<=longitudCopiar-1; i++ ) {
	  pUint[ tamMax-i-1 ] = pString[ i ];
	} // for

	return pUint;
} // ()

// ----------------------------------------------------------
// ----------------------------------------------------------
class ServicioEnEmisora {

public:


  // --------------------------------------------------------
  // --------------------------------------------------------

  // .........................................................
  // .........................................................
  /**
   * conn_handle:N, chr:BLECharacteristic, data:Lista<N>, len:N -> ()
   * @param conn_handle valor para identificar el proceso en el callback
   * @param chr caracteristica escrita
   * @param data informacion escrita
   * @param len longitud de la informacion
   */
  using CallbackCaracteristicaEscrita = void ( uint16_t conn_handle,
											   BLECharacteristic * chr,
											   uint8_t * data, uint16_t len); 
  // .........................................................
  // .........................................................
  class Caracteristica {
  private:
	uint8_t uuidCaracteristica[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
	  // least signficant byte, el primero
	  '0', '1', '2', '3', 
	  '4', '5', '6', '7', 
	  '8', '9', 'A', 'B', 
	  'C', 'D', 'E', 'F'
	};

	// 
	// 
	// 
	BLECharacteristic laCaracteristica;

  public:

	// .........................................................
	// .........................................................
  /**
   * Constructor para la clase Caracteristica con solo el nombre
   * Texto -> constructor()
   *
   * @param nombreCaracteristica_ 
   *
   */
	Caracteristica( const char * nombreCaracteristica_ )
	  :
	  laCaracteristica( stringAUint8AlReves( nombreCaracteristica_, &uuidCaracteristica[0], 16 ) )
	{
	  
	} // ()

	// .........................................................
	// .........................................................
  /**
   * Constructor para la clase Caracteristica
   * Texto, N, SecureMode_t, SecureMode_t, N -> constructor()
   * 
   * @param nombreCaracteristica_ 
   * @param props mascara de las propiedades.
   * @param permisoRead permiso de lectura del servicio
   * @param permisoWrite permiso de escritura del servicio
   * @param tam tamanyo maximo de los datos 
   *
   */
	Caracteristica( const char * nombreCaracteristica_ ,
					uint8_t props,
					SecureMode_t permisoRead,
					SecureMode_t permisoWrite, 
					uint8_t tam ) 
	  :
	  Caracteristica( nombreCaracteristica_ ) // llamada al otro constructor
	{
	  (*this).asignarPropiedadesPermisosYTamanyoDatos( props, permisoRead, permisoWrite, tam );
	} // ()

  private:
	// .........................................................
	// CHR_PROPS_WRITE , CHR_PROPS_READ ,  CHR_PROPS_NOTIFY 
	// .........................................................
  /**
   * N -> asignarPropiedades()
   * Asignar propiedades de escritura, lectura y/o notificacion
   *
   * @param props mascara de propiedades
   *
   */
	void asignarPropiedades ( uint8_t props ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( " laCaracteristica.setProperties( props ); ");
	  (*this).laCaracteristica.setProperties( props );
	} // ()

	// .........................................................
	// SecureMode_t::SECMODE_OPEN  , SecureMode_t::SECMODE_NO_ACCESS
	// .........................................................
  /**
   * SecureMode_t, SecureMode_t -> asignarPermisos()
   *
   * @param permisoRead permiso de lectura del servicio
   * @param permisoWrite permiso de escritura del servicio
   *
   */
	void asignarPermisos( SecureMode_t permisoRead, SecureMode_t permisoWrite ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( "laCaracteristica.setPermission( permisoRead, permisoWrite ); " );
	  (*this).laCaracteristica.setPermission( permisoRead, permisoWrite );
	} // ()

	// .........................................................
	// .........................................................
  /**
   * N -> asignarTamanyoDatos()
   *
   * @param tam tamayo maximo de los datos que se transmitiran en el servicio.
   * 
   */
	void asignarTamanyoDatos( uint8_t tam ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.print( " (*this).laCaracteristica.setFixedLen( tam = " );
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( tam );
	  // (*this).laCaracteristica.setFixedLen( tam );
	  (*this).laCaracteristica.setMaxLen( tam );
	} // ()

  public:
	// .........................................................
	// .........................................................
  /**
   * N, SecureMode_t, SecureMode_t, N -> asignarPropiedadesPermisosYTamanyoDatos()
   *
   * @param props mascara de las propiedades.
   * @param permisoRead permiso de lectura del servicio
   * @param permisoWrite permiso de escritura del servicio
   * @param tam tamanyo maximo de los datos 
   *
   */
	void asignarPropiedadesPermisosYTamanyoDatos( uint8_t props,
												 SecureMode_t permisoRead,
												 SecureMode_t permisoWrite, 
												 uint8_t tam ) {
	  asignarPropiedades( props );
	  asignarPermisos( permisoRead, permisoWrite );
	  asignarTamanyoDatos( tam );
	} // ()
												 

	// .........................................................
	// .........................................................
  /**
   * Texto -> escribirDatos() -> N
   *
   * @param str texto a escribir
   *
   * @return numero de bytes escritos
   */
	uint16_t escribirDatos( const char * str ) {
	  // Serial.print( " return (*this).laCaracteristica.write( str  = " );
	  // Serial.println( str );

	  uint16_t r = (*this).laCaracteristica.write( str );

	  // Serial.print( ">>>Escritos " ); Serial.print( r ); Serial.println( " bytes con write() " );

	  return r;
	} // ()

	// .........................................................
	// .........................................................
  /**
   * Texto -> notificarDatos() -> N
   *
   * @param str datos a notificar
   *
   * @return numero de bytes notificados
   */
	uint16_t notificarDatos( const char * str ) {
	  
	  uint16_t r = laCaracteristica.notify( &str[0] );

	  return r;
	} //  ()

	// .........................................................
	// .........................................................
  /**
   * CallbackCaracteristicaEscrita -> instalarCallbackCaracteristicaEscrita()
   *
   * @param cb callback de caracterisitica escrita a instalar
   */
	void instalarCallbackCaracteristicaEscrita( CallbackCaracteristicaEscrita cb ) {
	  (*this).laCaracteristica.setWriteCallback( cb );
	} // ()

	// .........................................................
	// .........................................................
  /**
   * activar()
   * 
   */
	void activar() {
	  err_t error = (*this).laCaracteristica.begin();
	  Globales::elPuerto.escribir(  " (*this).laCaracteristica.begin(); error = " );
	  Globales::elPuerto.escribir(  error );
	} // ()

  }; // class Caracteristica
  
  // --------------------------------------------------------
  // --------------------------------------------------------
private:
  
  uint8_t uuidServicio[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
	// least signficant byte, el primero
	'0', '1', '2', '3', 
	'4', '5', '6', '7', 
	'8', '9', 'A', 'B', 
	'C', 'D', 'E', 'F'
  };

  //
  //
  //
  BLEService elServicio;

  //
  //
  //
  std::vector< Caracteristica * > lasCaracteristicas;

public:
  
  // .........................................................
  // .........................................................
  /**
   * Texto -> constructor()
   *
   * @param nombreServicio_
   *
   */
  ServicioEnEmisora( const char * nombreServicio_ )
	:
	elServicio( stringAUint8AlReves( nombreServicio_, &uuidServicio[0], 16 ) )
  {
	
  } // ()
  
  // .........................................................
  // .........................................................
  /**
   * escribeUUID()
   * Escribe el uuid por el puerto serie
   */
  void escribeUUID() {
  	Serial.println ( "**********" );
  	for (int i=0; i<= 15; i++) {
  	  Serial.print( (char) uuidServicio[i] );
  	}
  	Serial.println ( "\n**********" );
  } // ()

  // .........................................................
  // .........................................................
  /**
   * Caracteristica -> anyadirCaracteristica()
   *
   * @param car Caracteristica a anyadir
   *
   */
  void anyadirCaracteristica( Caracteristica & car ) {
	(*this).lasCaracteristicas.push_back( & car );
  } // ()

  // .........................................................
  // .........................................................
  /**
   * activarServicio()
   *
   */
  void activarServicio( ) {
	// entiendo que al llegar aquí ya ha sido configurado
	// todo: características y servicio

	err_t error = (*this).elServicio.begin();
	Serial.print( " (*this).elServicio.begin(); error = " );
	Serial.println( error );

	for( auto pCar : (*this).lasCaracteristicas ) {
	  (*pCar).activar();
	} // for

  } // ()

  // .........................................................
  // .........................................................
  operator BLEService&() {
	// "conversión de tipo": si pongo esta clase en un sitio donde necesitan un BLEService
	return elServicio;
  } // ()
	
}; // class

#endif

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------

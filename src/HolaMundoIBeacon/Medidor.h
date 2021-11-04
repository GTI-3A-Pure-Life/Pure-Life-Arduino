// -*- mode: c++ -*-

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

#include <Arduino.h>
#include <Adafruit_TinyUSB.h> // for Serial

// Definicion de los pines UART
#define RX_PIN 15
#define TX_PIN 17

// ----------------------------------------------------------
// Rubén Pardo Casanova
// 2021-09-14
// ----------------------------------------------------------

// ------------------------------------------------------
// ------------------------------------------------------
class Medidor {

  // .....................................................
  // .....................................................
private:

public:

  // .....................................................
  // .....................................................
  /**
   * Constructor para la clase Medidor
   *
   */
  Medidor(  ) {
  } // ()

  // .....................................................
  // .....................................................
  /**
   * iniciarMedidor() 
   */
  void iniciarMedidor() {
	// las cosas que no se puedan hacer en el constructor, if any
    Serial1.begin(9600);

  } // ()

  // .....................................................
  // .....................................................
  /**
   * medirCO() -> N
   *
   * @returns el valor obtenido con el sensor de co2 (primera version con valores falsos).
   *
   */
  int medirCO() {
     //medir varias veces y hacer un promedio para reducir error
    // 
    Serial.println("EMPEZAR MEDIR CO----------");
    int i = 0;// contador de los 11 valores
    int j = 0;// contador de veces
    
    int sensorData [11] = {0,0,0,0,0,0,0,0,0,0,0};
    
 
      
    Serial1.print('\r'); // Inicia una lectura del sensor. Ahora hay que espera a que nos envíe algo de vuelta!
    for (int i =0; i<11; i++) {
       while(!Serial1.available()) { Serial.print("..");}
        sensorData[i] = Serial1.parseInt();
      }

     Serial1.flush();
    
    
    Serial.print("TERMINAR MEDIR CO---------- ");
    Serial.println(sensorData[1]);
    
	  return sensorData[1]/*/numMedidasAMedir*/;//devolvemos co2
  } // ()

/** 
 * @author Lorena-Ioana Florescu
 * @version 04/11/2021
 * medirSO2()
 * Metodo para obtener la medicion de SO2
 */
  int medirSO2(){
    return random(0,140);
  }

/**
 * @author Lorena-Ioana Florescu
 * @version 04/11/2021
 * medirNO2()
 * Metodo para obtener la medicion de NO2
 */
   int medirNO2(){
    return random(0,115);
  }

/**
 * @author Lorena-Ioana Florescu
 * @version 04/11/2021
 * medirO3()
 * Metodo para obtener la medicion de O3
 */
    int medirO3(){
    return random(0,95);
  }



  
}; // class

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
#endif

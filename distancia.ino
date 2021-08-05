#include "ServoDist.h"
#define UMBRAL 30.00

volatile int estado = HIGH;
float tanterior = 0;
ServoDist distanciador;

void setup() {
  Serial.begin(9600);
  attachInterrupt(0, intExt, FALLING);
  pinMode(BUZZER_PIN, OUTPUT);    
  distanciador.inicializar();
}

void loop() {
    distanciador.mostrarDistancia();
    if(estado == HIGH){
      if(distanciador.getDistancia() < UMBRAL && distanciador.getEstadoServo() == 0){
        distanciador.zumbar();
        distanciador.abrir();
      }else if(distanciador.getDistancia() > UMBRAL && distanciador.getEstadoServo() == 180){
        distanciador.noZumbar();
        distanciador.cerrar();
      }else{
        distanciador.noZumbar();
        distanciador.mostrarEstadoServo();  
      }
    }else{
      distanciador.zumbar();
      distanciador.abrir(); 
      distanciador.mostrarEstadoServo("Apertura manual");
    }

    
}

void intExt() {
  if((millis()-tanterior) > 500){
    estado = !estado;
  }
  tanterior = millis();
}

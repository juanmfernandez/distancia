#include "Arduino.h"
//#include <Wire.h>
//#include <OneWire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define BUZZER_PIN 7

Servo servo;

int PINSERVO = 6;
int PULSOMIN = 1000;
int PULSOMAX = 2000;

int TRIG = 9;
int ECO = 10;

long DURACION;
int DISTANCIA;

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7);

class ServoDist {

    private:

    public:

        void inicializar(){
            Serial.begin(9600);
            servo.attach(PINSERVO, PULSOMIN, PULSOMAX);
            servo.write(0);
            pinMode(TRIG, OUTPUT);
            pinMode(ECO, INPUT);
            pinMode(BUZZER_PIN, OUTPUT);
            lcd.setBacklightPin(3, POSITIVE);
            lcd.setBacklight(HIGH);
            lcd.begin(16, 2);
            lcd.clear();
        }

        float getDistancia() {
            digitalWrite(TRIG, LOW);
            delayMicroseconds(2);
            digitalWrite(TRIG, HIGH);
            delayMicroseconds(10);
            digitalWrite(TRIG, LOW);
            
            DURACION = pulseIn(ECO, HIGH);
            DISTANCIA = DURACION / 58.2; //espec del fabricante constante
            return DISTANCIA;
        }

        void mostrarDistancia() {

            float DISTANCIA = getDistancia();

            Serial.print("Distancia: ");
            Serial.print(DISTANCIA);
            Serial.println(" cm");
            
            lcd.setCursor(0, 1);
            lcd.print("Dist: ");
            lcd.print(DISTANCIA);
            lcd.print(" cm");
            delay(600);
        }

        void zumbar(){
          digitalWrite(BUZZER_PIN, HIGH);
          delay(100);
          digitalWrite(BUZZER_PIN, LOW);
        }

        void noZumbar(){
          digitalWrite(BUZZER_PIN, LOW);
        }
        
        void abrir(){
          servo.write(180);
        }

        void cerrar(){
          servo.write(0);
        }
        
        int getEstadoServo(){
          return servo.read();
        }

        void mostrarEstadoServo(char msg[10] = NULL) {
            if(msg == NULL){
              int estado = getEstadoServo();
              Serial.print("Estado: ");
              Serial.println(estado);
              
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Estado: ");
              lcd.print(estado);
            }else{
              Serial.println(msg);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(msg);
            }        
        }
};

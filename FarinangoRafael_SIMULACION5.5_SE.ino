/*
 *CAPITULO V: FUNCIONES ESPECIFICAS
 *CODIGO 23: MANEJO DE MODO SLEEP 
 *OBJETIVO: REALIZAR UN CONTROL DE MODOS SLEEP POR MEDIO DE INTERRUPCIONES
 *NOMBRE: RAFAEL FARINANGO
 *                              MODO SLEEP Y DE AHORRO DE BATERIA
 *                              CONSUMO ES DE 100-500mA 
 *                              AHORRO DE BATERIA HASTA DE 10mA
 *                              LIBRERIAS: avr/sleep.h, avr/power.h
 */

#include<avr/power.h>
#include<avr/sleep.h>
#include<avr/wdt.h>
#include <MsTimer2.h>
#include<EEPROM.h>
int dato;
int on=0;
void(* resetFunc) (void) = 0; 
//void on(void);
void setup() {
   dato=EEPROM.read(0);
   Serial.begin(9600);
   Serial.println("SETUP");
   if(dato==0){
    set_sleep_mode(SLEEP_MODE_STANDBY);
    sleep_enable();
    EEPROM.write(0,1);
    wdt_enable(WDTO_8S);
    }
    else{
    sleep_disable();
     EEPROM.write(0,0);
      MsTimer2::set(10000,tiempo); // configura timer 2 a un segundo
       MsTimer2::start();
    }
   attachInterrupt(0,encender,LOW);
}
void loop() {
if(dato==0){
  Serial.println("DORMIDO");
  delay(20);
 sleep_mode(); 
}
 else{
  Serial.println("DESPIERTO");
  delay(1000);
  }
}
void tiempo(){
  Serial.println("DORMIDO");
  delay(2000);
  sleep_mode();
 }
 
 void encender (){
    resetFunc();  
 }


//#include <avr/sleep.h>
//#include <avr/power.h>
//#include <avr/wdt.h>
//#include <MsTimer2.h>
//#include <EEPROM.h>
//
//
//int dato;
//int on = 0;
//
//void(*resetFunc) (void) = 0;        //es la funcion para reseteo  //void on(void)
//
//
//void setup() {
//  dato = EEPROM.read(0);
//  Serial.begin(9600);
//  Serial.println("SETUP");
//  if(dato == 0){
//    set_sleep_mode(SLEEP_MODE_STANDBY);
//    sleep_enable();
//    EEPROM.write(0,1);
//    wdt_enable(WDTO_8S);
//  }
//  else{
//    sleep_disable();
//    EEPROM.write(0,0);
//    MsTimer2::set(1000, tiempo);      //configura de timer2 a 1 seg
//    MsTimer2::start();
//  }  
//  attachInterrupt(0, encender, LOW);
//}
//
//
//void loop() {
//  if(dato == 0){
//    Serial.println("DORMIDO");
//    delay(20);
//    sleep_mode();                 //entra al estado de "DORMIDO"
//  }
//  else{
//    Serial.println("DESPIERTO");
//    delay(1000);  
//  }  
//}
//
//
//void tiempo(){
//  Serial.println("DORMIDO");
//  delay(2000);
//  sleep_mode();
//}
//
//
//void encender(){
//  resetFunc();
//}

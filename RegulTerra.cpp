#include "RegulTerra.h"
#include <Arduino.h>

// le contructeur de l'eclairage
Eclairage::Eclairage(int8_t pin_Relais_Eclairage) {
  this->pin_Relais_Eclairage = pin_Relais_Eclairage;
  pinMode(pin_Relais_Eclairage, OUTPUT);
  digitalWrite(pin_Relais_Eclairage, HIGH);
}

// le contructeur du chauffage
RegulTemp::RegulTemp(int8_t pin_Relais_Chauffage) {
  this->pin_Relais_Chauffage = pin_Relais_Chauffage;
  pinMode(pin_Relais_Chauffage, OUTPUT);
  digitalWrite(pin_Relais_Chauffage, HIGH);
}

// le contructeur du brumisateur
RegulHumi::RegulHumi(int8_t pin_Relais_Brumisateur) {
  this->pin_Relais_Brumisateur = pin_Relais_Brumisateur;
  pinMode(pin_Relais_Brumisateur, OUTPUT);
  digitalWrite(pin_Relais_Brumisateur, HIGH);
}

// le contructeur du flotteur
Niveau::Niveau(int8_t pin_Flotteur) {
  this->pin_Flotteur = pin_Flotteur;
  pinMode(pin_Flotteur, INPUT_PULLUP);
}

// le contructeur du Buzzer
Alarme::Alarme(int8_t pin_Buzzer) {
  this->pin_Buzzer = pin_Buzzer;
  pinMode(pin_Buzzer, OUTPUT);
}

// la fonction qui gère l'éclairage
bool Eclairage::gestion( int8_t Maintenant_H, int8_t Maintenant_M, int8_t Lever_H, int8_t Lever_M, int8_t Coucher_H, int8_t Coucher_M ) {
	bool result;
    int Lever = (Lever_H * 100 + Lever_M);
    int Coucher = (Coucher_H * 100 + Coucher_M);  
    int Maintenant = (Maintenant_H * 100 + Maintenant_M);  
    if (Maintenant > Lever && Maintenant < Coucher) {
      digitalWrite(pin_Relais_Eclairage, LOW); 
      result = true;
    } else {
      digitalWrite(pin_Relais_Eclairage, HIGH);
      result = false;
    }
    return result;  
  }

// la fonction qui régule la température
bool RegulTemp::gestion( float value_Temp, int8_t target_Temp, float Hys_Temp ) {  	
	bool result;
	if (isnan(value_Temp)) { 
		digitalWrite(pin_Relais_Chauffage, HIGH); 
		result = false;
	} else {
        if (value_Temp < target_Temp - Hys_Temp) { 
			digitalWrite(pin_Relais_Chauffage, LOW); 
          	result = true;
        }
        if (value_Temp > target_Temp + Hys_Temp) { 
          digitalWrite(pin_Relais_Chauffage, HIGH); 
          result = false;
        }  
	} 
	return result;            
}

// la fonction qui régule l'humidité
bool RegulHumi::gestion( float value_Humi, int8_t target_Humi, int8_t Hys_Humi ) {   
	bool result;
	if (isnan(value_Humi)) { 
		digitalWrite(pin_Relais_Brumisateur, HIGH); 
		result = false;
	} else {
        if (value_Humi < target_Humi - Hys_Humi) { 
			digitalWrite(pin_Relais_Brumisateur, LOW); 
          	result = true;
        }
        if (value_Humi > target_Humi + Hys_Humi) { 
          digitalWrite(pin_Relais_Brumisateur, HIGH); 
          result = false;
        }  
	}
	return result;                  
}

// la fonction qui vérifie le niveau d'eau
bool Niveau::verif() {   
	bool Niveau_Eau = digitalRead(pin_Flotteur);    
	return Niveau_Eau;                  
}


// la fonction qui joue les notes
void Alarme::beep( int note, int duree ) {                   
    tone(pin_Buzzer, note);                              
    delay(duree);
    noTone(pin_Buzzer); 
    delay(duree*0.25);
}

// la fonction qui alerte
void Alarme::Alerte_Sonore() {
  beep(NOTE_AS4, 125); 
  beep(NOTE_G4, 125);
  beep(NOTE_AS4, 125); 
}

// la fonction qui alerte temp
int8_t Alarme::Alerte_Temp(float value_Temp, int8_t TempMin, int8_t TempMax) {
	int8_t result;
	if (value_Temp < TempMin) { result = 0; }
	if (value_Temp > TempMax) { result = 2; }
	else{ result = 1; }
	return result;
}



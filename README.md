# RegulTerra

Une librairie pour les terrarium.

- la class **Eclairage** 
    - un constructeur : **Eclairage(pin_de_votre_relais);**    
    il déclarera le GPIO en sortie pour le relais de la lumière.
    - une méthode : **gestion(Maintenant_H, Maintenant_M, Lever_H, Lever_M, Coucher_H, Coucher_M);**    
    elle active le relais quand l'heure est comprise entre le lever et le coucher.     

- la class **RegulTemp**
    - un constructeur : **RegulTemp(pin_de_votre_relais);**    
    il déclarera le GPIO en sortie pour le relais du chauffage.
    - une méthode : **gestion(température_lu_d'un capteur(type float), consigne_de_température(type int), Hystérésis_pour_la_consigne(type float));**    
    elle active le relais quand la température est en dessous de la consigne - l'Hystérésis et retourne 1.    
    elle désactive le relais quand la température est au dessus de la consigne + l'Hystérésis et retourne 0.    

- la class **RegulHumi**
    - un constructeur : **RegulHumi(pin_de_votre_relais);**    
    il déclarera le GPIO en sortie pour le relais du brumisateur.
    - une méthode : **gestion(humidité_lu_d'un capteur(type float), consigne_d_humidité(type int), Hystérésis_pour_l_humidité(type int));**    
    elle active le relais quand l'humidité est en dessous de la consigne - l'Hystérésis et retourne 1.    
    elle désactive le relais quand l'humidité est au dessus de la consigne + l'Hystérésis et retourne 0.

- la class **Niveau**
  - un constructeur : **Niveau(pin_de_votre_flotteur);**    
  il déclarera le GPIO en entrée avec pull_up pour le flotteur.  
  - une méthode : **verif();**    
    elle  retourne 1 si le niveau est bon.   
    elle retourne 0 si le niveau est insuffisant.   

- la class **Alarme**
  - un constructeur : **Alarme(pin_de_votre_buzzer);**    
  il déclarera le GPIO en sortie pour le buzzer.  
  - une méthode : **Alerte_Temp(température_lu_d'un capteur(type float), Consigne_Temp_Mini(type int),  Consigne_Temp_Maxi(type int));**   
  elle  retourne 0 si la température est en dessous de la consigne mini.
  elle  retourne 2 si la température est au dessus de la consigne maxi.
  elle  retourne 1 si la température est comprise entre la consigne mini et la consigne maxi.
  - une méthode : **Alerte_Sonore()**    
  elle sonne l'alarme. 
  

#define PIN_TRIG 22
#define PIN_ECHO 23
#define PIN_BP_STOP 14

#define PIN_LED_ROUGE 4
#define PIN_LED_JAUNE 5
#define PIN_LED_VERTE 17

#define PIN_OUTPUT_STOP 18
#define PIN_OUTPUT_SLOW 19

int distanceCm = 0;
boolean stateStop = LOW;


void setup() {
  Serial.begin(115200); //Initialise les liaisons series
  initInputOutput();
}


void loop() {
  
  distanceCm = readCapteurUs(); 
  Serial.println(distanceCm); //Debug
  Serial.println(stateStop); //Debug
  
  if (digitalRead(PIN_BP_STOP) == LOW) { 
    stateStop = !stateStop;
    delay(50);
  }
  
  // Bouton enfoncé OU distance inférieure à 60 cm
  if ((stateStop == HIGH) || (distanceCm < 60)) { 
    digitalWrite(PIN_OUTPUT_STOP, LOW);
    digitalWrite(PIN_OUTPUT_SLOW, HIGH);
    digitalWrite(PIN_LED_ROUGE, HIGH);
    digitalWrite(PIN_LED_JAUNE, LOW);
    digitalWrite(PIN_LED_VERTE, LOW);
  }
  // Distance entre 60 et 230 cm
  else if ((stateStop == LOW) && ((distanceCm > 60) && (distanceCm < 150))) { 
    digitalWrite(PIN_OUTPUT_STOP, HIGH);
    digitalWrite(PIN_OUTPUT_SLOW, LOW);
    digitalWrite(PIN_LED_ROUGE, LOW);
    digitalWrite(PIN_LED_JAUNE, HIGH);
    digitalWrite(PIN_LED_VERTE, LOW);
  }  
  // Distance supérieur à 150 et inférieur a 220 cm
  else if ((stateStop == LOW) && ((distanceCm > 150) && (distanceCm < 220))) { 
    digitalWrite(PIN_OUTPUT_STOP, LOW);
    digitalWrite(PIN_OUTPUT_SLOW, LOW);
    digitalWrite(PIN_LED_ROUGE, LOW);
    digitalWrite(PIN_LED_JAUNE, LOW);
    digitalWrite(PIN_LED_VERTE, HIGH);
  }  
  // Distance supérieur à 220 cm
  else if ((stateStop == LOW) && (distanceCm == 1000)) { 
    digitalWrite(PIN_OUTPUT_STOP, LOW);
    digitalWrite(PIN_OUTPUT_SLOW, LOW);
    digitalWrite(PIN_LED_ROUGE, LOW);
    digitalWrite(PIN_LED_JAUNE, LOW);
    digitalWrite(PIN_LED_VERTE, LOW);
  } 
  delay(200); //delai dde 200ms pour éviter les variation brusque d'etat
}


//Procedure de lecture capteur US
long readCapteurUs() {
  long duration;
  float distance; // Modification de distance en type float pour les décimales.
  digitalWrite(PIN_TRIG, LOW); 
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10); 
  digitalWrite(PIN_TRIG, LOW);
  duration = pulseIn(PIN_ECHO, HIGH);
  distance = (duration/2) / 29.1;
    if (distance >= 220 || distance <= 0){
    return distance = 1000;
  }
  else {
    return distance;
  }
}

//Procedure d'initialisation des entrées/sorties
void initInputOutput() {

  pinMode(PIN_TRIG, OUTPUT); //Initialisation sortie trig (signal)
  digitalWrite(PIN_TRIG, LOW); //Initialisation sortie trig etat LOW
  pinMode(PIN_ECHO, INPUT); //Initialisation entree echo (retour)

  pinMode(PIN_LED_ROUGE, OUTPUT); //Initialisation sortie led rouge
  pinMode(PIN_LED_JAUNE, OUTPUT); //Initialisation sortie led jaune
  pinMode(PIN_LED_VERTE, OUTPUT); //Initialisation sortie led verte

  pinMode(PIN_BP_STOP, INPUT_PULLUP); //Initialisation entre bp
  pinMode(PIN_OUTPUT_STOP, OUTPUT); //Initialisation sortie stop robot
  pinMode(PIN_OUTPUT_SLOW, OUTPUT); //Initialisation sortie 50% de vitesse
  
}

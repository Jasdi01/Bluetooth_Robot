#include <SoftwareSerial.h>

#define ENA 5 // Pin de contrôle de vitesse moteur 1
#define IN1 9 // Pin d'entrée 1 du moteur 1
#define IN2 10 // Pin d'entrée 2 du moteur 1

#define ENB 6 // Pin de contrôle de vitesse moteur 2
#define IN3 4 // Pin d'entrée 1 du moteur 2
#define IN4 7 // Pin d'entrée 2 du moteur 2

#define BluetoothTx 1
#define BluetoothRx 0

SoftwareSerial bluetooth(BluetoothTx, BluetoothRx);

#define POMPE_PIN 13 // Pin de contrôle de la pompe d'arrosage

//Définir la vitesse 
int vitesse = 0;

void setup() {
  // Configuration de la communication série Bluetooth
  bluetooth.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(POMPE_PIN, OUTPUT);
  
  // Vitesse initiale du moteur (0-255)
  analogWrite(ENA, vitesse);
  analogWrite(ENB, vitesse);
}

void loop() {
  if (bluetooth.available() > 0) {
    char command = bluetooth.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {
  switch (command) {
    case 'Av': // Avancer
      moveForward();
      Augmenter_Vit();
      break;
    case 'Re': // Reculer
      moveBackward();
      Diminuer_Vit();
      break;
    case 'Ga': // Tourner à gauche
      turnLeft();
      Augmenter_Vit();
      break;
    case 'Dr': // Tourner à droite
      turnRight();
      Augmenter_Vit();
      break;
    case 'St': // Arrêter
      stopMoving();
      break;
    case 'Po': // Activer la pompe
      activatePump();
      break;
    default:
      break;
  }

  //Mise en mode automatique
  if (command == 'At') {
    moveForward(); // Avancer
    Augmenter_Vit(); 
    activatePump(); //Activer la pompe 
    delay(5000); //Attendre 

    turnLeft(); //Tourner à gauche
    Augmenter_Vit();
    activatePump(); //Activer la pompe 
    delay(5000); //Attendre 5s

    moveBackward(); //Reculer
    Augmenter_Vit(); 
    activatePump(); //Activer la pompe 
    delay(5000); //Attendre 5s

    turnLeft(); //Tourner à gauche
    Augmenter_Vit();
    activatePump(); //Activer la pompe 
    delay(5000); //Attendre 5s

    stopMoving();
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMoving() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void activatePump() {
  digitalWrite(POMPE_PIN, HIGH); // Allume la pompe
  delay(5000); // Active la pompe pendant 5 secondes (modifiable selon vos besoins)
  digitalWrite(POMPE_PIN, LOW); // Éteint la pompe
}

void Augmenter_Vit() {
  vitesse += 10;
  if (vitesse > 255) {
    vitesse = 255;
  }
  analogWrite(ENA, vitesse);
  analogWrite(ENB, vitesse);
}

void Diminuer_Vit() {
  vitesse -= 10;
  if (vitesse < 0) {
    vitesse = 0;
  }
  analogWrite(ENA, vitesse);
  analogWrite(ENB, vitesse);
}

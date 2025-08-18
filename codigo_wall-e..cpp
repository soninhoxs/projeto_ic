#include <Ultrasonic.h>
#include <DMPH.h>
#include <Servo.h>

#define DISTANCIA_SEGURA 20

Servo servo;
int resultado = 0;
int distanciadireita = 0;
int distanciaesquerda = 0;
Ultrasonic sensor(11, 12);
long distancia;
DMPH motor1(9, 8, 7);
DMPH motor2(10, 13 , 7);

void setup(){  
  Serial.begin(9600);
  servo.attach(7, 500, 2500);
  centralizar_servo();
}

void centralizar_servo() {
  servo.write(105);
  delay(300);
}

// Checa distâncias nos lados e retorna 1 (direita) ou 2 (esquerda)
int checar() {
  servo.write(15);
  delay(1000);
  distanciadireita = sensor.Ranging(CM);
  Serial.print("Direita: ");
  Serial.println(distanciadireita);

  servo.write(165);
  delay(1000);
  distanciaesquerda = sensor.Ranging(CM);
  Serial.print("Esquerda: ");
  Serial.println(distanciaesquerda);

  centralizar_servo();

  if (distanciadireita > distanciaesquerda)
    return 1;
  else if (distanciaesquerda > distanciadireita)
    return 2;
  else
    return random(1, 3);
}

void virar_direita() {
  motor1.move(1);
  motor2.move(-1);
  delay(320);
}

void virar_esquerda() {
  motor1.move(-1);
  motor2.move(1);
  delay(280);
}

void parar() {
  motor1.move(0);
  motor2.move(0);
  delay(1000);
}

void andar() {
  motor1.move(1);
  motor2.move(1);
}

void loop() {
  distancia = sensor.Ranging(CM);
  Serial.print("Distância = ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia >= DISTANCIA_SEGURA) {
    andar();
  } else {
    parar();
    resultado = checar();
    if (resultado == 1) {
      virar_direita();
    } else if (resultado == 2) {
      virar_esquerda();
    }
  }
}
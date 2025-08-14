#include <Ultrasonic.h>
  #include <DMPH.h>
  #include <Servo.h>

  int resultado = 0;
  Servo servo;
  int distanciadireita = 0;
  int distanciaesquerda = 0;
  Ultrasonic sensor(11, 12);
  long distancia;

 DMPH motor1(9, 8, 7);
 DMPH motor2(5, 4, 7);

 void setup(){  
  Serial.begin (9600);
  servo.attach(7, 500, 2500);
  servo.write(90);
 }

 int checar (){
 
  servo.write(0);
  //distancia = ??
  delay(2000);
  distanciadireita = sensor.read(CM);
  Serial.println(distanciadireita);

  servo.write(180);
  //distancia =
  delay(2000);
  distanciaesquerda = sensor.read(CM);
  Serial.println(distanciaesquerda);

  servo.write(90);
  if(distanciadireita > distanciaesquerda) {
  int resultado = 1;
  return resultado;
  }
  else {
  int resultado = 2;
  return resultado;
  }

 
}

int virar_direita(){
  motor1.move(1);
  motor2.move(-1);
  delay(250);
}

int virar_esquerda(){
  motor1.move(-1);
  motor2.move(1);
  Serial.println(distanciaesquerda);
  delay(250);
}

int parar(){
  motor1.move(0);
  motor2.move(0);
  delay(1000);
}

int andar(){
  motor1.move(1);
  motor2.move(1);
}


  void loop() {

  distancia = sensor.read(CM);
 Serial.print("Distância = ");
 Serial.print(distancia);
 Serial.println(" cm");


  if (distancia>=20) {
     andar();
  }
  else {
    parar();
    resultado = checar();
    if (resultado == 1){
      virar_direita();
      Serial.println(resultado);
      delay(100);

    }
    else if (resultado == 2){
      virar_esquerda();
      Serial.println(resultado);
      delay(100);

    }

  }
  }
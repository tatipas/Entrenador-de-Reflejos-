#include <Servo.h>

Servo myservo;
int r3 = 4;
int g3 = 3;
int b3 = 2;
int r1 = 7;
int g1 = 6;
int b1 = 5;
int r4 = 10;
int g4 = 9;
int b4 = 11;
int r2 = 13;
int g2 = 12;
int b2 = 11;
int analog = A0;
int mult = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(r1, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(g3, OUTPUT);
  pinMode(r4, OUTPUT);
  pinMode(g4, OUTPUT);
  pinMode(b4, OUTPUT);

  myservo.attach(8);

  Serial.begin(9600);
  myservo.write(180);

}

void loop() {
  apagarTodas();

  int del = menu();
  Serial.println(del);


  int puntos = 0;
  int cont = 10;
  while (cont != 0) {
    int foco = random(1, 9);

    if (foco < 5) {
      puntos += secuencia(foco, del);
      cont--;
    } else {
      if (foco == 8) {
        int trampa = random(1, 5);
        puntos -= focoTrampa(trampa, del);
      }
    }
    sumarPuntos( puntos );
    delay(500);
  }
  apagarTodas();
  delay(2000);
  prenderTodas();
  Serial.println(puntos);
  while (analogRead(analog) == 0) {
Serial.println("alo");
  }   
    apagarTodas();
  delay(2000);

}



int secuencia(int foco, int vDelay) {
  int r = 0;
  int g = 0;
  int b = 0;
  designarColores(foco, r, g, b);

  int starttime = millis();
  int endtime = starttime;
  int retorno = 0;
  int valorA0 = 0;
  digitalWrite(g, HIGH); //verde
  while ((endtime - starttime) <= vDelay && retorno == 0) // do this loop for up to 1000mS
  {
    valorA0 = analogRead(analog) / 10;
    if (botonCorrecto(foco, valorA0)) {
      retorno = 3;
    } else {
      if (valorA0 != 0 ) {
        apagarTodas();
        return 0;
      }
    }
    endtime = millis();
  }

  starttime = millis();
  endtime = starttime;
  digitalWrite(r, HIGH); //amarillo

  while ((endtime - starttime) <= vDelay && retorno == 0) // do this loop for up to 1000mS
  {
    valorA0 = analogRead(analog) / 10;
    if (botonCorrecto(foco, valorA0)) {
      retorno = 2;
    } else {
      if (valorA0 != 0 ) {
        apagarTodas();
        return 0;
      }
    }
    endtime = millis();
  }
  starttime = millis();
  endtime = starttime;
  digitalWrite(g, LOW); //rojo

  while ((endtime - starttime) <= vDelay && retorno == 0) // do this loop for up to 1000mS
  {
    valorA0 = analogRead(analog) / 10;
    if (botonCorrecto(foco, valorA0)) {
      retorno = 1;
    } else {
      if (valorA0 != 0 ) {
        apagarTodas();
        return 0;
      }
    }
    endtime = millis();
  }
  digitalWrite(r, LOW); //rojo
  delay(vDelay);
  return retorno;

}

int focoTrampa(int foco, int vDelay) {
  int b = 0;
  int r = 0;
  int g = 0;
  designarColores(foco, r, g, b);
  int starttime = millis();
  int endtime = starttime;
  int retorno = 0;
  bool led = false;
  while ((endtime - starttime) <= vDelay * 3 && retorno == 0) // do this loop for up to 1000mS
  {
    if (led) {
      delay(100);
      digitalWrite(b, HIGH);
    } else {
            delay(100);
      digitalWrite(b, LOW);
    }
    int valorA0 = analogRead(analog) / 10;
    if (valorA0 != 0) {
      digitalWrite(b, LOW);
      return 1;
    }
    led = !led;
    endtime = millis();
  }
  digitalWrite(b, LOW);
  return retorno;
}

float menu() {
  myservo.write(180);
  digitalWrite(g1, HIGH);
  digitalWrite(b2, HIGH);
  digitalWrite(g3, HIGH);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, HIGH);
  int op = 0;
  while (op == 0) {
    int valorA0 = analogRead(analog) / 10;
    Serial.println(op);

    if (botonCorrecto(1, valorA0)) {
      op = 1000 ;
    }
    if (botonCorrecto(2, valorA0)) {
      op = 750 ;
    }
    if (botonCorrecto(3, valorA0)) {
      op = 500 ;
    }
    if (botonCorrecto(4, valorA0)) {
      Serial.println("4");
      op = 250 ;
    }

  }
  digitalWrite(g1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(g3, LOW);
  digitalWrite(r3, LOW);
  digitalWrite(r4, LOW);
  return op;
}

void designarColores(int foco, int& r, int& g, int& b) {
  switch (foco) {
    case 1:
      r = r1;
      g = g1;
      b = b1;
      break;
    case 2:
      r = r2;
      g = g2;
      b = b2;
      break;
    case 3:
      r = r3;
      g = g3;
      break;
    case 4:
      r = r4;
      g = g4;
      b = b4;
      break;
  }
}

bool botonCorrecto(int foco, int valor) {

  switch (foco) {
    case 1:
      return (valor > 8 && valor < 14);
      break;
    case 2:
      return (valor > 14 && valor < 18);
      break;
    case 4:
      return (valor > 17 && valor < 30);
      break;
    case 3:
      return (valor > 80);
      break;
  }
}

void apagarTodas() {
  int r;
  int g;
  int b;
  designarColores(1, r, g , b);
  digitalWrite(r, LOW);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
  designarColores(2, r, g , b);
  digitalWrite(r, LOW);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
  designarColores(3, r, g , b);
  digitalWrite(r, LOW);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
  designarColores(4, r, g , b);
  digitalWrite(r, LOW);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
}
void sumarPuntos(int punt) {
  int intervalo = 6;
  myservo.write(180 - (intervalo * punt));
}

void prenderTodas() {
  int r;
  int g;
  int b;
  designarColores(1, r, g , b);
  digitalWrite(r, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  designarColores(2, r, g , b);
  digitalWrite(r, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  designarColores(3, r, g , b);
  digitalWrite(r, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  designarColores(4, r, g , b);
  digitalWrite(r, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
}

#ifndef DiscoH
#define DiscoH
#include "ObjetoCuadrico.h"

class Disco: public ObjetoCuadrico  // Clase hija que hereda de ObjetoCuadrico
 {
 private:
  // Atributos
  float inner;
  float outer;
  int paralelos;
  int meridianos;

 public:
  // Constructoras y destructora
  Disco(float inner,float outer,int paralelos,int meridianos);
  // Métodos públicos
  void dibuja();
 };

#endif

#ifndef CilindroH
#define CilindroH
#include "ObjetoCuadrico.h"

class Cilindro: public ObjetoCuadrico  // Clase hija que hereda de ObjetoCuadrico
 {
 private:
  // Atributos
  float rbase;
  float rtop;
  float h;
  int paralelos;
  int meridianos;

 public:
  // Constructoras y destructora
  Cilindro(float rbase,float rtop,float h,int paralelos,int meridianos);
  // Métodos públicos
  void dibuja();
 };

#endif
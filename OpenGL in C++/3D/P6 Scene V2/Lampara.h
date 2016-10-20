#ifndef LamparaH
#define LamparaH
#include "ObjetoCuadrico.h"

class Lampara: public ObjetoCuadrico
 {
 private:
  // Atributos
  float rbase;
  float rtop;
  float h;
  int paralelos;
  int meridianos;
  GLfloat PosicionLuz1[4];  // Posición de la lámpara
  GLfloat dir1[3];  // Dirección el la que sale la luz de la lámpara
  bool encendida;  // Indica si la lámpara está encendida
  GLfloat angulo;  // Indica el ángulo de la luz que sale de la lámpara

 public:
  // Constructoras y destructora
  Lampara(float rbase,float rtop,float h,int paralelos,int meridianos);
  // Métodos públicos
  void dibuja();  // Dibuja la lámpara
  void setLamp();  // Enciende o apaga la lámpara
  void setAngulo(float f);  // Cambia el ángulo de la luz que sale de la lámpara
 };

#endif

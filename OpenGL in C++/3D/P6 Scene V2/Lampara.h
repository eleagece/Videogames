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
  GLfloat PosicionLuz1[4];  // Posici�n de la l�mpara
  GLfloat dir1[3];  // Direcci�n el la que sale la luz de la l�mpara
  bool encendida;  // Indica si la l�mpara est� encendida
  GLfloat angulo;  // Indica el �ngulo de la luz que sale de la l�mpara

 public:
  // Constructoras y destructora
  Lampara(float rbase,float rtop,float h,int paralelos,int meridianos);
  // M�todos p�blicos
  void dibuja();  // Dibuja la l�mpara
  void setLamp();  // Enciende o apaga la l�mpara
  void setAngulo(float f);  // Cambia el �ngulo de la luz que sale de la l�mpara
 };

#endif

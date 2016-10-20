#ifndef LapizH
#define LapizH
#include "PuntoVector.h"

class Lapiz
 {
 private:
  PuntoVector* pos;  // posición del lápiz (x,y)
  float dir;  // dirección del avance (en radianes)

 public:
  // Constructor, destructor
  Lapiz(PuntoVector*,float);
  ~Lapiz();
  // Getters y setters
  PuntoVector* DamePos();
  void PonPos(PuntoVector*);
  float DameDir();
  void PonDir(float);
  // Métodos
  void Girar(float ang);
  PuntoVector* Mover(float,bool);
 };

#endif

#ifndef LapizH
#define LapizH
#include "PuntoVector.h"

class Lapiz
 {
 private:
  PuntoVector* pos;  // posici�n del l�piz (x,y)
  float dir;  // direcci�n del avance (en radianes)

 public:
  // Constructor, destructor
  Lapiz(PuntoVector*,float);
  ~Lapiz();
  // Getters y setters
  PuntoVector* DamePos();
  void PonPos(PuntoVector*);
  float DameDir();
  void PonDir(float);
  // M�todos
  void Girar(float ang);
  PuntoVector* Mover(float,bool);
 };

#endif

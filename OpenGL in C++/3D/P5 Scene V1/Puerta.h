#ifndef PuertaH
#define PuertaH
#include "ObjetoCompuesto3D.h"
#include "Tablero.h"
#include "Esfera.h"

class Puerta: public ObjetoCompuesto3D
 {
 private:
  bool abierta;
 public:
  Puerta();
  // M�todos p�blicos
  void setPuerta();
 };

#endif
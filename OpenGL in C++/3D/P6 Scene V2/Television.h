#ifndef TelevisionH
#define TelevisionH
#include "ObjetoCompuesto3D.h"
#include "Tablero.h"

class Television: public ObjetoCompuesto3D
 {
 private:
  bool apagada;
  Tablero* tft;

 public:
  // Constructoras y destructora
  Television();
  // Métodos públicos
  void setTV();
 };

#endif
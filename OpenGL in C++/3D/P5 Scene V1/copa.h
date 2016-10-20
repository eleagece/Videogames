#ifndef CopaH
#define CopaH
#include "Malla.h"
#include <math.h>

const double RBASE=0.25;  // radio de la base
const double RPIE=0.05;  // radio de la base inferior del cilindro
const double RCAZO=0.02;  // radio de la base superior del cilindro
const double ABASE=0.1;  // altura de la base
const double APIE=0.4;  // altura del cilindro
const double ACAZO=0.4;  // altura del cazo

class Copa: public Malla
 {
 public:
  // Constructoras y destructora
  Copa(int np, int nq, float h);  // np=número de lados del círculo, nq=número de círculos del cazo
 };

#endif
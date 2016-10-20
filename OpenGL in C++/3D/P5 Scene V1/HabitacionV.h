#ifndef HabitacionVH
#define HabitacionVH
#include "ObjetoCompuesto3D.h"
#include "Tablero.h"
#include "Television.h"
#include "Sofa.h"

class HabitacionV: public ObjetoCompuesto3D
 {
 private:
  Television* tv;

 public:
  // Constructoras y destructora
  HabitacionV();
  // Métodos públicos
  void setTV();
 };

#endif
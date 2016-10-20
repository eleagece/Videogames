#ifndef HabitacionLH
#define HabitacionLH
#include "Television.h"
#include "Muebles.h"
#include "Estanteria.h"
#include "Puerta.h"
#include "Lampara.h"

class HabitacionL: public ObjetoCompuesto3D
 {
 private:
  Muebles* muebles;  // Necesario declararlos para poder hacer transformaciones sobre ellos
  Puerta* puerta;  // Necesario declararla para poder hacer transformaciones sobre ella
  //Cilindro* lampara;  // Necesario declararla para poder hacer transformaciones sobre ella
  Lampara* lampara;  // Necesario declararla para poder hacer transformaciones sobre ella

 public:
  // Constructoras y destructora
  HabitacionL();
  // Métodos públicos para hacer transformaciones sobre la puerta
  void setPuerta();
  // Métodos públicos para hacer transformaciones sobre los muebles
  void escalaMueble(float x,float y,float z);
  void trasladaMueble(float x,float y,float z);
  void rotaMueble(float a,float x,float y,float z);
  // Métodos públicos para hacer transformaciones sobre la lampara
  void setLamp();
  void escalaLamp(float x,float y,float z);
  void trasladaLamp(float x,float y,float z);
  void rotaLamp(float a,float x,float y,float z);
 };

#endif

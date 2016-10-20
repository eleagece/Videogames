#ifndef SegmentoH
#define SegmentoH
#include <gl\gl.h>
#include <gl\glu.h>
#include "PuntoVector.h"

class Segmento
 {
 private:
  // Atributos
  PuntoVector* puntoOrigen;
  PuntoVector* puntoDestino;
  // Métodos                                                    
  unsigned char getCode(PuntoVector*,PuntoVector*,PuntoVector*);
  void corteF0(PuntoVector*,PuntoVector*,PuntoVector*,PuntoVector*);
  void corteF1(PuntoVector*,PuntoVector*,PuntoVector*,PuntoVector*);
  void corteF2(PuntoVector*,PuntoVector*,PuntoVector*,PuntoVector*);
  void corteF3(PuntoVector*,PuntoVector*,PuntoVector*,PuntoVector*);
  
 public:
  // Constructores
  Segmento();
  Segmento(float,float,float,float);  // Constructor parametrizado (float,float,float,float)
  Segmento(PuntoVector*,PuntoVector*);  // Constructor parametrizado (PuntoVector*,PuntoVector*)
  ~Segmento();
  // Getters y setters
  PuntoVector* DamePuntoOrigen();
  PuntoVector* DamePuntoDestino();
  // Métodos
  void Dibuja();
  bool CS(PuntoVector*,PuntoVector*);
  void salvaSegmento(ofstream& f);
  void cargaSegmento(ifstream&);
 };

#endif

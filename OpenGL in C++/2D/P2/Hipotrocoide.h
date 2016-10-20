#ifndef HipotrocoideH
#define HipotrocoideH
#include "Segmento.h"
#include "Lista.h"
#include <math>
#include <gl\gl.h>
#include <gl\glu.h>

class Hipotrocoide
 {
 private:
  // Atributos
  float oX,oY,a,b,c,n;
  Lista<Segmento>* listaSegmentos;
  // Métodos privados
  int MCD(int,int);

 public:
  // Constructores, destructor
  Hipotrocoide();
  Hipotrocoide(float,float,float,float,float,float);
  ~Hipotrocoide();
  // Setters
  void PonValores(float,float,float,float,float,float);
  // Métodos
  void AgregaSegsHipotrocoide(float,float,float,float,float,float);

  void Dibuja();
  void DibujaSelec();
  void Recorta(PuntoVector*,PuntoVector*);
  bool SelecHipotrocoide(float,float);
  void Precisa(bool);
  void Gira();
  void salvaHipotrocoide(ofstream& f);
  void cargaHipotrocoide(ifstream&);
 };

#endif

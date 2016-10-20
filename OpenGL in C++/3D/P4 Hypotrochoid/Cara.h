#ifndef CaraH
#define CaraH
#include "VNormal.h"
#include <vector>
#include "PV3d.h"
using namespace std;

const int NELEMS=4;  // lados de la cara

class Cara
 {
 private:
  // Atributos
  VNormal* c[NELEMS];  // Array de punteros a pares de �ndices (v�rtice,normal)
  int nelems;  // N�mero de elementos del array

 public:
  // Constructores y destructor
  Cara() {nelems=0;}
  ~Cara();
  // Getters y setters
  int getSize() {return nelems;}
  int getAbsSize() {return NELEMS;}
  VNormal* getPos(int p) {return c[p];}  // Devuelve el puntero al par de la posici�n p
  // M�todos p�blicos
  void addPos(int v, int n);  // A�ade un puntero a un par al final del array de punteros de pares
  void addV(int v);  // A�ade un �ndice de v�rtice a la cara
  void setN(int n);  // Actualiza el �ndice de la normal de todos los v�rtices
  void dibuja(vector<PV3d*>* tv,vector<PV3d*>* tn, bool b);  // Dibuja los v�rtices de la cara
 };

#endif
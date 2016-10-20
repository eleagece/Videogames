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
  VNormal* c[NELEMS];  // Array de punteros a pares de índices (vértice,normal)
  int nelems;  // Número de elementos del array

 public:
  // Constructores y destructor
  Cara() {nelems=0;}
  ~Cara();
  // Getters y setters
  int getSize() {return nelems;}
  int getAbsSize() {return NELEMS;}
  VNormal* getPos(int p) {return c[p];}  // Devuelve el puntero al par de la posición p
  // Métodos públicos
  void addPos(int v, int n);  // Añade un puntero a un par al final del array de punteros de pares
  void addV(int v);  // Añade un índice de vértice a la cara
  void setN(int n);  // Actualiza el índice de la normal de todos los vértices
  void dibuja(vector<PV3d*>* tv,vector<PV3d*>* tn, bool b);  // Dibuja los vértices de la cara
 };

#endif
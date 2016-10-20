#pragma hdrstop
#include "Cara.h"
#pragma package(smart_init)

// Constructores y destructor
Cara::~Cara()
 {
 // Recorre el array de punteros de índices (vértice,normal) eliminándolos
 for (int i=0; i<nelems; i++)
  {
  delete c[i];
  }
 }

// Métodos públicos
void Cara::addPos(int v, int n)
 {
 // Añade un puntero a un par al final del array de punteros de pares
 c[nelems]=new VNormal(v,n);
 nelems++;
 }

void Cara::addV(int v)
 {
 // Añade un índice de vértice a la cara
 c[nelems]=new VNormal(v,0);
 nelems++;
 }

void Cara::setN(int n)
 {
 // Actualiza el índice de la normal de todos los vértices
 for (int i=0; i<nelems; i++)
  {
  c[i]->setN(n);
  }
 }

void Cara::dibuja(vector<PV3d*>* tv, vector<PV3d*>* tn, bool b)
 {
 // Recorre el array de punteros de índice (vértice,normal) obteniendo el
 // índice del vértice y el índice de la normal correspondiente. La normal es
 // la misma para todos los vértices así que nos podemos quedar con cualquiera.
 // Se pintan las líneas uniendo los vértices para tener la cara.
 if (b)
  glBegin(GL_LINE_STRIP);
 else
  glBegin(GL_POLYGON);
  int n=c[0]->getN();  // ELIMINABLE B
  glNormal3d(tn->at(n)->getX(),tn->at(n)->getY(),tn->at(n)->getZ());  // ELIMINABLE B
  for (int i=0; i<nelems; i++)
   {
   // Obtener indice v, indice n
   int v=c[i]->getV();
   //int n=c[i]->getN();  // ELIMINABLE
   // dibujar
   //glNormal3d(tn->at(n)->getX(),tn->at(n)->getY(),tn->at(n)->getZ());  // ELIMINABLE
   glVertex3d(tv->at(v)->getX(),tv->at(v)->getY(),tv->at(v)->getZ());
   }
  int v=c[0]->getV();
  //int n=c[0]->getN();  // ELIMINABLE
  //glNormal3d(tn->at(n)->getX(),tn->at(n)->getY(),tn->at(n)->getZ());  // ELIMINABLE
  glVertex3d(tv->at(v)->getX(),tv->at(v)->getY(),tv->at(v)->getZ());
  // tv->at(v)->getX()  // como el vector es un puntero accedemos a sus datos con -> (1er ->)
  // tv->at(v)->getX()  // como los elementos del vector son punteros accedemos a sus datos también con -> (2º ->)
 glEnd();
 }


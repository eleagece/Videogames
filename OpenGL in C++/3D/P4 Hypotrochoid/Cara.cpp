#pragma hdrstop
#include "Cara.h"
#pragma package(smart_init)

// Constructores y destructor
Cara::~Cara()
 {
 // Recorre el array de punteros de �ndices (v�rtice,normal) elimin�ndolos
 for (int i=0; i<nelems; i++)
  {
  delete c[i];
  }
 }

// M�todos p�blicos
void Cara::addPos(int v, int n)
 {
 // A�ade un puntero a un par al final del array de punteros de pares
 c[nelems]=new VNormal(v,n);
 nelems++;
 }

void Cara::addV(int v)
 {
 // A�ade un �ndice de v�rtice a la cara
 c[nelems]=new VNormal(v,0);
 nelems++;
 }

void Cara::setN(int n)
 {
 // Actualiza el �ndice de la normal de todos los v�rtices
 for (int i=0; i<nelems; i++)
  {
  c[i]->setN(n);
  }
 }

void Cara::dibuja(vector<PV3d*>* tv, vector<PV3d*>* tn, bool b)
 {
 // Recorre el array de punteros de �ndice (v�rtice,normal) obteniendo el
 // �ndice del v�rtice y el �ndice de la normal correspondiente. La normal es
 // la misma para todos los v�rtices as� que nos podemos quedar con cualquiera.
 // Se pintan las l�neas uniendo los v�rtices para tener la cara.
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
  // tv->at(v)->getX()  // como los elementos del vector son punteros accedemos a sus datos tambi�n con -> (2� ->)
 glEnd();
 }


#pragma hdrstop
#include "Cilindro.h"
#pragma package(smart_init)

//****************************************************************************//
//*** Constructoras y destructora ********************************************//
//****************************************************************************//
Cilindro::Cilindro(float rbase, float rtop, float h, int paralelos, int meridianos)//:ObjetoCuadrico()
 {
 //---- Constructora parametrizada -------------------------------------------//
 //-- Se pasan como parámetros el radio de la base inferior (rbase) y su-   --//
 //-- perior (rtop), el número de divisiones verticales y horizontales      --//
 //-- (paralelos y meridianos) y la altura del cilindro (h)                 --//
 //---------------------------------------------------------------------------//
 this->rbase=rbase;
 this->rtop=rtop;
 this->h=h;
 this->paralelos=paralelos;
 this->meridianos=meridianos;
 }

//****************************************************************************//
//*** Métodos públicos *******************************************************//
//****************************************************************************//
void Cilindro::dibuja()
 {
 //---- dibuja() -------------------------------------------------------------//
 //-- Dibuja el cilindro (como objeto cuádrico)                             --//
 //---------------------------------------------------------------------------//
 glPushMatrix();  // Mete una matriz nueva
  m->ejecutaTAfin();  // Ejecuta transformación afín a los puntos
  glColor4f(color->getR(),color->getG(),color->getB(),1.0);  // Color del objeto
  gluCylinder(objeto,rbase,rtop,h,paralelos,meridianos);  // Se dibuja el objeto
 glPopMatrix();  // Saca la matriz después de operar sobre ella
 }

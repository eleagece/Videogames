#pragma hdrstop
#include "Disco.h"
#pragma package(smart_init)

//****************************************************************************//
//*** Constructoras y destructora ********************************************//
//****************************************************************************//
Disco::Disco(float inner, float outer, int paralelos, int meridianos)//:ObjetoCuadrico()
 {
 //---- Constructora parametrizada -------------------------------------------//
 //-- Se pasan como par�metros el radio interior y exterior del disco       --//
 //-- (inner y outer) y el n�mero de divisiones conc�ntricas (paralelos) y  --//
 //-- y desde el centro (meridianos)                                        --//
 //---------------------------------------------------------------------------//
 this->inner=inner;
 this->outer=outer;
 this->paralelos=paralelos;
 this->meridianos=meridianos;
 }
 
//****************************************************************************//
//*** M�todos p�blicos *******************************************************//
//****************************************************************************//
void Disco::dibuja()
 {
 //---- dibuja() -------------------------------------------------------------//
 //-- Dibuja el disco (como objeto cu�drico)                                --//
 //---------------------------------------------------------------------------//
 glPushMatrix();  // Mete una matriz nueva
  m->ejecutaTAfin();  // Ejecuta transformaci�n af�n a los puntos
  glColor4f(color->getR(),color->getG(),color->getB(),1.0);  // Color del objeto
  gluDisk(objeto,inner,outer,paralelos,meridianos);  // Se dibuja el objeto
 glPopMatrix();  // Saca la matriz despu�s de operar sobre ella
 }

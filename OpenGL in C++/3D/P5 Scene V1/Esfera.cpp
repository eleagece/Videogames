#pragma hdrstop
#include "Esfera.h"
#pragma package(smart_init)

//****************************************************************************//
//*** Constructoras y destructora ********************************************//
//****************************************************************************//
Esfera::Esfera(float radio, int paralelos, int meridianos)//:ObjetoCuadrico()
 {
 //---- Constructora parametrizada -------------------------------------------//
 //-- Se pasan como par�metros el radio de la esfera y el n�mero de divi-   --//
 //-- siones verticales y horizontales (paralelos y meridianos)             --//
 //---------------------------------------------------------------------------//
 this->radio=radio;
 this->paralelos=paralelos;
 this->meridianos=meridianos;
 }

//****************************************************************************//
//*** M�todos p�blicos *******************************************************//
//****************************************************************************//
void Esfera::dibuja()
 {
 //---- dibuja() -------------------------------------------------------------//
 //-- Dibuja la esfera (como objeto cu�drico)                               --//
 //---------------------------------------------------------------------------//
 glPushMatrix();  // Mete una matriz nueva
  m->ejecutaTAfin();  // Ejecuta transformaci�n af�n a los puntos
  glColor4f(color->getR(),color->getG(),color->getB(),1.0);  // Color del objeto
  gluSphere(objeto,radio,paralelos,meridianos);  // Se dibuja el objeto
 glPopMatrix();  // Saca la matriz despu�s de operar sobre ella
 }

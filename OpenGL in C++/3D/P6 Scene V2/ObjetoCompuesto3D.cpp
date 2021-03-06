#pragma hdrstop
#include "ObjetoCompuesto3D.h"
#pragma package(smart_init)

//****************************************************************************//
//*** Constructoras y destructora ********************************************//
//****************************************************************************//
ObjetoCompuesto3D::ObjetoCompuesto3D()//:Objeto3D()
 {
 //---- Constructora por defecto ---------------------------------------------//
 //-- Llama a la constructora por defecto de Objeto3D() y luego crea el     --//
 //-- vector de objetos                                                     --//
 //---------------------------------------------------------------------------//
 objetos=new vector<Objeto3D*>();
 }

ObjetoCompuesto3D::~ObjetoCompuesto3D()
 {
 //---- Destructora ----------------------------------------------------------//
 //-- Llama a la destructora de Objeto3D() y luego elimina el vector de ob- --//
 //-- jetos junto con sus objetos                                           --//
 //---------------------------------------------------------------------------//
 for (unsigned int i=0; i<objetos->size(); i++)
  {
  delete objetos->at(i);
  }
 delete objetos;
 }

//****************************************************************************//
//*** M�todos p�blicos *******************************************************//
//****************************************************************************//
void ObjetoCompuesto3D::dibuja()
 {
 //---- dibuja() -------------------------------------------------------------//
 //-- Recorre el vector de Objeto3D dibuj�ndolos                            --//
 //---------------------------------------------------------------------------//
 glPushMatrix();  // Mete una matriz nueva
  m->ejecutaTAfin();  // Ejecuta transformaci�n af�n a los puntos
  glColor4f(color->getR(),color->getG(),color->getB(),1.0);  // Color predeterminado para el conjunto de Objeto3D
  for (unsigned int i=0; i<objetos->size(); i++)
   {
   objetos->at(i)->dibuja();
   }
 glPopMatrix();  // Saca la matriz despu�s de operar sobre ella
 }


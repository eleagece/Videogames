#pragma hdrstop
#include "ObjetoCuadrico.h"
#pragma package(smart_init)

//****************************************************************************//
//*** Constructoras y destructora ********************************************//
//****************************************************************************//
ObjetoCuadrico::ObjetoCuadrico()//:Objeto3D()
 {
 //---- Constructora por defecto ---------------------------------------------//
 //-- Llama a la constructora por defecto de Objeto3D() y luego crea el     --//
 //-- objeto cu�drico y le pone el estilo de dibujado                       --//
 //---------------------------------------------------------------------------//
 objeto=gluNewQuadric();
 gluQuadricDrawStyle(objeto,/*GLU_LINE*/GLU_FILL);
 }

ObjetoCuadrico::~ObjetoCuadrico()
 {
 //---- Destructora ----------------------------------------------------------//
 //-- Llama a la destructora de Objeto3D() y luego elimina el objeto cu�-   --//
 //-- drico                                                                 --//
 //---------------------------------------------------------------------------//
 gluDeleteQuadric(objeto);
 }


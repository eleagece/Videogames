#pragma hdrstop
#include "Objeto3D.h"
#pragma package(smart_init)

//****************************************************************************//
//*** Constructoras y destructora ********************************************//
//****************************************************************************//
Objeto3D::Objeto3D()
 {
 //---- Constructora por defecto ---------------------------------------------//
 //---------------------------------------------------------------------------//
 color=new Color(0,0,0);  // Color negro
 m=new TAfin();  // TAfin por defecto
 }

Objeto3D::~Objeto3D()
 {
 //---- Destructora ----------------------------------------------------------//
 //-- Es un m�todo virtual, aqu� s�lo se ejecuta la parte com�n de todos    --//
 //-- hijos, es decir, eliminar el color y la transformaci�n af�n           --//
 //---------------------------------------------------------------------------//
 delete color;
 delete m;
 }

//****************************************************************************//
//*** M�todos p�blicos *******************************************************//
//****************************************************************************//
TAfin* Objeto3D::getTAfin()
 {
 //---- getTAfin() -----------------------------------------------------------//
 //-- Devuelve la transformaci�n af�n del objeto para operar sobre ella     --//
 //---------------------------------------------------------------------------//
 return m;
 }

Color* Objeto3D::getColor()
 {
 //---- getColor() -----------------------------------------------------------//
 //-- Devuelve el color del objeto                                          --//
 //---------------------------------------------------------------------------//
 return color;
 }

void Objeto3D::setColor(float r, float g, float b)
 {
 //---- setColor() -----------------------------------------------------------//
 //-- Pone color al objeto variando sus valores 'r', 'g' y 'b'              --//
 //---------------------------------------------------------------------------//
 color->setR(r);
 color->setG(g);
 color->setB(b);
 }


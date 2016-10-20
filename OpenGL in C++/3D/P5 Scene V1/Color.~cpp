#pragma hdrstop
#include "Color.h"
#pragma package(smart_init)

//****************************************************************************//
//*** Constructoras y destructora ********************************************//
//****************************************************************************//
Color::Color(int r, int g, int b)
 {
 //---- Constructora parametrizada -------------------------------------------//
 //-- Se pasan valores de 0..255 y se convierten a formato OpenGL 0..1      --//
 //---------------------------------------------------------------------------//
 this->r=(float) r/255.0;
 this->g=(float) g/255.0;
 this->b=(float) b/255.0;
 }

Color::Color(float r, float g, float b)
 {
 //---- Constructora parametrizada -------------------------------------------//
 //-- Se pasan valores de 0..1 directamente                                 --//
 //---------------------------------------------------------------------------//
 this->r=r;
 this->g=g;
 this->b=b;
 }

//****************************************************************************//
//*** Métodos públicos *******************************************************//
//****************************************************************************//
float Color::getR()
 {
 return r;
 }

float Color::getG()
 {
 return g;
 }

float Color::getB()
 {
 return b;
 }

void Color::setR(float c)
 {
 r=c;
 }

void Color::setG(float c)
 {
 g=c;
 }

void Color::setB(float c)
 {
 b=c;
 }

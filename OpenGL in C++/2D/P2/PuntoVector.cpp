#include <vcl.h>
#pragma hdrstop
#include "PuntoVector.h"

// Constructores y destructor
PuntoVector::PuntoVector()
 {
 }

PuntoVector::PuntoVector(float X, float Y)
 {
 x=X;
 y=Y;
 }

PuntoVector::PuntoVector(PuntoVector* pv)
 {
 x=pv->dameX();
 y=pv->dameY();
 }

// Getters y setters
float PuntoVector::dameX()
 {
 return x;
 }

void PuntoVector::ponX(float X)
 {
 x=X;
 }

float PuntoVector::dameY()
 {
 return y;
 }

void PuntoVector::ponY(float Y)
 {
 y=Y;
 }

// Métodos
void PuntoVector::rotaP(PuntoVector* centroRot, float ang)
 {
 float cx=centroRot->dameX();
 float cy=centroRot->dameY();
 float dx=(1.0-cos(ang*(M_PI/180.0)))*cx + sin(ang*(M_PI/180.0))*cy;
 float dy=-sin(ang*(M_PI/180.0))*cx + (1.0-cos(ang*(M_PI/180.0)))*cy;
 float x1=x*cos(ang*(M_PI/180.0)) - y*sin(ang*(M_PI/180.0))+dx;
 float y1=x*sin(ang*(M_PI/180.0)) + y*cos(ang*(M_PI/180.0))+dy;
 x=x1;
 y=y1;
 }

void PuntoVector::salvaPunto(ofstream& f)
 {
 f.write((char*)&x,sizeof(float));
 f.write((char*)&y,sizeof(float));
 }

void PuntoVector::cargaPunto(ifstream& f)
 {
 f.read((char*)&x,sizeof(float));
 f.read((char*)&y,sizeof(float));
 }
#pragma package(smart_init)

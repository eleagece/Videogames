#pragma hdrstop
#include "PV3d.h"
#pragma package(smart_init)

//****************************************************************************//
//*** Constructoras y destructora ********************************************//
//****************************************************************************//
PV3d::PV3d(double x,double y,double z,int ext)
 {
 //---- Constructora por defecto ---------------------------------------------//
 //---------------------------------------------------------------------------//
 _x=x;
 _y=y;
 _z=z;
 _ext=ext;
 }

PV3d::PV3d(PV3d* p)
 {
 //---- Destructora ----------------------------------------------------------//
 //---------------------------------------------------------------------------//
 _x=p->getX();
 _y=p->getY();
 _z=p->getZ();
 _ext=p->getExt();
 }

//****************************************************************************//
//*** Métodos públicos *******************************************************//
//****************************************************************************//
double PV3d::dot(PV3d* w)
 {
 //---- dot(...) -------------------------------------------------------------//
 //-- Realiza el producto escalar con del vector actual con el vector w     --//
 //---------------------------------------------------------------------------//
 return (_x*w->getX())+(_y*w->getY())+(_z*w->getZ());
 }

void PV3d::normalize()
 {
 //---- normalize() ----------------------------------------------------------//
 //-- Normaliza el vector (lo pone a módulo=1)                              --//
 //---------------------------------------------------------------------------//
 double mod=this->module();
 if (mod!=0)
  {
  _x=_x/mod;
  _y=_y/mod;
  _z=_z/mod;
  }
 else
  {
  _x=0.0;
  _y=0.0;
  _z=0.0;
  }
 }

void PV3d::prodV(PV3d* a, PV3d* b)
 {
 //---- prodV(...) -----------------------------------------------------------//
 //-- Establece las coordenadas del vector según el resultado de a x b. Es  --//
 //-- decir, guarda el producto vectorial de a x b en el propio PV3d        --//
 //---------------------------------------------------------------------------//
 _x=a->getY()*b->getZ() - a->getZ()*b->getY();
 _y=-(a->getX()*b->getZ() - a->getZ()*b->getX());
 _z=a->getX()*b->getY() - a->getY()*b->getX();
 _ext=1;
 }

PV3d* PV3d::prodVect(PV3d* w)
 {
 //---- prodVect(...) --------------------------------------------------------//
 //-- Realiza el producto vectorial del vector actual con el vector w y lo  --//
 //-- devuelve                                                              --//
 //---------------------------------------------------------------------------//
 PV3d* p;
 double xPV=_y*w->getZ() - w->getY()*_z;
 double yPV=_x*w->getZ() - w->getX()*_z;
 double zPV=_x*w->getY() - w->getX()*_y;
 p=new PV3d(xPV,yPV,zPV,0);
 return p;
 }

double PV3d::module()
 {
 //---- module() -------------------------------------------------------------//
 //-- Devuelve el módulo del vector actual                                  --//
 //---------------------------------------------------------------------------//
 double aux=pow(_x,2)+pow(_y,2)+pow(_z,2);
 return sqrt(aux);  // sqrt(_x^2+_y^2+_z^2)
 }

double PV3d::alpha(PV3d* w)
 {
 //---- alpha(...) -----------------------------------------------------------//
 //-- Devuelve el ángulo que forma el vector actual con el vector w (en º)  --//
 //---------------------------------------------------------------------------//
 double num=dot(w);
 double den=this->module()*w->module();
 if (w->getZ()>0 && w->getX()>0)  // Primer cuadrante
  return (acos(num/den)*(180.0/M_PI));
 else if (w->getZ()<0 && w->getX()>0)  // Segundo cuadrante
  return (acos(num/den)*(180.0/M_PI));
 else if (w->getZ()<0 && w->getX()<0)  // Tercer cuadrante
  return (360-(acos(num/den)*(180.0/M_PI)));
 else if (w->getZ()>0 && w->getX()<0)  // Cuarto cuadrante
  return (360-(acos(num/den)*(180.0/M_PI)));
 else
  return (acos(num/den)*(180.0/M_PI));
 }

void PV3d::dibuja(GLdouble tam,GLfloat R,GLfloat G,GLfloat B)
 {
 //---- dibuja(...) ----------------------------------------------------------//
 //-- Dibuja el punto con tamaño y color especificado                       --//
 //---------------------------------------------------------------------------//
 glPointSize(tam);
 glColor3f(R,G,B);
 glBegin(GL_POINTS);
  glVertex3f(_x,_y,_z);
 glEnd();
 glPointSize(1.0);
 glColor3f(1.0,1.0,1.0);
 }

void PV3d::dibuja()
 {
 //---- dibuja() -------------------------------------------------------------//
 //-- Dibuja el punto tal cual                                              --//
 //---------------------------------------------------------------------------//
 glBegin(GL_LINES);
  glVertex3f(_x,_y,_z);
 glEnd();
 }


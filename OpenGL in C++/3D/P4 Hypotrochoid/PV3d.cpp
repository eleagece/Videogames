#pragma hdrstop
#include "PV3d.h"
#pragma package(smart_init)

// Constructores
PV3d::PV3d(double x,double y,double z,int ext)
 {
 _x=x;
 _y=y;
 _z=z;
 _ext=ext;
 }

PV3d::PV3d(PV3d* p)
 {
 _x=p->getX();
 _y=p->getY();
 _z=p->getZ();
 _ext=p->getExt();
 }

// M�todos p�blicos
double PV3d::dot(PV3d* w)
 {
 return (_x*w->getX())+(_y*w->getY())+(_z*w->getZ());
 }

PV3d* PV3d::prodVect(PV3d* w)
 {
 PV3d* p;
 double xPV=_y*w->getZ() - w->getY()*_z;
 double yPV=_x*w->getZ() - w->getX()*_z;
 double zPV=_x*w->getY() - w->getX()*_y;
 p=new PV3d(xPV,yPV,zPV,0);
 return p;
 }

double PV3d::module()
 {
 double aux=pow(_x,2)+pow(_y,2)+pow(_z,2);
 return sqrt(aux);  // sqrt(_x^2+_y^2+_z^2)
 }

double PV3d::alpha(PV3d* w)
 {
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
 glBegin(GL_LINES);
  glVertex3f(_x,_y,_z);
 glEnd();
 }


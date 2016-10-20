#pragma hdrstop
#include "Lampara.h"
#pragma package(smart_init)

Lampara::Lampara(float rbase,float rtop,float h,int paralelos,int meridianos)//:ObjetoCuadrico()
 {
 // Cilindro que forma la lámpara
 this->rbase=rbase;
 this->rtop=rtop;
 this->h=h;
 this->paralelos=paralelos;
 this->meridianos=meridianos;
 // Luz posicional (foco de la lámpara)
 encendida=false;
 glDisable(GL_LIGHT1);  // Esta fuente de luz está apagada al principio
 GLfloat LuzDifusa1[]={1.0,1.0,1.0,1.0};  // Se establece la intensidad de la luz difusa para LIGHT1
 glLightfv(GL_LIGHT1,GL_DIFFUSE,LuzDifusa1);
 GLfloat LuzAmbiente1[]={0.0,0.0,0.0,1.0};  // Se establece la intensidad de la luz ambiente para LIGHT1
 glLightfv(GL_LIGHT1,GL_AMBIENT,LuzAmbiente1);
 GLfloat LuzEspecular1[]={0.0,0.0,0.0,1.0};  // Se establece la intensidad de la luz especular para LIGHT1
 glLightfv(GL_LIGHT1,GL_SPECULAR,LuzEspecular1);
 PosicionLuz1[0]=0.0; PosicionLuz1[1]=0.0;  // x,y,z indican la posición de la luz, w es 1 al ser una luz posicional
 PosicionLuz1[2]=0.0; PosicionLuz1[3]=1.0;
 glLightfv(GL_LIGHT1,GL_POSITION,PosicionLuz1);
 angulo=45.0;  // Se establece el ángulo de apertura de la luz (45x2=90º)
 glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,angulo);
 dir1[0]=0.0; dir1[1]=0.0;  // x,y,z establecen la dirección que toma el foco
 dir1[2]=-1.0; //dir1[3]=0.0;
 glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,dir1);
 }

void Lampara::dibuja()
 {
 glPushMatrix();  // Mete una matriz nueva
  m->ejecutaTAfin();  // Ejecuta transformación afín a los puntos
  glLightfv(GL_LIGHT1,GL_POSITION,PosicionLuz1);  // Cambia la posición de la luz
  glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,dir1);  // Cambia la dirección de la luz
  glColor4f(color->getR(),color->getG(),color->getB(),1.0);  // Color del objeto
  gluCylinder(objeto,rbase,rtop,h,paralelos,meridianos);  // Se dibuja el objeto
 glPopMatrix();  // Saca la matriz después de operar sobre ella
 }

void Lampara::setLamp()
 {
 if (encendida)
  {
  glDisable(GL_LIGHT1);
  }
 else
  {
  glEnable(GL_LIGHT1);
  }
 encendida=!encendida;
 }

void Lampara::setAngulo(float f)
 {
 angulo*=f;  // Aumenta o disminuye el ángulo según el aumento (1.1) o disminución (0.9) de f
 glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,angulo);
 }


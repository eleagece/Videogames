#include <vcl.h>
#pragma hdrstop
#include "Hipotrocoide3D.h"
#pragma package(smart_init)

// Constructores y destructor
Hipotrocoide3D::Hipotrocoide3D(int np, int nq, int a, int b, int c)
 {
 // Genera un hipotrocoide en 3D aproximado por nq rodajas por vuelta (precisión), np puntos para el polígono que
 // hace la extrusión y de parámetros a, b y c. Se toma como origen el centro de coordenadas.
 this->a=a;  // Valores del hipotrocoide
 this->b=b;
 this->c=c;
 int numVueltas=b/MCD(a,b);  // Número de vueltas totales necesarias para que una hipotrocoide se complete
 int rodajasTotal;  // Número total de rodajas de la hipotrocoide
 if (nq<10)  // Si el número de rodajas por vuelta es menor que 10 la precisión sería muy mala...
  {
  rodajasTotal=numVueltas*10+1;  // ...así que utilizamos un mínimo de 10 rodajas por vuelta para calcular las totales
  nqInt=10;  // Para el cálculo de la posición del coche
  }
 else  // Si el número de rodajas por vuelta es mayor o igual que 10 la precisión es aceptable...
  {
  rodajasTotal=numVueltas*nq+1;  // ...así que utilizamos nq para calcular las rodajas totales
  nqInt=nq;  // Para el cálculo de la posición del coche
  }
 base=new vector<PV3d*>();  // Creación de polígono de base para la extrusión...
 this->genCirculo(np,0.8);  // ...y generación de sus puntos
 double t=0;
 for (int i=0; i<rodajasTotal; i++)  // Recorremos el total de las rodajas
  {
  t=i*2*M_PI/nq;
  for (int j=0; j<np; j++)  // Recorremos los puntos del polígono inicial haciendo Frenet a cada uno de ellos
   {
   PV3d* p=this->marcoFrenet(base->at(j),t);  // Frenet sobre un punto del polígono base para obtener el convertido...
   tv->push_back(p);  // ...y su inserción en el vector de vértices tv
   }
  if (i>0)
   this->genMallaCil4(np);  // Genera el último prisma correspondiente de la extrusión
  }
 // Creamos el coche
 /*carroceriaA=gluNewQuadric();
 gluQuadricDrawStyle(carroceriaA,GLU_FILL);  */
 double R=a-b; double Q=R/b;
 iInt=0;  // Rodaja inicial en la que está el coche
 tCoche=0;  // tCoche es el ángulo para calcular la posición de la hipotrocoide por la que va el coche
 posX=R*cos(tCoche)+c*cos(tCoche*Q); posY=R*sin(tCoche)-c*sin(tCoche*Q);  // Posición inicial del coche
 orient=new PV3d(0,0,1,0);  // Vector de orientación inicial del coche
 // Carrocería
 carroceriaA=new Malla();
 carroceriaA->ponVertice(0.5,0,-0.6); carroceriaA->ponVertice(0.5,0.2,-0.6); carroceriaA->ponVertice(-0.5,0.2,-0.6);
 carroceriaA->ponVertice(-0.5,0,-0.6); carroceriaA->ponVertice(0.5,0,0.6); carroceriaA->ponVertice(0.5,0.2,0.6);
 carroceriaA->ponVertice(-0.5,0.2,0.6); carroceriaA->ponVertice(-0.5,0,0.6);
 carroceriaA->genMallaCubo();
 carroceriaB=new Malla();
 carroceriaB->ponVertice(0.25,0.2,-0.3); carroceriaB->ponVertice(0.25,0.4,-0.3); carroceriaB->ponVertice(-0.25,0.4,-0.3);
 carroceriaB->ponVertice(-0.25,0.2,-0.3); carroceriaB->ponVertice(0.25,0.2,0.3); carroceriaB->ponVertice(0.25,0.4,0.3);
 carroceriaB->ponVertice(-0.25,0.4,0.3); carroceriaB->ponVertice(-0.25,0.2,0.3);
 carroceriaB->genMallaCubo();
 // Ruedas
 ruedaA=gluNewQuadric(); ruedaB=gluNewQuadric(); ruedaC=gluNewQuadric(); ruedaD=gluNewQuadric();
 tapaA=gluNewQuadric(); tapaB=gluNewQuadric(); tapaC=gluNewQuadric(); tapaD=gluNewQuadric();
 gluQuadricDrawStyle(ruedaA,GLU_FILL); gluQuadricDrawStyle(ruedaB,GLU_FILL);
 gluQuadricDrawStyle(ruedaC,GLU_FILL); gluQuadricDrawStyle(ruedaD,GLU_FILL);
 gluQuadricDrawStyle(tapaA,GLU_FILL); gluQuadricDrawStyle(tapaB,GLU_FILL);
 gluQuadricDrawStyle(tapaC,GLU_FILL); gluQuadricDrawStyle(tapaD,GLU_FILL);
 }

Hipotrocoide3D::~Hipotrocoide3D()
 {
 for (unsigned int i=0; i<base->size(); i++)  // Eliminación de los puntos del polígono base
  {
  delete base->at(i);
  }
 delete base;  // Eliminación del polígono base
 delete carroceriaA;  // Eliminación de la carrocería del coche
 delete carroceriaB;
 gluDeleteQuadric(ruedaA); gluDeleteQuadric(ruedaB); gluDeleteQuadric(ruedaC); gluDeleteQuadric(ruedaD);
 gluDeleteQuadric(tapaA); gluDeleteQuadric(tapaB); gluDeleteQuadric(tapaC); gluDeleteQuadric(tapaD);
 delete orient;  // Eliminación del vector de orientación inicial
 }

// Métodos privados
int Hipotrocoide3D::MCD(int u, int v)
 {
 while (u>0)
  {
  if (u<v)
   {
   int temp;
   temp=u;
   u=v;
   v=temp;
   }
  u=u-v;
  }
 return v;
 }

PV3d* Hipotrocoide3D::marcoFrenet(PV3d* p, double t)
 {
 // Recibimos p, punto del polígono base que se transforma en q. Y recibimos
 // t que es el ángulo por el que gira la hipotrocoide. Devolvemos el punto
 // transformado q.
 double R=a-b;
 double Q=R/b;
 double x=R*cos(t)+c*cos(t*Q);  // X(t)
 double xP=-R*sin(t)-c*Q*sin(t*Q);  // X'(t)
 double xPP=-R*cos(t)-c*Q*Q*cos(t*Q);  // X''(t)
 double z=R*sin(t)-c*sin(t*Q);  // Z(t)
 double zP=R*cos(t)-c*Q*cos(t*Q);  // Z'(t)
 double zPP=-R*sin(t)+c*Q*Q*sin(t*Q);  // Z''(t)
 PV3d* cOrig=new PV3d(x,0,z,0);  // C(t)
 PV3d* cP=new PV3d(xP,0,zP,0);  // C'(t)
 PV3d* cPP=new PV3d(xPP,0,zPP,0);  // C''(t)
 PV3d* bNum=cP->prodVect(cPP);
 double bDen=bNum->module();
 PV3d* b=new PV3d(bNum->getX()/bDen,bNum->getY()/bDen,bNum->getZ()/bDen,0);  // B(t)
 double mod_cP=cP->module();  // ||C'(t)||
 PV3d* tOrig=new PV3d(cP->getX()/mod_cP,0,cP->getZ()/mod_cP,0);  // T(t)
 PV3d* n=b->prodVect(tOrig);  // N(t)
 double xN,yN,zN=0;  // Coordenadas del punto transformado
 double px=p->getX();  // Coordenadas del punto sin transformar al que se aplica Frenet
 double py=p->getY();
 double pz=p->getZ();
 xN=n->getX()*px + b->getX()*py + tOrig->getX()*pz + cOrig->getX();
 yN=n->getY()*px + b->getY()*py + tOrig->getY()*pz + cOrig->getY();
 zN=n->getZ()*px + b->getZ()*py + tOrig->getZ()*pz + cOrig->getZ();
 PV3d* q=new PV3d(xN,yN,zN,1);  // Punto que se devolverá transformado
 delete cOrig, delete cP; delete cPP; delete bNum; delete b; delete tOrig; delete n;
 return q;
 }

void Hipotrocoide3D::genCirculo(int np, double r)
 {
 double alpha=(360.0/(double)np)*(M_PI/180.0);  // Ángulo de cada rodaja en radianes
 double sum=0;
 double x,y,z;
 for (int i=0; i<np; i++)  // Inserción de puntos en el polígono base
  {
  x=r*cos(sum);
  y=-r*sin(sum);
  sum+=alpha;
  base->push_back(new PV3d(x,y,0,1));
  }
 }

void Hipotrocoide3D::dibujaRueda(GLUquadric* obj, double x, double z)
 {
 glPushMatrix();
  glTranslatef(x,0,z);
  glRotatef(90,0,1,0);
  gluCylinder(obj,0.2,0.2,0.2,8,1);
 glPopMatrix();
 }

void Hipotrocoide3D::dibujaTapa(GLUquadric* obj, double x, double z)
 {
 glPushMatrix();
  glTranslatef(x,0,z);
  glRotatef(90,0,1,0);
  gluDisk(obj,0,0.2,8,1);
 glPopMatrix();
 }

// Métodos públicos
void Hipotrocoide3D::setCoche(bool cond)
 {
 // cond: true=hacia delante, false=hacia detrás
 double R=a-b; double Q=R/b;
 if (cond)
  {
  iInt=iInt+1;
  tCoche=iInt*2*M_PI/nqInt;
  posX=R*cos(tCoche)+c*cos(tCoche*Q);
  posY=R*sin(tCoche)-c*sin(tCoche*Q);
  }
 else
  {
  iInt=iInt-1;
  tCoche=iInt*2*M_PI/nqInt;
  posX=R*cos(tCoche)+c*cos(tCoche*Q);
  posY=R*sin(tCoche)-c*sin(tCoche*Q);
  }
 }

void Hipotrocoide3D::dibujaCoche()
 {
 double R=a-b;
 double Q=R/b;
 glColor4f(1,0,0,1);
 glPushMatrix();
  glTranslatef(posX,0,posY);  // Movemos el coche por la hipotrocoide
  tangente=new PV3d(-R*sin(tCoche)-c*Q*sin(tCoche*Q),0,R*cos(tCoche)-c*Q*cos(tCoche*Q),0);  // Vector tangente en el punto actual
  rotCoche=orient->alpha(tangente);
  delete tangente;
  glRotatef(rotCoche,0,1,0);  // Rotamos el coche por la hipotrocoide en el plano Y
  carroceriaA->dibuja(false);
  carroceriaB->dibuja(false);
  glColor4f(0,0,0,1);
  dibujaRueda(ruedaA,0.5,0.35);
  dibujaRueda(ruedaB,0.5,-0.35);
  dibujaRueda(ruedaC,-0.7,0.35);
  dibujaRueda(ruedaD,-0.7,-0.35);
  dibujaTapa(tapaA,0.7,0.35);
  dibujaTapa(tapaB,0.7,-0.35);
  dibujaTapa(tapaC,-0.7,0.35);
  dibujaTapa(tapaD,-0.7,-0.35);
 glPopMatrix();
 glColor4f(1,1,1,1);
 }

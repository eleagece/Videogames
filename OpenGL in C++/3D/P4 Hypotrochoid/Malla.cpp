#pragma hdrstop
#include "Malla.h"
#pragma package(smart_init)

// Constructores y destructor
Malla::Malla()
 {
 tc=new vector<Cara*>();  // Crea el vector de caras
 tn=new vector<PV3d*>();  // Crea el vector de normales
 tv=new vector<PV3d*>();  // Crea el vector de v�rtices
 tn->push_back(new PV3d(0,0,0,0));
 rotX=0; rotY=0; rotZ=0;
 }

Malla::~Malla()
 {
 for (unsigned int i=0; i<tc->size(); i++)  // Elimina las caras una por una
  {
  delete tc->at(i);
  }
 delete tc;  // Finalmente elimna el vector de caras
 for (unsigned int i=0; i<tn->size(); i++)   // Elimina las normales una por una
  {
  delete tn->at(i);
  }
 delete tn;  // Finalmente elimna el vector de normales
 for (unsigned int i=0; i<tv->size(); i++)  // Elimina los v�rtices una por una
  {
  delete tv->at(i);
  }
 delete tv;  // Finalmente elimna el vector de v�rtices
 }

// M�todos protected
void Malla::genMallaCil4(int nelem)
 {
 // Genera las caras de un prisma de nelem lados de base. A nelem m�s alto m�s
 // parecido a un cilindro ser�.
 // El prisma formar� parte de una colecci�n de prismas encadenados, y este se-
 // r� el �ltimo generado (hasta el momento, luego pueden venir m�s):
 // V�rtices base inferior tv[long-2*nelem..long-nelem-1]
 // V�rtices base superior tv[long-nelem..long-1]
 // Este m�todo actualiza tn y tc. tv ya est� actualizado antes de llamar al
 // m�todo y tiene que ser as� para poder acceder a los �ltimos v�rtices que
 // son los que forman el prisma
 Cara* c;
 PV3d* n;
 int iinf=tv->size()-2*nelem;  // Primer v�rtice de la base inferior
 int isup=tv->size()-nelem;  // Primer v�rtice de la base superior
 for (int i=0; i<nelem-1; i++)  // Recorrido de nelem-1 iteraciones, una por cada
  {                             // lado/v�rtice/cara de la base (excepto la �ltima)
  c=new Cara();  // Cara generada
  c->addV(i+iinf);  // A�adimos primer v�rtice inferior
  c->addV(i+isup);  // A�adimos primer v�rtice superior
  c->addV(i+isup+1);  // A�adimos segundo v�rtice superior
  c->addV(i+iinf+1);  // A�adimos segundo v�rtice inferior y se completa la cara
  n=this->normalNewell(c);  // Obtenemos la normal de la cara generada
  tn->push_back(n);  // A�adimos la normal de la cara al vector de normales
  c->setN(tn->size()-1);  // Actualiza el �ndice de la normal de los v�rtices de la cara
  tc->push_back(c);  // Se a�ade la cara al vector de caras
  }
 c=new Cara();  // Lo mismo pero para la �ltima cara
 c->addV(isup-1);
 c->addV(isup+nelem-1);
 c->addV(isup);
 c->addV(iinf);
 n=this->normalNewell(c);
 tn->push_back(n);
 c->setN(tn->size()-1);
 tc->push_back(c);
 }

/*void Malla::addCirculo(int np,double r,double h)
 {
 // Genera un pol�gono base que simula un c�rculo en el plano (0,h,0)
 // con radio r y aproximado por np lados
 double alpha=(360.0/(double)np)*(M_PI/180.0);  // �ngulo correspondiente a cada rodaja en radianes
 double sum=0;  // Acumula el �ngulo por el que se va calculando el punto
 double x,z;  // Guardan las posiciones del punto (x,h,z)
 for (int i=0; i<np; i++)  // Vueltas para calcular los np puntos
  {
  x=r*cos(sum);  // Calcula punto x
  z=-r*sin(sum);  // Calcula punto z
  sum+=alpha;  // Se acumula el �ngulo para la siguiente iteraci�n
  tv->push_back(new PV3d(x,h,z,1));  // Se a�ade el punto (x,h,z)
  }
 }  */

// M�todos privados
PV3d* Malla::normalNewell(Cara* c)
 {
 // Devuelve la normal de la cara c
 double nx,ny,nz=0;  // Valores (x,y,z) del vector normal a la cara c
 PV3d* p;  // V�rtice actual en el an�lisis de Newell
 PV3d* q;  // V�rtice sucesor en el an�lisis de Newell
 for (int i=0; i<c->getSize(); i++)  // Recorre los v�rtices de la cara para calcular la normal mediante Newell
  {
  p=tv->at(c->getPos(i)->getV());  // Se obtiene el v�rtice actual
  q=tv->at(c->getPos(SUC(i,c->getSize()))->getV());  // Se obtiene el v�rtice sucesor
  nx+=(p->getY()-q->getY())*(p->getZ()+q->getZ());  // Valor x del vector normal a la cara c acumulado
  ny+=(p->getZ()-q->getZ())*(p->getX()+q->getX());  // Valor y del vector normal a la cara c acumulado
  nz+=(p->getX()-q->getX())*(p->getY()+q->getY());  // Valor z del vector normal a la cara c acumulado
  }
 PV3d* n=new PV3d(nx,ny,nz,0);  // Se han recorrido todos los v�rtices y se tienen los valores (x,y,z) de la normal
 return n;  // Devolvemos la normal creada
 }

// M�todos p�blicos
void Malla::genMallaCubo()
 {
 Cara* c=new Cara();
 c->addV(0); c->addV(1); c->addV(5); c->addV(4);
 PV3d* n=normalNewell(c); tn->push_back(n); c->setN(tn->size()-1); tc->push_back(c);
 c=new Cara();
 c->addV(1); c->addV(2); c->addV(6); c->addV(5);
 n=normalNewell(c); tn->push_back(n); c->setN(tn->size()-1); tc->push_back(c);
 c=new Cara();
 c->addV(2); c->addV(3); c->addV(7); c->addV(6);
 n=normalNewell(c); tn->push_back(n); c->setN(tn->size()-1); tc->push_back(c);
 c=new Cara();
 c->addV(3); c->addV(0); c->addV(4); c->addV(7);
 n=normalNewell(c); tn->push_back(n); c->setN(tn->size()-1); tc->push_back(c);
 c=new Cara();
 c->addV(0); c->addV(3); c->addV(2); c->addV(1);
 n=normalNewell(c); tn->push_back(n); c->setN(tn->size()-1); tc->push_back(c);
 c=new Cara();
 c->addV(5); c->addV(6); c->addV(7); c->addV(4);
 n=normalNewell(c); tn->push_back(n); c->setN(tn->size()-1); tc->push_back(c);
 }

void Malla::ponVertice(double x, double y, double z)
 {
 PV3d* p=new PV3d(x,y,z,1);
 tv->push_back(p);
 }

void Malla::setGiro(int eje, int dir)
 {
 // eje: 1=x, 2=y, 3=z | dir: 0=neg, 1=pos
 switch (eje)
  {
  case 1:
   if (dir==1)
    rotX=rotX+10;
   else
    rotX=rotX-10;
   break;
  case 2:
   if (dir==1)
    rotY=rotY+10;
   else
    rotY=rotY-10;
   break;
  case 3:
   if (dir==1)
    rotZ=rotZ+10;
   else
    rotZ=rotZ-10;
   break;
  }
 };

void Malla::dibuja(bool b)
 {
 glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
 glRotatef(rotX,1,0,0);
 glRotatef(rotY,0,1,0);
 glRotatef(rotZ,0,0,1);
 for (unsigned int i=0; i<tc->size(); i++)  // Se recorren todas las caras...
  {
  tc->at(i)->dibuja(tv,tn,b);  // ...dibuj�ndolas
  }
 glPopMatrix();
 }


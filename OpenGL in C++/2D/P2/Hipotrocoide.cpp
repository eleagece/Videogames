#include <vcl.h>
#pragma hdrstop
#include "Hipotrocoide.h"

//****************************************************************************//
// Constructores, destructor
//****************************************************************************//
Hipotrocoide::Hipotrocoide()
 {
 listaSegmentos=new Lista<Segmento>();
 }

Hipotrocoide::Hipotrocoide(float oX, float oY, float a, float b, float c, float segmentosVuelta)
 {
 this->oX=oX;
 this->oY=oY;
 this->a=a;
 this->b=b;
 this->c=c;
 this->n=segmentosVuelta;
 // Algoritmo del hipotrocoide animado, va haciendo nuevos segmentos cada vez que pasa
 AgregaSegsHipotrocoide(oX,oY,a,b,c,segmentosVuelta);
 }

Hipotrocoide::~Hipotrocoide()
 {
 delete listaSegmentos;
 listaSegmentos=NULL;
 }

void Hipotrocoide::PonValores(float oX, float oY, float a, float b, float c, float segmentosVuelta)
 {
 this->oX=oX;
 this->oY=oY;
 this->a=a;
 this->b=b;
 this->c=c;
 this->n=segmentosVuelta;
 }

void Hipotrocoide::Precisa(bool precision)
 {
 if (precision)
  n=n+10;
 else
  if (n>=10)
   n=n-10;
 delete listaSegmentos;
 AgregaSegsHipotrocoide(oX,oY,a,b,c,n);
 }

void Hipotrocoide::AgregaSegsHipotrocoide(float oX, float oY, float a, float b, float c, float segmentosVuelta)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Inserta un hipotrocoide "hip" en "listaHipotrocoides"
 // -El hipotrocoide "hip" se eliminará al hacer el delete de
 //  "listaHipotrocoides"
 ///////////////////////////////////////////////////////////////////////////////
 float x,y,v,w;
 listaSegmentos=new Lista<Segmento>();
 int numVueltas=b/MCD(a,b);  // Número de vueltas totales
 int segmentosTotal=numVueltas*segmentosVuelta;  // Número de segmentos de todas las vueltas
 for (int t=0; t<=segmentosTotal; t++)
  {
  x=((a-b)*cos(t*2*M_PI/segmentosVuelta))+(c*cos(t*2*M_PI/segmentosVuelta*((a-b)/b)))+oX;
  y=((a-b)*sin(t*2*M_PI/segmentosVuelta))-(c*sin(t*2*M_PI/segmentosVuelta*((a-b)/b)))+oY;
  if (t==0)  // Primera iteración para guardar el primer punto
   {
   v=x; w=y;
   }
  else
   {
   Segmento* seg=new Segmento(v,w,x,y);
   listaSegmentos->inserta(seg);
   v=x; w=y;
   }
  }
 }

int Hipotrocoide::MCD(int u, int v)
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

void Hipotrocoide::Dibuja()
 {
 glColor3f(1,1,0);  // Amarillo
 listaSegmentos->inicia();
 for (int i=0; i<listaSegmentos->getLongitud(); i++)
  {
  listaSegmentos->getActual()->Dibuja();
  listaSegmentos->avanza();
  }
 glColor3f(1,1,1);  // Blanco
 }

void Hipotrocoide::DibujaSelec()
 {
 glColor3f(1,0,0);  // Rojo
 listaSegmentos->inicia();
 for (int i=0; i<listaSegmentos->getLongitud(); i++)
  {
  listaSegmentos->getActual()->Dibuja();
  listaSegmentos->avanza();
  }
 glColor3f(1,1,1);  // Blanco
 }

void Hipotrocoide::Recorta(PuntoVector* R1,PuntoVector* R2)
 {
 listaSegmentos->inicia();
 for (unsigned int i=0; i<listaSegmentos->getLongitud(); i++)
  {
  bool b=listaSegmentos->getActual()->CS(R1,R2);
  if (b)
   {
   listaSegmentos->eliminaActual();  // Se elimina el segmento actual si se encuentra totalmente fuera (CS devolvió true)
   i--;  // Se reduce el índice porque nos hemos cargado a uno y tenemos que recorrer todos
   }
  else
   listaSegmentos->avanza();
  }
 }

bool Hipotrocoide::SelecHipotrocoide(float x, float y)
 {
 float match=a+b;//10;  // Distancia máxima para poder seleccionar hipotrocoide
 if (oX-match<x && x<oX+match && oY-match<y && y<oY+match)
  return true;
 else
  return false;
 }

void Hipotrocoide::Gira()
 {
 listaSegmentos->inicia();
 PuntoVector* centroRot=new PuntoVector(oX,oY);
 for (unsigned int i=0; i<listaSegmentos->getLongitud(); i++)
  {
  PuntoVector* pvo=listaSegmentos->getActual()->DamePuntoOrigen();
  PuntoVector* pvd=listaSegmentos->getActual()->DamePuntoDestino();
  pvo->rotaP(centroRot,30);
  pvd->rotaP(centroRot,30);
  listaSegmentos->avanza();
  }
 delete centroRot;
 }

void Hipotrocoide::salvaHipotrocoide(ofstream& f)
 {
 int n2=listaSegmentos->getLongitud();
 f.write((char*)&a,sizeof(float));
 f.write((char*)&b,sizeof(float));
 f.write((char*)&c,sizeof(float));
 f.write((char*)&n,sizeof(float));
 f.write((char*)&oX,sizeof(float));
 f.write((char*)&oY,sizeof(float));
 f.write((char*)&n2,sizeof(int));
 listaSegmentos->inicia();
 for (int i=0; i<listaSegmentos->getLongitud(); i++)
  {
  listaSegmentos->getActual()->salvaSegmento(f);
  listaSegmentos->avanza();
  }
 }

void Hipotrocoide::cargaHipotrocoide(ifstream& f)
 {
 int n2;
 f.read((char*)&a,sizeof(float));
 f.read((char*)&b,sizeof(float));
 f.read((char*)&c,sizeof(float));
 f.read((char*)&n,sizeof(float));
 f.read((char*)&oX,sizeof(float));
 f.read((char*)&oY,sizeof(float));
 f.read((char*)&n2,sizeof(int));
 for (int i=0; i<n2; i++)
  {
  Segmento* aux=new Segmento();
  aux->cargaSegmento(f);
  listaSegmentos->inserta(aux);
  }
 }
#pragma package(smart_init)


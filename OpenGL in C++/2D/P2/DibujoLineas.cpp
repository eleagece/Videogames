#include <vcl.h>
#pragma hdrstop
#include "DibujoLineas.h"

//****************************************************************************//
// Constructores, destructor
//****************************************************************************//
DibujoLineas::DibujoLineas()
 {
 listaSegmentos=new Lista<Segmento>();
 }

DibujoLineas::~DibujoLineas()
 {
 delete listaSegmentos;
 listaSegmentos=NULL;
 }

//****************************************************************************//
// Getters
//****************************************************************************//
Lista<Segmento>* DibujoLineas::DameLista()
 {
 return listaSegmentos;
 }

//****************************************************************************//
// M�todos p�blicos que dibujan el dibujo de l�neas
//****************************************************************************//
void DibujoLineas::Dibuja()
 {
 listaSegmentos->inicia();
 for (int i=0; i<listaSegmentos->getLongitud(); i++)
  {
  listaSegmentos->getActual()->Dibuja();
  listaSegmentos->avanza();
  }
 }

void DibujoLineas::DibujaSelec()
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

//****************************************************************************//
// M�todo p�blicos que modifican el dibujo de l�neas
//****************************************************************************//
void DibujoLineas::PonSegmento(Segmento* seg)
 {
 listaSegmentos->inserta(seg);
 }
 
void DibujoLineas::Recorta(PuntoVector* R1,PuntoVector* R2)
 {
 listaSegmentos->inicia();
 for (unsigned int i=0; i<listaSegmentos->getLongitud(); i++)
  {
  bool b=listaSegmentos->getActual()->CS(R1,R2);
  if (b)
   {
   listaSegmentos->eliminaActual();  // Se elimina el segmento actual si se encuentra totalmente fuera (CS devolvi� true)
   i--;  // Se reduce el �ndice porque nos hemos cargado a uno y tenemos que recorrer todos
   }
  else
   listaSegmentos->avanza();
  }
 }

//****************************************************************************//
// M�todo p�blico que selecciona el dibujo de l�neas
//****************************************************************************//
bool DibujoLineas::SelecDibujoLineas(float x, float y)
 {
 float match=10;  // Distancia m�xima para poder seleccionar un punto
 int i=0;
 float oX,oY,dX,dY;
 bool encontrado=false;
 listaSegmentos->inicia();
 while (i<listaSegmentos->getLongitud() && !encontrado)
  {
  oX=listaSegmentos->getActual()->DamePuntoOrigen()->dameX();
  oY=listaSegmentos->getActual()->DamePuntoOrigen()->dameY();
  dX=listaSegmentos->getActual()->DamePuntoDestino()->dameX();
  dY=listaSegmentos->getActual()->DamePuntoDestino()->dameY();
  if ((oX-match<x && x<oX+match && oY-match<y && y<oY+match) ||
     (dX-match<x && x<dX+match && dY-match<y && y<dY+match))
   encontrado=true;
  if (!encontrado)
   {
   i++;
   listaSegmentos->avanza();
   }
  }
 if (encontrado)
  return true;
 else
  return false;
 }

//****************************************************************************//
// M�todos p�blicos que cargan y salvan el dibujo de l�neas
//****************************************************************************//
void DibujoLineas::salvaDibLineas(ofstream& f)
 {
 int longS=listaSegmentos->getLongitud();
 f.write((char*)&longS,sizeof(int));
 listaSegmentos->inicia();
 for (int i=0; i<longS; i++)
  {
  listaSegmentos->getActual()->salvaSegmento(f);
  listaSegmentos->avanza();
  }
 }

void DibujoLineas::cargaDibLineas(ifstream& f)
 {
 int n;
 f.read((char*)&n,sizeof(float));
 for (int i=0; i<n; i++)
  {
  Segmento* aux=new Segmento();
  aux->cargaSegmento(f);
  listaSegmentos->inserta(aux);
  }
 }

#pragma package(smart_init)

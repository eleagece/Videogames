#include <vcl.h>
#pragma hdrstop
#include "Segmento.h"

// Constructores
Segmento::Segmento()
 {
 puntoOrigen=new PuntoVector();
 puntoDestino=new PuntoVector();
 }

Segmento::Segmento(float XA, float YA, float XB, float YB)
 {
 puntoOrigen=new PuntoVector(XA,YA);
 puntoDestino=new PuntoVector(XB,YB);
 }

Segmento::Segmento(PuntoVector* pOrigen, PuntoVector* pDestino)
 {
 puntoOrigen=pOrigen;
 puntoDestino=pDestino;
 }

Segmento::~Segmento()
 {
 delete puntoOrigen;
 delete puntoDestino;
 puntoOrigen=NULL;
 puntoDestino=NULL;
 }

// Getters y setters
PuntoVector* Segmento::DamePuntoOrigen()
 {
 return puntoOrigen;
 }

PuntoVector* Segmento::DamePuntoDestino()
 {
 return puntoDestino;
 }

// Métodos
void Segmento::Dibuja()
 {
 glBegin(GL_LINES);
  glVertex2f(puntoOrigen->dameX(),puntoOrigen->dameY());
  glVertex2f(puntoDestino->dameX(),puntoDestino->dameY());
 glEnd();
 }

bool Segmento::CS(PuntoVector* R1, PuntoVector* R2)
 {
       unsigned char codP1=getCode(puntoOrigen,R1,R2);
        unsigned char codP2=getCode(puntoDestino,R1,R2);
        // Casos BASE
        // Éxito trivial: origen y destino dentro de R
        if (codP1==0 && codP2==0)
                return false;   // No se recorta más
        // Rechazo trivial: origen y destino exteriores a la misma frontera
        if ((codP1 & codP2)!=0)
                return true;    // Se recorta toda

        // CASO RECURSIVO
        // Corte con 4 fronteras para P1
        if (codP1>=8){
                corteF0(puntoOrigen,puntoDestino,R1,R2);
                return CS(R1,R2);
                }
        else if (codP1>=4){
                corteF1(puntoOrigen,puntoDestino,R1,R2);
                return CS(R1,R2);
                }
        else if (codP1>=2){
                corteF2(puntoOrigen,puntoDestino,R1,R2);
                return CS(R1,R2);
                }
        else if (codP1==1){
                corteF3(puntoOrigen,puntoDestino,R1,R2);
                return CS(R1,R2);
                }
        else

        // Si no ha habido corte con P1: 
        // Corte con 4 fronteras para P2
        if (codP2>=8){
                corteF0(puntoDestino,puntoOrigen,R1,R2);
                return CS(R1,R2);
                }
        else if (codP2>=4){
                corteF1(puntoDestino,puntoOrigen,R1,R2);
                return CS(R1,R2);
                }
        else if (codP2>=2){
                corteF2(puntoDestino,puntoOrigen,R1,R2);
                return CS(R1,R2);
                }
        else if (codP2==1){
                corteF3(puntoDestino,puntoOrigen,R1,R2);
                return CS(R1,R2);
                }
        // Esto no se alcanza nunca porque corresponde con el RECHAZO TRIVIAL
        else return false;
 }

unsigned char Segmento::getCode(PuntoVector* p,PuntoVector* R1,PuntoVector* R2)
{
        unsigned char cod=0;
        // Exterior a frontera 0
        if (p->dameX() < R1->dameX())
                cod |=8;
        // Exterior a frontera 2
        else if (p->dameX() > R2->dameX())
                cod |=2;
        // Exterior a frontera 1
        if (p->dameY() > R1->dameY())
                cod |=4;
        // Exterior a frontera 3
        else if (p->dameY() < R2->dameY())
                cod |=1;

        return cod;
}
//---------------------------------------------------------------------------
void Segmento::corteF0(PuntoVector* o,PuntoVector* dest,PuntoVector* R1,PuntoVector* R2)
{
        GLfloat d= (dest->dameY()-o->dameY())*(dest->dameX()-R1->dameX())/(dest->dameX()-o->dameX());
        o->ponX(R1->dameX());
        o->ponY(dest->dameY()-d);
}
//---------------------------------------------------------------------------
void Segmento::corteF2(PuntoVector* o,PuntoVector* dest,PuntoVector* R1,PuntoVector* R2)
{
        GLfloat d= (dest->dameY()-o->dameY())*(dest->dameX()-R2->dameX())/(dest->dameX()-o->dameX());
        o->ponX(R2->dameX());
        o->ponY(dest->dameY()-d);
}
//---------------------------------------------------------------------------
void Segmento::corteF1(PuntoVector* o,PuntoVector* dest,PuntoVector* R1,PuntoVector* R2)
{
        GLfloat d= (dest->dameX()-o->dameX())*(dest->dameY()-R1->dameY())/(dest->dameY()-o->dameY());
        o->ponX(dest->dameX()-d);
        o->ponY(R1->dameY());
}
//---------------------------------------------------------------------------
void Segmento::corteF3(PuntoVector* o,PuntoVector* dest,PuntoVector* R1,PuntoVector* R2)
{
        GLfloat d= (dest->dameX()-o->dameX())*(dest->dameY()-R2->dameY())/(dest->dameY()-o->dameY());
        o->ponX(dest->dameX()-d);
        o->ponY(R2->dameY());
}

void Segmento::salvaSegmento(ofstream& f)
 {
 puntoOrigen->salvaPunto(f);
 puntoDestino->salvaPunto(f);
 }

void Segmento::cargaSegmento(ifstream& f)
 {
 puntoOrigen->cargaPunto(f);
 puntoDestino->cargaPunto(f);
 }




#pragma package(smart_init)

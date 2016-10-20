//---------------------------------------------------------------------------
#pragma hdrstop
#include "Pelota.h"
//-------------------------------------------------------------- -------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Pelota::Pelota(vector<PuntoV*>* vec,double r,PuntoV* c,PuntoV* d)
{
        _puntos=vec;
        _radio=r;
        _centro=c;
        _dir=d;
        _nor=new PuntoV(d->getY(),-d->getX());
}
//---------------------------------------------------------------------------
Pelota::~Pelota()
{
        for (unsigned int i=0; i<_puntos->size(); i++)
                {
                delete _puntos->at(_puntos->size()-i-1);
                }
        delete _puntos;
        delete _centro;
        delete _dir;
        delete _nor;
}
//---------------------------------------------------------------------------
void Pelota::Dibuja()
{
        glBegin(GL_POLYGON);
        for (unsigned int i=0; i<_puntos->size(); i++)
                {
                glVertex2d(_puntos->at(i)->getX(),_puntos->at(i)->getY());
                }
        glEnd();
}
//---------------------------------------------------------------------------
void Pelota::Avanzar(double t)
{
        for (unsigned int i=0; i<_puntos->size(); i++)
                {
                PuntoV* p=_puntos->at(i);
                p->setX(p->getX()+t*_dir->getX());
                p->setY(p->getY()+t*_dir->getY());
                }
       _centro->setX(_centro->getX()+t*_dir->getX());
       _centro->setY(_centro->getY()+t*_dir->getY());
}
//---------------------------------------------------------------------------

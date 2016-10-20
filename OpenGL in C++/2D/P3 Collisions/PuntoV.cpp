//---------------------------------------------------------------------------
#pragma hdrstop
#include "PuntoV.h"
//--------------------------------------------- ------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
PuntoV::PuntoV(float x,float y)
{
        _x=x;
        _y=y;
}
//---------------------------------------------------------------------------
PuntoV::PuntoV(PuntoV* p)
{
        _x=p->getX();
        _y=p->getY();
}
//---------------------------------------------------------------------------
double PuntoV::dot(PuntoV* w)
{
        return (_x*w->getX())+(_y*w->getY());
}
//---------------------------------------------------------------------------
double PuntoV::module()
{
        double aux=pow(_x,2)+pow(_y,2);
        return sqrt(aux);
}
//---------------------------------------------------------------------------
double PuntoV::alpha(PuntoV* w)
{
        double num=dot(w);
        double den=this->module()*w->module();
        return acos(num/den)*(180.0/M_PI);
}
//---------------------------------------------------------------------------
void PuntoV::dibuja(GLdouble tam,GLfloat R,GLfloat G,GLfloat B)
{
        glPointSize(tam);
        glColor3f(R,G,B);
        glBegin(GL_POINTS);
        glVertex2f(_x,_y);
        glEnd();
        glPointSize(1.0);
        glColor3f(1.0,1.0,1.0);
}
//---------------------------------------------------------------------------
PuntoV* PuntoV::menos(PuntoV* w)
{
        return new PuntoV(_x-w->getX(),_y-w->getY());
}
//---------------------------------------------------------------------------
PuntoV* PuntoV::escala(double k)
{
        return new PuntoV(_x+k*_x,k*_y);
}
//---------------------------------------------------------------------------

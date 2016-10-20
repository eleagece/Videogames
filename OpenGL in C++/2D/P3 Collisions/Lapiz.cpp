//---------------------------------------------------------------------------
#pragma hdrstop
#include "Lapiz.h"
//----------------------------------------------- ----------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
PuntoV* Lapiz::mover(GLdouble dist,bool pintar)
{
        // Obtenemos coordenadas destino
        GLdouble x=_pos->getX()+(dist*cos(_dir));
        GLdouble y=_pos->getY()+(dist*sin(_dir));
        // Trazamos en caso necesario
        if (pintar){
                glBegin(GL_LINES);
                glVertex2f(_pos->getX(),_pos->getY());
                glVertex2f(x,y);
                glEnd();
        }
        // Actualizamos nueva posición
        _pos->setX(x);
        _pos->setY(y);
        return _pos;
}
//---------------------------------------------------------------------------

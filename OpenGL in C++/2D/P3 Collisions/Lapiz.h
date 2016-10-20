//---------------------------------------------------------------------------
#ifndef LapizH
#define LapizH
// Include ------------------------------------------------------------------
#include "PuntoV.h"
//---------------------------------------------------------------------------
// Tipos --------------------------------------------------------------------
//-------------------------------------------------------- -------------------
// clases -------------------------------------------------------------------
class Lapiz
{
private:	// User declarations
        // Posici�n del l�piz
        PuntoV* _pos;
        // Direcci�n de avance en radianes
        GLdouble _dir;

public:		// User declarations
        // Contruye un punto con origen pos y direccion dir especificada en grados
        Lapiz(PuntoV* pos,GLdouble dir){_pos=pos; _dir=dir*(M_PI/180.0);}
        ~Lapiz(){delete _pos;}

        // Gets & Sets
        PuntoV* getPos()
                {return _pos;}
        void setPos(PuntoV* pos)
                {_pos=pos;}
        // Devuelve la direcci�n en grados
        GLdouble getDir()
                {return (_dir*180.0)/M_PI;}
        // Par�metro expresado en grados
        void setDir(GLdouble dir)
                {_dir=dir*(M_PI/180.0);}

        // Efect�a un giro de ang grados con respecto a la direcci�n actual.
        // Para �ngulos positivos gira a la izquierda, para negativos a la derecha.
        void girar(GLdouble ang)
                {_dir+=ang*(M_PI/180.0);}
        // Avanza el l�piz una distancia indicada
        // No pinta el trazo a no ser que se le indique
        // Devuelve un puntero al punto de destino
        PuntoV* mover(GLdouble,bool);


};
//---------------------------------------------------------------------------
#endif
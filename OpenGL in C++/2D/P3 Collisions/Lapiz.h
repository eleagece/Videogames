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
        // Posición del lápiz
        PuntoV* _pos;
        // Dirección de avance en radianes
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
        // Devuelve la dirección en grados
        GLdouble getDir()
                {return (_dir*180.0)/M_PI;}
        // Parámetro expresado en grados
        void setDir(GLdouble dir)
                {_dir=dir*(M_PI/180.0);}

        // Efectúa un giro de ang grados con respecto a la dirección actual.
        // Para ángulos positivos gira a la izquierda, para negativos a la derecha.
        void girar(GLdouble ang)
                {_dir+=ang*(M_PI/180.0);}
        // Avanza el lápiz una distancia indicada
        // No pinta el trazo a no ser que se le indique
        // Devuelve un puntero al punto de destino
        PuntoV* mover(GLdouble,bool);


};
//---------------------------------------------------------------------------
#endif
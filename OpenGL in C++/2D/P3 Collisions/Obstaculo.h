//---------------------------------------------------------------------------
#ifndef ObstaculoH
#define ObstaculoH
// Include ------------------------------------------------------------------
#include "PuntoV.h"
//---------------------------------------------------------------------------
// Tipos --------------------------------------------------------------------
//--------------------- ------------------------------------------------------
// clases -------------------------------------------------------------------
// Representa un obst�culo, de forma abstracta
class Obstaculo
{
protected:	// User declarations
        // Identificador de clase
        int _id;

private:
        // Recubre el obst�culo con otro, dejando un grosor de separaci�n
        virtual void Recubre(double)=0;

public:		// User declarations
        // Determina si el Vector que entra como par�metro colisiona con el
        // obst�culo. Devuelve �xito o fracaso, la normal de impacto y thit.
        virtual bool Colision(PuntoV*,PuntoV*,PuntoV*,double&,PuntoV*,bool)=0;
        // Dibuja el obst�culo
        virtual void Dibuja()=0;
        //
        int getId(){return _id;}

};
//---------------------------------------------------------------------------
#endif
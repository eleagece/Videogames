//---------------------------------------------------------------------------
#ifndef ObstaculoH
#define ObstaculoH
// Include ------------------------------------------------------------------
#include "PuntoV.h"
//---------------------------------------------------------------------------
// Tipos --------------------------------------------------------------------
//--------------------- ------------------------------------------------------
// clases -------------------------------------------------------------------
// Representa un obstáculo, de forma abstracta
class Obstaculo
{
protected:	// User declarations
        // Identificador de clase
        int _id;

private:
        // Recubre el obstáculo con otro, dejando un grosor de separación
        virtual void Recubre(double)=0;

public:		// User declarations
        // Determina si el Vector que entra como parámetro colisiona con el
        // obstáculo. Devuelve éxito o fracaso, la normal de impacto y thit.
        virtual bool Colision(PuntoV*,PuntoV*,PuntoV*,double&,PuntoV*,bool)=0;
        // Dibuja el obstáculo
        virtual void Dibuja()=0;
        //
        int getId(){return _id;}

};
//---------------------------------------------------------------------------
#endif
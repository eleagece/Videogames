//---------------------------------------------------------------------------

#ifndef CirculoH
#define CirculoH
// Include ------------------------------------------------------------------
#include "Obstaculo.h"
#include "Corteza.h"
#include "PuntoV.h"
#include <vector>
#include "Lapiz.h"
// Tipos ------------------------------------------------------------------ --
//---------------------------------------------------------------------------
// clases -------------------------------------------------------------------
// Representa un circulo
class Circulo: public Obstaculo
{
private:	// User declarations
        // Lista con todas las aristas del obst�culo
        Corteza* _poli;
        //
        Corteza* _corteza;
        //
        void Recubre(double);

public:		// User declarations
        Circulo(vector<PuntoV*>*,double,bool);
        ~Circulo();
        // Determina si el Vector que entra como par�metro colisiona con
        // alguna arista del obst�culo. // obst�culo. Devuelve �xito o fracaso,
        // la normal de impacto y thit.
        bool Colision(PuntoV*,PuntoV*,PuntoV*,double&,PuntoV*,bool);
        // Dibuja el obst�culo
        void Dibuja();
};
//---------------------------------------------------------------------------
#endif

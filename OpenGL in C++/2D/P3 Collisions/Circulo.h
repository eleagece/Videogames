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
        // Lista con todas las aristas del obstáculo
        Corteza* _poli;
        //
        Corteza* _corteza;
        //
        void Recubre(double);

public:		// User declarations
        Circulo(vector<PuntoV*>*,double,bool);
        ~Circulo();
        // Determina si el Vector que entra como parámetro colisiona con
        // alguna arista del obstáculo. // obstáculo. Devuelve éxito o fracaso,
        // la normal de impacto y thit.
        bool Colision(PuntoV*,PuntoV*,PuntoV*,double&,PuntoV*,bool);
        // Dibuja el obstáculo
        void Dibuja();
};
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------
#ifndef CuboH
#define CuboH
// Include ------------------------------------------------------------------
#include "Malla.h"
//---------------------------------------------------------------------------
// Tipos --------------------------------------------------------------------
/* longitud cubo eje x */
const float ANCHO=8.0;
/* longitud cubo eje y */
const float ALTO=2.0;
/* longitud cubo eje z */
const float LARGO=8.0;
//---------------------------------------------------------------------------
// clases -------------------------------------------------------------------
/* Dibuja un cubo con un número de divisiones específico:
nx: divisiones eje x
ny: divisiones eje y
nz: divisiones eje z */
class Cubo: public Malla
{
private:	// User declarations
        /* Divisiones eje x */
        int nx;
        /* Divisiones eje y */
        int ny;
        /* Divisiones eje z */
        int nz;

        void genBase(double h, PV3d* n);
        void genFrente(double h, PV3d* n);
        void genLado(double h, PV3d* n);

public:		// User declarations
        // Constructora
        /* nx=divisiones eje x, ny=divisiones eje y, nz=divisiones eje z */
        Cubo(int nx, int ny, int nz);

        /* */
        void dibujaPeana();

};
//---------------------------------------------------------------------------
#endif

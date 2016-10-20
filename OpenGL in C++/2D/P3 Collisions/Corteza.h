//---------------------------------------------------------------------------
#ifndef CortezaH
#define CortezaH
// Include ------------------------------------------------------------------
#include "PuntoV.h"
#include "Lapiz.h"
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
// Tipos ---------- ----------------------------------------------------------
//---------------------------------------------------------------------------
// clases -------------------------------------------------------------------
// Representa un obstáculo convexo
class Corteza
{
private:	// User declarations
        // Lista con todas las aristas del obstáculo
        vector<PuntoV*>* _vertices;
        vector<PuntoV*>* _normales;
        vector<PuntoV*>* _dirs;
        //
        int _long;

public:		// User declarations
        Corteza(vector<PuntoV*>*);
        ~Corteza();
        // Dibuja la corteza
        void Dibuja();
        //
        int getLong(){return _long;}
        //
        bool cbeck(PuntoV*,PuntoV*,PuntoV*,double&,PuntoV*);
        //
        PuntoV* getNormal(int i){return _normales->at(i);}
        //
        PuntoV* getDir(int i){return _dirs->at(i);}
        //
        PuntoV* getVer(int i){return _vertices->at(i);}
};
//---------------------------------------------------------------------------
#endif
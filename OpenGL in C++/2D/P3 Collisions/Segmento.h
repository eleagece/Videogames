//---------------------------------------------------------------------------
#ifndef SegmentoH
#define SegmentoH
// Include ------------------------------------------------------------------
#include "Obstaculo.h"
#include "Corteza.h"
#include "PuntoV.h"
#include <vector>
using namespace std;
//--------------------------------- ------------------------------------------
// Tipos --------------------------------------------------------------------
//---------------------------------------------------------------------------
// clases -------------------------------------------------------------------
// Representa un segmento mediante una recta en forma paramétrica
class Segmento: public Obstaculo
{
private:	// User declarations
        // Punto de inicio
        PuntoV* _ini;
        // Punto de fin
        PuntoV* _fin;
        // Vector dirección
        PuntoV* _dir;
        // Vector normal (por la derecha)
        PuntoV* _nor;
        //
        Corteza* _corteza;
        //
        void Recubre(double);
        //
        void trazaArco(PuntoV* inicio,PuntoV* fin,PuntoV* centro,vector<PuntoV*>* lista);

public:		// User declarations
        // Inicializa los atributos inicio y fin, si se quiere recubrir
        // y el grosor de recubrimiento
        Segmento(PuntoV*,PuntoV*,double,bool);
        ~Segmento();
        //
        bool Colision(PuntoV*,PuntoV*,PuntoV*,double&,PuntoV*,bool);
        // Dibuja el segmento
        void Dibuja();
        // Devuelve el punto de inicio del segmento
        PuntoV* getIni(){return _ini;}
        // Devuelve el punto de inicio del segmento
        PuntoV* getFin(){return _fin;}
        //
        PuntoV* getNormal(){return _nor;}
        //
        PuntoV* getDir(){return _dir;}
};
//---------------------------------------------------------------------------
#endif
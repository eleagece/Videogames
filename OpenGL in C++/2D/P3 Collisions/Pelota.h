//---------------------------------------------------------------------------
#ifndef PelotaH
#define PelotaH
// Include ------------------------------------------------------------------
#include "PuntoV.h"
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
// Tipos --------------------------------------------------------------------
//---------------------------------------------------------------------------
// clases -------------------------------------------------------------------
// Representa una pelota con movimiento, aproximada mediante un polígono regular
class Pelota                 
{
private:	// User declarations
        // Puntos de la pelota
        vector<PuntoV*>* _puntos;
        // Radio de la pelota
        double _radio;
        // Centro de la pelota
        PuntoV* _centro;
        // Dirección de la pelota
        PuntoV* _dir;
        // Normal de la dirección;
        PuntoV* _nor;

public:		// User declarations
        // Inicializa los atributos de la pelota: polígono, radio, centro, dirección
        Pelota(vector<PuntoV*>*,double,PuntoV*,PuntoV*);
        ~Pelota();
        // Dibuja la pelota
        void Dibuja();
        // Avanza la pelota en su dirección. El parámetro t pertenece al
        // intervalo [0,1] e indica si se avanza el paso entero o una fracción.
        void Avanzar(double t);
        // Cambia la dirección de la pelota
        void setDir(PuntoV* d){delete _dir; _dir=d;}
        // Devuelve la dirección de la pelota
        PuntoV* getDir(){return _dir;}
        // Devuelve el centro de la pelota
        PuntoV* getCentro(){return _centro;}
        // Devuelve la normal de la dirección de la pelota
        PuntoV* getNormal(){return _nor;}


};
//---------------------------------------------------------------------------
#endif
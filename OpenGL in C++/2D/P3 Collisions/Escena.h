//---------------------------------------------------------------------------
#ifndef EscenaH
#define EscenaH
// Include ------------------------------------------------------------------
#include "Pelota.h"
#include "Obstaculo.h"
#include "Segmento.h"
#include "Lapiz.h"
#include "Convexo.h"
//---------------------------------------------------------------------------
// Tipos --------------------------------------------------------------------
const double RADIO=10.0;
const double BALLINIX=-125.0;
const double BALLINIY=125.0;          
const double CT=1.0;
//---------------------------------------------------------------------------
// clases -------------------------------------------------------------------
class Escena
{
private:	// User declarations

  float fuerzaFreno;  // Fuerza del freno de la pelota
  int x,y;  // Indican la posición del testigo de tiro
  int testigo;  // Indican la posición del testigo en valor 1-1600

        // Representa la pelota
        Pelota* _ball;
        // Lista con todos los obstáculos
        vector<Obstaculo*> _obs;
        // Centro del inicio de la pelota
        PuntoV* _centro;
        // Genera una pelota desde el punto especificado, con radio especificado
        void GeneraPelota(PuntoV*,double r);
        void GeneraPelota2(PuntoV*,double,double);
        // Genera el campo donde rebotará la pelota
        void GeneraCampo();
        //

        //
        vector<PuntoV*>* nuevoReg(PuntoV* centro,int nlados,double lado);
        //


public:		// User declarations
vector<PuntoV*>* aproxPelota(PuntoV*,double);
 bool _recubrimiento;
  bool freno;  // Freno para la pelota
        Escena();
        ~Escena();
        // Dibuja en la escena la pelota y los obstáculos
        void dibuja();
        // Inicia una pelota con dirección aleatoria
        void inicia1(bool);
        void IniciaTiro(bool);
        // Establece la reacción de la escena ante un temporizador
        void timeout();
        void DaTestigo(posTestigo);

};
//---------------------------------------------------------------------------
#endif

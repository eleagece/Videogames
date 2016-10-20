//---------------------------------------------------------------------------
#ifndef EspiralH
#define EspiralH
// Include ------------------------------------------------------------------
#include "Malla.h"
#include <math.h>
//---------------------------------------------------------------------------
// Tipos --------------------------------------------------------------------
/* incremento del par�metro t de la ecuaci�n de la espiral */
const float inc=0.2;
/* incremento de la rotaci�n de la esfera */
const float incRot=10.0;
//---------------------------------------------------------------------------
// clases -------------------------------------------------------------------
/*
REPRESENTA UNA ESPIRAL EN 3D EN OPENGL CON ECUACI�N PARAM�TRICA:
        X(t)=sin(t)-t*cos(t)
        Y(t)=-cos(t)-t*sin(t)
        Z(t)=0
*/
class Espiral: public Malla
{
private:	// User declarations
        /* radio de la espiral */
        double radio;
        /* puntos del c�rculo que se toma como base de la espiral */
        vector<PV3d*>* base;
        /* esfera que se mueve por dentro de la espiral */
        GLUquadricObj* esfera;
        /* posici�n de la esfera dentro del tubo */
        double posx;
        double posy;
        /* par�metro t de movimiento de la esfera a lo largo del tubo */
        double param;
        /* �ngulo de rotaci�n de la esfera (en grados) */
        double rot;

        /* calcula el t-�simo marco de frenet para el punto p */
        PV3d* marcoFrenet(PV3d* p,double t);
        /* genera el c�rculo tomado como base de la espiral en el plano XY */
        void genCirculo(int np,double r);

public:		// User declarations
        // Constructora
        Espiral(int np, int nq, double r);
        ~Espiral();

        /* Dibuja la esfera */
        void dibujaEsfera();
        /* Avanza la esfera dentro del tubo */
        void avanzaEsfera();
        /* Retrocede la esfera dentro del tubo */
        void retrocedeEsfera();
        /* Rota la esfera hacia la derecha */
        void rotaRight();
        /* Rota la esfera hacia la izquierda */
        void rotaLeft();
        /* Reinicia la traslaci�n y la rotaci�n de la esfera */
        void reiniciaEsfera();

};
//---------------------------------------------------------------------------
#endif
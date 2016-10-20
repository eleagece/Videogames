//---------------------------------------------------------------------------
#ifndef EspiralH
#define EspiralH
// Include ------------------------------------------------------------------
#include "Malla.h"
#include <math.h>
//---------------------------------------------------------------------------
// Tipos --------------------------------------------------------------------
/* incremento del parámetro t de la ecuación de la espiral */
const float inc=0.2;
/* incremento de la rotación de la esfera */
const float incRot=10.0;
//---------------------------------------------------------------------------
// clases -------------------------------------------------------------------
/*
REPRESENTA UNA ESPIRAL EN 3D EN OPENGL CON ECUACIÓN PARAMÉTRICA:
        X(t)=sin(t)-t*cos(t)
        Y(t)=-cos(t)-t*sin(t)
        Z(t)=0
*/
class Espiral: public Malla
{
private:	// User declarations
        /* radio de la espiral */
        double radio;
        /* puntos del círculo que se toma como base de la espiral */
        vector<PV3d*>* base;
        /* esfera que se mueve por dentro de la espiral */
        GLUquadricObj* esfera;
        /* posición de la esfera dentro del tubo */
        double posx;
        double posy;
        /* parámetro t de movimiento de la esfera a lo largo del tubo */
        double param;
        /* ángulo de rotación de la esfera (en grados) */
        double rot;

        /* calcula el t-ésimo marco de frenet para el punto p */
        PV3d* marcoFrenet(PV3d* p,double t);
        /* genera el círculo tomado como base de la espiral en el plano XY */
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
        /* Reinicia la traslación y la rotación de la esfera */
        void reiniciaEsfera();

};
//---------------------------------------------------------------------------
#endif
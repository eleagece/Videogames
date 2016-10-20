//---------------------------------------------------------------------------
#ifndef PuntoVH
#define PuntoVH
// Include ------------------------------------------------------------------
#include <math.h>
#include <vcl.h>
#include <gl\gl.h>
#include <gl\glu.h>
//---------------------------------------------------------------------------
// Tipos --------------------------------------------------------------------
//---------------------------------------------------------------------------
// clases ------------------- ------------------------------------------------
// Representa un punto vector en openGL
class PuntoV
{
private:	// User declarations
        // Coordenadas del punto
        float _x,_y;

public:		// User declarations
        // Constructora: inicializa las coordenadas
        PuntoV(float,float);
        PuntoV(PuntoV*);
        // Gets & Sets
        double getX(){return _x;}
        double getY(){return _y;}
        void setX(double x){_x=x;}
        void setY(double y){_y=y;}
        // Realiza el producto escalar con w
        double dot(PuntoV* w);
        // Devuelve el módulo del vector
        double module();
        // Devuelve el ángulo que forma con w (en grados)
        double alpha(PuntoV* w);
        // Dibuja el punto con tamaño y color especificado
        void dibuja(GLdouble tam,GLfloat R,GLfloat G,GLfloat B);
        // Resta al vector actual, el vector indicado
        PuntoV* menos(PuntoV*);
        // Devuelve el vector escalado adecuadamente. NO modifica el vector actual
        PuntoV* escala(double);

};
//---------------------------------------------------------------------------
#endif
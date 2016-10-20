#ifndef EscenaH
#define EscenaH
#include "HabitacionV.h"
#include "HabitacionL.h"
#include "Puerta.h"

class Escena: public ObjetoCompuesto3D
{
private:
 // Atributos
 HabitacionL* habL;
 HabitacionV* habV;

public:
 // Constructoras y destructora
 Escena();
 // Métodos públicos
 void setTV();  // Enciende o apaga la tele
 void setLamp();  // Enciende o apaga la lámpara
 void setPuerta();  // Abre o cierra la puerta
 void escala(int selec,float x,float y,float z);  // Escala la escena, la lámpara o los muebles
 void traslada(int selec,float x,float y,float z);  // Traslada la escena, la lámpara o los muebles
 void rota(int selec,float a,float x,float y,float z);  // Rota la escena, la lámpara o los muebles
 };

#endif
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
 // M�todos p�blicos
 void setTV();  // Enciende o apaga la tele
 void setLamp();  // Enciende o apaga la l�mpara
 void setPuerta();  // Abre o cierra la puerta
 void escala(int selec,float x,float y,float z);  // Escala la escena, la l�mpara o los muebles
 void traslada(int selec,float x,float y,float z);  // Traslada la escena, la l�mpara o los muebles
 void rota(int selec,float a,float x,float y,float z);  // Rota la escena, la l�mpara o los muebles
 };

#endif
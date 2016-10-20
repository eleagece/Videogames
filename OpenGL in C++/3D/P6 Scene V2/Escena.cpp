#pragma hdrstop
#include "Escena.h"
#pragma package(smart_init)

//****************************************************************************//
//*** Constructoras y destructora ********************************************//
//****************************************************************************//
Escena::Escena()//:ObjetoCompuesto3D()
 {
 // habitación llena (se mete primero para que la luz vaya lo primero de todo)
 habL=new HabitacionL();
 objetos->push_back(habL);
 // habitación vacía
 habV=new HabitacionV();
 objetos->push_back(habV);
 }

//****************************************************************************//
//*** Métodos públicos *******************************************************//
//****************************************************************************//
void Escena::setTV()
 {
 habV->setTV();
 }

void Escena::setLamp()
 {
 habL->setLamp();
 }

void Escena::setPuerta()
 {
 habL->setPuerta();
 }

void Escena::escala(int selec, float x, float y, float z)
 {
 switch(selec)
  {
  case 1:
   getTAfin()->escala(x,y,z);
   break;
  case 2:
   habL->escalaMueble(x,y,z);
   break;
  case 3:
   habL->escalaLamp(x,y,z);
   break;
  }
 }

void Escena::traslada(int selec, float x, float y, float z)
 {
 switch(selec)
  {
  case 1:
   getTAfin()->traslada(x,y,z);
   break;
  case 2:
   habL->trasladaMueble(x,y,z);
   break;
  case 3:
   habL->trasladaLamp(x,y,z);
   break;
  }
 }

void Escena::rota(int selec, float a, float x, float y, float z)
 {
 switch(selec)
  {
  case 1:
   getTAfin()->rota(a,x,y,z);
   break;
  case 2:
   habL->rotaMueble(a,x,y,z);
   break;
  case 3:
   habL->rotaLamp(a,x,y,z);
  }
 }

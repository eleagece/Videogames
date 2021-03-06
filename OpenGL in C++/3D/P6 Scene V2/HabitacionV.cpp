#pragma hdrstop
#include "HabitacionV.h"
#pragma package(smart_init)

HabitacionV::HabitacionV()//:ObjetoCompuesto3D()
 {
 // sueloA
 Tablero* sueloA=new Tablero(17,2,8,16.5,0.2,8,"baldosa.bmp",0,0,0,0,0,1,true);
 sueloA->setColor(0.5,0.4,0.3);
 sueloA->getTAfin()->traslada(-3.5,4.8,-3.5);
 objetos->push_back(sueloA);
 // sueloB
 Tablero* sueloB=new Tablero(19,2,4,20,0.2,4,"baldosa.bmp",0,0,0,0,0,1,true);
 sueloB->setColor(0.5,0.4,0.3);
 sueloB->getTAfin()->traslada(-7.0,4.8,4.5);
 objetos->push_back(sueloB);
 // paredA
 Tablero* paredA=new Tablero(20,5,2,20,5,0.2);
 paredA->setColor(0.8,0.8,0.7);
 paredA->getTAfin()->traslada(-7.0,5,-3.7);
 objetos->push_back(paredA);
 // paredB
 Tablero* paredB=new Tablero(2,5,4,0.2,5,4);
 paredB->setColor(0.8,0.8,0.7);
 paredB->getTAfin()->traslada(-7.2,5,4.5);
 objetos->push_back(paredB);
 // paredC1
 Tablero* paredC1=new Tablero(2,2,4,0.2,1.5,4);
 paredC1->setColor(0.8,0.8,0.7);
 paredC1->getTAfin()->traslada(-7.2,8.5,0.5);
 objetos->push_back(paredC1);
 // paredC2
 Tablero* paredC2=new Tablero(2,2,4,0.2,2,4);
 paredC2->setColor(0.8,0.8,0.7);
 paredC2->getTAfin()->traslada(-7.2,5,0.5);
 objetos->push_back(paredC2);
 // paredD
 Tablero* paredD=new Tablero(2,5,4,0.2,5,4);
 paredD->setColor(0.8,0.8,0.7);
 paredD->getTAfin()->traslada(-7.2,5,-3.5);
 objetos->push_back(paredD);
 // cuadro
 Tablero* cuadro=new Tablero(4,3,2,3.7,2.5,0.2);
 cuadro->setColor(0.8,0.8,0);
 cuadro->getTAfin()->traslada(-5.7,6.7,-3.5);
 objetos->push_back(cuadro);
 // sofa
 Sofa* sofa=new Sofa();
 sofa->getTAfin()->traslada(8,5,4.0);
 sofa->getTAfin()->rota(-180,0,1,0);
 objetos->push_back(sofa);
 // Television
 tv=new Television();
 tv->getTAfin()->traslada(0.4,5.1,-3.5);
 objetos->push_back(tv);
 }

void HabitacionV::setTV()
 {
 this->tv->setTV();
 }


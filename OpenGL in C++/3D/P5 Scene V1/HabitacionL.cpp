#pragma hdrstop
#include "HabitacionL.h"
#pragma package(smart_init)

HabitacionL::HabitacionL()//:ObjetoCompuesto3D()
 {
 // suelo
 Tablero* suelo=new Tablero(20,2,12,20,0.2,12);
 suelo->setColor(0.5,0.4,0.3);
 suelo->getTAfin()->traslada(-7.0,-0.2,-3.5);
 objetos->push_back(suelo);
 // paredA
 Tablero* paredA=new Tablero(6,5,2,6,5,0.2);
 paredA->setColor(0.8,0.8,0.7);
 paredA->getTAfin()->traslada(-7.0,0,-3.7);
 objetos->push_back(paredA);
 // paredA1
 Tablero* paredA1=new Tablero(4,2,2,4,2,0.2);
 paredA1->setColor(0.8,0.8,0.7);
 paredA1->getTAfin()->traslada(-1.0,0,-3.7);
 objetos->push_back(paredA1);
 // paredA2
 Tablero* paredA2=new Tablero(4,2,2,4,1.5,0.2);
 paredA2->setColor(0.8,0.8,0.7);
 paredA2->getTAfin()->traslada(-1.0,3.5,-3.7);
 objetos->push_back(paredA2);
 // paredB
 Tablero* paredB=new Tablero(10,5,2,10,5,0.2);
 paredB->setColor(0.8,0.8,0.7);
 paredB->getTAfin()->traslada(3.0,0,-3.7);
 objetos->push_back(paredB);
 // paredC
 Tablero* paredC=new Tablero(2,5,12,0.2,5,12);
 paredC->setColor(0.8,0.8,0.7);
 paredC->getTAfin()->traslada(-7.2,0,-3.5);
 objetos->push_back(paredC);
 // paredD
 Tablero* paredD=new Tablero(2,5,6,0.2,5,6);
 paredD->setColor(0.8,0.8,0.7);
 paredD->getTAfin()->traslada(13,0,-3.5);
 objetos->push_back(paredD);
 // paredE
 Tablero* paredE=new Tablero(2,2,2,0.2,1,2);
 paredE->setColor(0.8,0.8,0.7);
 paredE->getTAfin()->traslada(13,4,2.5);
 objetos->push_back(paredE);
 // paredF
 Tablero* paredF=new Tablero(2,5,4,0.2,5,4);
 paredF->setColor(0.8,0.8,0.7);
 paredF->getTAfin()->traslada(13,0,4.5);
 objetos->push_back(paredF);
 // escalon1
 Tablero* escalon1=new Tablero(4,2,8,3.5,1,8);
 escalon1->setColor(0.3,0.2,0.1);
 escalon1->getTAfin()->traslada(-7,0,-3.5);
 objetos->push_back(escalon1);
 // escalon2
 Tablero* escalon2=new Tablero(4,2,7,3.5,1,7);
 escalon2->setColor(0.3,0.2,0.1);
 escalon2->getTAfin()->traslada(-7,1,-3.5);
 objetos->push_back(escalon2);
 // escalon3
 Tablero* escalon3=new Tablero(4,2,6,3.5,1,6);
 escalon3->setColor(0.3,0.2,0.1);
 escalon3->getTAfin()->traslada(-7,2,-3.5);
 objetos->push_back(escalon3);
 // escalon4
 Tablero* escalon4=new Tablero(4,2,5,3.5,1,5);
 escalon4->setColor(0.3,0.2,0.1);
 escalon4->getTAfin()->traslada(-7,3,-3.5);
 objetos->push_back(escalon4);
 // escalon5
 Tablero* escalon5=new Tablero(4,2,4,3.5,1,4);
 escalon5->setColor(0.3,0.2,0.1);
 escalon5->getTAfin()->traslada(-7,4,-3.5);
 objetos->push_back(escalon5);
 // est
 Estanteria* est=new Estanteria();
 est->getTAfin()->traslada(5,3,-3.5);
 objetos->push_back(est);
 // muebles
 muebles=new Muebles();
 objetos->push_back(muebles);
 // puerta
 puerta=new Puerta();
 puerta->getTAfin()->traslada(13,0.0,2.5);
 objetos->push_back(puerta);
 // lampara
 lampara=new Cilindro(1.5,1,0.6,10,10);
 lampara->setColor(0.8,0.8,0);
 lampara->getTAfin()->traslada(2.5,4.2,4);
 lampara->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(lampara);
 }

void HabitacionL::setPuerta()
 {
 this->puerta->setPuerta();
 }
 
void HabitacionL::escalaMueble(float x, float y, float z)
 {
 muebles->getTAfin()->escala(x,y,z);
 }

void HabitacionL::trasladaMueble(float x, float y, float z)
 {
 muebles->getTAfin()->traslada(x,y,z);
 }

void HabitacionL::rotaMueble(float a, float x, float y, float z)
 {
 muebles->getTAfin()->rota(a,x,y,z);
 }

void HabitacionL::escalaLamp(float x, float y, float z)
 {
 lampara->getTAfin()->rota(90,1,0,0);  // Recoloca la lámpara en posición inicial para poder hacer la escalación correctamente
 lampara->getTAfin()->escala(x,y,z);
 lampara->getTAfin()->rota(-90,1,0,0);  // Vuelve a colocar la lámpara de forma adecuada
 }

void HabitacionL::trasladaLamp(float x, float y, float z)
 {
 lampara->getTAfin()->rota(90,1,0,0);  // Recoloca la lámpara en posición inicial para poder hacer la traslación correctamente
 lampara->getTAfin()->traslada(x,y,z);
 lampara->getTAfin()->rota(-90,1,0,0);  // Vuelve a colocar la lámpara de forma adecuada
 }

void HabitacionL::rotaLamp(float a, float x, float y, float z)
 {
 lampara->getTAfin()->rota(90,1,0,0);  // Recoloca la lámpara en posición inicial para poder hacer la rotación correctamente
 lampara->getTAfin()->rota(a,x,y,z);
 lampara->getTAfin()->rota(-90,1,0,0);  // Vuelve a colocar la lámpara de forma adecuada
 }


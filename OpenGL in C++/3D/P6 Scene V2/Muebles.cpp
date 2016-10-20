#pragma hdrstop
#include "Muebles.h"
#pragma package(smart_init)

Muebles::Muebles()//:ObjetoCompuesto3D()
 {
 // Mesa
 Mesa* mesa=new Mesa();                                             
 mesa->getTAfin()->traslada(0,0,2.5);
 objetos->push_back(mesa);
 // Silla izquierda
 Silla* silla1=new Silla();
 silla1->getTAfin()->traslada(-2,0.0,3.25);
 //silla1->getTAfin()->rota(90,0,1,0);
 objetos->push_back(silla1);
 // Silla derecha
 Silla* silla2=new Silla();
 silla2->getTAfin()->traslada(7,0.0,4.75);
 silla2->getTAfin()->rota(180,0,1,0);
 objetos->push_back(silla2);
 // Copa izquierda
 Copa* copa1=new Copa(6,4,0.5);
 copa1->getTAfin()->traslada(1.2,1.7,5);
 copa1->setColor(0.1,0.1,0.1);
 objetos->push_back(copa1);
 // Copa derecha
 Copa* copa2=new Copa(6,4,0.5);
 copa2->getTAfin()->traslada(3.8,1.7,5);
 copa2->setColor(0.1,0.1,0.1);
 objetos->push_back(copa2);
 // plato1
 Disco* plato1=new Disco(0,0.6,10,10);
 plato1->setColor(0.1,0.1,0.1);
 plato1->getTAfin()->traslada(1.2,1.71,3.5);
 plato1->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(plato1);
 // plato2
 Disco* plato2=new Disco(0,0.6,10,10);
 plato2->setColor(0.1,0.1,0.1);
 plato2->getTAfin()->traslada(3.8,1.71,3.5);
 plato2->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(plato2);
 // hipotrocoide1
 Hipotrocoide3D* hipotrocoide1=new Hipotrocoide3D(5,15,5,3,5);
 hipotrocoide1->setColor(0,0.8,0);
 hipotrocoide1->getTAfin()->traslada(1.2,1.71,3.5);
 hipotrocoide1->getTAfin()->escala(0.05,0.05,0.05);
 objetos->push_back(hipotrocoide1);
 // hipotrocoide2
 Hipotrocoide3D* hipotrocoide2=new Hipotrocoide3D(5,15,5,3,5);
 hipotrocoide2->setColor(0,0.8,0);
 hipotrocoide2->getTAfin()->traslada(3.8,1.71,3.5);
 hipotrocoide2->getTAfin()->escala(0.05,0.05,0.05);
 objetos->push_back(hipotrocoide2);
 // sofa
 Sofa* sofa=new Sofa();
 sofa->getTAfin()->traslada(5,0.0,-3.0);
 sofa->getTAfin()->rota(-15,0,1,0);
 objetos->push_back(sofa);
 }

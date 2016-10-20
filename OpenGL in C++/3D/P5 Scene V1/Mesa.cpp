#pragma hdrstop
#include "Mesa.h"
#pragma package(smart_init)

Mesa::Mesa()//:ObjetoCompuesto3D()
 {
 // pata
 Cilindro* pata=new Cilindro(1,1,1.5,8,8);
 pata->setColor(0.3,0.2,0.1);      
 pata->getTAfin()->traslada(2.5,0,1.5);
 pata->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(pata);
 // tab
 Tablero* tab=new Tablero(5,2,2,5,0.2,3);
 tab->setColor(0.8,0.8,0);
 tab->getTAfin()->traslada(0,1.5,0);
 objetos->push_back(tab);
 }

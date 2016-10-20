//---------------------------------------------------------------------------
#pragma hdrstop    
#include "Circulo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Circulo::Circulo(vector<PuntoV*>* puntos,double grosor,bool rec)
{
        _id=1;
        _poli=new Corteza(puntos);
        if (rec) Recubre(grosor);
}
//---------------------------------------------------------------------------
Circulo::~Circulo()
{
        delete _poli;
        delete _corteza;
}
//---------------------------------------------------------------------------
bool Circulo::Colision(PuntoV* A,PuntoV* dir_in,PuntoV* nor_in,double& thit,PuntoV* nor,bool rec)
{
        if (!rec)
                {
                return _poli->cbeck(A,dir_in,nor_in,thit,nor);
        }else   return _corteza->cbeck(A,dir_in,nor_in,thit,nor);
}
//---------------------------------------------------------------------------
void Circulo::Dibuja()
{
        _poli->Dibuja();
        //_corteza->Dibuja();
}
//---------------------------------------------------------------------------
void Circulo::Recubre(double grosor)
{
        double k;
        vector<PuntoV*>* puntos=new vector<PuntoV*>();
        k=grosor/_poli->getNormal(0)->module();
        // Recubrir por la derecha
        PuntoV* p1=new PuntoV(_poli->getVer(0)->getX()+k*_poli->getNormal(0)->getX(),
                                _poli->getVer(0)->getY()+k*_poli->getNormal(0)->getY());
        PuntoV* p2=new PuntoV(_poli->getVer(1)->getX()+k*_poli->getNormal(0)->getX(),_poli->getVer(1)->getY()+k*_poli->getNormal(0)->getY());
        puntos->push_back(p1);
        puntos->push_back(p2);
        int fin=_poli->getLong()-1;
        for (unsigned int i=1; i<fin; i++){
                k=grosor/_poli->getNormal(i)->module();
                // Recubrir por la derecha
                p1=new PuntoV(_poli->getVer(i)->getX()+k*_poli->getNormal(i)->getX(),
                                _poli->getVer(i)->getY()+k*_poli->getNormal(i)->getY());
                p2=new PuntoV(_poli->getVer(i+1)->getX()+k*_poli->getNormal(i)->getX(),_poli->getVer(i+1)->getY()+k*_poli->getNormal(i)->getY());
                // Generar arco
                // TODO
                puntos->push_back(p1);
                puntos->push_back(p2);
        }
        // Última arista
        PuntoV* deb=_poli->getNormal(fin);
        k=grosor/deb->module();
        // Recubrir por la derecha
        p1=new PuntoV(_poli->getVer(fin)->getX()+k*_poli->getNormal(fin)->getX(),
                        _poli->getVer(fin)->getY()+k*_poli->getNormal(fin)->getY());
        p2=new PuntoV(_poli->getVer(0)->getX()+k*_poli->getNormal(fin)->getX(),_poli->getVer(0)->getY()+k*_poli->getNormal(fin)->getY());
        // Generar arco
        // TODO
        puntos->push_back(p1);
        puntos->push_back(p2);
        // Generar arco de cierre
        // TODO
        _corteza=new Corteza(puntos);


}
//---------------------------------------------------------------------------

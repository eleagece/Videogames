//---------------------------------------------------------------------------
#pragma hdrstop
#include "Corteza.h"       
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
Corteza::Corteza(vector<PuntoV*>* puntos)
{
        _vertices=puntos;
        _long=puntos->size();
        _normales=new vector<PuntoV*>();
        _dirs=new vector<PuntoV*>();
        PuntoV* dir;
        PuntoV* nor;
        for (unsigned int i=0; i<_vertices->size()-1; i++)
                {
                // Cálculo de las dirs
                PuntoV* act=_vertices->at(i);
                PuntoV* sig=_vertices->at(i+1);
                dir=new PuntoV(sig->getX()-act->getX(),
                                sig->getY()-act->getY());
                _dirs->push_back(dir);
                // Cálculo de las normales
                nor=new PuntoV(dir->getY(),-dir->getX());
                _normales->push_back(nor);
                }
        // Última arista
        dir=new PuntoV(_vertices->at(0)->getX()-_vertices->at(_vertices->size()-1)->getX(),
                        _vertices->at(0)->getY()-_vertices->at(_vertices->size()-1)->getY());
        _dirs->push_back(dir);
        nor=new PuntoV(dir->getY(),-dir->getX());
        _normales->push_back(nor);

}
//---------------------------------------------------------------------------
Corteza::~Corteza()
{
        for (unsigned int i=0; i<_vertices->size(); i++)
                {
                delete _vertices->at(_vertices->size()-i-1);
                }
        delete _vertices;
        for (unsigned int i=0; i<_normales->size(); i++)
                {
                delete _normales->at(_normales->size()-i-1);
                }
        delete _normales;
        for (unsigned int i=0; i<_dirs->size(); i++)
                {
                delete _dirs->at(_dirs->size()-i-1);
                }
        delete _dirs;
}
//---------------------------------------------------------------------------
void Corteza::Dibuja()
{       /*
        glBegin(GL_LINES);
        PuntoV* aux;
        for (unsigned int i=0;i<_vertices->size()-1;i++)
                {
                aux=_vertices->at(i);
                glVertex2d(aux->getX(),aux->getY());
                aux=_vertices->at(i+1);
                glVertex2d(aux->getX(),aux->getY());
                }
        aux=_vertices->at(_vertices->size()-1);
        glVertex2d(aux->getX(),aux->getY());
        aux=_vertices->at(0);
        glVertex2d(aux->getX(),aux->getY());
        glEnd();
        */
        /*
        // DEBUG: dibujo de normales desde el centro del segmento
        for (unsigned int i=0;i<_vertices->size();i++){
        PuntoV* mid=new PuntoV(_vertices->at(i)->getX()+_dirs->at(i)->getX()/2.0,_vertices->at(i)->getY()+_dirs->at(i)->getY()/2.0);
                glBegin(GL_LINES);
                        glVertex2f(mid->getX(),mid->getY());
                        glVertex2f(mid->getX()+_normales->at(i)->getX(),mid->getY()+_normales->at(i)->getY());
                glEnd();
        delete mid;
        }*/

        glBegin(GL_POLYGON);
        for (unsigned int i=0;i<_vertices->size();i++)
                {
                glVertex2d(_vertices->at(i)->getX(),_vertices->at(i)->getY());
                }
        glEnd();
}
//---------------------------------------------------------------------------
bool Corteza::cbeck(PuntoV* A,PuntoV* dir_in,PuntoV* nor_in,double& thit,PuntoV* nor)
{
        PuntoV* n;
        PuntoV* p;
        PuntoV* v;
        PuntoV* BA=new PuntoV(0,0);
        double tin=-250.0;
        double tout=250.0;
        double denom;
        double numer;
        double taux;
        for (unsigned int i=0; i<_vertices->size();i++){
                n=_normales->at(i);
                p=_vertices->at(i);
                //v=_dirs->at(i);
                denom=n->dot(dir_in);
                BA->setX(p->getX()-A->getX());
                BA->setY(p->getY()-A->getY());
                numer=n->dot(BA);
                if (denom==0 && numer<=0) {delete BA; return false;} // Segmento paralelo exterior a uno de los lados
                if (denom!=0){
                        taux=numer/denom;
                        if (denom<0){ // Segmento entrando
                                if (taux>tout) {delete BA; return false;}
                                if (taux>tin){ // Actualizar tin y la normal de impacto
                                        tin=taux;
                                        nor->setX(n->getX());
                                        nor->setY(n->getY());
                                }
                        }
                        if (denom>0){ // Segmento saliendo
                                if (taux<tin) {delete BA; return false;}
                                tout=min(tout,taux);
                        }
                }
        }
        if (tin>0 && tin<thit){
                thit=tin;
                delete BA;
                return true;
        }
        {delete BA; return false;}
        /*
        bool exito=false;
        PuntoV* BA;
        double thit1;
        double thit2;
        for (unsigned int i=0; i<_vertices->size();i++)
        {
        // TODO: GENERAL
        // ENTRADA: VECTOR DE ENTRADA
        // SALIDA: ÉXITO O FRACASO, NORMAL DE IMPACTO
                PuntoV* t1=_normales->at(i);
                PuntoV* t2=_vertices->at(i);
                PuntoV* t3=_dirs->at(i);
                double denom=_normales->at(i)->dot(dir_in);
                BA=new PuntoV(_vertices->at(i)->getX()-A->getX(),_vertices->at(i)->getY()-A->getY());
                double number=_normales->at(i)->dot(BA);
                if (denom!=0 && (number<0.0)) // No son paralelas y está a la derecha
                        {
                        // IMPACTO POSIBLE
                        // Calculamos thit2
                        double thit2=number/denom;
                        if (denom<0){ // Entrando
                        if (thit2>0.0 && thit2<thit){
                                // LAS DIRECCIONES SE CRUZAN
                                denom=_dirs->at(i)->dot(nor_in);
                                BA->setX(A->getX()-_vertices->at(i)->getX());
                                BA->setY(A->getY()-_vertices->at(i)->getY());
                                number=BA->dot(nor_in);
                                double thit1=number/denom;
                                        if (0.0<thit1 && thit1<1.0){
                                                nor->setX(_normales->at(i)->getX());
                                                nor->setY(_normales->at(i)->getY());
                                                thit=thit2;
                                                exito=true;
                                        }
                                }
                        }
                }
        delete BA;
        }
        return exito;
        */
}
//---------------------------------------------------------------------------

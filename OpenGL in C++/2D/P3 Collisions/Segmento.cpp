//------------------------------------------------------------ ---------------
#pragma hdrstop
#include "Segmento.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Segmento::Segmento(PuntoV* ini,PuntoV* fin,double grosor,bool rec)
{
        _id=0;
        _ini=ini;
        _fin=fin;
        _dir=new PuntoV(fin->getX()-ini->getX(),fin->getY()-ini->getY());
        _nor=new PuntoV(_dir->getY(),-_dir->getX());
        if (rec) Recubre(grosor);
}
//---------------------------------------------------------------------------
Segmento::~Segmento()
{
        delete _ini;
        delete _fin;
        delete _dir;
        delete _nor;
        delete _corteza;
}
//---------------------------------------------------------------------------
bool Segmento::Colision(PuntoV* A,PuntoV* dir_in,PuntoV* nor_in,double& thit,PuntoV* nor,bool rec)
{
        if (!rec){
        // ALGORITMO GENERAL SEGMENTO VS SEGMENTO
        /*
        double denom=_nor->dot(dir_in);
        PuntoV* BA=new PuntoV(_ini->getX()-A->getX(),_ini->getY()-A->getY());
        double number=_nor->dot(BA);
        double thit2;
        double thit1;
        if (denom!=0) {
                // IMPACTO POSIBLE, LAS DIRECCIONES SE CRUZAN
                // Calculamos THIT2 (EL DE ENTRADA)
                thit2=number/denom;
                if (thit2<=0 || thit2>=1)
                        {delete BA; return false;}
                // Calculamos THIT1 (EL DEL PROPIO SEGMENTO)
                denom=_dir->dot(nor_in);
                BA->setX(A->getX()-_ini->getX());
                BA->setY(A->getY()-_ini->getY());
                number=BA->dot(nor_in);
                thit1=number/denom;
                if (thit1<0 || thit1>1)
                        {delete BA; return false;}
                nor->setX(_nor->getX());
                nor->setY(_nor->getY());
                thit=thit2;
                delete BA;
                return true;
        } else {
                delete BA;
                return false;
                }
        */
        double denom=_nor->dot(dir_in);
        PuntoV* BA=new PuntoV(_ini->getX()-A->getX(),_ini->getY()-A->getY());
        double number=_nor->dot(BA);
        if (denom!=0 && (number<-0.002 || number>0.002)) {
                // IMPACTO POSIBLE
                // Calculamos thit2
                double thit2=number/denom;
                if (0.0<thit2 && thit2<1.0){
                        // LAS DIRECCIONES SE CRUZAN
                        denom=_dir->dot(nor_in);
                        BA->setX(A->getX()-_ini->getX());
                        BA->setY(A->getY()-_ini->getY());
                        number=BA->dot(nor_in);
                        double thit1=number/denom;
                        if (0.0<thit1 && thit1<1.0){
                                nor->setX(_nor->getX());
                                nor->setY(_nor->getY());
                                thit=thit2;
                                delete BA;
                                return true;
                                }
                        else {delete BA; return false;}
                        }
                else {delete BA; return false;}
        }
        delete BA;
        return false;
        }
        else return _corteza->cbeck(A,dir_in,nor_in,thit,nor);
}
//---------------------------------------------------------------------------
void Segmento::Dibuja()
{
        glBegin(GL_LINES);
        glVertex2f(_ini->getX(),_ini->getY());
        glVertex2f(_fin->getX(),_fin->getY());
        glEnd();
        /*
        // DEBUG: dibujo de normales desde el centro del segmento
        PuntoV* mid=new PuntoV(_ini->getX()+_dir->getX()/2.0,_ini->getY()+_dir->getY()/2.0);
        glBegin(GL_LINES);
        glVertex2f(mid->getX(),mid->getY());
        glVertex2f(mid->getX()+_nor->getX(),mid->getY()+_nor->getY());
        glEnd();
        delete mid;
        */

        // DEBUG: DIBUJO DE CORTEZA
        //_corteza->Dibuja();
}
//---------------------------------------------------------------------------
void Segmento::Recubre(double grosor)
{
        double k=grosor/_nor->module();
        vector<PuntoV*>* puntos=new vector<PuntoV*>();
        // Recubrir por la derecha
        PuntoV* di=new PuntoV(_ini->getX()+k*_nor->getX(),_ini->getY()+k*_nor->getY());
        PuntoV* df=new PuntoV(_fin->getX()+k*_nor->getX(),_fin->getY()+k*_nor->getY());
        PuntoV* ii=new PuntoV(_fin->getX()-k*_nor->getX(),_fin->getY()-k*_nor->getY());
        PuntoV* ifi=new PuntoV(_ini->getX()-k*_nor->getX(),_ini->getY()-k*_nor->getY());
        puntos->push_back(di);
        puntos->push_back(df);
        // Arco para borde izquierdo (desde df a ii)
        //trazaArco(df,ii,_fin,puntos);
        // Recubrir por la izquierda
        puntos->push_back(ii);
        puntos->push_back(ifi);
        // Arco para borde derecho (desde ifi a di)
        //trazaArco(ifi,di,_ini,puntos);
        // Creamos la corteza con los puntos obtenidos
        _corteza=new Corteza(puntos);
}
//---------------------------------------------------------------------------

void Segmento::trazaArco(PuntoV* inicio,PuntoV* fin,PuntoV* centro,vector<PuntoV*>* lista)
{
        // Ángulo total: inicio con respecto al fin
        double x1=inicio->getX()-centro->getX();
        double y1=inicio->getY()-centro->getY();
        PuntoV* p1=new PuntoV(x1,y1);
        double x2=fin->getX()-centro->getX();
        double y2=fin->getY()-centro->getY();
        PuntoV* p2=new PuntoV(x2,y2);
        double total=p1->alpha(p2);
        // Radio
        double radio=p1->module();
        // Ángulo offset: p1 respecto al eje x
        PuntoV* ejex=new PuntoV(500,0);
        double offset=ejex->alpha(p1);
        delete p1;
        delete p2;
        delete ejex;
        // Procedemos a crear el arco
        PuntoV* aux;
        double x;
        double y;
        double angulo;
        double dx;
        double dy;
        for (int i=1;i<5;i++){
                angulo=(offset+(i*total/5))*(M_PI/180.0);
                dx=radio*cos(angulo);
                dy=radio*sin(angulo);
                x=centro->getX()+dx;
                y=centro->getY()+dy;
                aux=new PuntoV(x,y);
                lista->push_back(aux);
        }
}
//---------------------------------------------------------------------------


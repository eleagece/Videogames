//---------------------------------------------------------------------------
#pragma hdrstop                                
#include "Escena.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Escena::Escena()
{
        _centro=new PuntoV(BALLINIX,BALLINIY);
        _ball=NULL;
        _recubrimiento=false;
 freno=true;
 fuerzaFreno=CT;
        GeneraCampo();
        x=0;
        y=0;
        testigo=0;
}
//---------------------------------------------------------------------------
Escena::~Escena()
{
        for (unsigned int i=0; i<_obs.size(); i++)
                {
                if (_obs.at(_obs.size()-i-1)->getId()==0)
                        delete (Segmento*) _obs.at(_obs.size()-i-1);
                else delete (Convexo*) _obs.at(_obs.size()-i-1);
                }
        delete _ball;
        delete _centro;
}
//---------------------------------------------------------------------------
void Escena::dibuja()
{
        // Dibujamos la pelota (VERDE)
        glColor3f(1,1,1);
        if (_ball!=NULL) _ball->Dibuja();
        // Dibujamos el campo (ROJO)
        glColor3f(1,1,0);
        for (unsigned int i=0; i<_obs.size(); i++)
                {
                _obs.at(i)->Dibuja();
                }
        // Dibujamos el origen de la pelota
        //_centro->dibuja(5,0,0,1);
        glColor3f(1,0,0);
             if (testigo>=1 && testigo<=400)  // Arriba
              {
              x=testigo-200;
              y=206;
              glBegin(GL_LINES);
               glVertex2i(x,y);
               glVertex2i(x,y+10);
              glEnd();
              }
             else if (testigo>=401 && testigo<=800)  // Derecha
              {
              x=206;
              y=testigo-400+(199-((testigo-400)*2));
              glBegin(GL_LINES);
               glVertex2i(x,y);
               glVertex2i(x+10,y);
              glEnd();
              }
             else if (testigo>=801 && testigo<=1200)  // Abajo
              {
              x=testigo-800+(199-((testigo-800)*2));
              y=-206;
              glBegin(GL_LINES);
               glVertex2i(x,y);
               glVertex2i(x,y-10);
              glEnd();
              }
             else if (testigo>=1201 && testigo<=1600)  // Izquierda
              {
              x=-206;
              y=testigo-200-1201;
              glBegin(GL_LINES);
               glVertex2i(x,y);
               glVertex2i(x-10,y);
              glEnd();
              }

}

void Escena::DaTestigo(int t)
 {
 testigo=t;
 }
//---------------------------------------------------------------------------
vector<PuntoV*>* Escena::aproxPelota(PuntoV* centro,double radio)
{
        // El número de lados es proporcional al radio
        int nlados=(int)radio;
        // ALPHA es el ángulo cuyo vértice es el centro de la circunferencia
        // que circunscribe al polígono regular.
        // BETHA son los otros 2 ángulos del triángulo que se forman al unir ese
        // centro con 2 vértices consecutivos.
        // GAMMA es el ángulo de dirección inicial para el lápiz
        GLdouble alphaRad=(2.0*M_PI)/(double)nlados;
        GLdouble bethaRad=(M_PI-alphaRad)/2.0;
        GLdouble gammaRad=M_PI-bethaRad;
        GLdouble gamma=gammaRad*(180.0/M_PI);
        GLdouble alpha=alphaRad*(180.0/M_PI);
        GLdouble lado=radio*cos(bethaRad)*2.0;
        //GLfloat radio=(lado/2.0)/cos(bethaRad);
        
        // Establecemos el origen del dibujo.
        PuntoV* origen=new PuntoV(centro->getX()+radio,centro->getY());
        vector<PuntoV*>* puntos=new vector<PuntoV*>();
        puntos->push_back(origen);

        // Ya tenemos el punto de origen y el ángulo de giro.
        // Procedemos a construirlo mediante lápiz
        Lapiz* l=new Lapiz(new PuntoV(centro->getX()+radio,centro->getY()),gamma);
        for (int i=0; i<nlados; i++){
                PuntoV* ori=new PuntoV(l->getPos());
                l->mover(lado,false);
                // Añadimos el nuevo punto
                puntos->push_back(ori);
                l->girar(alpha);
        }
        delete l;
        return puntos;
}
//---------------------------------------------------------------------------
void Escena::GeneraPelota(PuntoV* c,double r/*,int angulo*/)
{
        // Generar dirección de movimiento aleatoria
        // Velocidad definida igual al radio
        // Elegimos aleatoriamente un ángulo de salida en grados
        int alpha=360;
        //int alpha=std::random(360);
        PuntoV* ori=new PuntoV(_centro->getX(),_centro->getY());
        Lapiz* l=new Lapiz(ori,alpha);
        l->mover(RADIO,false);
        PuntoV* dir=new PuntoV(l->getPos()->getX()-_centro->getX(),
                                l->getPos()->getY()-_centro->getY());
        delete l;
        // Generar la pelota
        vector<PuntoV*>* puntos=aproxPelota(c,r);
        _ball=new Pelota(puntos,r,c,dir);
}

void Escena::GeneraPelota2(PuntoV* c, double alpha, double r)
{
        PuntoV* ori=new PuntoV(c->getX(),c->getY());
        Lapiz* l=new Lapiz(ori,alpha);
        l->mover(RADIO,false);
        PuntoV* dir=new PuntoV(l->getPos()->getX()-c->getX(),
                                l->getPos()->getY()-c->getY());
        delete l;
        // Generar la pelota
        vector<PuntoV*>* puntos=aproxPelota(c,r);
        _ball=new Pelota(puntos,r,c,dir);
}
//---------------------------------------------------------------------------
void Escena::GeneraCampo()
{
        // Bordes del tablero: segmentos
        /*
        Obstaculo* lado;
        double x,y,dx,dy;
        for (int i=1; i<5; i++){
                switch (i){
                        case 1: x=250.0; y=250.0; dx=250.0; dy=-250.0; break;
                        case 2: x=250.0; y=-250.0; dx=-250.0; dy=-250.0; break;
                        case 3: x=-250.0; y=-250.0; dx=-250.0; dy=250.0; break;
                        case 4: x=-250.0; y=250.0; dx=250.0; dy=250.0; break;
                }
                lado=new Segmento(new PuntoV(x,y),new PuntoV(dx,dy),RADIO,true);
                _obs.push_back(lado);
        }

        Segmento* aux1= new Segmento(new PuntoV(60,-160.0),new PuntoV(195.0,-100.0),RADIO,true);
        _obs.push_back(aux1);*/

 vector<PuntoV*>* bordeSup=new vector<PuntoV*>();
        bordeSup->push_back(new PuntoV(200,200));
        bordeSup->push_back(new PuntoV(200,205));
        bordeSup->push_back(new PuntoV(-200,205));
        bordeSup->push_back(new PuntoV(-200,200));
        _obs.push_back(new Convexo(bordeSup,RADIO,true));
 vector<PuntoV*>* bordeInf=new vector<PuntoV*>();
        bordeInf->push_back(new PuntoV(-200,-200));
        bordeInf->push_back(new PuntoV(-200,-205));
        bordeInf->push_back(new PuntoV(200,-205));
        bordeInf->push_back(new PuntoV(200,-200));
        _obs.push_back(new Convexo(bordeInf,RADIO,true));
 vector<PuntoV*>* bordeDer=new vector<PuntoV*>();
        bordeDer->push_back(new PuntoV(200,205));
        bordeDer->push_back(new PuntoV(200,-205));
        bordeDer->push_back(new PuntoV(205,-205));
        bordeDer->push_back(new PuntoV(205,205));
        _obs.push_back(new Convexo(bordeDer,RADIO,true));
 vector<PuntoV*>* bordeIzq=new vector<PuntoV*>();
        bordeIzq->push_back(new PuntoV(-200,205));
        bordeIzq->push_back(new PuntoV(-205,205));
        bordeIzq->push_back(new PuntoV(-205,-205));
        bordeIzq->push_back(new PuntoV(-200,-205));
        _obs.push_back(new Convexo(bordeIzq,RADIO,true));

        // Circulo:
        PuntoV* c=new PuntoV(0.0,0.0);
        vector<PuntoV*>* aux4=nuevoReg(c,30,10);
        _obs.push_back(new Convexo(aux4,RADIO,true));

        // Convexos:
        PuntoV* d=new PuntoV(91,-110);
        vector<PuntoV*>* aux5=nuevoReg(d,4,50);
        _obs.push_back(new Convexo(aux5,RADIO,true));

        vector<PuntoV*>* aux2=new vector<PuntoV*>();
        aux2->push_back(new PuntoV(150.0,85.0));
        aux2->push_back(new PuntoV(150.0,150.0));
        aux2->push_back(new PuntoV(15.0,150.0));
        _obs.push_back(new Convexo(aux2,RADIO,true));

        vector<PuntoV*>* aux3=new vector<PuntoV*>();
        aux3->push_back(new PuntoV(-150.0,-150.0));
        aux3->push_back(new PuntoV(15.0,-150.0));
        aux3->push_back(new PuntoV(-150.0,-60.0));
        _obs.push_back(new Convexo(aux3,RADIO,true));
}
//---------------------------------------------------------------------------
void Escena::inicia1(bool rec)
{
        delete _ball;
        _recubrimiento=rec;
        PuntoV* c=new PuntoV(_centro->getX(),_centro->getY());
        GeneraPelota(c,RADIO);
}

void Escena::IniciaTiro(bool rec)
 {
 _recubrimiento=rec;
 PuntoV* c;
 PuntoV* d;
 if (_ball==NULL)
  {
  c=new PuntoV(_centro->getX(),_centro->getY());
  d=new PuntoV(x-_centro->getX(),y-_centro->getY());
  }
 else
  {
  c=new PuntoV(_ball->getCentro()->getX(),_ball->getCentro()->getY());
  d=new PuntoV(x-c->getX(),y-c->getY());
  }
 PuntoV* plano=new PuntoV(1,0);
 double angulo=plano->alpha(d);
 if (y<c->getY())
  angulo=-angulo;
 delete _ball;
 delete plano;
 delete d;
 fuerzaFreno=CT;
 GeneraPelota2(c,angulo,RADIO);
 }

//---------------------------------------------------------------------------
void Escena::timeout()
{
        if (_ball!=NULL)
        {
        // Comprobar colisiones con obstáculos
        bool exito=false;
        PuntoV* normal=new PuntoV(0.0,0.0);
        PuntoV* normal_aux=new PuntoV(0.0,0.0);
        double thit=CT;
        double thit_aux=CT;
        for (unsigned int i=0; i<_obs.size(); i++)
                {
                if(_obs.at(i)->Colision(_ball->getCentro(),_ball->getDir(),_ball->getNormal(),thit_aux,normal_aux,_recubrimiento))
                        {
                        if (thit_aux<thit)
                                {
                                thit=thit_aux;
                                normal->setX(normal_aux->getX());
                                normal->setY(normal_aux->getY());
                                exito=true;
                                }
                        }
                }
        // Avanzar la pelota thit
                if (freno && fuerzaFreno>0)
                {
                _ball->Avanzar(fuerzaFreno-0.005);
                fuerzaFreno=fuerzaFreno-0.005;
                }
               else if (freno)
                  _ball->Avanzar(0);
                 else
                  _ball->Avanzar(thit); // Calcular dirección de rebote */
        if (exito)
                {
                double k=2.0*(_ball->getDir()->dot(normal)/normal->dot(normal));
                double x=_ball->getDir()->getX()-k*normal->getX();
                double y=_ball->getDir()->getY()-k*normal->getY();
                _ball->setDir(new PuntoV(x,y));
                }
        delete normal;
        delete normal_aux;
        }
}
//---------------------------------------------------------------------------
vector<PuntoV*>* Escena::nuevoReg(PuntoV* centro,int nlados,double lado)
{      
        // ALPHA es el ángulo cuyo vértice es el centro de la circunferencia
        // que circunscribe al polígono regular.
        // BETHA son los otros 2 ángulos del triángulo que se forman al unir ese
        // centro con 2 vértices consecutivos.
        // GAMMA es el ángulo de dirección inicial para el lápiz
        GLdouble alphaRad=(2.0*M_PI)/(double)nlados;
        GLdouble bethaRad=(M_PI-alphaRad)/2.0;
        GLdouble gammaRad=M_PI-bethaRad;
        GLdouble gamma=gammaRad*(180.0/M_PI);
        GLdouble alpha=alphaRad*(180.0/M_PI);
        GLdouble radio=(lado/2.0)/cos(bethaRad);
        // Establecemos el origen del dibujo.
        PuntoV* origen=new PuntoV(centro->getX()+radio,centro->getY());
        delete centro;
        vector<PuntoV*>* aux=new vector<PuntoV*>();
        aux->push_back(new PuntoV(origen));
        // Ya tenemos el punto de origen y el ángulo de giro.
        // Procedemos a construirlo mediante lápiz
        Lapiz* l=new Lapiz(origen,gamma);
        for (int i=0; i<nlados; i++){
                l->mover(lado,false);
                PuntoV* ori=new PuntoV(l->getPos());
                // Añadir arista
                aux->push_back(ori);
                l->girar(alpha);
        }
        delete l;
        return aux;
}

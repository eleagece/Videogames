//---------------------------------------------------------------------------
#pragma hdrstop
#include "Espiral.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Espiral::Espiral(int np,int nq,double r):Malla()
{
        base=new vector<PV3d*>();
        // Generamos la circunferencia base de la espiral
        this->genCirculo(np,r);
        radio=r;
        double t=0;
        // Aplicamos nq veces el marco de frenet
        for (int i=0; i<nq; i++)
        {
                // Aplicamos Frenet a cada punto del polígono inicial
                for (int j=0; j<np; j++)
                {
                        PV3d* p=this->marcoFrenet(base->at(j),t);
                        tv->push_back(p);
                }
                if (i>0) //this->genMallaCil4(np);
                        this->genMallaCil3(np);
                t+=inc;
        }

        /* Creamos la esfera */
        esfera=gluNewQuadric();
        gluQuadricDrawStyle(esfera,GLU_LINE);
        rot=param=0;
        this->avanzaEsfera();

}
//---------------------------------------------------------------------------
Espiral::~Espiral()
{
        for (unsigned int i=0; i<base->size(); i++)
        {
                delete base->at(i);
        }
        delete base;
        gluDeleteQuadric(esfera);
}
//---------------------------------------------------------------------------
PV3d* Espiral::marcoFrenet(PV3d* p,double t)
{
        PV3d* q;
        double x,y,z=0;
        double px=p->getX();
        double py=p->getY();
        double pz=p->getZ();
        x=(-t+px)*cos(t)+(pz+1)*sin(t);
        //x=px*cos(t)+pz*sin(t)+sin(t)-t*cos(t);
        y=(pz-1)*cos(t)+(-t+px)*sin(t);
        //y=px*sin(t)-pz*cos(t)-cos(t)-t*sin(t);
        z=py;
        // Creamos el punto
        q=new PV3d(x,y,z,1);
        return q;
}
//---------------------------------------------------------------------------
void Espiral::genCirculo(int np,double r)
{
        double alpha=(360.0/(double)np)*(M_PI/180.0);
        double sum=0.0;
        double x,y,z;
        for (int i=0; i<np; i++)
        {
                x=r*cos(sum);
                y=-r*sin(sum);
                sum+=alpha;
                base->push_back(new PV3d(x,y,0,1));
        }
}
//---------------------------------------------------------------------------
void Espiral::dibujaEsfera()
{
        glColor4f(1.0,0.0,0.0,1.0);
        glPushMatrix();
        // Aplicamos traslación a lo largo de la espiral
        glTranslatef(posx,posy,0);
        // Aplicamos rotación sobre su propio eje
        glRotatef(rot,0,1,0);
        // Situamos polos en la parte superior e inferior
        glRotatef(90,1,0,0);
        gluSphere(esfera,radio*0.7,20,20);
        glPopMatrix();
        glColor4f(1.0,1.0,1.0,1.0);
}
//---------------------------------------------------------------------------
void Espiral::avanzaEsfera()
{
        param+=inc;
        if (param<0) param=0;
        posx=sin(param)-(param)*cos(param);
        posy=-cos(param)-(param)*sin(param);
}
//---------------------------------------------------------------------------
void Espiral::retrocedeEsfera()
{
        param-=inc;
        if (param<0) param=0;
        posx=sin(param)-(param)*cos(param);
        posy=-cos(param)-(param)*sin(param);
}
//---------------------------------------------------------------------------
void Espiral::rotaRight()
{
        rot+=incRot;
}
//---------------------------------------------------------------------------
void Espiral::rotaLeft()
{
        rot-=incRot;
}
//---------------------------------------------------------------------------
void Espiral::reiniciaEsfera()
{
        param=rot=0;
        this->avanzaEsfera();
}
//---------------------------------------------------------------------------

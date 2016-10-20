//---------------------------------------------------------------------------
#pragma hdrstop
#include "Cubo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Cubo::Cubo(int nx, int ny, int nz):Malla()
{
        this->nx=nx;
        this->ny=ny;
        this->nz=nz;
        PV3d* n=new PV3d(0,-1,0,0);
        this->genBase(0,n);
        delete n;
        n=new PV3d(0,1,0,0);
        this->genBase(1,n);
        delete n;
        n=new PV3d(0,0,-1,0);
        this->genFrente(0,n);
        delete n;
        n=new PV3d(0,0,1,0);
        this->genFrente(1,n);
        delete n;
        n=new PV3d(-1,0,0,0);
        this->genLado(0,n);
        delete n;
        n=new PV3d(1,0,0,0);
        this->genLado(1,n);
        delete n;

}
//---------------------------------------------------------------------------
void Cubo::dibujaPeana()
{
        glPushMatrix();
        glScalef(ANCHO,ALTO,LARGO);
        glTranslatef(-0.5,0,-0.5);
        this->dibuja();
        glPopMatrix();
}
//---------------------------------------------------------------------------
void Cubo::genBase(double h,PV3d* n)
{
        double xMin=0;
        double zMin=0;
        //int numV=nx*nz;
        //int numN=numV;
        //int numC=(nx-1)*(nz-1);
        double incX=1.0/(nx-1);
        double incZ=1.0/(nz-1);
        double x=xMin;
        for (int i=0; i<nx; i++)
        {
                double z=zMin;
                for (int j=0; j<nz; j++)
                {
                        //int indiceV=i*nz+j;
                        tv->push_back(new PV3d(x,h,z,1));
                        if (i>0 && j>0)
                        {
                                //int indiceC=(i-1)*(nz-1)+(j-1);
                                Cara* c=new Cara();
                                c->addV(tv->size()-1);
                                c->addV(tv->size()-1-nz);
                                c->addV(tv->size()-1-nz-1);
                                c->addV(tv->size()-1-1);
                                tn->push_back(new PV3d(n->getX(),n->getY(),n->getZ(),0));
                                //PV3d* no=this->normalNewell(c);
                                //tn->push_back(no);
                                c->setN(tn->size()-1);
                                tc->push_back(c);
                        }
                        z+=incZ;
                }
                x+=incX;
        }
}
//---------------------------------------------------------------------------
void Cubo::genFrente(double h,PV3d* n)
{
        double xMin=0;
        double yMin=0;
        //int numV=nx*ny;
        //int numN=numV;
        //int numC=(nx-1)*(ny-1);
        double incX=1.0/(nx-1);
        double incY=1.0/(ny-1);
        double x=xMin;
        for (int i=0; i<nx; i++)
        {
                double y=yMin;
                for (int j=0; j<ny; j++)
                {
                        //int indiceV=i*ny+j;
                        tv->push_back(new PV3d(x,y,h,1));
                        if (i>0 && j>0)
                        {
                                //int indiceC=(i-1)*(ny-1)+(j-1);
                                Cara* c=new Cara();
                                c->addV(tv->size()-1);
                                c->addV(tv->size()-1-ny);
                                c->addV(tv->size()-1-ny-1);
                                c->addV(tv->size()-1-1);
                                tn->push_back(new PV3d(n->getX(),n->getY(),n->getZ(),0));
                                c->setN(tn->size()-1);
                                tc->push_back(c);
                        }
                        y+=incY;
                }
                x+=incX;
        }
}
//---------------------------------------------------------------------------
void Cubo::genLado(double h,PV3d* n)
{
        double yMin=0;
        double zMin=0;
        //int numV=ny*nz;
        //int numN=numV;
        //int numC=(ny-1)*(nz-1);
        double incY=1.0/(ny-1);
        double incZ=1.0/(nz-1);
        double y=yMin;
        for (int i=0; i<ny; i++)
        {
                double z=zMin;
                for (int j=0; j<nz; j++)
                {
                        //int indiceV=i*nz+j;
                        tv->push_back(new PV3d(h,y,z,1));
                        if (i>0 && j>0)
                        {
                                //int indiceC=(i-1)*(nz-1)+(j-1);
                                Cara* c=new Cara();
                                c->addV(tv->size()-1);
                                c->addV(tv->size()-1-nz);
                                c->addV(tv->size()-1-nz-1);
                                c->addV(tv->size()-1-1);
                                tn->push_back(new PV3d(n->getX(),n->getY(),n->getZ(),0));
                                c->setN(tn->size()-1);
                                tc->push_back(c);
                        }
                        z+=incZ;
                }
                y+=incY;
        }
}
//---------------------------------------------------------------------------

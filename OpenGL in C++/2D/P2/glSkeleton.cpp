//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("glSkeleton.res");
USEFORM("UFP.cpp", GLForm2D);
USEUNIT("Lista.cpp");
USEUNIT("Nodo.cpp");
USEUNIT("Escena.cpp");
USEUNIT("Segmento.cpp");
USEUNIT("PuntoVector.cpp");
USEUNIT("Hipotrocoide.cpp");
USEUNIT("DibujoLineas.cpp");
USEUNIT("Lapiz.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGLForm2D), &GLForm2D);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------

#include "main.h"

#ifdef XX_EXE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // TESTS HERE ====================================

    xx::XMLParser parser = xx::XMLParser ("network.config");
    if (!parser.parse ())
        XX_ERROR ("Parsing xml file failed!");
    else
        parser.printAll ();

    // ===============================================

    return 0;
}

#endif // XX_EXE
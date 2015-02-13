#include "main.h"

#ifdef XX_EXE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Test here:
    XMLParser parser = XMLParser ("network.config");
    parser.parse ();
    parser.printAll ();
}

#endif // XX_EXE
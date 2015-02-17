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

    xx::QuickMenu * qm = xx::xxQM::create ();
    xx::XMLParser parser = xx::XMLParser ("menu.xml");
    parser.parse ();

    qm->setScheme (parser.getScheme ());
    

    // ===============================================

    return 0;
}

#endif // XX_EXE
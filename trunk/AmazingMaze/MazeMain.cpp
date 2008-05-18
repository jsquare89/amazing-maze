#include "Precompiled.hpp"
#include "MazeMain.hpp"
#include "MainWindow.hpp"
#include "Egl/Context.hpp"	
#include "Egl/SurfaceProperties.hpp"	
#include <ctime>

namespace AmazingMaze
{
    // static 
    const char * CApp::MAIN_WINDOW_TITLE = "Main Window";

    CApp::CApp(void) : m_pContext(new Egl::CContext()),
                       m_pMainWindow()
    {
        // Seed the random-number generator with the current time so that
        // the numbers will be different every time we run.
        std::srand(static_cast<unsigned int>(std::time(0)));
        //std::srand(3412548653);
    }

    CApp::~CApp(void)
    {

    }

    void
    CApp::Run(int, char **)
    {
        // Create main window
        m_pMainWindow = m_pContext->
            CreateEglWindow<CMainWindow>(
                Egl::SurfaceProperties::SURFACE_RGBA | 
                Egl::SurfaceProperties::SURFACE_DOUBLE | 
                Egl::SurfaceProperties::SURFACE_DEPTH,
                MAIN_WINDOW_TITLE, 
                0, 0, 10, 10);        
        
        // Show the main window modally
        m_pContext->RunMainLoop();
    }

} // namespace AmazingMaze

// Global Variables:
//HINSTANCE hInst;								// current instance
//TCHAR szTitle[MAX_LOADSTRING];					// The title bar text

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
    UNREFERENCED_PARAMETER(hInstance);

 	// TODO: Place code here.
	//MSG msg;
	//HACCEL hAccelTable;

	// Initialize global strings
	//LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadString(hInstance, IDC_MY3DMAZE, szWindowClass, MAX_LOADSTRING);

    AmazingMaze::CApp app;
    app.Run(0, 0);
	return 0;
}

#pragma once

#include <boost/shared_ptr.hpp>
#include "Egl/Common.hpp"

namespace AmazingMaze
{
    /** Main class for the project. */
    class CApp
    {
    public:

        /** Main window title. */
        static const char * MAIN_WINDOW_TITLE;

    public:

        /** Constructor. */
        CApp(void);

        /** Destructor. */
        ~CApp(void) throw();

        /** Runs this app. */
        void Run(int argc, char **argv);
        
    private:

        /** DGL context. */
        Egl::ContextPtr_t m_pContext;

        /** Main window */
        Egl::WindowPtr_t m_pMainWindow;
    };
} // namespace AmazingMaze
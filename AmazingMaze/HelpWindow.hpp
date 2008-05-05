#pragma once

#include <boost/shared_ptr.hpp>
#include "Egl/Common.hpp"
#include "Egl/Window.hpp"

namespace AmazingMaze
{
    /** Main class for the project. */
    class CHelpWindow : public Egl::CWindow
    {
    public:


    public:

        /** Constructor. */
        CHelpWindow(void);

        /** Destructor */
        virtual ~CHelpWindow(void) throw();

    private:

        /** Handles OnDraw event. */
        void HandleOnDraw(void);

        /** Handles OnReshape event. */
        void HandleOnReshape(int nWidth, int nHeight);

        /** Handle OnCreate event. */
        void HandleOnCreate(void);

        /** Handle OnDestroy event. */
        void HandleOnDestroy(void);

        /** Handle OnKey event. */
        void HandleOnKey(int nKeyCode, bool bIsSystemKey, Egl::KeyState_e eKeyState, int nCursorX, int nCursorY);
    };
} // namespace AmazingMaze
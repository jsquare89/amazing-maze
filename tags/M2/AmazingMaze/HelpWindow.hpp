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

        /** Handles Draw event. */
        void HandleDraw(const Egl::CWindow &, Egl::CEventArgs & rArgs);

        /** Handles Reshape event. */
        void HandleReshape(const Egl::CWindow &, Egl::CWindowReshapeEventArgs & rArgs);

        /** Handle Create event. */
        void HandleCreate(const Egl::CWindow &, Egl::CEventArgs & rArgs);

        /** Handle Destroy event. */
        void HandleDestroy(const Egl::CWindow &, Egl::CEventArgs & rArgs);

        /** Handle Key event. */
        void HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs);

        /** Updates the projection matrix. */
        void UpdateProjectionMatrix(const int nWidth, const int nHeight);

        /** Updates the viewport. */
        void UpdateViewport(const int nWidth, const int nHeight);
    };
} // namespace AmazingMaze
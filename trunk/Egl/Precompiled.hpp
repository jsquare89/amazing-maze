// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "Egl/Targetver.h"
#include <tchar.h>
#include <cstdlib>

//#pragma warning (push)
//#pragma warning (disable:4505)
//#include "glut/glut.h"
//#pragma warning (push)

// Save warning level and disable some for CPW
#pragma warning (push)
#pragma warning (disable:4100)
#pragma warning (disable:4505)

// Define stuff we need so CPW won't barf
#define wstrlen wcslen

#ifdef NDEBUG
    // Include release version of CPW
#   define CPWDLL_EXTERN
#   include <cpw.h>
#   undef CPWDLL_EXTERN
#else
    // Include debug version of CPW
#   define CPWDLLDBG_EXTERN
#   include <cpw.h>
#   undef CPWDLLDBG_EXTERN
#endif

// Undefine stuff defined by CPW that will hurt us
#undef false
#undef true
#undef bool

// Undefine stuff we defined before CPW so it wouldn't barf
#undef wstrlen

// Pop warnings as they were before disabling some for CPW
#pragma warning (pop)
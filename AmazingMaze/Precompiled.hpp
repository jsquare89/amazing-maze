// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// C RunTime Header Files
#include <cstdlib>
#include <tchar.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define NOMINMAX
// Windows Header Files:
#include <windows.h>
#include <Mmsystem.h>

#pragma warning (push)
//#pragma warning (disable:4505)
#include <gl/gl.h>
#include <gl/glu.h>
#pragma warning (pop)

#include <audiere/audiere.h>
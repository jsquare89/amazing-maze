# Microsoft Developer Studio Project File - Name="Cpw" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Cpw - Win32 Debug Static Library
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Cpw.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Cpw.mak" CFG="Cpw - Win32 Debug Static Library"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Cpw - Win32 Debug Static Library" (based on "Win32 (x86) Static Library")
!MESSAGE "Cpw - Win32 Release Static Library" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Cpw - Win32 Debug Static Library"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Cpw___Win32_Debug_Static_Library"
# PROP BASE Intermediate_Dir "Cpw___Win32_Debug_Static_Library"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "DebugStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./" /I "../../include/" /I "../../include/internal" /I "../../include/internal/win32" /I "../../../freetype-2.0.5/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "CPW_INTERN" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./" /I "../../src/include/" /I "../../src/" /I "../../../../freetype-2.0.6/include/" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "CPW_INTERN" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../libs/CpwLib_dbg.lib"
# ADD LIB32 /nologo /out:"../../output/win32/CpwLib_dbg.lib"

!ELSEIF  "$(CFG)" == "Cpw - Win32 Release Static Library"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Cpw___Win32_Release_Static_Library"
# PROP BASE Intermediate_Dir "Cpw___Win32_Release_Static_Library"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "ReleaseStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /Ob2 /I "./" /I "../../include/" /I "../../include/internal" /I "../../include/internal/win32" /I "../freetype-2.0.5/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "CPW_INTERN" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Ob2 /I "./" /I "../../src/include/" /I "../../src/" /I "../../../../freetype-2.0.6/include/" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "CPW_INTERN" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../libs/CpwLib.lib"
# ADD LIB32 /nologo /out:"../../output/win32/CpwLib.lib"

!ENDIF 

# Begin Target

# Name "Cpw - Win32 Debug Static Library"
# Name "Cpw - Win32 Release Static Library"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\cpw_bitmaps.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_callbacks.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_error.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_event.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_font.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_get.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_glextensions.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_images.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_init.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_joystick.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_keymouse.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_libtarga.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_linkedelement.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_linkedlist.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_main.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_menus.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_opensl.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_perftracker.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_primitives.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_state.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_timers.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_videosettings.c
# End Source File
# Begin Source File

SOURCE=..\..\src\win32\cpw_win32.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_window.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cpw_windowlist.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\include\cpw_bitmaps.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_callbacks.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_error.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_event.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_extern.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_font.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_get.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_glextensions.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_images.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_init.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_joystick.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_keymouse.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_libtarga.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_linkedelement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_linkedlist.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_macros.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_main.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_menus.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_opensl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_perftracker.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_primdata.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_primitives.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_state.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_str.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_timers.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_videosettings.h
# End Source File
# Begin Source File

SOURCE=..\..\src\win32\cpw_win32.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_window.h
# End Source File
# Begin Source File

SOURCE=..\..\src\include\cpw_windowlist.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\Cpw.txt
# End Source File
# Begin Source File

SOURCE=..\..\Todo.txt
# End Source File
# End Target
# End Project

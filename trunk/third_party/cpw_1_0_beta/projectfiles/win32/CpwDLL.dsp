# Microsoft Developer Studio Project File - Name="CpwDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CpwDLL - Win32 Debug CpwDLL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CpwDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CpwDLL.mak" CFG="CpwDLL - Win32 Debug CpwDLL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CpwDLL - Win32 Release CpwDLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CpwDLL - Win32 Debug CpwDLL" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CpwDLL - Win32 Release CpwDLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CpwDLL___Win32_Release_CpwDLL"
# PROP BASE Intermediate_Dir "CpwDLL___Win32_Release_CpwDLL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../output/win32/"
# PROP Intermediate_Dir "ReleaseDLL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "./" /I "../../include/" /I "../../include/internal" /I "../../include/internal/win32" /I "../freetype-2.0.5/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CPWDLL_EXPORTS" /D "CPW_INTERN" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MD /W3 /GX /O2 /I "./" /I "../../src/include/" /I "../../src/" /I "../../../../freetype-2.0.6/include/" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CPWDLL_EXPORTS" /D "CPW_INTERN" /FD /c
# SUBTRACT CPP /X /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib freetypeMT.lib opengl32.lib glu32.lib /nologo /dll /machine:I386 /out:"../../libs/CpwDLL.dll" /libpath:"../../libs"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /libpath:"../../libs/win32"

!ELSEIF  "$(CFG)" == "CpwDLL - Win32 Debug CpwDLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CpwDLL___Win32_Debug_CpwDLL"
# PROP BASE Intermediate_Dir "CpwDLL___Win32_Debug_CpwDLL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../output/win32/"
# PROP Intermediate_Dir "DebugDLL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./" /I "../../src/include/" /I "../../src/" /I "../../../../freetype-2.0.5/include/" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CPWDLL_EXPORTS" /D "CPW_INTERN" /FD /GZ /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./" /I "../../src/include/" /I "../../src/" /I "../../../../freetype-2.0.6/include/" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CPWDLL_EXPORTS" /D "CPW_INTERN" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib freetypeMT_dbg.lib opengl32.lib glu32.lib /nologo /dll /debug /machine:I386 /out:"../../output/win32/CpwDLL_dbg.dll" /pdbtype:sept /libpath:"../../libs"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../output/win32/CpwDLL_dbg.dll" /pdbtype:sept /libpath:"../../libs/win32"

!ENDIF 

# Begin Target

# Name "CpwDLL - Win32 Release CpwDLL"
# Name "CpwDLL - Win32 Debug CpwDLL"
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
# Begin Source File

SOURCE=.\CpwDLL.c
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

SOURCE=..\..\src\include\cpw_intern.h
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
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project

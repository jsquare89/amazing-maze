/***************************************************************************/
/*                                                                         */
/*  cpw_keymouse.c                                                         */
/*                                                                         */
/*    Querying realtime keyboard and mouse state.                          */
/*                                                                         */
/*  Copyright 2001-2002 by                                                 */
/*  Jim Mathies,                                                           */
/*                                                                         */
/*  This file is part of the Cpw project, and may only be used,            */
/*  modified, and distributed under the terms of the Cpw project           */
/*  license.  By continuing to use, modify, or distribute this file        */
/*  you indicate that you have read the license and understand and         */
/*  accept it fully.                                                       */
/*                                                                         */
/*  File Platform: cross                                                   */
/*                                                                         */
/***************************************************************************/

#include "cpw_keymouse.h"
#include "cpw_error.h"
#include CPW_LOCALHOST_H

bool cpwMouseCapabilities( pCpw cpw, CpwMouseCapabilities * mcaps )
{
    if ( mcaps == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    memset( mcaps, 0, sizeof( CpwMouseCapabilities ) );
    cpw_localhost_mousecaps( cpw, mcaps );
    return true;
}

bool cpwMouseState( pCpw cpw, CpwMouseInfo * info )
{
    if ( info == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    cpw_localhost_mousestate( cpw, info );

    return true;
}

bool cpwKeyState( pCpw cpw, CpwKeyConstant key )
{
    return cpw->keyboard_state[key];
}

uint_32 cpw_keymouse_translatekeyconstant( uint_32 keycode, bool shift )
{
    if ( shift ) {

      /* shift key down */

      switch ( keycode ) {
        case CPW_KEY_1:           return '!';
        case CPW_KEY_2:           return '@';
        case CPW_KEY_3:           return '#';
        case CPW_KEY_4:           return '$';
        case CPW_KEY_5:           return '%';
        case CPW_KEY_6:           return '^';
        case CPW_KEY_7:           return '&';
        case CPW_KEY_8:           return '*';
        case CPW_KEY_9:           return '(';
        case CPW_KEY_0:           return ')';

        case CPW_KEY_MINUS:       return '_';
        case CPW_KEY_EQUALS:      return '+';
        case CPW_KEY_LBRACKET:    return '{';
        case CPW_KEY_RBRACKET:    return '}';
        case CPW_KEY_SEMICOLON:   return ':';
        case CPW_KEY_APOSTROPHE:  return '~';
        case CPW_KEY_QUOTE:       return '"';
        case CPW_KEY_COMMA:       return '<';
        case CPW_KEY_PERIOD:      return '>';
        case CPW_KEY_SLASH:       return '?';
        case CPW_KEY_BACKSLASH:   return '|';
        case CPW_KEY_SPACE:       return ' ';

        case CPW_KEY_A:           return 'A';
        case CPW_KEY_B:           return 'B';
        case CPW_KEY_C:           return 'C';
        case CPW_KEY_D:           return 'D';
        case CPW_KEY_E:           return 'E';
        case CPW_KEY_F:           return 'F';
        case CPW_KEY_G:           return 'G';
        case CPW_KEY_H:           return 'H';
        case CPW_KEY_I:           return 'I';
        case CPW_KEY_J:           return 'J';
        case CPW_KEY_K:           return 'K';
        case CPW_KEY_L:           return 'L';
        case CPW_KEY_M:           return 'M';
        case CPW_KEY_N:           return 'N';
        case CPW_KEY_O:           return 'O';
        case CPW_KEY_P:           return 'P';
        case CPW_KEY_Q:           return 'Q';
        case CPW_KEY_R:           return 'R';
        case CPW_KEY_S:           return 'S';
        case CPW_KEY_T:           return 'T';
        case CPW_KEY_U:           return 'U';
        case CPW_KEY_V:           return 'V';
        case CPW_KEY_W:           return 'W';
        case CPW_KEY_X:           return 'X';
        case CPW_KEY_Y:           return 'Y';
        case CPW_KEY_Z:           return 'Z';
      }

    } else {
      
      /* no shift key */
      
      switch ( keycode ) {
        case CPW_KEY_1:           return '1';
        case CPW_KEY_2:           return '2';
        case CPW_KEY_3:           return '3';
        case CPW_KEY_4:           return '4';
        case CPW_KEY_5:           return '5';
        case CPW_KEY_6:           return '6';
        case CPW_KEY_7:           return '7';
        case CPW_KEY_8:           return '8';
        case CPW_KEY_9:           return '9';
        case CPW_KEY_0:           return '0';

        case CPW_KEY_MINUS:       return '-';
        case CPW_KEY_EQUALS:      return '=';
        case CPW_KEY_LBRACKET:    return '[';
        case CPW_KEY_RBRACKET:    return ']';
        case CPW_KEY_SEMICOLON:   return ';';
        case CPW_KEY_APOSTROPHE:  return '`';
        case CPW_KEY_QUOTE:       return '\'';
        case CPW_KEY_COMMA:       return ',';
        case CPW_KEY_PERIOD:      return '.';
        case CPW_KEY_SLASH:       return '/';
        case CPW_KEY_BACKSLASH:   return '\\';
        case CPW_KEY_SPACE:       return ' ';

        case CPW_KEY_A:           return 'a';
        case CPW_KEY_B:           return 'b';
        case CPW_KEY_C:           return 'c';
        case CPW_KEY_D:           return 'd';
        case CPW_KEY_E:           return 'e';
        case CPW_KEY_F:           return 'f';
        case CPW_KEY_G:           return 'g';
        case CPW_KEY_H:           return 'h';
        case CPW_KEY_I:           return 'i';
        case CPW_KEY_J:           return 'j';
        case CPW_KEY_K:           return 'k';
        case CPW_KEY_L:           return 'l';
        case CPW_KEY_M:           return 'm';
        case CPW_KEY_N:           return 'n';
        case CPW_KEY_O:           return 'o';
        case CPW_KEY_P:           return 'p';
        case CPW_KEY_Q:           return 'q';
        case CPW_KEY_R:           return 'r';
        case CPW_KEY_S:           return 's';
        case CPW_KEY_T:           return 't';
        case CPW_KEY_U:           return 'u';
        case CPW_KEY_V:           return 'v';
        case CPW_KEY_W:           return 'w';
        case CPW_KEY_X:           return 'x';
        case CPW_KEY_Y:           return 'y';
        case CPW_KEY_Z:           return 'z';
      }
    }
    return 0;
}



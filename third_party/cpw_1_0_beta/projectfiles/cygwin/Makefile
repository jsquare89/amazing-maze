SRC = ../../src
INCLUDE = $(SRC)/include
#FREETYPE = /d/freetype-2.0.6
FREETYPE = /cygdrive/f/Projects/freetype-2.0.6

VPATH = $(SRC):$(INCLUDE):$(SRC)/win32:$(FREETYPE)/include

OBJSLOC = ../../output/cygwin

OBJS = cpw_bitmaps.o \
cpw_callbacks.o \
cpw_error.o \
cpw_event.o \
cpw_font.o \
cpw_get.o \
cpw_glextensions.o \
cpw_images.o \
cpw_init.o \
cpw_joystick.o \
cpw_keymouse.o \
cpw_libtarga.o \
cpw_linkedelement.o \
cpw_linkedlist.o \
cpw_main.o \
cpw_menus.o \
cpw_opensl.o \
cpw_perftracker.o \
cpw_primitives.o \
cpw_state.o \
cpw_timers.o \
cpw_videosettings.o \
cpw_win32.o \
cpw_window.o \
cpw_windowlist.o

CC = gcc
CFLAGS = -mno-cygwin -DCPW_INTERN -DCygWin -UWIN32 -I$(INCLUDE) \
-I$(SRC)/win32 -I$(FREETYPE)/include -I/usr/include

libcpw.a: $(OBJS)
	ar rvu libcpw.a $(OBJS)
	ranlib libcpw.a
#	mkdir ../../output/cygwin
#	mv libcpw.a ../../output/cygwin

cpw_bitmaps.o: cpw_bitmaps.h
cpw_callbacks.o: cpw_callbacks.h cpw_window.h
cpw_error.o: cpw_error.h
cpw_event.o: cpw_event.h cpw_error.h cpw_windowlist.h cpw_win32.h
cpw_font.o: cpw_font.h cpw_error.h cpw_win32.h
cpw_get.o: cpw_event.h cpw_error.h cpw_windowlist.h
cpw_glextensions.o: cpw_glextensions.h cpw_windowlist.h cpw_error.h
cpw_images.o: cpw_images.h cpw_error.h cpw_libtarga.h cpw_bitmaps.h cpw_window.h
cpw_init.o: cpw_init.h cpw_error.h
cpw_joystick.o: cpw_joystick.h cpw_error.h cpw_timers.h cpw_win32.h
cpw_keymouse.o: cpw_keymouse.h cpw_error.h cpw_win32.h
cpw_libtarga.o: cpw_libtarga.h
cpw_linkedelement.o: cpw_linkedelement.h
cpw_linkedlist.o: cpw_linkedlist.h
cpw_main.o: cpw_main.h cpw_event.h cpw_error.h cpw_timers.h cpw_win32.h
cpw_menus.o: cpw_menus.h cpw_error.h cpw_windowlist.h cpw_win32.h
cpw_opensl.o: cpw_opensl.h
cpw_perftracker.o: cpw_perftracker.h cpw_error.h cpw_win32.h
cpw_primitives.o: cpw_primitives.h cpw_primdata.h cpw_error.h
cpw_state.o: cpw_state.h cpw_event.h cpw_init.h cpw_window.h cpw_windowlist.h \
cpw_menus.h cpw_timers.h cpw_joystick.h cpw_videosettings.h \
cpw_primitives.h cpw_glextensions.h cpw_perftracker.h cpw_font.h \
cpw_win32.h
cpw_timers.o: cpw_timers.h cpw_error.h cpw_linkedlist.h cpw_joystick.h \
cpw_win32.h
cpw_videosettings.o: cpw_videosettings.h cpw_window.h cpw_error.h cpw_win32.h
cpw_win32.o: cpw_win32.h cpw_event.h cpw_error.h cpw_init.h cpw_main.h \
cpw_windowlist.h cpw_joystick.h
cpw_window.o: cpw_window.h cpw_windowlist.h cpw_event.h cpw_main.h \
cpw_error.h cpw_win32.h
cpw_windowlist.o: cpw_windowlist.h

clean:
	rm -f *.o libcpw.a
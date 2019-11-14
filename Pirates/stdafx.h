#ifndef STDAFX_H
#define STDAFX_H

#ifdef _WIN32
#define PDC_DLL_BUILD
#include "curses.h"
#else
#include <ncurses.h>
#endif

#define PLATFORM_CURSES
//#define PLATFORM_SFML

#endif // STDAFX_H

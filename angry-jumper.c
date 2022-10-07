#ifndef _AN_ANGRYJUMPER_C
#define _AN_ANGRYJUMPER_C

#include <curses.h>
#include <stdlib.h>

#include "iofunc.c"
#include "menu.c"
#include "setup_curses.c"

int main() {
    char* username;

    init_curses();              // Initialize curses and set up basic curses parameters

    main_menu(username);

    end_curses();
}

#endif
#ifndef _AN_ANGRYJUMPER_C
#define _AN_ANGRYJUMPER_C

#include <curses.h>
#include <stdlib.h>

#include "iofunc.c"
#include "menu.c"
#include "setup_curses.c"
#include "levels.c"



int main(){
    char* username;
    int control;
    char level1[5000];

    init_curses();              // Initialize curses and set up basic curses parameters

    /* TODO: Make welcome screen*/
    main_menu(username);        // from menu.c   
    read_level("levels/level1.txt", level1);

    resizeterm(40, 80);
    
    move(0, 0);
    for(int i = 0; i < 5000; i++)
        addch(level1[i]);
    refresh();


    end_curses();
}

#endif
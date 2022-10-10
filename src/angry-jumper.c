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
    char level1[SCENE_COLS * SCENE_LINES * LV1_SCENES_NUMBER];

    init_curses();              // Initialize curses and set up basic curses parameters
    
    if(getmaxy(stdscr) <= SCENE_LINES || getmaxx(stdscr) <= SCENE_COLS){
        printf("Your terminal is to small. Resize window");
        end_curses();
        exit(-1);
    }

    /* TODO: Make welcome screen*/
    main_menu(username);        // from menu.c   
    read_level("levels/level1.txt", level1);
    print_level(level1);

    refresh();

    getch();
    end_curses();
}

#endif
#ifndef _AN_WINDOW_C
#define _AN_WINDOW_C

#include <curses.h>

#define WINDOW_HEIGHT 25
#define WINDOW_WIDTH 80

void check_win_size(){
    if(getmaxy(stdscr) <= WINDOW_HEIGHT || getmaxx(stdscr) <= WINDOW_WIDTH){
        printf("Your terminal is to small. Resize window");
        end_curses();
        exit(-1);
    }
}

#endif

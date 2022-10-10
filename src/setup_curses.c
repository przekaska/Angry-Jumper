#ifndef _AN_SET_CURS_C
#define _AN_SET_CURS_C

#include <curses.h>

void init_curses(){
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
}

void end_curses(){
    endwin();
}

#endif


#ifndef _AN_MENU_C
#define _AN_MENU_C

#include "iofunc.c"

void main_menu(char* name){
    attron(A_BOLD);

    print_msg(stdscr, LINES / 2 - 1, COLS / 2, "ENTER YOUR NAME", IOCENT);
    take_input(stdscr, LINES / 2 + 1, COLS / 2, 16, IOCENT);

    clear();
    attroff(A_BOLD);
}

#endif

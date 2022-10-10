#ifndef _AN_LEVELS_C
#define _AN_LEVELS_C

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#include "setup_curses.c"

#define SCENE_LINES 24 
#define SCENE_COLS 91   // last column for new line character

#define LV1_SCENES_NUMBER 1


void read_level(const char *filename, char* buffer){
    FILE *file = fopen(filename, "r");
    int c;

    if(NULL == file){
        printf("Cannot find file: %s", filename);
        end_curses();
        exit(-1);
    }

    for(int i = 0; (c = getc(file)) != EOF; i++)
        buffer[i] = c;
}


void print_level(char* level){
    move(0, 0);
    for(int i = 0; i < SCENE_COLS * SCENE_LINES * LV1_SCENES_NUMBER; i++)
        addch(level[i]);
}


#endif
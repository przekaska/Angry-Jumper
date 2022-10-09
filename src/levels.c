#ifndef _AN_LEVELS_C
#define _AN_LEVELS_C

#include <stdlib.h>
#include <stdio.h>

#include "setup_curses.c"

#define SCENE_SIZE 1600

#define LV1_SCENES_NUMBER 1


void read_level(const char *filename, char* buffer){
    FILE *file = fopen(filename, "r");
    int c;
    char buff[5000];

    if(NULL == file){
        printf("Cannot find file: %s", filename);
        end_curses();
        exit(-1);
    }

    for(int i = 0; (c = getc(file)) != EOF; i++)
        buffer[i] = c;

}





#endif
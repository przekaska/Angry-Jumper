#ifndef AN_OBJECT_C
#define AN_OBJECT_C

#include <stdlib.h>
#include <curses.h>
#include <time.h>

#include "window.c"

struct Objects{
    int *platforms;
};

struct Objects *init_objects(){ 
    static int platforms[16] = {    3,      20,     50, 
                                    9,      80,     80, 
                                    3,      150,    50, 
                                    12,     120,    150, 
                                    1,      180,    120, 
                                    -1};

    static struct Objects _objects;

    _objects.platforms = platforms; 

    return &_objects;
}


void draw_platforms(struct Player *player, struct Objects *objects, int i){
    mvaddch(WINDOW_HEIGHT - objects->platforms[i], objects->platforms[i + 1] - player->x + INIT_X, 'T');
    mvaddch(WINDOW_HEIGHT - objects->platforms[i], objects->platforms[i + 1] - player->x + objects->platforms[i + 2] + INIT_X, ' ');
}


void check_if_standing(struct Player *player, struct Objects *objects, int i){
    if(player->is_falling)
        if(player->x >= objects->platforms[i + 1] && player->x <= (objects->platforms[i + 1] + objects->platforms[i + 2]))
            if(player->previous_y >= objects->platforms[i] + 1 && player->y <= objects->platforms[i] + 1)
                player->is_standing = true;
}

#endif

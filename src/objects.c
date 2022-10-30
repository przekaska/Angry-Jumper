#ifndef AN_OBJECT_C
#define AN_OBJECT_C

#include <stdlib.h>
#include <curses.h>
#include <time.h>

#include "window.c"
#include "player.c"

#define PLATFORMS_SIZE 15

#define BUILDING_BLOCK 'T'


int *init_platforms(){                      /*  Y       b-X     e-X  */
    static int platforms[PLATFORMS_SIZE] = {     5,      30,     80, 
                                                3,      60,     180, 
                                                6,      200,    230, 
                                                10,     250,    350, 
                                                2,      300,    350 };
    return platforms;
}


void draw_platforms(struct Player *player, int *platforms, int i){
    mvaddch(WINDOW_HEIGHT - platforms[i], platforms[i + 1] - player->x + INIT_X, BUILDING_BLOCK);
    mvaddstr(WINDOW_HEIGHT - platforms[i], platforms[i + 2] - player->x + INIT_X, "   ");
}


void check_if_standing(struct Player *player, int *platforms, int i){
    if(!player->is_rising)  
        if(player->x >= platforms[i + 1] && player->x <= platforms[i + 2])
            if(player->previous_y >= platforms[i] + 1 &&  player->y <= platforms[i] + 1){
                player->is_standing = true;          
                if(!player->is_reset){
                    player->y = platforms[i] + 1;
                    player->bg_element_buffer = ' ';
                    mvaddch(WINDOW_HEIGHT - platforms[i], INIT_X, 'T');
                }
            }
}


void draw_whole_platforms(int* platforms){
    for(int i = 0; platforms[i + 1] < WINDOW_WIDTH; i += 3)
        for(int j = platforms[i + 1]; j < platforms[i + 2]; j++)
            mvaddch(WINDOW_HEIGHT - platforms[i], j, BUILDING_BLOCK);
}


void platforms_generator(int *platforms){
    srand(time(NULL));

    
}







#endif


#ifndef _AN_PLAYER_C
#define _AN_PLAYER_C

#include <curses.h>

/* Starting positions */
#define INIT_Y 20
#define INIT_X 10


struct Player{
    char skin;
    int y;
    int x;
};

/* Set default player values*/
struct Player *init_player(){

    static struct Player player;
    player.skin = 'O';
    player.y = INIT_Y;
    player.x = INIT_X;  

    return &player;
}

#endif
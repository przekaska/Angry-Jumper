#ifndef _AN_PLAYER_C
#define _AN_PLAYER_C

#include <curses.h>

/* Starting positions */
#define STD_Y 30
#define STD_X 10


struct Player{
    char* skin;
    int y;
    int x;
};

/* Set default player values*/
struct Player *init_player(){

    static struct Player player;
    player.skin = "O";
    player.y = STD_Y;
    player.x = STD_X;  

    return &player;
}

#endif
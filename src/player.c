#ifndef _AN_PLAYER_C
#define _AN_PLAYER_C

#include <curses.h>

#define STD_Y 30
#define STD_X 10


struct Player{
    char* skin;
    int y;

    /* MOVES */
    char *idle;
    char *jump; 
    char *fall;

    char* move;
};


struct Player *init_player(){
    static char idle[32] = {};

    static char jump[32] = {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0,
                     0, 0, -1, 0, 0, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1};

    static char fall[32] = {0, 0, -1, 0, 0, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1,
                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    

    static struct Player player;
    player.skin = "O";
    player.y = STD_Y;
    player.idle = idle;
    player.jump = jump;
    player.fall = fall;


    return &player;
}

void player_jump(int y){

}

#endif
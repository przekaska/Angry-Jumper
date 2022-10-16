#ifndef _AN_ANGRYJUMPER_C
#define _AN_ANGRYJUMPER_C

#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "iofunc.c"
#include "menu.c"
#include "setup_curses.c"
#include "player.c"


int main(){
    char* username;

                    //  y1  x1   w1  y2 x2 w2 y3 x3 w3 y4 x4 w4 y5 x5 w5
    int platforms[16] = {5, 50, 10, 15, 130, 4, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0};                 
    char key;

    int move_iterator = 0;
    int player_x = 0;
    int position_buffer = 0;

    init_curses();              // Initialize curses and set up basic curses parameters
    
    // if(getmaxy(stdscr) <= 20 || getmaxx(stdscr) <= 80){
        // printf("Your terminal is to small. Resize window");
        // end_curses();
        // exit(-1);
    // }

    /* TODO: Make welcome screen*/
    main_menu(username);        // from menu.c
    
    struct Player *player = init_player();
    player->move = player->fall;

    nodelay(stdscr, TRUE);
    while((key = getch()) != 10){
        
        player->y += player->move[move_iterator];

        if(key == 3){
            player->move = player->jump;
            move_iterator = 0;
        }


        if(move_iterator == 31){
            move_iterator = 0;
            player->move = player->idle;
        }


        mvaddstr(STD_Y - position_buffer, STD_X, " ");    
        mvaddstr(STD_Y - player->y, STD_X, player->skin);

        for(int i = 0; platforms[i] != -1; i += 3){
            mvaddch(STD_Y - platforms[i], platforms[i + 1] - player_x, 'Z');
            mvaddch(STD_Y - platforms[i], platforms[i + 1] - player_x + platforms[i + 2], ' ');
        }

        usleep(20000);
        move_iterator++;
        player_x++;
        position_buffer = player->y;
    }


    refresh();

    getch();
    end_curses();
}

#endif
#ifndef _AN_ANGRYJUMPER_C
#define _AN_ANGRYJUMPER_C

#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "iofunc.c"
#include "menu.c"
#include "setup_curses.c"
#include "player.c"


#define WINDOW_HEIGHT 25
#define WINDOW_WIDTH 80

int main(){
    /* 'platforms' array contains data of every platfrom. Each platfrom has three variables:
        1. Y-coordinate, 2. X-coordinate, 3. Width. The last variable in the array must contain
        -1 as a sign of the end of array. It let us to avoid dynamic allocation of memory. */
                        /*  y       x       w   */    
    int platforms[16] = {   3,      100,    50, 
                            10,     120,    80, 
                            4,      30,     50, 
                            18,     300,    15, 
                           -1,      0,      0, 
                        0};

    char moves[5] = {};

    char* username;
    char key;
    int previous_position = 0;

    char move_iterator = 0;
    int change_iterator = 0;

    init_curses();              /* Initialize curses and set up basic curses parameters */
    
    /* Check if user's window if big enough to properly display the game */
    if(getmaxy(stdscr) <= WINDOW_HEIGHT || getmaxx(stdscr) <= WINDOW_WIDTH){
        printf("Your terminal is to small. Resize window");
        end_curses();
        exit(-1);

    /* TODO: Make welcome screen*/
    main_menu(username);        // from menu.c
    }
    
    struct Player *player = init_player();
    bool is_standing = false;
    bool is_reseted = false;
    int sth = 32;
    
    nodelay(stdscr, TRUE);  // getch() won't block game loop
    
    while((key = getch()) != 10){        

        if(key == 3){
            for(int i = 0; i < 5; i++)
                moves[i] = 1;

            is_standing = false;          
            move_iterator = 0;
        }

        if(!is_standing){
            if(move_iterator > 5){
                move_iterator = 0;
                change_iterator++;
                moves[change_iterator%5] -= 1;
            }
            player-> y += moves[move_iterator];
            is_reseted = false;
        }            
        
        if(is_standing && !is_reseted){
            for(int i = 0; i < 5; i++)
                moves[i] = 0;
            is_reseted = true;
        }

     /* Draw platform and check if player is standing on one of them.
        Platforms data is stored in 'platforms' array. */    
        is_standing = false;
        for(int i = 0; platforms[i] != -1; i += 3){
                        
         /* Platforms are going from the right to the left and never change their
            Y-coordinate. So we can just add one building block on the left side
            of the platform and remove block from the right side to achive moving efect */
            mvaddch(WINDOW_HEIGHT - platforms[i], platforms[i + 1] - player->x + INIT_X, 'B');
            mvaddch(WINDOW_HEIGHT - platforms[i], platforms[i + 1] - player->x + platforms[i + 2] + INIT_X, ' ');

         /* Checking if player is standing on the platfrom */
            if(player->x > platforms[i + 1] && player->x < (platforms[i + 1] + platforms[i + 2]))
                if(previous_position >= platforms[i] + 1 && player->y <= platforms[i] + 1)
                    is_standing = true;
        }
        
                
    /*  This block of code draws player avatar on the screen.
        Firstly, it removes player skin from the previous position,
        then is adds it on the new position.    */   
        mvaddch(WINDOW_HEIGHT - previous_position, INIT_X, sth);

        sth = A_CHARTEXT & mvwinch(stdscr, player->y, INIT_X);    
        mvaddch(WINDOW_HEIGHT - player->y, INIT_X, player->skin);
        

        previous_position = player->y;
        player->x++;
        move_iterator++;
        usleep(33333);
    }


    refresh();

    getch();
    end_curses();
    
}
#endif
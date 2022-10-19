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


int main(){
    /* 'platforms' array contains data of every platfrom. Each platfrom has three variables:
        1. Y-coordinate, 2. X-coordinate, 3. Width. The last variable in the array must contain
        -1 as a sign of the end of array. It let us to avoid dynamic allocation of memory. */
                        /*  y       x       w   */    
    int platforms[16] = {   10,     50,     50, 
                            15,     120,    80, 
                            8,      50,     50, 
                            18,     130,    15, 
                           -1,      0,      0, 
                        0};

    char* username;
    char key;
    int previous_position = 0;

    init_curses();              /* Initialize curses and set up basic curses parameters */
    
    /* Check if user's window if big enough to properly display the game */
    if(getmaxy(stdscr) <= 1 || getmaxx(stdscr) <= 1){
        printf("Your terminal is to small. Resize window");
        end_curses();
        exit(-1);
    }

    /* TODO: Make welcome screen*/
    main_menu(username);        // from menu.c
    
    struct Player *player = init_player();

    nodelay(stdscr, TRUE);  // getch() won't block game loop
    while((key = getch()) != 10){   

     /* Draw platform and check if player is standing on one of them.
        Platforms data is stored in 'platforms' array. */    
        for(int i = 0; platforms[i] != -1; i += 3){
            
         /* Platforms are going from the right to the left and never change their
            Y-coordinate. So we can just add one building block on the left side
            of the platform and remove block from the right side to achive moving efect */
            mvaddch(STD_Y - platforms[i], platforms[i + 1] - player->x, 'Z');
            mvaddch(STD_Y - platforms[i], platforms[i + 1] - player->x + platforms[i + 2], ' ');

         /* Checking if player is standing on the platfrom */
            if(player->y == platforms[i] + 1 &&
               player->x > platforms[i + 1] && 
               player->x < (platforms[i + 1] + platforms[i + 2])){
               } 
        }

    /*  This block of code draws player avatar on the screen.
        Firstly, it removes player skin from the previous position,
        then is adds it on the new position.    */
        mvaddstr(STD_Y - previous_position, STD_X, " ");    
        mvaddstr(STD_Y - player->y, STD_X, player->skin);


        previous_position = player->y;  // We need this, to clear it in the next frame
        player->x++;

        usleep(33333);
    }


    refresh();

    getch();
    end_curses();
    
}
#endif
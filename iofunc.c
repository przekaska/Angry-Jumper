#include <curses.h>
#include <string.h>
#include <stdlib.h>

#ifdef __linux__
    #include <unistd.h>
    #define IODELAY 70000
#elif _WIN32
    #include <Windows.h>
    #define IODELAY 70
#endif

#define IOLEFT 0
#define IOCENT 1
#define IORIGH 2

/* ############## OUTPUT ############## */

void printmsg(WINDOW *win, int y, int x, const char *msg, const int option){
    int msg_len;

    /* save some basic parameters */
    msg_len = strlen(msg);                          // Save these parameters because
                                                    // they'll be used multiple times

    /* Print message char by char*/
    for (int i = 0; i < msg_len; i++){
        switch(option){
            /* Just print every character one by one from the left */
            case IOLEFT:
                mvwaddch(win, y, x + i, msg[i]);
                break;
            /* Print every character one by one, but move the string so it stays in the center*/
            case IOCENT:
                for(int j = 0; j <= i; j++)
                    mvwaddch(win, y, (x - i/2 + j), msg[j]);
                break;
            /* Just print every character one by one from the right*/    
            case IORIGH:
                for(int j = 0; j <= i; j++)
                    mvwaddch(win, y, x - i + j, msg[j]);
                break;
        }
        
        refresh();

        /* After printing every character, take a break for a nice efect of printing */
        #ifdef __linux__
            usleep(IODELAY);
        #elif _WIN32
            Sleep(IODELAY);
        #endif
    }
}





/* ############## INPUT ############## */

/* This function can handle user input echo in three different ways:
* Option 1 (I_LEFT): Echo input from the left to the right (like usually done)
* Option 2 (I_CENT): Echo displayed that the center of the string stays in the defined position
* Option 3 (I_RIGH): Echo displayed from the right to the left. Opposite to option 1 */

/* NOTE: In every option input is printed char by char, because this way provide much simpler
   implementation of handling input echoing.  */

char* take_input(WINDOW *win, int y, int x, int size, int option){
    char* input;
    char ch;                              
    input = calloc(size, sizeof(int));          // Maximum size has to be predefined, because of performance
    noecho();
    wmove(win, y, x);

    switch(option){
        case IOLEFT:
            for(int i = 0; (ch = getch()) != 10; i++)
                if(i < size){
                    input[i] = ch;
                    waddch(win, input[i]);
                }
            break;


        case IOCENT:
            for(int i = 0; (ch = getch()) != 10; i++)
                if(i < size){
                    input[i] = ch;
                    wmove(win, y, x - i/2);
                    for (int j = 0; j <= i; j++)
                        waddch(win, input[j]);
                }
            break;


        case IORIGH:
            for (int i = 0; (ch = getch()) != 10; i++)
                if (i < size){
                    input[i] = ch;
                    for (int j = 0; j <= i; j++)
                        mvwaddch(win, y, x - i + j, input[j]);              // use mvwaddch insted of waddch, because the                                                                    // beggining of the echo needs to be moved every
                }                                                           // time user enters character    
            break;
    }
    

    return input;
}


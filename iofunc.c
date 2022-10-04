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

void I_LEFT(WINDOW *win, int y, int x, int size, char *input);
void I_CENT(WINDOW *win, int y, int x, int size, char *input);
void I_RIGH(WINDOW *win, int y, int x, int size, char *input);


/* ############## OUTPUT ############## */

void printmsg(WINDOW *win, int y, int x, const char *msg, const int option){
    int msg_len;

    /* save some basic parameters */
    msg_len = strlen(msg);                          // Save these parameters because
                                                    // they'll be used multiple times

    /* Print message char by char*/
    for (int i = 0; i < msg_len; i++){
        /* Just print every character one by one from the left */
        if (option == IOLEFT)
            mvwaddch(win, y, x + i, msg[i]);
        /* Print every character one by one, but move the string so it stays in the center*/
        else if (option == IOCENT)
            for(int j = 0; j <= i; j++)
                mvwaddch(win, y, (x - i/2 + j), msg[j]);
        /* Just print every character one by one from the right*/    
        else
            for(int j = 0; j <= i; j++)
                mvwaddch(win, y, x - i + j, msg[j]);

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

char* take_input(WINDOW *win, int y, int x, int size, void (*option)(WINDOW*, int, int, int, char*)){
    char* input;
    input = calloc(size, sizeof(int));          // Maximum size has to be predefined, because of performance

    option(win, y, x, size, input);            
    
    return input;
}

void I_LEFT(WINDOW *win, int y, int x, int size, char *input){
    wmove(win, y, x);
        for(int i = 0; (input[i] = getch()) != 10; i++)
            if(i < size)
                waddch(win, input[i]);
}


void I_CENT(WINDOW *win, int y, int x, int size, char *input){
    for(int i = 0; (input[i] = getch()) != 10; i++)
        if(i < size){
            wmove(win, y, x - i/2);
            for (int j = 0; j <= i; j++)
                waddch(win, input[j]);
        }
}


void I_RIGH(WINDOW *win, int y, int x, int size, char *input){
    for (int i = 0; (input[i] = getch()) != 10; i++)
        if (i < size)
            for (int j = 0; j <= i; j++)
                mvwaddch(win, y, x - i + j, input[j]);              // use mvwaddch insted of waddch, because the 
}                                                                   // beggining of the echo needs to be moved every
                                                                    // time user enters character

#include <curses.h>
#include <string.h>

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

        /*Between printing every character, take a break for a nice efect of printing*/
        #ifdef __linux__
            usleep(IODELAY);
        #elif _WIN32
            Sleep(IODELAY);
        #endif
    }
}

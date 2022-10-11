#ifndef _AM_OBJECTS_C
#define _AM_OBJECTS_C

#include <string.h>
#include <curses.h>

/* Plants */
#define OB_SPRUCE "@@@_@@@\n@@( )@@\n@(   )@\n(_   _)\n@@| |@@\n"

/* Terrain */
#define OB_MOUNTAIN1 "@@@@@@/\\@@@@\n@@@@@/  \\@@@\n@@/\\/    \\@@\n@/        \\@\n/          \\\n"
#define OB_MOUNTAIN2 "@@@@@@/\\@@@@@@\n@@@@@/  \\@@@@@\n@@@@/\\/\\/\\@@@@\n@@@/      \\@@@\n@@/        \\@@\n@/          \\@\n/            \\n"

/* Clouds */
#define OB_CLOUD1 "@@@__@@@\n@_(  )_@\n(______)\n"
#define OB_CLOUD2 "@@@___@@@\n@_(   )_@\n(_______)\n"
#define OB_CLOUD3 "@@@____@@@\n@_(    )_@\n(________)\n"
#define OB_CLOUD4 "@@@@@@___@@@@@@\n@@@__(   )__@@@\n@_(         )_@\n(_____________)\n"
#define OB_CLOUD5 "@@@@____@@@@\n@__(    )__@\n(_        _)\n@@(______)@@\n"

void add_object(WINDOW *win, int y, int x, const char* object){
    wmove(win, y, x);
    int y1 = y;
    int x1 = x;

    for(int i = 0; i < strlen(object); i++){
        if(object[i] == '@')
            x1++;
        else if(object[i] == '\n'){
            x1 = x;
            y1++;
        }
        else {
            mvwaddch(win, y1, x1, object[i]);
            x1++;
        }
    }
}


#endif

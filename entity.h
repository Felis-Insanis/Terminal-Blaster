#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

struct ENTITY { // The top-left corner, dimensions and sprite of a given ENTITY, alongside the window it shows up in
    int  y0;                // y-value of top-left corner of the sprite
    int  x0;                // x-value of top-left corner of the sprite
    int  height;            // height of the sprite (for rendering purposes)
    int  width;             // width of the sprite (for rendering purposes)
    char aliveSprite0[400]; // the sprite itself in one long string of characters
    WINDOW *window;         // the window the ENTITY is in
};

struct ENTITY createENT(int y0, int x0, int h, int w, char sprite[400], WINDOW *window) { // a tool for quickly filling out an ENTITY struct's values
    struct ENTITY e; // creates a temporary ENTITY struct

    //fills it out
    e.y0     = y0;      // sets y at top-left of entity to y0
    e.x0     = x0;      // sets x at top-left of entity to x0
    e.height = h;       // sets entity height
    e.width  = w;       // sets entity width
    e.window = window;  // sets the window the entity will be displayed in

    strcpy(e.aliveSprite0, sprite); // copies the sprite string "sprite" into e.aliveSprite0

    return e; // and then returns it as one big clump of data, to be copied into another ENTITY struct in main
}

void drawENT(struct ENTITY e){ // shortcut for drawing an ENTITY's sprite with a given top left corner
    int y; // the y coordinate the "pen" is at
    int x; // the x coordinate the "pen" is at
    int c; // the index of the character in the sprite-string that is currently being drawn

    for (int vI = 0; vI < e.height; vI++){       // iterating through the vertical lines
        y = e.y0 + vI; // updates the y coordinate of the pen

        for (int hI = 0; hI < e.width; hI++){    // iterating through the horisontal columns
            x = e.x0 + hI; // updates the x coordiante of the pen
            c = vI * e.width + hI; // updates the loaction in the string where the pen will copy a character from

            mvwaddch(e.window, y, x, e.aliveSprite0[c]); // draws the appropriate character at the given relative y,x coordinates of the given window
        }
    } 
}

// void shiftENT(int index, struct ENTITY *arrayPtr, int length) { // shifts elements
//     int i;
//     for (i = index; i < length; i++){
//         arrayPtr[i] = arrayPtr[i+1];
//     }
// }

// void removeIndexENT(int index, struct ENTITY *arrayPtr, int length) { // shifts elements, then reallocates
//     struct ENTITY *tmp;

//     shiftENT(index, arrayPtr, length);

//     tmp = realloc(arrayPtr, (length-1) * sizeof(struct ENTITY));

//     if (tmp == NULL) {
//         exit(EXIT_FAILURE);
//     }
//     arrayPtr = tmp;
// }
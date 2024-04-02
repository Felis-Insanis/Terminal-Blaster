#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

struct PROJECTILE { // The top-left corner, dimensions and sprite of a given PROJECTILE, alongside the window it shows up in
    int  y0;                    // y-value of top-left corner of the sprite
    int  x0;                    // x-value of top-left corner of the sprite
    int  height;                // height of the sprite (for rendering purposes)
    int  width;                 // width of the sprite (for rendering purposes)
    char sprite[2];             // the sprite itself in one long string of characters
    WINDOW* window;             // the window the PROJECTILE is in
    struct PROJECTILE* next;    // the adress of the next projectile
};

struct PROJECTILE createPROJECTILE(int y0, int x0, int h, int w, char sprite[2], WINDOW *window) { // a tool for quickly filling out an PROJECTILE struct's values
    struct PROJECTILE e; // creates a temporary PROJECTILE struct

    //fills it out
    e.y0     = y0;      // sets y at top-left of PROJECTILE to y0
    e.x0     = x0;      // sets x at top-left of PROJECTILE to x0
    e.height = h;       // sets PROJECTILE height
    e.width  = w;       // sets PROJECTILE width
    e.window = window;  // sets the window the PROJECTILE will be displayed in
    e.next   = NULL;

    strcpy(e.sprite, sprite); // copies the sprite string "sprite" into e.aliveSprite0

    return e; // and then returns it as one big clump of data, to be copied into another PROJECTILE struct in main
}

void drawPROJECTILE(struct PROJECTILE e){ // shortcut for drawing an PROJECTILE's sprite with a given top left corner
    int y; // the y coordinate the "pen" is at
    int x; // the x coordinate the "pen" is at
    int c; // the index of the character in the sprite-string that is currently being drawn

    for (int vI = 0; vI < e.height; vI++){       // iterating through the vertical lines
        y = e.y0 + vI; // updates the y coordinate of the pen

        for (int hI = 0; hI < e.width; hI++){    // iterating through the horisontal columns
            x = e.x0 + hI; // updates the x coordiante of the pen
            c = vI * e.width + hI; // updates the loaction in the string where the pen will copy a character from

            mvwaddch(e.window, y, x, e.sprite[c]); // draws the appropriate character at the given relative y,x coordinates of the given window
        }
    } 
}

void deletePROJECTILE() {
    
}
#include <stdio.h>             // standard input-output library, idk if it's used, but idc either
#include <stdlib.h>            // a bunch of useful functions, idk which ones though
#include <ncurses.h>           // the "visual" (ASCII graphics) library that powers this project (and kills me)
#include <string.h>            // useful string-manipulation tools (aka character lists)
#include "player.h"            // the sprite of the player
#include "enemyStatic.h"       // the sprite of the static enemy type           (unused)
#include "projectileEnemy.h"   // sprite for a projectile cast by enemies       (WIP)
#include "projectilePlayer.h"  // sprite for a projectile cast by the player    (WIP)

struct entity { // The top-left corner, dimensions and sprite of a given entity, alongside the window it shows up in
    int  y0;                // y-value of top-left corner of the sprite
    int  x0;                // x-value of top-left corner of the sprite
    int  height;            // height of the sprite (for rendering purposes)
    int  width;             // width of the sprite (for rendering purposes)
    char aliveSprite0[400]; // the sprite itself in one long string of characters
    WINDOW *window;         // the window the entity is in
};

struct entity createEntity(int h, int w, char sprite[400], WINDOW *window) { // a tool for quickly filling out an entity struct's values
    struct entity e; // creates a temporary entity struct

    //fills it out
    e.height = h;       // should explain itself
    e.width  = w;       // should explain itself
    e.window = window;  // should explain itself

    strcpy(e.aliveSprite0, sprite); // copies the sprite string "sprite" into e.aliveSprite0

    return e; // and then returns it as one big clump of data, to be copied into another entity struct in main
}

void drawEntity(struct entity e, int y0, int x0){ // shortcut for drawing an entity's sprite with a given top left corner
    int y; // the y coordinate the "pen" is at
    int x; // the x coordinate the "pen" is at
    int c; // the index of the character in the sprite-string that is currently being drawn

    for (size_t vI = 0; vI < e.height; vI++){       // iterating through the vertical lines
        y = y0 + vI; // updates the y coordinate of the pen

        for (size_t hI = 0; hI < e.width; hI++){    // iterating through the horisontal columns
            x = x0 + hI; // updates the x coordiante of the pen
            c = vI * e.width + hI; // updates the loaction in the string where the pen will copy a character from

            mvwaddch(e.window, y, x, e.aliveSprite0[c]); // draws the appropriate character at the given relative y,x coordinates of the given window
        }
    } 
}

int lengthEntity(struct entity *arrayPtr) { // returns the length of an array of entities
    return sizeof(arrayPtr)/sizeof(struct entity);
}

void remove(int index, struct entity *arrayPtr) { // moves every element back by one index after given index, basically removes the element at the given index
    int i;
    for (i = index; i < lengthEntity(arrayPtr); i++){
        arrayPtr[i] = arrayPtr[i+1];
    }
}

void removeFromEntityArrayByID(int index, struct entity *arrayPtr) { // removes an element based on index and reduces the size of the array
    remove(index, arrayPtr);
    arrayPtr = (struct entity*) realloc(arrayPtr, sizeof(arrayPtr) - sizeof(struct entity));
}

int main() {
    char c;     // stores input as a single ASCII character
    c = '\0';   // sets a temporary null value as the input so the first iteration in the while loop doesn't bug out
    
    initscr();              // inititalise the "graphics"
    nodelay(stdscr, TRUE);  // the program now doesn't wait for input each loop

    // const height, width = getmaxy(stdscr), getmaxx(stdscr);
    // WINDOW *playArea = newpad(height, width);
    struct entity* projectile;
    struct entity player;                           // variable representing the player entity
    int playerY = 0;                                // current Y-coordinate of player
    int playerX = 0;                                // current X-coordinate of player
    player = createEntity(7, 14, spriteP1, stdscr); // fills the player entity with info
    projectile = (struct entity*) calloc(0, sizeof(struct entity));

    drawEntity(player, playerY, playerX);           // draws the player entity for the first time
    
    while (c != 27) {   // game loop, stops when 'esc' is pressed (ASCII character code 27)
        c = getch();    // getting input

        switch (c){     // handling input
        case 'w':       // moves player up
            playerY--;
            break;

        case 's':       // moves player down
            playerY++;
            break;

        case 'a':       // moves player left
            playerX--;
            break;

        case 'd':       // moves player right
            playerX++;
            break;
        case ' ':
            projectile = (struct entity*)realloc(projectile, sizeof(struct entity));
            break;

        default:
            break;
        };

        // drawing the new frame
        clear();                                // clears the screen
        drawEntity(player, playerY, playerX);   // draws the player sprite on the screen
        refresh();                              // refreshes the screen so that everything drawn will show up
        napms(1);
    }

    endwin(); // closes the graphics and restores the terminal
    free(projectile);
    return 0; // closes the program
}
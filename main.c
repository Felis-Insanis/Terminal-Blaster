// Imports
#include <stdio.h>              // standard input-output library, idk if it's used, but idc either
#include <stdlib.h>             // a bunch of useful functions, idk which ones though
#include <ncurses.h>            // the "visual" (ASCII graphics) library that powers this project (and kills me)
#include <string.h>             // useful string-manipulation tools (aka character lists)
#include "entity.h"             // class ENTITY and methods for it
#include "player.h"             // the sprite of the player
#include "enemyStatic.h"        // the sprite of the static enemy type           (unused)
#include "projectileEnemy.h"    // sprite for a projectile cast by enemies       (WIP)
#include "projectilePlayer.h"   // sprite for a projectile cast by the player    (WIP)

int main() {
    char c;     // stores input as a single ASCII character
    c = '\0';   // sets a temporary null value as the input so the first iteration in the while loop doesn't bug out
    
    initscr();              // inititalise the "graphics"
    nodelay(stdscr, TRUE);  // the program now doesn't wait for input each loop

    int height, width;
    height = getmaxy(stdscr);
    width  = getmaxx(stdscr);
    

    // WINDOW *playArea = newpad(height, width);
    struct ENTITY* projectile;
    int nrProjectiles = 0;
    int nrProjectilesRemoved = 0;
    char projRemoved[10];
    char strNrProjectiles[10];
    char strProjectilesNr[10];

    struct ENTITY player;                           // variable representing the player ENTITY
    player = createENT(0, 0, 7, 14, spriteP1, stdscr); // fills the player ENTITY with info
    projectile = (struct ENTITY*) calloc(0, sizeof(struct ENTITY));

    drawENT(player);           // draws the player ENTITY for the first time
    
    while (c != 27) {   // game loop, stops when 'esc' is pressed (ASCII character code 27)
        c = getch();    // getting input

        if (nrProjectiles > 0) {
            for (int i = 0; i < nrProjectiles; i++){
                if (projectile[i].x0 < width){
                    projectile[i].x0++;
                } else {
                    removeIndexENT(i, projectile, nrProjectiles);
                    nrProjectilesRemoved++;
                    sprintf(projRemoved, "%d", nrProjectilesRemoved);
                    beep();
                }
            }
        }

        

        switch (c){     // handling input
        case 'w':       // moves player up
            player.y0--;
            break;

        case 's':       // moves player down
            player.y0++;
            break;

        case 'a':       // moves player left
            player.x0--;
            break;

        case 'd':       // moves player right
            player.x0++;
            break;
        case ' ':
            nrProjectiles ++;
            sprintf(strNrProjectiles, "%d", nrProjectiles);
            mvaddstr(0, width-10, strNrProjectiles);

            projectile = (struct ENTITY*)realloc(projectile, nrProjectiles * sizeof(struct ENTITY)); // IMPORTANT FIX:
            beep();
            projectile[nrProjectiles-1] = createENT(player.y0, player.x0, 1, 2, spriteLazer, stdscr);
            break;

        default:
            break;
        };

        // drawing the new frame
        // clear();            // clears the screen
        drawENT(player);    // draws the player sprite on the screen
        for (int i = 0; i < nrProjectiles; i++){
            drawENT(projectile[i]);
        }
        sprintf(strNrProjectiles, "%d", nrProjectiles);
        sprintf(strProjectilesNr, "%d", sizeof(*projectile));

        mvaddstr(0, width-10, strNrProjectiles);
        mvaddstr(1, width-10, strProjectilesNr);
        mvaddstr(2, width-10, projRemoved);

        refresh();          // refreshes the screen so that everything drawn will show up
        napms(20);           // makes the program wait 1 ms between each frame to prevent overheating
    }

    endwin(); // closes the graphics and restores the terminal
    free(projectile); // clears the memory address of "projectile"
    return 0; // closes the program
}
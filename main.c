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
#include "projectile.h"         // class PROJECTILE and methods for it

int main() {
    char c;     // stores input as a single ASCII character
    c = '\0';   // sets a temporary null value as the input so the first iteration in the while loop doesn't bug out
    
    initscr();              // inititalise the "graphics"
    cbreak();               // disable line buffering
    nodelay(stdscr, TRUE);  // the program now doesn't wait for input each loop
    noecho();
    int height, width;
    height = getmaxy(stdscr);
    width  = getmaxx(stdscr);
    
    WINDOW * ui = subwin(stdscr, 5, width, 0, 0);
    WINDOW * stage = subwin(stdscr, height-5, width, 5, 0);
    nodelay(stage, TRUE);  // the program now doesn't wait for input each loop

    // WINDOW *playArea = newpad(height, width);
    projectile_t* projectileHead; // the head of the PROJECTILE linked list
    int nrProjectiles = 0;
    char projRemoved[10];
    char strNrProjectiles[10];

    struct ENTITY player;                           // variable representing the player ENTITY
    player = createENT(1, 1, 7, 14, spriteP1, stage); // fills the player ENTITY with info

    projectileHead = (projectile_t *) malloc(sizeof(projectile_t));
    projectileHead->next = NULL; // c

    box(ui, '|', '-');
    box(stage, '|', '-');

    drawENT(player);           // draws the player ENTITY for the first time
    
    while (c != 27) {   // game loop, stops when 'esc' is pressed (ASCII character code 27) (function keys also get interpreted as the escape key)
        c = wgetch(stage);    // getting input

        if (projectileHead->next != NULL) {
            moveProjectiles(projectileHead, stdscr);
        }

        switch (c){     // handling input
            case 'w':       // moves player up
                if (player.y0 > 1) {
                    player.y0--;
                }
                break;

            case 's':       // moves player down
                if (player.y0 < height - player.height*2 + 1) {
                    player.y0++;
                }
                break;

            case 'a':       // moves player left
                if (player.x0 > 1) {
                    player.x0--;
                }
                break;

            case 'd':       // moves player right
                if (player.x0 < width - player.width - 1) {
                    player.x0++;
                }
                break;
            case ' ':
                newProjectile(projectileHead, TRUE, player.y0 + 1, player.x0 + 14, 2, 1, spriteLazer, stage);
                nrProjectiles ++;
                newProjectile(projectileHead, TRUE, player.y0 + 5, player.x0 + 14, 2, 1, spriteLazer, stage);
                nrProjectiles ++;
                
                wclear(ui);
                box(ui, '|', '-');
                sprintf(strNrProjectiles, "%d", nrProjectiles);
                mvwaddstr(ui, 1, width-10, strNrProjectiles);
                mvwaddstr(ui, 2, width-10, projRemoved);
                wrefresh(ui);

                break;

            default:
                break;
        };

        // drawing the new frame
        wclear(stage);            // clears the screen
        drawENT(player);    // draws the player sprite on the screen
        drawPROJECTILE(projectileHead);

        box(stage, '|', '-');

        refresh();           // refreshes the screen so that everything drawn will show up
        napms(20);           // makes the program wait 1 ms between each frame to prevent overheating
    }
    nocbreak();
    endwin(); // closes the graphics and restores the terminal
    return 0; // closes the program
}
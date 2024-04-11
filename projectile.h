#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct PROJECTILE { // The top-left corner, dimensions and sprite of a given PROJECTILE, alongside the window it shows up in
    int  y0;                    // y-value of top-left corner of the sprite
    int  x0;                    // x-value of top-left corner of the sprite
    int  height;                // height of the sprite (for rendering purposes)
    int  width;                 // width of the sprite (for rendering purposes)
    char sprite[3];             // the sprite itself in one long string of characters
    WINDOW* window;             // the window the PROJECTILE is in
    struct PROJECTILE* next;    // the adress of the next projectile
} projectile_t;

void drawPROJECTILE(projectile_t* head){ // shortcut for drawing an PROJECTILE's sprite with a given top left corner
    projectile_t *current = head;
    
    int y; // the y coordinate the "pen" is at
    int x; // the x coordinate the "pen" is at
    int c; // the index of the character in the sprite-string that is currently being drawn

    while (current->next != NULL) {
        current = current->next;
        for (int vI = 0; vI < current->height; vI++){       // iterating through the vertical lines
            y = current->y0 + vI; // updates the y coordinate of the pen

            for (int hI = 0; hI < current->width; hI++){    // iterating through the horisontal columns
                x = current->x0 + hI; // updates the x coordiante of the pen
                c = vI * current->width + hI; // updates the loaction in the string where the pen will copy a character from

                mvwaddch(current->window, y, x, current->sprite[c]); // draws the appropriate character at the given relative y,x coordinates of the given window
            }
        } 
    }
    
}

projectile_t* deletePROJECTILE(projectile_t* head, int index) {
    int i = 0;
    projectile_t *current = head;
    projectile_t *tmp;

    for (i = 0; i < index; i++){
        current = current->next;
    }
    
    tmp = current->next;
    current->next = tmp->next;
    free(tmp);
    return current;
}

void moveProjectiles(projectile_t* head, WINDOW* screen) {
    projectile_t* current = head;
    projectile_t* next = current->next;
    projectile_t* tmp;

    while (next != NULL) {
        if (next->x0+next->width <= getmaxx(screen)){
            next->x0++;
        } else {
            tmp = next->next;
            free(next);
            current->next = tmp;
        }
        
        if (current->next != NULL){
            current = current->next;
            next = current->next;
        } else {
            next = NULL;
        }
    }
}

void newProjectile(projectile_t * head, int y0, int x0, int width, int height, char sprite[2], WINDOW* window) {
    projectile_t * current = head;
    
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = (projectile_t *) malloc(sizeof(projectile_t));
    current->next->y0 = y0;
    current->next->x0 = x0;
    current->next->height = height;
    current->next->width = width;
    strcpy(current->next->sprite, sprite);
    current->next->window = window;
    current->next->next = NULL;
}

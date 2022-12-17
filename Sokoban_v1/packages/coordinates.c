#include <stdio.h>
#include <stdlib.h>

/* Structure for storing 2-dimensional coordinates. */
struct Coordonnees {
    int x;
    int y;
};

/* Data type for storing 2-dimensional coordinates. */
typedef struct Coordonnees Coordonnees;

/* Coordinates constructor. */
Coordonnees coordonnees(int x, int y) {
    Coordonnees a;
    a.x = x;
    a.y = y;
    return a;
}

/* Coordinates displayer. */
void displayCoordonnees (Coordonnees c) {
    printf("(%d, %d)\n", c.x, c.y);
}
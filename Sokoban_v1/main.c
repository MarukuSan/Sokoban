#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <string.h>
/* Import coordinates.c for using functions on type Coordinates */
#include "./packages/coordinates.c"
/* Import matrices.c for using functions on type Matrix */
#include "./packages/matrices.c"

int main() {

    initscr();
    curs_set(0);
    int m = 12;
    int n = 15;
    Matrix a = matrix(m, n);    

    char c;

    while(c != 'q') {
        displayMatrix(a);
        c = getch();

        switch (c) {
            case 'j':
                goToLeft(a);
                break;
            case 'l':
                goToRight(a);
                break;
            case 'i':
                goToUp(a);
                break;
            case 'k':
                goToDown(a);
                break;        
            default:
                break;
        }
        erase();
    }

    endwin();

    return 0;
} 
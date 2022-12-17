#include <stdlib.h>

enum BlockType {
    BLOCK,
    PERSO,
    PERSO2,
    BOITE,
    BOITE2,
    POINT,
    VOID
};

typedef enum BlockType BlockType;

struct Block {
    Coordonnees position;
    BlockType type;
    char output;
};

typedef struct Block Block;

/* Block constructor. */
Block block(Coordonnees c, BlockType t) {
    Block a;
    a.position = c;
    a.type = t;
    switch (a.type) {
    case BLOCK:
        a.output = '#';
        break;
    case PERSO:
        a.output = 'P';
        break;
    case PERSO2:
        a.output = 'P';
        break;
    case BOITE:
        a.output = 'B';
        break;
    case BOITE2:
        a.output = '$';
        break;
    case POINT:
        a.output = '*';
        break;
    default:
        a.output = ' ';
        break;
    }

    return a;
}

void displayBlock(Block b) {
    printf("I'm a %c at (%d, %d)\n", b.output, b.position.x, b.position.y);
}

struct Matrix {
    // Number of line
    int l;
    // Number of column
    int c;
    // Matrix who represent the plateform
    Block** m;
};

typedef struct Matrix Matrix;

/* Matrix constructor. */
Matrix matrix(int line, int column) {
    Matrix a;
    a.l = line;
    a.c = column;
    a.m = malloc(line*sizeof(Block*));
    for (int i = 0; i < line; i++) {
        a.m[i] = malloc(column*sizeof(Block));
    }

    /* Initialize the plateform with '#' */
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            if ((i == 0) || (i == a.l-1) || (j == 0) || (j == a.c-1)) {
                a.m[i][j] = block(coordonnees(i, j), BLOCK);
            }
            else {
                a.m[i][j] = block(coordonnees(i, j), VOID);
            }
        }
    }

    a.m[5][5] = block(coordonnees(5, 5), PERSO);
    a.m[7][7] = block(coordonnees(7, 7), BOITE);
    a.m[4][4] = block(coordonnees(4, 4), POINT);
    a.m[9][9] = block(coordonnees(7, 7), BOITE);
    a.m[2][9] = block(coordonnees(4, 4), POINT);

    return a;
}

/* Affiche une matrice de taille N */
void displayMatrix(Matrix mat) {
    printw("\n");
    for (int i=0; i<mat.l; i++) {
        for (int j=0; j<mat.c; j++) {
            printw("%c", mat.m[i][j].output);
        }
        printw("\n");
    }
}

/* Recherche ou se trouve le personnage P dans la matrice */
Coordonnees searchPerso(Matrix mat) {
    for (int i = 0; i < mat.l; i++) {
        for (int j = 0; j < mat.c; j++) {
            if (mat.m[i][j].output == 'P') {
                return coordonnees(i, j);
            }
        }
    }
    /* On ne trouve pas T */
    return coordonnees(-1, -1);
}

void goToLeft(Matrix mat) {
    Coordonnees a = searchPerso(mat);
    if (mat.m[a.x][a.y].type == PERSO) {
        if (mat.m[a.x][a.y-1].type == VOID) {
            mat.m[a.x][a.y].output = ' ';
            mat.m[a.x][a.y].type = VOID;
            
            mat.m[a.x][a.y-1].output = 'P';
            mat.m[a.x][a.y-1].type = PERSO;
        }
        else if (mat.m[a.x][a.y-1].type == BOITE) {
            if (mat.m[a.x][a.y-2].type == VOID) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x][a.y-1].output = 'P';
                mat.m[a.x][a.y-1].type = PERSO;

                mat.m[a.x][a.y-2].output = 'B';
                mat.m[a.x][a.y-2].type = BOITE;
            }
            else if (mat.m[a.x][a.y-2].type == POINT) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x][a.y-1].output = 'P';
                mat.m[a.x][a.y-1].type = PERSO;

                mat.m[a.x][a.y-2].output = '$';
                mat.m[a.x][a.y-2].type = BOITE2;
            }
        }
        else if (mat.m[a.x][a.y-1].type == BOITE2) {
            if (mat.m[a.x][a.y-2].type == VOID) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x][a.y-1].output = 'P';
                mat.m[a.x][a.y-1].type = PERSO2;

                mat.m[a.x][a.y-2].output = 'B';
                mat.m[a.x][a.y-2].type = BOITE;
            }
            else if (mat.m[a.x][a.y-2].type == POINT) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x][a.y-1].output = 'P';
                mat.m[a.x][a.y-1].type = PERSO2;

                mat.m[a.x][a.y-2].output = '$';
                mat.m[a.x][a.y-2].type = BOITE2;
            }
        }
        else if (mat.m[a.x][a.y-1].type == POINT) {
            mat.m[a.x][a.y].output = ' ';
            mat.m[a.x][a.y].type = VOID;

            mat.m[a.x][a.y-1].output = 'P';
            mat.m[a.x][a.y-1].type = PERSO2;
        }
    }
    else {
        if (mat.m[a.x][a.y-1].type == VOID) {
            mat.m[a.x][a.y].output = '*';
            mat.m[a.x][a.y].type = POINT;
            
            mat.m[a.x][a.y-1].output = 'P';
            mat.m[a.x][a.y-1].type = PERSO;
        }
        else if (mat.m[a.x][a.y-1].type == BOITE) {
            if (mat.m[a.x][a.y-2].type == VOID) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x][a.y-1].output = 'P';
                mat.m[a.x][a.y-1].type = PERSO;

                mat.m[a.x][a.y-2].output = 'B';
                mat.m[a.x][a.y-2].type = BOITE;
            }
            else if (mat.m[a.x][a.y-2].type == POINT) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x][a.y-1].output = 'P';
                mat.m[a.x][a.y-1].type = PERSO;

                mat.m[a.x][a.y-2].output = '$';
                mat.m[a.x][a.y-2].type = BOITE2;
            }
        }
        else if (mat.m[a.x][a.y-1].type == BOITE2) {
            if (mat.m[a.x][a.y-2].type == VOID) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x][a.y-1].output = 'P';
                mat.m[a.x][a.y-1].type = PERSO2;

                mat.m[a.x][a.y-2].output = 'B';
                mat.m[a.x][a.y-2].type = BOITE;
            }
            else if (mat.m[a.x][a.y-2].type == POINT) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x][a.y-1].output = 'P';
                mat.m[a.x][a.y-1].type = PERSO2;

                mat.m[a.x][a.y-2].output = '$';
                mat.m[a.x][a.y-2].type = BOITE2;
            }
        }
    }
}

void goToRight(Matrix mat) {
    Coordonnees a = searchPerso(mat);
    if (mat.m[a.x][a.y].type == PERSO) {
        if (mat.m[a.x][a.y+1].type == VOID) {
            mat.m[a.x][a.y].output = ' ';
            mat.m[a.x][a.y].type = VOID;
            
            mat.m[a.x][a.y+1].output = 'P';
            mat.m[a.x][a.y+1].type = PERSO;
        }
        else if (mat.m[a.x][a.y+1].type == BOITE) {
            if (mat.m[a.x][a.y+2].type == VOID) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x][a.y+1].output = 'P';
                mat.m[a.x][a.y+1].type = PERSO;

                mat.m[a.x][a.y+2].output = 'B';
                mat.m[a.x][a.y+2].type = BOITE;
            }
            else if (mat.m[a.x][a.y+2].type == POINT) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x][a.y+1].output = 'P';
                mat.m[a.x][a.y+1].type = PERSO;

                mat.m[a.x][a.y+2].output = '$';
                mat.m[a.x][a.y+2].type = BOITE2;
            }
        }
        else if (mat.m[a.x][a.y+1].type == BOITE2) {
            if (mat.m[a.x][a.y+2].type == VOID) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x][a.y+1].output = 'P';
                mat.m[a.x][a.y+1].type = PERSO2;

                mat.m[a.x][a.y+2].output = 'B';
                mat.m[a.x][a.y+2].type = BOITE;
            }
            else if (mat.m[a.x][a.y+2].type == POINT) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x][a.y+1].output = 'P';
                mat.m[a.x][a.y+1].type = PERSO2;

                mat.m[a.x][a.y+2].output = '$';
                mat.m[a.x][a.y+2].type = BOITE2;
            }
        }
        else if (mat.m[a.x][a.y+1].type == POINT) {
            mat.m[a.x][a.y].output = ' ';
            mat.m[a.x][a.y].type = VOID;

            mat.m[a.x][a.y+1].output = 'P';
            mat.m[a.x][a.y+1].type = PERSO2;
        }
    }
    else {
        if (mat.m[a.x][a.y+1].type == VOID) {
            mat.m[a.x][a.y].output = '*';
            mat.m[a.x][a.y].type = POINT;
            
            mat.m[a.x][a.y+1].output = 'P';
            mat.m[a.x][a.y+1].type = PERSO;
        }
        else if (mat.m[a.x][a.y+1].type == BOITE) {
            if (mat.m[a.x][a.y+2].type == VOID) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x][a.y+1].output = 'P';
                mat.m[a.x][a.y+1].type = PERSO;

                mat.m[a.x][a.y+2].output = 'B';
                mat.m[a.x][a.y+2].type = BOITE;
            }
            else if (mat.m[a.x][a.y+2].type == POINT) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x][a.y+1].output = 'P';
                mat.m[a.x][a.y+1].type = PERSO;

                mat.m[a.x][a.y+2].output = '$';
                mat.m[a.x][a.y+2].type = BOITE2;
            }
        }
        else if (mat.m[a.x][a.y+1].type == BOITE2) {
            if (mat.m[a.x][a.y+2].type == VOID) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x][a.y+1].output = 'P';
                mat.m[a.x][a.y+1].type = PERSO2;

                mat.m[a.x][a.y+2].output = 'B';
                mat.m[a.x][a.y+2].type = BOITE;
            }
            else if (mat.m[a.x][a.y+2].type == POINT) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x][a.y+1].output = 'P';
                mat.m[a.x][a.y+1].type = PERSO2;

                mat.m[a.x][a.y+2].output = '$';
                mat.m[a.x][a.y+2].type = BOITE2;
            }
        }
    }
}

void goToDown(Matrix mat) {
    Coordonnees a = searchPerso(mat);
    if (mat.m[a.x][a.y].type == PERSO) {
        if (mat.m[a.x+1][a.y].type == VOID) {
            mat.m[a.x][a.y].output = ' ';
            mat.m[a.x][a.y].type = VOID;
            
            mat.m[a.x+1][a.y].output = 'P';
            mat.m[a.x+1][a.y].type = PERSO;
        }
        else if (mat.m[a.x+1][a.y].type == BOITE) {
            if (mat.m[a.x+2][a.y].type == VOID) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x+1][a.y].output = 'P';
                mat.m[a.x+1][a.y].type = PERSO;

                mat.m[a.x+2][a.y].output = 'B';
                mat.m[a.x+2][a.y].type = BOITE;
            }
            else if (mat.m[a.x+2][a.y].type == POINT) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x+1][a.y].output = 'P';
                mat.m[a.x+1][a.y].type = PERSO;

                mat.m[a.x+2][a.y].output = '$';
                mat.m[a.x+2][a.y].type = BOITE2;
            }
        }
        else if (mat.m[a.x+1][a.y].type == BOITE2) {
            if (mat.m[a.x+2][a.y].type == VOID) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x+1][a.y].output = 'P';
                mat.m[a.x+1][a.y].type = PERSO2;

                mat.m[a.x+2][a.y].output = 'B';
                mat.m[a.x+2][a.y].type = BOITE;
            }
            else if (mat.m[a.x+2][a.y].type == POINT) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x+1][a.y].output = 'P';
                mat.m[a.x+1][a.y].type = PERSO2;

                mat.m[a.x+2][a.y].output = '$';
                mat.m[a.x+2][a.y].type = BOITE2;
            }
        }
        else if (mat.m[a.x+1][a.y].type == POINT) {
            mat.m[a.x][a.y].output = ' ';
            mat.m[a.x][a.y].type = VOID;

            mat.m[a.x+1][a.y].output = 'P';
            mat.m[a.x+1][a.y].type = PERSO2;
        }
    }
    else {
        if (mat.m[a.x+1][a.y].type == VOID) {
            mat.m[a.x][a.y].output = '*';
            mat.m[a.x][a.y].type = POINT;
            
            mat.m[a.x+1][a.y].output = 'P';
            mat.m[a.x+1][a.y].type = PERSO;
        }
        else if (mat.m[a.x+1][a.y].type == BOITE) {
            if (mat.m[a.x+2][a.y].type == VOID) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x+1][a.y].output = 'P';
                mat.m[a.x+1][a.y].type = PERSO;

                mat.m[a.x+2][a.y].output = 'B';
                mat.m[a.x+2][a.y].type = BOITE;
            }
            else if (mat.m[a.x+2][a.y].type == POINT) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x+1][a.y].output = 'P';
                mat.m[a.x+1][a.y].type = PERSO;

                mat.m[a.x+2][a.y].output = '$';
                mat.m[a.x+2][a.y].type = BOITE2;
            }
        }
        else if (mat.m[a.x+1][a.y].type == BOITE2) {
            if (mat.m[a.x+2][a.y].type == VOID) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x+1][a.y].output = 'P';
                mat.m[a.x+1][a.y].type = PERSO2;

                mat.m[a.x+2][a.y].output = 'B';
                mat.m[a.x+2][a.y].type = BOITE;
            }
            else if (mat.m[a.x+2][a.y].type == POINT) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x+1][a.y].output = 'P';
                mat.m[a.x+1][a.y].type = PERSO2;

                mat.m[a.x+2][a.y].output = '$';
                mat.m[a.x+2][a.y].type = BOITE2;
            }
        }
    }
}

void goToUp(Matrix mat) {
    Coordonnees a = searchPerso(mat);
    if (mat.m[a.x][a.y].type == PERSO) {
        if (mat.m[a.x-1][a.y].type == VOID) {
            mat.m[a.x][a.y].output = ' ';
            mat.m[a.x][a.y].type = VOID;
            
            mat.m[a.x-1][a.y].output = 'P';
            mat.m[a.x-1][a.y].type = PERSO;
        }
        else if (mat.m[a.x-1][a.y].type == BOITE) {
            if (mat.m[a.x-2][a.y].type == VOID) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x-1][a.y].output = 'P';
                mat.m[a.x-1][a.y].type = PERSO;

                mat.m[a.x-2][a.y].output = 'B';
                mat.m[a.x-2][a.y].type = BOITE;
            }
            else if (mat.m[a.x-2][a.y].type == POINT) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x-1][a.y].output = 'P';
                mat.m[a.x-1][a.y].type = PERSO;

                mat.m[a.x-2][a.y].output = '$';
                mat.m[a.x-2][a.y].type = BOITE2;
            }
        }
        else if (mat.m[a.x-1][a.y].type == BOITE2) {
            if (mat.m[a.x-2][a.y].type == VOID) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x-1][a.y].output = 'P';
                mat.m[a.x-1][a.y].type = PERSO2;

                mat.m[a.x-2][a.y].output = 'B';
                mat.m[a.x-2][a.y].type = BOITE;
            }
            else if (mat.m[a.x-2][a.y].type == POINT) {
                mat.m[a.x][a.y].output = ' ';
                mat.m[a.x][a.y].type = VOID;

                mat.m[a.x-1][a.y].output = 'P';
                mat.m[a.x-1][a.y].type = PERSO2;

                mat.m[a.x-2][a.y].output = '$';
                mat.m[a.x-2][a.y].type = BOITE2;
            }
        }
        else if (mat.m[a.x-1][a.y].type == POINT) {
            mat.m[a.x][a.y].output = ' ';
            mat.m[a.x][a.y].type = VOID;

            mat.m[a.x-1][a.y].output = 'P';
            mat.m[a.x-1][a.y].type = PERSO2;
        }
    }
    else {
        if (mat.m[a.x-1][a.y].type == VOID) {
            mat.m[a.x][a.y].output = '*';
            mat.m[a.x][a.y].type = POINT;
            
            mat.m[a.x-1][a.y].output = 'P';
            mat.m[a.x-1][a.y].type = PERSO;
        }
        else if (mat.m[a.x-1][a.y].type == BOITE) {
            if (mat.m[a.x-2][a.y].type == VOID) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x-1][a.y].output = 'P';
                mat.m[a.x-1][a.y].type = PERSO;

                mat.m[a.x-2][a.y].output = 'B';
                mat.m[a.x-2][a.y].type = BOITE;
            }
            else if (mat.m[a.x-2][a.y].type == POINT) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x-1][a.y].output = 'P';
                mat.m[a.x-1][a.y].type = PERSO;

                mat.m[a.x-2][a.y].output = '$';
                mat.m[a.x-2][a.y].type = BOITE2;
            }
        }
        else if (mat.m[a.x-1][a.y].type == BOITE2) {
            if (mat.m[a.x-2][a.y].type == VOID) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x-1][a.y].output = 'P';
                mat.m[a.x-1][a.y].type = PERSO2;

                mat.m[a.x-2][a.y].output = 'B';
                mat.m[a.x-2][a.y].type = BOITE;
            }
            else if (mat.m[a.x-2][a.y].type == POINT) {
                mat.m[a.x][a.y].output = '*';
                mat.m[a.x][a.y].type = POINT;

                mat.m[a.x-1][a.y].output = 'P';
                mat.m[a.x-1][a.y].type = PERSO2;

                mat.m[a.x-2][a.y].output = '$';
                mat.m[a.x-2][a.y].type = BOITE2;
            }
        }
    }
}
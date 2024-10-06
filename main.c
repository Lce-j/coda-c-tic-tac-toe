#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char grille[3][3];

void initialiserGrille() {
    int numero = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grille[i][j] = ' ';  
        }
    }
}

void afficherGrille() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", grille[i][j]);
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n---|---|---\n");
    }
    printf("\n");
}

int verifierVictoire() {
    for (int i = 0; i < 3; i++) {
        if (grille[i][0] == grille[i][1] && grille[i][1] == grille[i][2])
            return 1;
    }

    for (int i = 0; i < 3; i++) {
        if (grille[0][i] == grille[1][i] && grille[1][i] == grille[2][i])
            return 1;
    }

    if (grille[0][0] == grille[1][1] && grille[1][1] == grille[2][2])
        return 1;
    if (grille[0][2] == grille[1][1] && grille[1][1] == grille[2][0])
        return 1;

    return 0;
}

int grillePleine() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grille[i][j] != 'X' && grille[i][j] != 'O')
                return 0;
        }
    }
    return 1;
}

void jouerOrdinateur() {
    int ligne, colonne;
    srand(time(NULL));
    do {
        ligne = rand() % 3;
        colonne = rand() % 3;
    } while (grille[ligne][colonne] == 'X' || grille[ligne][colonne] == 'O');

    grille[ligne][colonne] = 'O';
    printf("L'ordinateur a joué.\n");
}


int main() {
    int choix;
    char joueur = 'X';
    initialiserGrille();

    while (1) {
        afficherGrille();

        if (joueur == 'X') {
            printf("Joueur %c, entrez votre choix (1 à 9) : ", joueur);
            scanf("%d", &choix);

            if (choix < 1 || choix > 9) {
                printf("Choix invalide, réessayez.\n");
                continue;
            }

            int ligne = (choix - 1) / 3;
            int colonne = (choix - 1) % 3;

            if (grille[ligne][colonne] == 'X' || grille[ligne][colonne] == 'O') {
                printf("Cette case est déjà prise, réessayez.\n");
                continue;
            }

            grille[ligne][colonne] = joueur;
        } 
        else {
            jouerOrdinateur();
        }

        if (verifierVictoire()) {
            afficherGrille();
            printf("Félicitations ! Le joueur %c a gagné !\n", joueur);
            break;
        }

        if (grillePleine()) {
            afficherGrille();
            printf("Match nul !\n");
            break;
        }

        joueur = (joueur == 'X') ? 'O' : 'X';
    }

    return 0;
}
/* Loé Lavaud
 * SI-C1b
 * 14.02.2022
 * bataille navale
 */

#include <stdio.h>
#include <time.h>
#include <windows.h>

char ligne = 0;
int choix = 0, colonne = 1;
int tableau_adverse[10][10] = {//tableau de memoire des bateau
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


int score() {
    for (int ligne = 0; ligne < 10; ++ligne) {
        for (int col = 0; col < 10; ++col) {
            return tableau_adverse[ligne][col];
        }
    }
}


void AffichageTableau() {
    printf("\n\n        --------Bataille Navale--------\n\n\n");
    printf("   |_A_|_B_|_C_|_D_|_E_|_F_|_G_|_H_|_I_|_J_|");

    for (int li = 0; li < 10; li++) {
        printf("\n%2d |", li + 1);
        for (int col = 0; col < 10; col++) {
            if (tableau_adverse[li][col] >= 0 && tableau_adverse[li][col] <= 5) {
                printf("___|");
            }
            if (tableau_adverse[li][col] == 10) {
                printf("_o_|");
            }
            if (tableau_adverse[li][col] >= 11 && tableau_adverse[li][col] <= 15) {
                printf("_*_|");
            }
            if (tableau_adverse[li][col] >= 21 && tableau_adverse[li][col] <= 25) {
                printf("_X_|");
            }
        }
    }
}


void DemandeJouer() {
    do {
        printf("\n\nQuelles case veux-tu jouer ?(A-F)");
        scanf("%s", &ligne);

        if (ligne >= 97 && ligne <= 106) { //passer de lettres a chiffre avec la table ASCII
            ligne -= 97;
        } else {
            ligne -= 65;
        }

        if (ligne >= 10 || ligne < 0) { //mettre une erreur si le chiffre n'est pas bon
            printf("coordonnée introuvable !!!");
        }

    } while (ligne >= 10 || ligne < 0); //repeter jusqu'à se que le chiffre sois bon

    do {
        printf("\nQuelles case veux-tu jouer ?(1-10)");
        scanf("%d", &colonne);

        colonne -= 1;//toujours la table ASCII

        if (colonne >= 10 || colonne < 0) {
            printf("coordonnée introuvable !!!\n");
        }

    } while (colonne >= 10 || colonne < 0);
}


int main() {
    SetConsoleOutputCP(65001);//pouvoir mettre des accents


    printf("\nQue voulez-vous faire ?\n\n");//menu
    printf("1 : Apprendre à jouer\n"
           "2 : Jouer contre un ordi\n"
           "3 : Jouer tout seul\n"
           "4 : Quitter\n");
    scanf("%d", &choix);

    switch (choix) {
        case 1:

            break;
        case 2:
            break;
        case 3:
            do {
                AffichageTableau();

                DemandeJouer();

                if (tableau_adverse[colonne][ligne] == 0) { //changer les chiffres du tableau pour pouvoir afficher l'endroit ou j'ai tirer
                    tableau_adverse[colonne][ligne] = 10;
                }
                if (tableau_adverse[colonne][ligne] == 1) {
                    tableau_adverse[colonne][ligne] = 11;
                }
                if (tableau_adverse[colonne][ligne] == 2) {
                    tableau_adverse[colonne][ligne] = 12;
                }
                if (tableau_adverse[colonne][ligne] == 3) {
                    tableau_adverse[colonne][ligne] = 13;
                }
                if (tableau_adverse[colonne][ligne] == 4) {
                    tableau_adverse[colonne][ligne] = 14;
                }
                if (tableau_adverse[colonne][ligne] == 5) {
                    tableau_adverse[colonne][ligne] = 15;
                }
            } while (score() >= 1 && score() <= 5);
        default:
            printf(" \nMerci et au revoir !\n");
            return 0;
    }
    return 0;
}
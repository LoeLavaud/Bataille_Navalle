/* Loé Lavaud
 * SI-C1b
 * 14.02.2022
 * bataille navale
 */

#include <stdio.h>
#include <time.h>
#include <windows.h>

char ligne = 0, name[30];
unsigned char saisie = 50;
int choix = 0, colonne = 1, nbtir, GrilleChoisi = 0;
int tableau_adverse[10][10] = {//tableau de memoire des bateau
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
    int nbbateau = 0;
    for (int li = 0; li < 10; li++) {
        for (int col = 0; col < 10; ++col) {
            if (tableau_adverse[li][col] >= 1 && tableau_adverse[li][col] <= 5) {
                nbbateau++;
            }
        }
    }
    return nbbateau;
}


void AffichageTableau(){
    printf("\n\n        --------Bataille Navale--------\n\n");

    printf(" Grille %d\n", GrilleChoisi + 1);

    printf("   |_A_|_B_|_C_|_D_|_E_|_F_|_G_|_H_|_I_|_J_|");

    for (int li = 0; li < 10; li++) { // afficher le tableau
        printf("\n%2d |", li + 1);
        for (int col = 0; col < 10; col++) {
            if (tableau_adverse[li][col] >= 0 && tableau_adverse[li][col] <= 5) {
                printf("___|");
            }
            if (tableau_adverse[li][col] == 10) { //si eau touché, alors ce symbole
                printf("_o_|");
            }
            if (tableau_adverse[li][col] >= 11 && tableau_adverse[li][col] <= 15) { //si bateau touché, alors ce symbole
                printf("_*_|");
            }
            if (tableau_adverse[li][col] >= 21 && tableau_adverse[li][col] <= 25) { //si bateau mort, alors ce symbole
                printf("_X_|");
            }
        }
    }
}


void DemandeJouer() {
    do {
        printf("\n\nQuelles case veux-tu jouer ?(colonne)");
        scanf("%s", &ligne);

        if (ligne >= 97 && ligne <= 106) {
            ligne -= 97;
        } else {
            ligne -= 65;
        }

        if (ligne >= 10 || ligne < 0) {
            printf("coordonnée introuvable !!!");
        }

    } while (ligne >= 10 || ligne < 0);

    do {
        printf("\nQuelles case veux-tu jouer ?(ligne)");
        scanf("%d", &colonne);

        colonne -= 1;

        if (colonne >= 10 || colonne < 0) {
            printf("coordonnée introuvable !!!\n");
        }

    } while (colonne >= 10 || colonne < 0);
}


void afficheFichier(char nomFichier[]) {
    //Cette fonction affiche le fichier texte
    //dont le nom est passé par la variable "nomFichier"
    char chaine[50] = "";//pour lire une ligne, longueur max 50
    FILE *fichier = NULL; // pointeur sur le fichier
    //ouverture du fichier en mode lecture seule
    fichier = fopen(nomFichier, "r");
    // teste si le fichier existe
    if (fichier == NULL) {
        printf("Le fichier n'existe pas!\n");
    } else {
        //lecture de la ligne suivante
        while (fgets(chaine, 50, fichier)) {
            printf("%s", chaine);//affichage ligne (y compris fin de ligne)
        }
        fclose(fichier); // fermeture du fichier
    }
}


void dateHeure(char chaine[]) {
    //Cette fonction va chercher la date et l'heure et l'écrit dans la variable qu'on lui donne
    time_t now;
    int h, min, s, day, month, year;//pour récupérer chaque détail

    time(&now);// Renvoie l'heure actuelle
    struct tm *local = localtime(&now);//structure qui contient chaque détail de l'heure
    h = local->tm_hour;
    min = local->tm_min;
    s = local->tm_sec;
    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;

    // Ecrire dans la chaine les détails du genre 28/03/2022 11:52:05
    sprintf(chaine, "%02d/%02d/%04d %02d:%02d:%02d", day, month, year, h, min, s);

}


void ajouteFichier(char nomFichier[], char ligne[]) {
    //Cette fonction ouvre le fichier nomFichier
    // et ajoute une ligne avec la chaine ligne[]
    FILE *fichier = NULL; // pointeur sur le fichier
    //ouverture du fichier en mode lecture seule
    fichier = fopen(nomFichier, "a");
    // teste si le fichier existe
    if (fichier == NULL) {
        printf("Le fichier n'existe pas!\n");
    } else {
        //Ecrire un saut de ligne puis la ligne
        fputs("\n", fichier);
        fputs(ligne, fichier);
        fclose(fichier); // fermeture du fichier
    }
}


void fnGrille() {
    srand((unsigned) time(NULL));
    int nbGrille = rand() % 5;
    GrilleChoisi = nbGrille;
    FILE *fichier = NULL; // pointeur sur le fichier
    char nomFichier[25] = "";
    sprintf(nomFichier, "../Grille%d.txt", nbGrille + 1);
    //en indiquant que l'on va lire cette fois
    fichier = fopen(nomFichier, "r");
    int x = 0, y = 0; //compteur de caractère
    while (!feof(fichier)) // Tant qu'il reste des caractères à lire
    {
        int c = fgetc(fichier); // lire un caractère
        if (c >= 0 && c <= 5){
            tableau_adverse[y][x] = c - '0';
            // Stocker le chiffre dans le modèle
            //incrementer pour passer sur chaque case du tableau
            x++;
            if (x == 9) {
                y++;
                x = 0;
            }
        }
    }
    fclose(fichier);
}


void ajouteFichierAvecHeure(char nomFichier[]) {
    char dateheure[20] = "";//chaine pour écrire l'heure
    char saisie2[50] = "";

    //récupération de l'heure
    dateHeure(dateheure);
    //Concaténation heure + saisie
    sprintf(saisie2, "%s %s | %d tirs |", dateheure, name, nbtir);
    //Ecriture dans le fichier
    ajouteFichier("../score.txt", saisie2);

}

int lectureFichierVersTableau(char nomFichier[]) {
    //Cette procédure lit le fichier nomFichier (ex: ../BN1.txt dans le répertoire du main.c)
    //on s'attend à un fichier du genre:
    // 0011111000
    // 0000033000... etc
    //et le transforme en fichier BN[10][10]
    char chaine[20];
    FILE *fichier = NULL; // pointeur sur le fichier
    //ouverture du fichier en mode lecture seule
    fichier = fopen(nomFichier, "r");
    // teste si le fichier existe
    if (fichier == NULL) {
        printf("Le fichier n'existe pas!\n");
    } else {
        int ligne = 0;
        //lecture de la ligne suivante (de 0 à 9 max)
        while (fgets(chaine, 20, fichier) && ligne < 10) {
            int co = 0;
            //la boucle s'arrête soit quand on est à 9, soit quand ce n'est pas un chiffre
            while (co < 10 && chaine[co] >= 48 && chaine[co] <= 57) {
                tableau_adverse[ligne][co] = chaine[co] - 48;
                co++;
            }
            ligne++;
        }
        fclose(fichier); // fermeture du fichier
    }
}

int main() {
    SetConsoleOutputCP(65001);

    do {
        printf("\nQue voulez-vous faire ?\n\n");
        printf("1 : Jouer\n"
               "2 : Didacticiel\n"
               "3 : Historique des scores\n"
               "4 : Quitter\n");

        printf("\nVotre choix :");
        scanf("%d", &choix);

        fnGrille();

        switch (choix) {
            case 1:
                nbtir = 0;
                fnGrille();
                do {
                    AffichageTableau();

                    printf("\n\nil restes %d case(s) à toucher", score());
                    printf("\nvous avez tiré %d fois", nbtir);
                    nbtir++;

                    DemandeJouer();

                    if (tableau_adverse[colonne][ligne] >= 0 && tableau_adverse[colonne][ligne] <= 5) {
                        tableau_adverse[colonne][ligne] += 10;
                    }


                } while (score() >= 1);
                AffichageTableau();


                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //mettre le texte en rouge
                printf("\n***********");
                printf("\n* YOU WIN *");
                printf("\n***********\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//remettre le texte en blanc

                printf("Entrez votre nom :");
                scanf("%s", &name);

                ajouteFichierAvecHeure("../score.txt");

                break;

            case 2:
                afficheFichier("../aide.txt");
                break;
            case 3:
                afficheFichier("../score.txt");
                break;
            case 4:
                printf(" \nMerci et au revoir !\n");
                return 0;
        }
    } while (choix < 3);
}

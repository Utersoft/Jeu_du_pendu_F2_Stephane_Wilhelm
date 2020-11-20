#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"


//Cette fonction demande à l'utilisateur d'entrer un mot à chercher
void init_mot(char mot[]){
//BUT : Initialiser le mot caché
//ENTREE : Le mot qui sera caché
//SORTIE : /
    int i = 0;
    int test = 0;
    do{
        test = 0;
        printf("Veuillez entrer un mot.(S'il s'agit d'un mot avec un ou des tiret(s), merci de ne pas les mettre.)\n");
        gets(mot);
        for(i = 0; i < strlen(mot); i++){
            if(mot[i] > 64 && mot[i] < 91){
                mot[i] += 32;
            }
            if(mot[i] == 45){
                test = 1;
            }
        }
    }while(test == 1);
}

//Cette fonction permet de préparer le tableau de caractère qui va s'afficher pour l'utilisateur
void init_affichage(char mot[], char motCache[], int tailleMot){
//BUT : initialiser le tableau de caractère de tiret du bas
//ENTREE : /
//SORTIE : /
    int i = 0;
    for(i = 0; i < tailleMot; i++){
        if ((mot[i] > 64 && mot[i] < 91) || (mot[i] > 96 && mot[i] < 123)){
            motCache[i] = '-';
        }else if(mot[i] == 32){
            motCache[i] = ' ';
        }
    }
}

void ecrire_lettre(char *lettre){
//BUT : Demander une lettre à l'utilisateur
//ENTREE : la lettre saisie par l'utilisateur
//SORTIE : /

    printf("Veuillez entrer une lettre.\n");
    fflush(stdin);
    *lettre = fgetc(stdin);
    if(*lettre > 64 && *lettre < 91){
        *lettre += 32;
    }
}



//Fonction de vérification de la lettre entrée
int verif_lettre (char lettreEntree, char lettreVerif){
//BUT : vérifier que la lettre se trouve dans le mot caché
//ENTREE : /
//SORTIE : /

    if(lettreVerif == lettreEntree){
        return 1;
    }else{
        return 0;
    }
}

//Affichage ou non de la lettre en fonction de sa présence dans le mot
void change_lettre (char lettreEntree, char mot[TAILLEMAX], char motCache[TAILLEMAX], int *testLettre){
//BUT : afficher la lettre entrée en fonction de la vérification de la lettre
//ENTREE : /
//SORTIE : /

    int i = 0;

    for(i = 0; i < strlen(mot); i++){
        if(verif_lettre(lettreEntree, mot[i])){
            motCache[i] = lettreEntree;
            *testLettre = verif_lettre(lettreEntree, mot[i]);
        }
    }
}


//Fonction qui test si le joueur a gagné
int condition_victoire (char mot[], char motVerif[]){
//BUT : tester la condition de victoire du joueur
//ENTREE : /
//SORTIE : /

    if(strcmp(mot, motVerif) == 0){
        return 1;
    }else{
        return 0;
    }

}

//Fonction qui test si le joueur a perdu
int condition_defaite(int compteur){
//BUT : tester la condition de défaite du joueur
//ENTREE : /
//SORTIE : /
    if(compteur <= DEFAITE){
        return 1;
    }else{
        return 0;
    }
}


//Cette fonction permet d'afficher le pendu à chaque étape
void affich_pendu(int compteur){
//BUT : Afficher le pendu pour l'utilisateur
//ENTREE : /
//SORTIE : L'affichage du pendu
    int i = 0, j = 0;
    char pendu[10][10];
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            pendu[i][j] = ' ';
        }
    }
    switch(compteur){
        case 0 :{
            pendu[6][9] = 92;
        }
        case 1 : {
            pendu[6][7] = '/';
        }
        case 2 : {
            pendu[5][8] = '|';
        }
        case 3 : {
            pendu[4][9] = '/';
        }
        case 4 : {
            pendu[4][7] = 92;
        }
        case 5 : {
            pendu[4][8] = 'O';
        }
        case 6 : {
            for(i = 1; i < 4; i++){
                pendu[i][8] = '|';
            }
        }
        case 7 : {
            for(j = 4; j < 9; j++){
                pendu[0][j] = '_';
            }
        }
        case 8 : {
            for(i = 1; i < 10; i++){
                pendu[i][3] = '|';
            }
        }
        case 9 : {
            for(j = 0; j < 10; j++){
                pendu[9][j] = '_';
            }
            break;
        }
    }

    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            printf("%c", pendu[i][j]);
        }
        printf("\n");
    }
}

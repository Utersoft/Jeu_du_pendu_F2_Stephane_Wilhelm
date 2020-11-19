/*//ALGORITHME : Jeu du pendu
//BUT : Demander à l'utilisateur de rentrer des lettres et/ou de proposer un mot pour trouver le mot caché.
//ENTREE : les lettres ou le mot
//SORTIE : les bonnes lettres, la potence


//Cette fonction demande à l'utilisateur d'entrer un mot à chercher
fonction init_mot() : chaine
//BUT : Initialiser le mot caché
//ENTREE : Le mot qui sera caché
//SORTIE : /

var mot : CHAINE

DEBUT
    ECRIRE "Veuillez entrer un mot."
    LIRE mot

    init_mot <- mot
FINFONCTION

//Cette fonction permet de préparer le tableau de caractère qui va s'afficher pour l'utilisateur
fonction init_affichage(chaine : mot) : chaine
//BUT : initialiser le tableau de caractère de tiret du bas
//ENTREE : /
//SORTIE : /
var motCache TABLEAU de CAR
var i <- 0 : ENTIER

DEBUT
    POUR i DE 0 A (longueur(mot) - 1) FAIRE
    DEBUT
        SI ((mot[i] > 64 ET mot[i] < 91) OU (mot[i] > 96 ET mot[i] < 123)) ALORS
        DEBUT
            motCache[i] <- "_"
        SINON
            motCache[i] <- " "
        FINSI
    FINPOUR

    init_affichage <- motCache
FINFONCTION


fonction ecrire_lettre() : CAR
//BUT : Demander une lettre à l'utilisateur
//ENTREE : la lettre saisie par l'utilisateur
//SORTIE : /

var lettre : CAR
DEBUT
    ECRIRE "Veuillez entrer une lettre."
    LIRE lettre
    ecrire_lettre <- lettre
FINFONCTION



//Fonction de vérification de la lettre entrée
fonction verif_lettre (car : lettreEntree, car : lettreVerif) : BOOLEEN
//BUT : vérifier que la lettre se trouve dans le mot caché
//ENTREE : /
//SORTIE : /

DEBUT
    SI (lettreVerif = lettreEntree) ALORS
    DEBUT
        verif_lettre <- VRAI
    SINON
        verif_lettre <- FAUX
    FINSI
FINFONCTION

//Affichage ou non de la lettre en fonction de sa présence dans le mot
fonction change_lettre (car : lettreEntree, chaine : mot, TABLEAU de CAR : motCache) : TABLEAU de CAR
//BUT : afficher la lettre entrée en fonction de la vérification de la lettre
//ENTREE : /
//SORTIE : /

var i <- 0 : ENTIER
DEBUT
    POUR i DE 0 A longueur(mot) - 1 FAIRE
    DEBUT
        SI (verif_lettre(lettreEntree, mot[i])) ALORS
        DEBUT
            motCache[i] <- lettreEntree
        FINSI
    FINPOUR
    change_lettre <- motCache
FINFONCTION


//Permet de tester si le joueur perd un point
fonction perte_point (car : lettreEntree, chaine : mot) : BOOLEEN
//BUT : tester si le joueur s'est trompé
//ENTREE : /
//SORTIE : /

var i <- 0 : ENTIER
var test <- FAUX : BOOLEEN

DEBUT
    POUR i DE 0 A longueur(mot) FAIRE
    DEBUT
        SI (verif_lettre(lettreEntree, mot[i])) ALORS
        DEBUT
            test <- VRAI
        FINSI
    FINPOUR
    perte_point <- test
FINFONCTION


//Fonction qui test si le joueur a gagné
fonction condition_victoire (chaine : mot, TABLEAU de CAR : motCache) : BOOLEEN
//BUT : tester la condition de victoire du joueur
//ENTREE : /
//SORTIE : /

DEBUT
    SI (mot = motCache) ALORS
    DEBUT
        condition_victoire <- VRAI
    SINON
        condition_victoire <-FAUX
    FINSI
FINFONCTION

//Fonction qui test si le joueur a perdu
fonction condition_defaite (ENTIER : compteur) : BOOLEEN
//BUT : tester la condition de défaire du joueur
//ENTREE : /
//SORTIE : /

DEBUT
    SI (compteur <= DEFAITE) ALORS
    DEBUT
        condition_defaite <- VRAI
    SINON
        condition_defaite <-FAUX
    FINSI
FINFONCTION

const ESSAIMAX <- 10
const DEFAITE <- 0

var mot : CHAINE
var letteSaisie : CAR
var motCache TABLEAU de CAR
var compteur <- ESSAIMAX : ENTIER

DEBUT
    mot <- init_mot()
    motCache <- init_affichage(mot)
    TANT QUE (condition_defaite(compteur) = FAUX OU condition_victoire(mot, motCache) = FAUX) FAIRE
    DEBUT
        lettreSaisie <- ecrire_lettre
        motCache <- change_lettre
        SI (perte_point(lettreSaisie, mot)) ALORS
        DEBUT
            compteur --;
            ECRIRE "La lettre n'est pas contenu dans le mot, vous perdez un point. Il vous reste ", compteur, "chance(s)."
        FINSI
    FINTANTQUE
    SI (condition_victoire(mot, motCache) ALORS
        ECRIRE "Bravo, vous avez gagné!"
    SINON
        ECRIRE "Vous avez perdu, le mot était ", mot, "..."
    FINSI
FIN

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ESSAIMAX 10
#define DEFAITE 0
#define TAILLEMAX 50

void init_mot(char mot[TAILLEMAX]);
void init_affichage(char mot[TAILLEMAX], char motCache[TAILLEMAX], int tailleMot;);
char ecrire_lettre();
int verif_lettre(char lettreEntree, char lettreVerif);
void change_lettre (char lettreEntree, char mot[TAILLEMAX], char motCache[TAILLEMAX]);
int perte_point (char lettreEntree, char mot[TAILLEMAX]);
int condition_victoire (char mot[], char motCache[], int tailleMot);
int condition_defaite (int compteur);
void affich_pendu(int compteur);

int main()
{
    char mot[TAILLEMAX];
    char lettreSaisie;
    char motCache[TAILLEMAX];
    int compteur = ESSAIMAX;
    int fin_defaite = 0;
    int fin_victoire = 0;
    int tailleMot = 0;
    char motPropose[TAILLEMAX];
    int choix = 0;

    init_mot(mot);
    tailleMot = strlen(mot);
    init_affichage(mot, motCache, tailleMot);
    system("cls");
    do{
        system("cls");
        printf("%s\n", motCache);
        affich_pendu(compteur);
        printf("Voulez-vous tenter d'entrer un mot?\n");
        printf("1. Oui\n2. Non\n");
        fflush(stdin);
        scanf("%d", &choix);
        //On propose à l'utilisateur de pouvoir entrer le mot directement pour gagné s'il pense l'avoir trouvé
        if(choix == 1){
            printf("Veuillez entrer le mot que vous pensez etre le bon.\n");
            fflush(stdin);
            gets(motPropose);
            //Si le mot est bon, fin_victoire passe à 1 (true)
            fin_victoire = condition_victoire(mot, motPropose, tailleMot);
            //L'utilisateur perd une chance s'il s'est trompé
            if(fin_victoire == 0){
                compteur--;
            }
        }else{
            lettreSaisie = ecrire_lettre();
            change_lettre(lettreSaisie, mot, motCache);
            //On test si le joueur s'est trompé et doit donc perdre une chance
            if(perte_point(lettreSaisie, mot)){
                compteur --;
                printf("La lettre n'est pas contenu dans le mot, vous perdez un point. Il vous reste %d chance(s).\n", compteur);
            }
            //Si le mot est bon, fin_victoire passe à 1 (true)
            fin_victoire = condition_victoire(mot, motCache, tailleMot);
        }
        //Si le compteur passe à 0, fin_defaite passe à 1 (true)
        fin_defaite = condition_defaite(compteur);
        system("pause");
    //On ne peut sortir qu'en ayant fin_defaite sur true ou fin_victoire sur true
    }while((fin_defaite == 0) && (fin_victoire == 0));
    system("cls");
    if(fin_victoire){
        printf("Bravo, vous avez gagne!\n");
    }else{
        printf("Vous avez perdu, le mot etait %s...\n", mot);
        affich_pendu(compteur);
        printf("\nOh non, il est mort!\n");
    }

    return 0;
}


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
            motCache[i] = '_';
        }else if(mot[i] == 32){
            motCache[i] = ' ';
        }else if(mot[i] == 45){
            motCache[i] == '-';
        }
    }
}

char ecrire_lettre(){
//BUT : Demander une lettre à l'utilisateur
//ENTREE : la lettre saisie par l'utilisateur
//SORTIE : /

    char lettre;

    printf("Veuillez entrer une lettre.\n");
    fflush(stdin);
    lettre = fgetc(stdin);
    if(lettre > 64 && lettre < 91){
        lettre += 32;
    }

    return lettre;
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
void change_lettre (char lettreEntree, char mot[TAILLEMAX], char motCache[TAILLEMAX]){
//BUT : afficher la lettre entrée en fonction de la vérification de la lettre
//ENTREE : /
//SORTIE : /

    int i = 0;

    for(i = 0; i < strlen(mot); i++){
        if(verif_lettre(lettreEntree, mot[i])){
            motCache[i] = lettreEntree;
            printf("La lettre etait bien dans le mot.\n");
        }
    }
}


//Permet de tester si le joueur perd un point
int perte_point (char lettreEntree, char mot[]){
//BUT : tester si le joueur s'est trompé
//ENTREE : /
//SORTIE : /

    int i = 0, test = 0;

    for(i = 0; i < strlen(mot); i++){
        if(verif_lettre(lettreEntree, mot[i]) == 0){
            test = 1;
        }else{
            test = 0;
            break;
        }
    }
    return test;
}


//Fonction qui test si le joueur a gagné
int condition_victoire (char mot[], char motCache[], int tailleMot){
//BUT : tester la condition de victoire du joueur
//ENTREE : /
//SORTIE : /
    int i = 0;
    int j = 0;
    for(i = 0; i < tailleMot; i++){
        if(mot[i] == motCache[i]){
            j++;
        }
    }
    if(j == tailleMot){
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"



int main()
{
    char mot[TAILLEMAX];
    char lettreUtilise[100] = {""};
    char lettreSaisie;
    char *pLettreSaisie = &lettreSaisie;
    char motCache[TAILLEMAX];
    int compteur = ESSAIMAX;
    int fin_defaite = 0;
    int fin_victoire = 0;
    int tailleMot = 0;
    char motPropose[TAILLEMAX];
    int choix = 0;
    int i = 0;
    int testLettre = 0;
    int *pTestLettre = &testLettre;

    init_mot(mot);
    tailleMot = strlen(mot);
    init_affichage(mot, motCache, tailleMot);
    system("cls");
    do{
        system("cls");
        *pTestLettre = 0;
        printf("%s\n", motCache);
        affich_pendu(compteur);
        printf("%s\n", lettreUtilise);
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
            fin_victoire = condition_victoire(mot, motPropose);
            //L'utilisateur perd une chance s'il s'est trompé
            if(fin_victoire == 0){
                compteur--;
            }
        }else{
            ecrire_lettre(pLettreSaisie);
            change_lettre(lettreSaisie, mot, motCache, pTestLettre);
            printf("%d\n", testLettre);
            //On test si le joueur s'est trompé et doit donc perdre une chance
            if(testLettre == 0){
                compteur --;
                printf("La lettre n'est pas contenu dans le mot, vous perdez un point. Il vous reste %d chance(s).\n", compteur);
                lettreUtilise[i] = lettreSaisie;
                i++;
            }else{
                printf("La lettre etait bien dans le mot.\n");
            }
            //Si le mot est bon, fin_victoire passe à 1 (true)
            fin_victoire = condition_victoire(mot, motCache);
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

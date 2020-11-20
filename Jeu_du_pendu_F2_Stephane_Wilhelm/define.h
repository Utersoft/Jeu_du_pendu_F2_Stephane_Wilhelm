#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED
#define ESSAIMAX 10
#define DEFAITE 0
#define TAILLEMAX 50

void init_mot(char mot[TAILLEMAX]);
void init_affichage(char mot[TAILLEMAX], char motCache[TAILLEMAX], int tailleMot;);
void ecrire_lettre(char *lettre);
int verif_lettre(char lettreEntree, char lettreVerif);
void change_lettre (char lettreEntree, char mot[TAILLEMAX], char motCache[TAILLEMAX], int *testLettre);
int condition_victoire (char mot[], char motCache[]);
int condition_defaite (int compteur);
void affich_pendu(int compteur);


#endif // DEFINE_H_INCLUDED

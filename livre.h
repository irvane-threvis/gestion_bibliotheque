#ifndef LIVRE_H
#define LIVRE_H

#define TITRE_MAX 100
#define AUTEUR_MAX 50

typedef struct Livre {
    int numero;
    char titre[TITRE_MAX];
    char nom_auteur[AUTEUR_MAX];
    char prenom_auteur[AUTEUR_MAX];
    int annee_edition;
    int nb_exemplaires;
    struct Livre *gauche;
    struct Livre *droite;
} Livre;


Livre* creer_livre(int num, char* titre, char* nom, char* prenom, int annee, int exemplaires);
Livre* ajouter_livre_abr(Livre* racine, Livre* nouveau);
Livre* rechercher_livre_numero(Livre* racine, int numero);
Livre* rechercher_livre_titre(Livre* racine, char* titre);
void afficher_livre(Livre* livre);
int compter_livres(Livre* racine);
Livre** obtenir_tableau_livres(Livre* racine, int* count);
void trier_livres_alphabetique(Livre** livres, int n);
void liberer_abr(Livre* racine);

#endif

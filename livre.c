#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livre.h"

Livre* creer_livre(int num, char* titre, char* nom, char* prenom, int annee, int exemplaires) {
    Livre* nouveau = (Livre*)malloc(sizeof(Livre));
    if (nouveau == NULL) return NULL;

    nouveau->numero = num;
    strncpy(nouveau->titre, titre, TITRE_MAX-1);
    strncpy(nouveau->nom_auteur, nom, AUTEUR_MAX-1);
    strncpy(nouveau->prenom_auteur, prenom, AUTEUR_MAX-1);
    nouveau->annee_edition = annee;
    nouveau->nb_exemplaires = exemplaires;
    nouveau->gauche = NULL;
    nouveau->droite = NULL;
    return nouveau;
}

Livre* ajouter_livre_abr(Livre* racine, Livre* nouveau) {
    if (racine == NULL) return nouveau;
    if (nouveau->numero < racine->numero)
        racine->gauche = ajouter_livre_abr(racine->gauche, nouveau);
    else if (nouveau->numero > racine->numero)
        racine->droite = ajouter_livre_abr(racine->droite, nouveau);
    else {
        printf("Numero deja existant.\n");
        free(nouveau);
    }
    return racine;
}

Livre* rechercher_livre_numero(Livre* racine, int numero) {
    if (racine == NULL || racine->numero == numero) return racine;
    if (numero < racine->numero)
        return rechercher_livre_numero(racine->gauche, numero);
    return rechercher_livre_numero(racine->droite, numero);
}

Livre* rechercher_livre_titre(Livre* racine, char* titre) {
    if (racine == NULL) return NULL;
    if (strcmp(racine->titre, titre) == 0) return racine;
    Livre* gauche = rechercher_livre_titre(racine->gauche, titre);
    if (gauche != NULL) return gauche;
    return rechercher_livre_titre(racine->droite, titre);
}

void afficher_livre(Livre* livre) {
    if (livre == NULL) {
        printf("Livre non trouve.\n");
        return;
    }
    printf("\Veuillez entrer les donnees du livre\n");
    printf("Numero: %d\n", livre->numero);
    printf("Titre: %s\n", livre->titre);
    printf("Auteur: %s %s\n", livre->prenom_auteur, livre->nom_auteur);
    printf("Annee: %d\n", livre->annee_edition);
    printf("Exemplaires: %d\n", livre->nb_exemplaires);
}

int compter_livres(Livre* racine) {
    if (racine == NULL) return 0;
    return 1 + compter_livres(racine->gauche) + compter_livres(racine->droite);
}

void parcours_infixe(Livre* racine, Livre** tableau, int* index) {
    if (racine != NULL) {
        parcours_infixe(racine->gauche, tableau, index);
        tableau[(*index)++] = racine;
        parcours_infixe(racine->droite, tableau, index);
    }
}

Livre** obtenir_tableau_livres(Livre* racine, int* count) {
    *count = compter_livres(racine);
    if (*count == 0) return NULL;

    Livre** tableau = (Livre**)malloc(*count * sizeof(Livre*));
    if (tableau == NULL) return NULL;

    int index = 0;
    parcours_infixe(racine, tableau, &index);
    return tableau;
}

int comparer_titres(const void* a, const void* b) {
    Livre* livreA = *(Livre**)a;
    Livre* livreB = *(Livre**)b;
    return strcmp(livreA->titre, livreB->titre);
}

void trier_livres_alphabetique(Livre** livres, int n) {
    qsort(livres, n, sizeof(Livre*), comparer_titres);
}

void liberer_abr(Livre* racine) {
    if (racine != NULL) {
        liberer_abr(racine->gauche);
        liberer_abr(racine->droite);
        free(racine);
    }
}

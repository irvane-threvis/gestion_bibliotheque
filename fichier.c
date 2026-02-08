#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livre.h"
#include "emprunt.h"
#include "fichier.h"

int sauvegarder_livres(Livre* racine) {
    FILE* fichier = fopen(FICHIER_LIVRES, "w");
    if (fichier == NULL) return 0;

    int count;
    Livre** livres = obtenir_tableau_livres(racine, &count);

    if (livres == NULL || count == 0) {
        fclose(fichier);
        return 1;
    }


    for (int i = 0; i < count; i++) {
        fprintf(fichier, "%d|%s|%s|%s|%d|%d\n",
               livres[i]->numero,
               livres[i]->titre,
               livres[i]->nom_auteur,
               livres[i]->prenom_auteur,
               livres[i]->annee_edition,
               livres[i]->nb_exemplaires);
    }

    free(livres);
    fclose(fichier);
    return 1;
}

Livre* charger_livres() {
    FILE* fichier = fopen(FICHIER_LIVRES, "r");
    if (fichier == NULL) return NULL;

    Livre* racine = NULL;
    char ligne[256];
    int count = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {

        if (strlen(ligne) <= 1) continue;


        if (strchr(ligne, '|') != NULL) {
            int numero, annee, exemplaires;
            char titre[100], nom[50], prenom[50];

            char* token = strtok(ligne, "|");
            if (token) numero = atoi(token);

            token = strtok(NULL, "|");
            if (token) strcpy(titre, token);

            token = strtok(NULL, "|");
            if (token) strcpy(nom, token);

            token = strtok(NULL, "|");
            if (token) strcpy(prenom, token);

            token = strtok(NULL, "|");
            if (token) annee = atoi(token);

            token = strtok(NULL, "|\n");
            if (token) exemplaires = atoi(token);

            Livre* nouveau = creer_livre(numero, titre, nom, prenom, annee, exemplaires);
            if (nouveau != NULL) {
                racine = ajouter_livre_abr(racine, nouveau);
                count++;
            }
        }
    }

    fclose(fichier);
    if (count > 0) {
        printf("%d livres charges depuis %s\n", count, FICHIER_LIVRES);
    }
    return racine;
}

int sauvegarder_emprunts(Emprunt* tete) {
    FILE* fichier = fopen(FICHIER_EMPRUNTS, "w");
    if (fichier == NULL) return 0;

    Emprunt* courant = tete;
    int count = 0;


    while (courant != NULL) {
        fprintf(fichier, "%d|%d|%s|%s|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d\n",
               courant->numero_livre,
               courant->numero_etudiant,
               courant->nom_etudiant,
               courant->prenom_etudiant,
               courant->date_emprunt.jour, courant->date_emprunt.mois, courant->date_emprunt.annee,
               courant->date_emprunt.heure, courant->date_emprunt.minute,
               courant->date_retour.jour, courant->date_retour.mois, courant->date_retour.annee,
               courant->date_retour.heure, courant->date_retour.minute,
               courant->est_retourne);

        courant = courant->suivant;
        count++;
    }

    fclose(fichier);
    return 1;
}

Emprunt* charger_emprunts() {
    FILE* fichier = fopen(FICHIER_EMPRUNTS, "r");
    if (fichier == NULL) return NULL;

    Emprunt* tete = NULL;
    Emprunt* dernier = NULL;
    char ligne[256];
    int count = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {

        if (strlen(ligne) <= 1) continue;


        if (strchr(ligne, '|') != NULL) {
            Emprunt* nouveau = (Emprunt*)malloc(sizeof(Emprunt));
            if (nouveau == NULL) break;


            char* token = strtok(ligne, "|");
            if (token) nouveau->numero_livre = atoi(token);

            token = strtok(NULL, "|");
            if (token) nouveau->numero_etudiant = atoi(token);

            token = strtok(NULL, "|");
            if (token) strcpy(nouveau->nom_etudiant, token);

            token = strtok(NULL, "|");
            if (token) strcpy(nouveau->prenom_etudiant, token);

            token = strtok(NULL, "|");
            if (token) nouveau->date_emprunt.jour = atoi(token);
            token = strtok(NULL, "|");
            if (token) nouveau->date_emprunt.mois = atoi(token);
            token = strtok(NULL, "|");
            if (token) nouveau->date_emprunt.annee = atoi(token);
            token = strtok(NULL, "|");
            if (token) nouveau->date_emprunt.heure = atoi(token);
            token = strtok(NULL, "|");
            if (token) nouveau->date_emprunt.minute = atoi(token);

            token = strtok(NULL, "|");
            if (token) nouveau->date_retour.jour = atoi(token);
            token = strtok(NULL, "|");
            if (token) nouveau->date_retour.mois = atoi(token);
            token = strtok(NULL, "|");
            if (token) nouveau->date_retour.annee = atoi(token);
            token = strtok(NULL, "|");
            if (token) nouveau->date_retour.heure = atoi(token);
            token = strtok(NULL, "|");
            if (token) nouveau->date_retour.minute = atoi(token);

            token = strtok(NULL, "|\n");
            if (token) nouveau->est_retourne = atoi(token);

            nouveau->suivant = NULL;

            if (tete == NULL) {
                tete = nouveau;
                dernier = nouveau;
            } else {
                dernier->suivant = nouveau;
                dernier = nouveau;
            }

            count++;
        }
    }

    fclose(fichier);
    if (count > 0) {
        printf("%d emprunts charges depuis %s\n", count, FICHIER_EMPRUNTS);
    }
    return tete;
}

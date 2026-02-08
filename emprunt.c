#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "emprunt.h"

DateGMT obtenir_date_gmt_actuelle() {
    time_t now;
    struct tm *gmt_time;
    time(&now);
    gmt_time = gmtime(&now);

    DateGMT date;
    date.jour = gmt_time->tm_mday;
    date.mois = gmt_time->tm_mon + 1;
    date.annee = gmt_time->tm_year + 1900;
    date.heure = gmt_time->tm_hour;
    date.minute = gmt_time->tm_min;
    return date;
}

int comparer_dates_gmt(DateGMT d1, DateGMT d2) {
    if (d1.annee != d2.annee) return d1.annee - d2.annee;
    if (d1.mois != d2.mois) return d1.mois - d2.mois;
    if (d1.jour != d2.jour) return d1.jour - d2.jour;
    if (d1.heure != d2.heure) return d1.heure - d2.heure;
    return d1.minute - d2.minute;
}

Emprunt* creer_emprunt(int num_livre, int num_etudiant, char* nom, char* prenom, int duree_jours) {
    Emprunt* nouveau = (Emprunt*)malloc(sizeof(Emprunt));
    if (nouveau == NULL) return NULL;

    nouveau->numero_livre = num_livre;
    nouveau->numero_etudiant = num_etudiant;
    strncpy(nouveau->nom_etudiant, nom, 49);
    strncpy(nouveau->prenom_etudiant, prenom, 49);
    nouveau->nom_etudiant[49] = '\0';
    nouveau->prenom_etudiant[49] = '\0';

    nouveau->date_emprunt = obtenir_date_gmt_actuelle();

    time_t maintenant;
    time(&maintenant);
    struct tm *gmt = gmtime(&maintenant);
    gmt->tm_mday += duree_jours;
    mktime(gmt);

    nouveau->date_retour.jour = gmt->tm_mday;
    nouveau->date_retour.mois = gmt->tm_mon + 1;
    nouveau->date_retour.annee = gmt->tm_year + 1900;
    nouveau->date_retour.heure = 23;
    nouveau->date_retour.minute = 59;

    nouveau->est_retourne = 0;
    nouveau->suivant = NULL;
    return nouveau;
}

Emprunt* ajouter_emprunt(Emprunt* tete, Emprunt* nouveau) {
    if (tete == NULL) return nouveau;
    nouveau->suivant = tete;
    return nouveau;
}

int retourner_livre(Emprunt* tete, int num_livre, int num_etudiant) {
    Emprunt* courant = tete;
    while (courant != NULL) {
        if (courant->numero_livre == num_livre &&
            courant->numero_etudiant == num_etudiant &&
            courant->est_retourne == 0) {
            courant->est_retourne = 1;
            courant->date_retour = obtenir_date_gmt_actuelle();
            return 1;
        }
        courant = courant->suivant;
    }
    return 0;
}

int compter_emprunts_non_retournes(Emprunt* tete, int num_livre) {
    int count = 0;
    Emprunt* courant = tete;
    while (courant != NULL) {
        if (courant->numero_livre == num_livre && courant->est_retourne == 0)
            count++;
        courant = courant->suivant;
    }
    return count;
}

void liberer_liste_emprunts(Emprunt* tete) {
    Emprunt* courant = tete;
    Emprunt* suivant;
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}

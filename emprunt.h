#ifndef EMPRUNT_H
#define EMPRUNT_H

#include <time.h>

typedef struct {
    int jour;
    int mois;
    int annee;
    int heure;
    int minute;
} DateGMT;

typedef struct Emprunt {
    int numero_livre;
    int numero_etudiant;
    char nom_etudiant[50];
    char prenom_etudiant[50];
    DateGMT date_emprunt;
    DateGMT date_retour;
    int est_retourne;
    struct Emprunt *suivant;
} Emprunt;


DateGMT obtenir_date_gmt_actuelle();
int comparer_dates_gmt(DateGMT d1, DateGMT d2);
Emprunt* creer_emprunt(int num_livre, int num_etudiant, char* nom, char* prenom, int duree_jours);
Emprunt* ajouter_emprunt(Emprunt* tete, Emprunt* nouveau);
int retourner_livre(Emprunt* tete, int num_livre, int num_etudiant);
int compter_emprunts_non_retournes(Emprunt* tete, int num_livre);
void liberer_liste_emprunts(Emprunt* tete);

#endif

#ifndef FICHIER_H
#define FICHIER_H

#include "livre.h"
#include "emprunt.h"

#define FICHIER_LIVRES "livres.txt"
#define FICHIER_EMPRUNTS "emprunts.txt"


int sauvegarder_livres(Livre* racine);
Livre* charger_livres();
int sauvegarder_emprunts(Emprunt* tete);
Emprunt* charger_emprunts();

#endif

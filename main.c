#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livre.h"
#include "emprunt.h"
#include "fichier.h"

void afficher_menu() {
    printf("\n=== GESTION DE BIBLIOTHEQUE UNIVERSITAIRE ===\n");
    printf("1. Ajouter un nouveau livre\n");
    printf("2. Afficher tous les livres (titres et auteurs)\n");
    printf("3. Rechercher un livre par son numero\n");
    printf("4. Rechercher un livre par son titre\n");
    printf("5. Verifier si un livre est disponible (par numero)\n");
    printf("6. Afficher livres par ordre alphabetique\n");
    printf("7. Emprunter un livre\n");
    printf("8. Afficher la liste de livres empruntes\n");
    printf("9. Retourner un livre \n");
    printf("10. Affichage de livres empruntes par un etudiant\n");
    printf("11. Affichage de livres non retournes avant une date donnee\n");
    printf("\n0. Quitter le programme\n");
    printf("\n Veuilllez choisir un menu: ");
}

void afficher_livres_tableau(Livre* racine, Emprunt* emprunts) {
    int count;
    Livre** livres = obtenir_tableau_livres(racine, &count);

    if (livres == NULL || count == 0) {
        printf("\n Aucun livre dans la bibliotheque.\n");
        return;
    }

    printf("\n+--------+--------------------------------+----------------------+--------+-------------+-------------+\n");
    printf("| Numero | Titre                          | Auteur               | Annee  | Exemplaires | Disponible  |\n");
    printf("+--------+--------------------------------+----------------------+--------+-------------+-------------+\n");

    for (int i = 0; i < count; i++) {
        int empruntes = compter_emprunts_non_retournes(emprunts, livres[i]->numero);
        int disponibles = livres[i]->nb_exemplaires - empruntes;

        char auteur_complet[80];
        snprintf(auteur_complet, sizeof(auteur_complet), "%s %s",
                 livres[i]->prenom_auteur, livres[i]->nom_auteur);

        printf("| %-6d | %-30s | %-20s | %-6d | %-11d | %-11s |\n",
               livres[i]->numero,
               livres[i]->titre,
               auteur_complet,
               livres[i]->annee_edition,
               livres[i]->nb_exemplaires,
               disponibles > 0 ? "OUI" : "NON");
    }

    printf("+--------+--------------------------------+----------------------+--------+-------------+-------------+\n");
    printf("Total: %d livres\n", count);

    free(livres);
}

int main() {
    Livre* bibliotheque = NULL;
    Emprunt* emprunts = NULL;
    int choix;

    bibliotheque = charger_livres();
    emprunts = charger_emprunts();

    do {
        afficher_menu();
        scanf("%d", &choix);

        switch(choix) {
            case 1: {
                int num, annee, exemplaires;
                char titre[100], nom[50], prenom[50];

                printf("\n INFORMATION DU LIVRE: \n");
                printf("Numero: "); scanf("%d", &num);

                if (rechercher_livre_numero(bibliotheque, num) != NULL) {
                    printf("Erreur: Ce numero existe deja.\n");
                    break;
                }

                printf("Titre: "); getchar(); fgets(titre, 100, stdin); titre[strcspn(titre, "\n")] = 0;
                printf("Nom auteur: "); fgets(nom, 50, stdin); nom[strcspn(nom, "\n")] = 0;
                printf("Prenom auteur: "); fgets(prenom, 50, stdin); prenom[strcspn(prenom, "\n")] = 0;
                printf("Annee: "); scanf("%d", &annee);
                printf("Exemplaires: "); scanf("%d", &exemplaires);

                Livre* nouveau = creer_livre(num, titre, nom, prenom, annee, exemplaires);
                if (nouveau) {
                    bibliotheque = ajouter_livre_abr(bibliotheque, nouveau);
                    sauvegarder_livres(bibliotheque);
                    printf("Livre ajoute avec succes!\n");
                } else {
                    printf("Erreur lors de la creation du livre.\n");
                }
                break;
            }

            case 2: { // Afficher tous les livres
                printf("\n LISTE DES LIVRES \n");
                afficher_livres_tableau(bibliotheque, emprunts);
                break;
            }

            case 3: { // Recherche par numero
                int num;
                printf("\n=== RECHERCHE PAR NUMERO ===\n");
                printf("Numero: "); scanf("%d", &num);

                Livre* livre = rechercher_livre_numero(bibliotheque, num);
                if (livre) {
                    afficher_livre(livre);
                    int empruntes = compter_emprunts_non_retournes(emprunts, num);
                    printf("Exemplaires disponibles: %d/%d\n",
                           livre->nb_exemplaires - empruntes, livre->nb_exemplaires);
                } else {
                    printf("Livre non trouve.\n");
                }
                break;
            }

            case 4: { // Recherche par titre
                char titre[100];
                printf("\n RECHERCHE PAR TITRE \n");
                printf("Titre: "); getchar(); fgets(titre, 100, stdin); titre[strcspn(titre, "\n")] = 0;

                Livre* livre = rechercher_livre_titre(bibliotheque, titre);
                if (livre) {
                    afficher_livre(livre);
                } else {
                    printf("Livre non trouve.\n");
                }
                break;
            }

            case 5: { // Verifier disponibilite
                int num;
                printf("\n VERIFICATION DE DISPONIBILITE \n");
                printf("Numero: "); scanf("%d", &num);

                Livre* livre = rechercher_livre_numero(bibliotheque, num);
                if (livre) {
                    int empruntes = compter_emprunts_non_retournes(emprunts, num);
                    printf("Livre: %s\n", livre->titre);
                    printf("Exemplaires totaux: %d\n", livre->nb_exemplaires);
                    printf("Exemplaires empruntes: %d\n", empruntes);
                    printf("Exemplaires disponibles: %d\n", livre->nb_exemplaires - empruntes);
                    printf("Disponible: %s\n", (livre->nb_exemplaires - empruntes) > 0 ? "OUI" : "NON");
                } else {
                    printf("Livre non trouve.\n");
                }
                break;
            }

            case 6: { // Affichage alphabetique
                printf("\n LIVRES PAR ORDRE ALPHABETIQUE \n");
                int count;
                Livre** livres = obtenir_tableau_livres(bibliotheque, &count);

                if (livres && count > 0) {
                    trier_livres_alphabetique(livres, count);
                    printf("\n+----+--------------------------------+----------------------+\n");
                    printf("| N° | Titre                          | Auteur               |\n");
                    printf("+----+--------------------------------+----------------------+\n");

                    for (int i = 0; i < count; i++) {
                        char auteur[80];
                        snprintf(auteur, sizeof(auteur), "%s %s",
                                 livres[i]->prenom_auteur, livres[i]->nom_auteur);

                        printf("| %-2d | %-30s | %-20s |\n",
                               i+1, livres[i]->titre, auteur);
                    }
                    printf("+----+--------------------------------+----------------------+\n");
                    free(livres);
                } else {
                    printf("Aucun livre dans la bibliotheque.\n");
                }
                break;
            }

            case 7: { // Emprunter un livre
                int num_livre, num_etudiant, duree;
                char nom[50], prenom[50];

                printf("\n=== EMPRUNT D'UN LIVRE ===\n");
                printf("Numero livre: "); scanf("%d", &num_livre);

                Livre* livre = rechercher_livre_numero(bibliotheque, num_livre);
                if (!livre) {
                    printf("Livre non trouve.\n");
                    break;
                }

                int empruntes = compter_emprunts_non_retournes(emprunts, num_livre);
                if (empruntes >= livre->nb_exemplaires) {
                    printf("Tous les exemplaires sont empruntes.\n");
                    break;
                }

                printf("Numero etudiant: "); scanf("%d", &num_etudiant);
                printf("Nom etudiant: "); getchar(); fgets(nom, 50, stdin); nom[strcspn(nom, "\n")] = 0;
                printf("Prenom etudiant: "); fgets(prenom, 50, stdin); prenom[strcspn(prenom, "\n")] = 0;
                printf("Duree (jours): "); scanf("%d", &duree);

                Emprunt* nouvel_emprunt = creer_emprunt(num_livre, num_etudiant, nom, prenom, duree);
                if (nouvel_emprunt) {
                    emprunts = ajouter_emprunt(emprunts, nouvel_emprunt);
                    sauvegarder_emprunts(emprunts);
                    printf("Emprunt enregistre avec succes !\n");

                    // Afficher les details avec heure GMT
                    printf("\nDetails de l'emprunt (GMT) :\n");
                    printf("   Livre: %s\n", livre->titre);
                    printf("   Etudiant: %s %s\n", prenom, nom);
                    printf("   Date emprunt: %02d/%02d/%04d %02d:%02d GMT\n",
                           nouvel_emprunt->date_emprunt.jour, nouvel_emprunt->date_emprunt.mois,
                           nouvel_emprunt->date_emprunt.annee, nouvel_emprunt->date_emprunt.heure,
                           nouvel_emprunt->date_emprunt.minute);
                    printf("   Date retour prevue: %02d/%02d/%04d %02d:%02d GMT\n",
                           nouvel_emprunt->date_retour.jour, nouvel_emprunt->date_retour.mois,
                           nouvel_emprunt->date_retour.annee, nouvel_emprunt->date_retour.heure,
                           nouvel_emprunt->date_retour.minute);
                } else {
                    printf("Erreur lors de la creation de l'emprunt.\n");
                }
                break;
            }

            case 8: { // Afficher livres empruntes
                printf("\n LIVRES EMPRUNTES \n");
                Emprunt* courant = emprunts;
                int count = 0;

                if (emprunts == NULL) {
                    printf("Aucun livre emprunte actuellement.\n");
                    break;
                }

                printf("\n+--------+--------------------------------+--------+---------------------------+---------------------------+\n");
                printf("| Livre  | Titre                          | Etud.  | Date Emprunt (GMT)        | Date Retour (GMT)         |\n");
                printf("+--------+--------------------------------+--------+---------------------------+---------------------------+\n");

                while (courant != NULL) {
                    if (courant->est_retourne == 0) {
                        count++;
                        Livre* livre = rechercher_livre_numero(bibliotheque, courant->numero_livre);
                        char titre[100] = "Inconnu";
                        if (livre) strcpy(titre, livre->titre);

                        printf("| %-6d | %-30s | %-6d | %02d/%02d/%04d %02d:%02d   | %02d/%02d/%04d %02d:%02d   |\n",
                               courant->numero_livre, titre, courant->numero_etudiant,
                               courant->date_emprunt.jour, courant->date_emprunt.mois, courant->date_emprunt.annee,
                               courant->date_emprunt.heure, courant->date_emprunt.minute,
                               courant->date_retour.jour, courant->date_retour.mois, courant->date_retour.annee,
                               courant->date_retour.heure, courant->date_retour.minute);
                    }
                    courant = courant->suivant;
                }

                printf("+--------+--------------------------------+--------+---------------------------+---------------------------+\n");
                printf("Total: %d livre(s) emprunte(s)\n", count);
                break;
            }

            case 9: { // Retourner un livre
                int num_livre, num_etudiant;
                printf("\n RETOUR D'UN LIVRE \n");
                printf("Numero livre: "); scanf("%d", &num_livre);
                printf("Numero etudiant: "); scanf("%d", &num_etudiant);

                if (retourner_livre(emprunts, num_livre, num_etudiant)) {
                    sauvegarder_emprunts(emprunts);
                    printf("Livre retourne avec succes !\n");

                    // Afficher la date de retour actuelle
                    DateGMT maintenant = obtenir_date_gmt_actuelle();
                    printf("   Date de retour: %02d/%02d/%04d %02d:%02d GMT\n",
                           maintenant.jour, maintenant.mois, maintenant.annee,
                           maintenant.heure, maintenant.minute);
                } else {
                    printf("Emprunt non trouve ou deja retourne.\n");
                }
                break;
            }

            case 10: { // Livres empruntes par etudiant
                int num_etudiant;
                printf("\n EMPRUNTS PAR ETUDIANT \n");
                printf("Numero etudiant: "); scanf("%d", &num_etudiant);

                Emprunt* courant = emprunts;
                int trouve = 0;

                printf("\n+--------+--------------------------------+---------------------------+---------------------------+\n");
                printf("| Livre  | Titre                          | Date Emprunt (GMT)        | Date Retour (GMT)         |\n");
                printf("+--------+--------------------------------+---------------------------+---------------------------+\n");

                while (courant != NULL) {
                    if (courant->numero_etudiant == num_etudiant && courant->est_retourne == 0) {
                        trouve = 1;
                        Livre* livre = rechercher_livre_numero(bibliotheque, courant->numero_livre);
                        char titre[100] = "Inconnu";
                        if (livre) strcpy(titre, livre->titre);

                        printf("| %-6d | %-30s | %02d/%02d/%04d %02d:%02d   | %02d/%02d/%04d %02d:%02d   |\n",
                               courant->numero_livre, titre,
                               courant->date_emprunt.jour, courant->date_emprunt.mois, courant->date_emprunt.annee,
                               courant->date_emprunt.heure, courant->date_emprunt.minute,
                               courant->date_retour.jour, courant->date_retour.mois, courant->date_retour.annee,
                               courant->date_retour.heure, courant->date_retour.minute);
                    }
                    courant = courant->suivant;
                }

                printf("+--------+--------------------------------+---------------------------+---------------------------+\n");
                if (!trouve) printf("Aucun emprunt trouve pour cet etudiant.\n");
                break;
            }

            case 11: { // Livres non retournes avant date
                DateGMT date;
                printf("\n LIVRES NON RETOURNES AVANT DATE \n");
                printf("Jour: "); scanf("%d", &date.jour);
                printf("Mois: "); scanf("%d", &date.mois);
                printf("Annee: "); scanf("%d", &date.annee);
                printf("Heure (0-23): "); scanf("%d", &date.heure);
                printf("Minute (0-59): "); scanf("%d", &date.minute);

                Emprunt* courant = emprunts;
                int trouve = 0;

                printf("\n+--------+--------------------------------+--------+---------------------------+---------------------------+\n");
                printf("| Livre  | Titre                          | Etud.  | Date Emprunt (GMT)        | Date Retour prevue (GMT)  |\n");
                printf("+--------+--------------------------------+--------+---------------------------+---------------------------+\n");

                while (courant != NULL) {
                    if (courant->est_retourne == 0 &&
                        comparer_dates_gmt(courant->date_retour, date) < 0) {
                        trouve = 1;
                        Livre* livre = rechercher_livre_numero(bibliotheque, courant->numero_livre);
                        char titre[100] = "Inconnu";
                        if (livre) strcpy(titre, livre->titre);

                        printf("| %-6d | %-30s | %-6d | %02d/%02d/%04d %02d:%02d   | %02d/%02d/%04d %02d:%02d   |\n",
                               courant->numero_livre, titre, courant->numero_etudiant,
                               courant->date_emprunt.jour, courant->date_emprunt.mois, courant->date_emprunt.annee,
                               courant->date_emprunt.heure, courant->date_emprunt.minute,
                               courant->date_retour.jour, courant->date_retour.mois, courant->date_retour.annee,
                               courant->date_retour.heure, courant->date_retour.minute);
                    }
                    courant = courant->suivant;
                }

                printf("+--------+--------------------------------+--------+---------------------------+---------------------------+\n");
                if (!trouve) printf("Aucun livre non retourne avant le %02d/%02d/%04d %02d:%02d GMT.\n",
                                    date.jour, date.mois, date.annee, date.heure, date.minute);
                break;
            }

            case 0: { // Quitter
                printf("\n=== SAUVEGARDE ET FERMETURE ===\n");
                sauvegarder_livres(bibliotheque);
                sauvegarder_emprunts(emprunts);
                printf("Donnees sauvegardees. Au revoir !\n");
                break;
            }

            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }

    } while (choix != 0);

    liberer_abr(bibliotheque);
    liberer_liste_emprunts(emprunts);

    return 0;
}

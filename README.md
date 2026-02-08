# gestion_bibliotheque
1




## Mini-Projet de Structures de données avancées

 Objectif: - Apprendre à utiliser les listes chaînées ;
 - Apprendre à utiliser les structures de données linéaires ;
 - Apprendre à utiliser les arbres (arbres binaires, arbres binaires de recherche (ABR))

Le but de ce mini-projet est de développer un logiciel pour gérer l’opération d’emprunt de livres au sein
d’une bibliothèque universitaire. Les livres de cette bibliothèque sont stockés dans un arbre binaire de
recherche où chaque élément est un livre représenté par : un numéro, un titre, le nom et le prénom de
l’auteur, une année d’édition et un nombre d’exemplaires. Les livres sont insérés dans l’arbre selon leurs
numéros.
Pour gérer l’opération d’emprunt de livres, on propose d’utiliser une liste chainée L où chaque élément
de cette liste est un enregistrement contenant les champs suivants : le numéro du livre emprunté, le
numéro, le nom et le prénom de l’étudiant, la date d’emprunt et la date de retour.
Travail demandé :
Développer un programme C qui doit permettre, à partir d’un menu, de réaliser les tâches suivantes:
Partie 1 :
1) Ajouter un nouveau livre à la l’arbre de livres.
2) Afficher tous les livres de la bibliothèque (affichage de titres et des auteures des livres)
3) Recherche un livre par son numéro (afficher les informations du livre).
4) Rechercher un livre par son titre (afficher les informations du livre s’il existe).
5) Vérifier si un livre identifié par son numéro est disponible ou non.
6) Affichage par ordre alphabétique de la liste de livres de la bibliothèque.
Partie 2 :
1) Emprunter un livre à un étudiant identifié par son numéro pour une période donnée.
2) Afficher la liste de livres empruntés.
3) Traiter le retour d’un livre (identifié par son numéro) emprunté par un étudiant (identifié par son
numéro).
Partie 3 :
1) Affichage de livres empruntés par un étudiant.
2) Affichage de la liste de livres non retournés dans une date donnée.
Travail supplémentaire : utiliser un fichier pour la création et le sauvegarde des deux listes. 
ANNEXE
Gestion du temps en C
La bibliothèque C propose au programmeur plusieurs fonctions et structures de données permettant la
gestion du temps. Ces fonctions et structures de données sont déclarées dans le fichier d’entête
time.h.
I. Récupération de la date et heure système (time)
Prototype
 time_t time(time_t *t);
Description
La fonction time donne le nombre de secondes écoulées depuis le 1er janvier 1970 à 0 heure
GMT. Si le pointeur t est différent de NULL, time place cette valeur à cette adresse. Time_t
définit les valeurs utilisées par les fonctions de gestion de temps; en fait time_t est un alias de
unsigned long.
Valeur retournée
Le temps écoulé en secondes depuis le 1er janvier 1970 à 0 heure GMT.
II. Conversion de la date et l'heure en une chaîne (ctime)
Prototype
 char *ctime(const time_t *t);
Description
La fonction ctime retourne sous la forme d'une chaîne de caractères la date *t d'une manière
formatée et plus explicite : "NNN MMM jj hh:mm:ss AAAA\n\0"
avec :
NNN Nom du jour (Mon, Tue, Wed, etc...)
MMM Nom du mois (Jan, Feb, Mar, etc...)
jj Numéro du jour (1, 2, ..., 31)
hh Heure (1, 2, ..., 24)
mm Minutes (1, ..., 59)
ss Secondes (1, ..., 59)
AAAA Année (1970...)
Valeur retournée
Cette fonction renvoie un pointeur sur une chaîne de caractères contenant la date et l'heure.
II. Conversion d'une date et heure sous format du calendrier
(localtime)
Prototype
 struct tm *localtime(const time_t *t);
Description
Cette fonction convertit la valeur reçue en une structure de type struct tm contenant les
composants temporels et applique des corrections de fuseau horaire et d'heure d'été ("daylight
saving time").
Valeur retournée
localtime retourne un pointeur sur une structure de type struct tm contenant les différents
composants temporels.
La structure struct tm
Structure définissant des subdivisions du temps :
struct tm {
 int tm_sec; /* Secondes */
 int tm_min; /* Minutes */
 int tm_hour; /* Heures (0 - 23) */
 int tm_mday; /* Quantième du mois (1 - 31) */
 int tm_mon; /* Mois (0 - 11) */
3
 int tm_year; /* An (= année calendaire - 1900) */
 int tm_wday; /* Jour de semaine (0 – 6 avec Dimanche = 0) */
 int tm_yday; /* Jour dans l'année (0 - 365) */
 int tm_isdst; /* heure d'été (1 : oui, 0 : non) */
};
Exemple
#include <stdio.h>
#include <time.h>
int main(void)
{
 time_t t;
 struct tm *tb;
 t = time(NULL);
 tb = localtime(&t);
 printf("date et heure : %s\n", ctime(&t));
 printf("Le numéro du mois est: %d\n", tb->tm_mon);
 return 0;
}
/*-- résultat possible de l'exécution ----------------------------
date et heure : Mon Dec 12 10:47:06 1994
Le numéro du mois est: 11
IV. Conversion d'une date et heure au standard GMT (gmtime)
Prototype
 struct tm *gmtime(const time_t *t);
Description
gmtime convertit directement vers l'heure GMT (Greenwich Mean Time), contrairement à
localtime qui applique des corrections de fuseau horaire et d'heure d'été.
Valeur retournée
gmtime retourne un pointeur sur une structure de type struct tm contenant les différents
composants temporels.
V. Conversion de la date et l'heure au format de calendrier en une
chaîne
 (asctime)
Prototype
 char *asctime(const struct tm *tblock);
Description
asctime convertit le contenu de la structure *tblock en une chaîne de 26 caractères au format
suivant : "NNN MMM jj hh:mm:ss AAAA\n\0"
Valeur retournée
Cette fonction renvoie un pointeur sur une chaîne de caractères contenant la date et l'heure.
Exemple
#include <stdio.h>
#include <time.h>
int main(void) {
 time_t t;
 struct tm *tb;
 t = time(NULL);
4
 tb = localtime(&t);
 printf("date et heure : %s", ctime(&t));
 printf("date et heure : %s", asctime(tb));
 return 0;
}
/*-- résultat de l'exécution ----------------------------
date et heure : Mon Dec 12 10:47:52 1994
date et heure : Mon Dec 12 10:47:52 1994
VI. Différence de deux dates (difftime)
Prototype
 double difftime(time_t time2, time_t time1);
Description
La fonction difftime calcule le temps écoulé en secondes entre time2 et time1.
Valeur retournée
Un nombre de type double représentant la différence en secondes.
Exemple
#include <stdio.h>
#include <time.h>
#include <unistd.h> /* sleep() */
int main(void) {
 time_t t1, t2;
 t1 = time(NULL);
 sleep(2); /* attente de 2 secondes */
 t2 = time(NULL);
 printf("difference : %lf secondes\n", difftime(t2, t1) );
 return 0;
}
/*-- résultat de l'exécution -------------------------
difference : 2.000000 secondes
VII. Conversion du temps au format du calendrier (mktime)
Prototype
 time_t mktime(struct tm *t);
Description
La fonction mktime convertit la date et l'heure contenues dans la structure *t en valeurs au
format retourné par la fonction time.
Valeur retournée
Une valeur de type time_t si le temps t a pu être converti sinon mktime retourne la valeur -1.
Exemple
#include <stdio.h>
#include <time.h>
int main(void) {
 struct tm t;
 time_t tps;
 int jour, mois, an;
 printf("Jour : "); scanf("%d", &jour);
 printf("Mois : "); scanf("%d", &mois);
5
 printf("Annee: "); scanf("%d", &an);
 t.tm_year = an - 1900;
 t.tm_mon = mois - 1;
 t.tm_mday = jour;
 t.tm_hour = t.tm_min = t.tm_sec = 0;
 tps = mktime(&t);
 printf("Date et heure: %s\n", ctime(&tps));
 return 0;
}
/*-- résultat de l'exécution -------------------------*/
Jour : 12
Mois : 12
Annee: 1994
Date et heure: Mon Dec 12 00:00:00 1994
#include<stdio.h>
#include<math.h>
#include <time.h>
typedef struct date
 {
 int jour;
 int mois;
 int annee;
 }date;

int anniversaire(date aujourdhui ,date naissance);
date difference(date a,date n);


int main(void)
{
struct tm *infos;
date aujourdhui,naissance,dif;
time_t temps_act;
time(&temps_act); /* Déterminer le temps actuel en secondes*/
infos = localtime(&temps_act);

aujourdhui.jour=infos->tm_mday;
aujourdhui.mois=1+(infos->tm_mon);
aujourdhui.annee=1900+(infos->tm_year);

printf("Entrez votre date de naissance JJ MM AAAA \n");
scanf ("%d %d %d", &(naissance.jour), &(naissance.mois),
&(naissance.annee));
printf("Vous avez %d ans \n",anniversaire(aujourdhui,naissance));
dif = difference(aujourdhui,naissance);
printf("La difference est de %d jours %d mois %d annees\n",
 dif.jour,dif.mois,anniversaire(aujourdhui,naissance));
getch();
return 0;
}
int anniversaire(date a,date n)
{
int tmp;
tmp = (a.annee)-(n.annee);
 if(((n.mois)*31 + (n.jour)) > ((a.mois)*31 + (a.jour)))
6
 tmp=tmp-1;
return tmp;
}

date difference(date a,date n)
{
date diff;
diff.mois = fabs(a.mois - n.mois);
diff.jour = fabs(a.jour - n.jour);
return diff;
}

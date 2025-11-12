#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Déclaration des structures
struct admin{
    char user[25];      // Nom de l'administrateur
    char mdp[25];       // Mot de passe de l'administrateur
};

struct film{
    int id;             // Identifiant unique pour un film
    char duree[10];     // Durée du film
    char titre[25];     // Titre du film
};

struct salle{
    int id;              // Identifiant unique pour une salle
    int capacite;        // Capacité de la salle
    char type_siege[25]; // Type de siège dans la salle
    char type_son[25];   // Type de son dans la salle
};

struct seance{
    int id;                 // Identifiant unique pour une séance
    int id_film;            // Identifiant du film projeté lors de la séance
    int id_salle;           // Identifiant de la salle où se déroule la séance
    char heure_debut[10];   // Heure de début de la séance
};

// Déclaration des fonctions
//-// MENUS //-//
void choix_accueil(int*, int, int*, struct seance*, int, struct admin*, int*, struct salle*, int*, struct film*, int*, char*); // Pointeur, choix utilisateur, connecté ou non, séances, nb de séances, administrateurs, nb d'administrateurs, salles, nb de salles, films, nb de films, utilisateur connecté
struct admin * choix_admin(int, int*, struct film*, int*, struct admin*, int*, struct salle*, int*, struct seance*, int*, char*); // Choix utilisateur, connecté ou non, films, nb de films, administrateurs, nb d'administrateurs, salles, nb de salles, séances, nb de séances, utilisateur connecté
struct admin * choix_admin_admin(int, struct admin*, int*, char*); // Choix utilisateur, administrateurs, nb d'administrateurs, utilisateur connecté
void choix_admin_film(int, struct film*, int*); // Choix utilisateur, films, nb de films
void choix_admin_salle(int, struct salle*, int*); // Choix utilisateur, salles, nb de salles
void choix_admin_seance(int, struct seance*, int*, struct film*, int, struct salle*, int); // Choix utilisateur, séances, nb de séances, films, nb de films, salles, nb de salles

//-// Gestion ADMIN //-//
struct admin * ajout_admin(struct admin*, int*); // Administrateurs, indice du nombre d'administrateurs
struct admin * supprimer_admin(struct admin*, int, char*); // Administrateurs, indice du nombre d'administrateurs, utilisateur connecté
struct admin * modifier_admin(struct admin*, int); // Administrateurs, indice du nombre d'administrateurs
struct admin * modifier_admin_details(struct admin*, int); // Administrateurs, indice de l'administrateur à modifier
int recherche(struct admin*, int, char*); // Administrateurs, indice du nombre d'administrateurs, nom de l'administrateur recherché

//-// Gestion FILM //-//
void ajout_film(struct film*, int*); // Films, indice du nombre de films
void supprimer_film(struct film*, int*); // Films, indice du nombre de films
void arrangement_film(struct film*, int *, int); // Films, indice du nombre de films, indice du film à supprimer
bool supprimer_film_check(struct film*, int); // Films, indice du nombre de films
void modifier_film(struct film*, int); // Films, indice du film à modifier
void modifier_film_details(struct film*, int); // Films, indice du film à modifier
int recherche_fl(struct film*, int, char*); // Films, indice du nombre de films, titre du film recherché

//-// Gestion SALLE //-//
void ajout_salle(struct salle*, int*); // Salles, indice du nombre de salles
void supprimer_salle(struct salle*, int*); // Salles, indice du nombre de salles
bool supprimer_salle_check(struct salle*, int); // Salles, indice du nombre de salles
void arrangement_salle(struct salle*, int*, int); // Salles, indice du nombre de salles, indice de la salle à supprimer
void modifier_salle(struct salle*, int*); // Salles, indice de la salle à modifier
void modifier_salle_choix(struct salle*, int); // Salles, indice de la salle à modifier
int recherche_sa(struct salle*, int, int); // Salles, indice du nombre de salles, identifiant de la salle recherchée

//-// Gestion SEANCE //-//
void ajout_seance(struct seance*, int*, struct film*, int, struct salle*, int); // Séances, indice du nombre de séances, films, indice du nombre de films, salles, indice du nombre de salles
void supprimer_seance(struct seance*, int); // Séances, indice du nombre de séances
void modifier_seance(struct seance*, int, struct film*, int, struct salle*, int); // Séances, indice de la séance à modifier, films, indice du nombre de films, salles, indice du nombre de salles
void modifier_seance_details(struct seance*, int, struct film*, int, struct salle*, int); // Séances, indice de la séance à modifier, films, indice du nombre de films, salles, indice du nombre de salles
int recherche_se(struct seance*, int, int); // Séances, indice du nombre de séances, identifiant de la séance recherchée
int compter_se(struct seance*, int); // Séances, indice du nombre de séances

//-// Déclaration pour le chargement et le sauvegarde des données //-//
int fichiers_presents(); // Vérifie la présence des fichiers de données

struct admin* chargement_ad(int*); // Charge les données des administrateurs, indice du nombre d'administrateurs
void chargement_fl(struct film*, int*); // Charge les données des films, indice du nombre de films
void chargement_sa(struct salle*, int*); // Charge les données des salles, indice du nombre de salles²²²²
void chargement_se(struct seance*, int*); // Charge les données des séances, indice du nombre de séances

void sorties(struct salle*, int, struct seance*, int, struct film*, int, struct admin*, int); // Enregistre les données dans les fichiers, indices
void sortie_salle(struct salle*, int); // Enregistre les données des salles
void sortie_film(struct film*, int); // Enregistre les données des films
void sortie_seance(struct seance*, int); // Enregistre les données des séances
void sortie_admin(struct admin*, int); // Enregistre les données des administrateurs

//-// DECLARATION DES AFFICHAGES //-//
void affichage_salle(struct salle *, int); // Affiche les données des salles
void affichage_admin(struct admin *, int); // Affiche les données des administrateurs
void affichage_film(struct film*, int); // Affiche les données des films
void affichage_seance(struct seance*, int, struct film*, int, struct salle*, int); // Affiche les données des séances
void affichage_seance_triee(struct seance*, int, struct film*, int, struct salle*, int); // Affiche les données des séances triées selon des critères

//-// DECLARATION DES OUTILS //-//
void barre(int nb); // Affiche une barre horizontale pour améliorer la lisibilité des affichages
void fullMaj(char*); // Convertit une chaîne en majuscules

void saisi_char(char*, char*); // Message, variable à modifier
void saisi_char_25(char*, char*); // Message, variable à modifier
void saisi_char_10(char*, char*); // Message, variable à modifier
int saisieInt(char*, int, int); // Saisie d'un entier avec contrôle de validité

int calcul(char*, char*); // Calcule le prix d'une séance en fonction du type de siège et du type de son
int fichier_existe(char*); // Vérifie l'existence d'un fichier

int fonction_menu(char*, int, int, char*, char*); // Affiche un menu et retourne le choix de l'utilisateur
void action_choix(int, int*); // Action selon le choix de l'utilisateur
void connexion(int*, struct admin*, int*, char*); // Connexion d'un administrateur
void deconnexion(int*, char*); // Déconnexion d'un administrateur
int acces_sup(); // Accès en tant que super administrateur


int main()
{
    // Vérifie la présence des fichiers de données nécessaires au démarrage du programme
    int start = fichiers_presents();
    if(start){

        // Déclaration des structures
        struct film fl[100];        //
        struct salle sa[100];       //  STATIQUES
        struct seance se[100];      //

        struct admin *ad=NULL;      //  DYNAMIQUE (pointeur)

        // Chargement des données dans les différentes structures
        int i_ad = 0, i_fl = 0, i_sa = 0, i_se = 0;
        chargement_fl(fl, &i_fl);
        chargement_sa(sa, &i_sa);
        chargement_se(se, &i_se);
        ad = chargement_ad(&i_ad);

        //Gestion de la session utilisateur
        int logged = 0, flag, choix;
        char who[25];
        char menu_accueil[5][45] = {"Afficher la liste des seances sous criteres.", "Se connecter en tant qu'administrateur.", "Arreter le programme"};
        char menu_admin[5][45] = {"Gestion des seances.", "Gestion des films.", "Gestion des salles.", "Gestion des administrateurs.", "Se deconnecter."};

        do{
            flag = 0;
            if(!logged) // S'il n'est pas connecté
            {
                choix = fonction_menu(&menu_accueil[0][0], 45, 3, "Menu d'accueil", ""); // Affiche le sous-menu et retourne le choix
                choix_accueil(&flag, choix, &logged, se, i_se, ad, &i_ad, sa, &i_sa, fl, &i_fl, who); // Fait l'action demandé
            }
            else // S'il est connecté - en tant qu'admin -
            {
                choix = fonction_menu(&menu_admin[0][0], 45, 5, "Menu administrateur", ""); // Affiche le sous-menu et retourne le choix
                ad = choix_admin(choix, &logged, fl, &i_fl, ad, &i_ad, sa, &i_sa, se, &i_se, who); // Fait l'action demandé
            }
        }while(!flag);

        // Enregistre les données dans les fichiers.
        sorties(sa, i_sa, se, i_se, fl, i_fl, ad, i_ad);
    }
}

// Fonction pour la connexion d'un administrateur
void connexion(int* log, struct admin* ad, int *taille, char* who)
{
    char s_login[25], s_mdp[25];
    int i;

    saisi_char_25("Nom d'utilisateur : ", s_login);
    saisi_char_25("Mot de passe : ", s_mdp);

    for(i=0; i<*taille; i++) //On va regarder toutes les combinaisons d'admins/mdp
    {
        if((strcmp(s_login, ad[i].user) == 0) && (strcmp(s_mdp, ad[i].mdp) == 0)) // Si une correspond
        {
            *log = 1; // Accès autorisé
            strcpy(who, ad[i].user); // La variable 'who' permet de savoir qui s'est connecté.
            printf("\nConnexion reussie ! Bienvenue %s.\n\n\n", who);
        }
    }
    if(*log == 0) // Sinon, accès refusé.
        printf("\nCombinaison utilisateur/mot de passe incorrecte.\n\n\n");

}

// Fonction pour la déconnexion d'un administrateur
void deconnexion(int* log, char* who)
{
    *log = 0; // On remet l'autorisation à 0.
    printf("Deconnexion reussie ! Aurevoir %s.\n\n", who);
}

// Fonction pour gérer les choix au menu d'accueil
void choix_accueil(int* flag, int choix, int* log, struct seance *se, int i_se, struct admin* ad, int *i_ad, struct salle* sa, int *i_sa, struct film* fl, int *i_fl, char* who)
{
    switch(choix){
    case 1:
        if(i_se > 0) // Si le nombre de film dépasse 0, on peut afficher la liste des séances.
            affichage_seance_triee(se, i_se, fl, *i_fl, sa, *i_sa);
        else
            printf("Aucune seance programmee !\n\n");
        break;

    case 2: // Connexion au programme (nécessite un mdp)
        connexion(log, ad, i_ad, who);
        break;

    case 3: // Arrêter le programme
        *flag = 1; // On modifie le flag pour quitter la boucle while du menu principal
        printf("\nAu revoir ! En esperant vous revoir tres vite.\n");
        break;
    default:
        printf("Erreur ! Numero non valide.\n\n");
    }
}

// Fonction pour gérer les choix dans le menu administrateur
struct admin * choix_admin(int choix, int* log, struct film *fl, int* i_fl, struct admin* ad, int* i_ad, struct salle* sa, int* i_sa, struct seance* se, int* i_se, char* who)
{
    int niveau = 0;
    char menu_choix[5][45] = {"Ajouter", "Supprimer", "Modifier"};

    switch(choix){
    case 0: break;
    case 1: // Gestion des séances
        choix_admin_seance(fonction_menu(&menu_choix[0][0], 45, 3, "Action desiree ? ('0' pour annuler)", "une seance."), se, i_se, fl, *i_fl, sa, *i_sa);
        break;

    case 2: // Gestion des films
        choix_admin_film(fonction_menu(&menu_choix[0][0], 45, 3, "Action desiree ? ('0' pour annuler)", "un film."), fl, i_fl);
        break;

    case 3: // Gestion des salles
        choix_admin_salle(fonction_menu(&menu_choix[0][0], 45, 3, "Action desiree ? ('0' pour annuler)", "une salle."), sa, i_sa);
        break;

    case 4: // Gestion des administrateurs (nécessite un mot de passe)
        if(acces_sup())
            ad = choix_admin_admin(fonction_menu(&menu_choix[0][0], 45, 3, "Action desiree ? ('0' pour annuler)", "un administrateur."), ad, i_ad, who);
        break;

    case 5: deconnexion(log, who); break; // Se déconnecter

    default:
        printf("Erreur !\n\n");
    }
    return ad;
}

// Gestion des séances : Ajouter, Modifier, Supprimer
void choix_admin_seance(int action, struct seance* se, int* i_se, struct film* fl, int i_fl, struct salle* sa, int i_sa)
{
    if(compter_se(se, *i_se) > 0 && action != 0) // Affiche les séances s'il y en a au moins une.
        affichage_seance(se, *i_se, fl, i_fl, sa, i_sa);

    switch(action){
    case 0: break; // Retour
    case 1: ajout_seance(se, i_se, fl, i_fl, sa, i_sa); break; // Ajout
    case 2: supprimer_seance(se, *i_se); break; // Suppression
    case 3: modifier_seance(se, *i_se, fl, i_fl, sa, i_sa); break; // Modification
    default:
        printf("Erreur : Choix incorrect.\n\n");
    }
}

// Ajoute une nouvelle séance à la structure
void ajout_seance(struct seance* se, int* i, struct film* fl, int i_fl, struct salle* sa, int i_sa)
{
    if(i_sa > 0 && i_fl > 0){ // On regarde s'il y a au moins une salle et un film d'encodé, sinon l'ajout d'une séance est impossible.
        printf("\nAJOUT D'UNE SEANCE\n\n");
        se[*i].id = *i; // Définis l'ID de la séance à notre compteur
        saisi_char("Heure de debut : ", se[*i].heure_debut);

        affichage_film(fl, i_fl);
        se[*i].id_film = saisieInt("Quel film souhaitez-vous ajouter (ID) ? : ", 1, i_fl) - 1; // On affiche à partir de 1 pour que l'utilisateur
                                                                                               // est plus de facilité.
        affichage_salle(sa, i_sa);
        se[*i].id_salle = saisieInt("Dans quelle salle (ID) ? : ", 1, i_sa) - 1;               // idem.
        printf("\nSeance ajoutee %! %s a %s dans la salle N%d.\n\n", fl[se[*i].id_film].titre, se[*i].heure_debut, sa[se[*i].id_salle].id + 1);
        *i = *i + 1;
    } else
        printf("Erreur : Une salle et un film doivent etre encode pour pouvoir programmer une seance !\n\n\n");
}

// Suppression d'une séance (l'ID devient -1 et donc inaccessible)
void supprimer_seance(struct seance* se, int i)
{
    int seance_supp, id_se;

    if(compter_se(se, i)>0){
        printf("\n\nSUPPRESSION D'UNE SEANCE\n");
        seance_supp = saisieInt("\nID : ", 0, i-1);
        id_se = recherche_se(se, i, seance_supp);
        if(id_se != -1)
        {
            printf("\nSeance %d supprimee.\n\n", se[id_se].id);
            se[id_se].id = -1;
        }
        else
        {
            printf("Erreur : Seance inconnue.\n\n");
        }
    }
    else{
        printf("Aucune seance programmee.\n\n");
    }
}

// Modification d'une séance
void modifier_seance(struct seance* se, int i, struct film* fl, int i_fl, struct salle* sa, int i_sa)
{
    int id_se, seance_mod;

    if(compter_se(se, i)>0){
        printf("\nMODIFICATION D'UNE SEANCE\n");
        seance_mod = saisieInt("ID de la seance : ", 1, i) - 1;
        id_se = recherche_se(se, i, seance_mod);
        if(id_se != -1)
        {
            modifier_seance_details(se, id_se, fl, i_fl, sa, i_sa);
        }
        else
        {
            printf("Erreur : Seance inconnue.\n\n");
        }
    }
    else{
        printf("Aucune seance programmee.\n\n");
    }
}

// Choix pour modifier un paramètre de la séance souhaitée
void modifier_seance_details(struct seance* se, int id_se, struct film* fl, int i_fl, struct salle* sa, int i_sa)
{
    char choix[10], nouveau[25];
    int nouveau_int, flag = 1;

    saisi_char("\nQue souhaitez-vous modifier ? (Film / Debut / Salle) : ", choix);
    fullMaj(choix);
    if(strcmp(choix, "DEBUT") == 0)
        saisi_char_10("Entrez la nouvelle heure de debut : ", se[id_se].heure_debut);

    else if(strcmp(choix, "FILM") == 0){
        affichage_film(fl, i_fl);
        se[id_se].id_film = saisieInt("Entrez l'ID du film souhaite : ", 1, i_fl) - 1;
    }
    else if(strcmp(choix, "SALLE") == 0){
        affichage_salle(sa, i_sa);
        se[id_se].id_salle = saisieInt("Entrez l'ID de la salle souhaitee : ", 1, i_sa) - 1;
    }
    else{
        printf("Parametre inconnu !\n");
        modifier_seance_details(se, id_se, fl, i_fl, sa, i_sa);
        flag = 0;
    }
    if(flag)
        printf("Seancee modifie avec succes !\n\n");
}

// Fonction qui retourne l'indice de la séance recherchée. Si pas trouvé : retourne -1
int recherche_se(struct seance* se, int max, int se_recherche)
{
    int i;
    for(i=0; i<max; i++)
    {
        if(se[i].id == se_recherche)
            return i;
    }
    return -1;
}

// Compte le nombre de séance
int compter_se(struct seance* se, int i_se)
{
    int i, cpt=0;
    for(i=0; i<i_se; i++)
    {
        if(se[i].id != -1)
            cpt++;
    }
    return cpt;
}


// Tentative de connexion en tant que super admin
int acces_sup()
{
    char admin[25] = "admin";
    char mdp[25] = "admin";

    char s_admin[25], s_mdp[25];
    saisi_char_25("Login admin+ : ", s_admin);
    saisi_char_25("Mot de passe admin+ :", s_mdp);

    if((strcmp(admin, s_admin) == 0) && (strcmp(mdp, s_mdp) == 0)){ // Si les données entrées sont identiques à celles en brutes plus haut -> Accès autorisé.
        printf("\nAcces administrateur+ accordee.\n\n");
        return 1;
    }
    else{
        printf("\nAcces refuse.\n\n");
        return 0;
    }
}

// Gestion des administrateurs : Ajouter, Supprimer, Modifier
struct admin * choix_admin_admin(int action, struct admin* ad, int* i_ad, char* who) // Procédure qui va rediriger le choix de l'utilisateur vers ce qu'il souhaite
{
    if(action != 0) // Si l'utilisateur ne retounr pas au menu précédent
        affichage_admin(ad, *i_ad);

    switch(action){
    case 0: break; // Retour
    case 1: ad = ajout_admin(ad, i_ad) ;break; // Ajoute un admin
    case 2: ad = supprimer_admin(ad, *i_ad, who); break; // Supprime un admin
    case 3: ad = modifier_admin(ad, *i_ad); break; // Modifie un admin
    default: printf("Erreur : Choix incorrect.\n\n"); break;
    }
    return ad;
}

// Ajoute un nouvel administrateur à la structure
struct admin * ajout_admin(struct admin *p, int* taille)
{
    struct admin tmp;
    struct admin *ancien;
    fflush(stdin);
    saisi_char_25("\nEntrez un nom : ", tmp.user);
    saisi_char_25("\nEntrez un mot de passe : ", tmp.mdp);
    ancien=p;
    p=(struct admin *)realloc(p,((*taille)+1)*sizeof(struct admin)); //p peut changer
    if(p!=NULL)
    {
       p[*taille]=tmp;
       (*taille)++;
    }
    else
    {
       p=ancien;
    }

    printf("\nAdministrateur %s (%s) ajoute avec succes.\n\n", tmp.user, tmp.mdp);
    return p;
}

//Supprime un administrateur de la structure (en mettant $ au 24ème caractère)
struct admin * supprimer_admin(struct admin* ad, int i, char* who)
{
    char admin_supp[25];
    int id_op;

    printf("\nSUPPRESSION D'UN ADMINISTRATEUR\n");
    saisi_char_25("Nom : ", admin_supp);
    id_op = recherche(ad, i, admin_supp);
    if(id_op != -1 && ad[id_op].user[24] != '$' && (strcmp(ad[id_op].user, who) != 0)){
        printf("\nAdministrateur %s supprime avec succes.\n\n\n", ad[id_op].user);
        ad[id_op].user[24] = '$';
    }
    else if(strcmp(ad[id_op].user, who) == 0)
        printf("\nErreur : Impossible de supprimer son compte administrateur.\n\n");
    else
        printf("\nErreur : Operateur inconnu.\n\n");

    return ad;
}

// Modifie le nom ou le mot de passe d'un administrateur
struct admin * modifier_admin(struct admin* ad, int i) // Fonction pour modifier le nom ou le mdp d'un opérateur
{
    char admin_mod[25];
    int id_op;

    printf("\nMODIFICATION D'UN OPERATEUR\n");
    saisi_char("Nom : ", admin_mod);
    id_op = recherche(ad, i, admin_mod);
    if(id_op != -1)
    {
        ad = modifier_admin_details(ad, id_op);
    }
    else
    {
        printf("Erreur : Administrateur inconnu.\n\n");
    }

    return ad;
}

// Choix pour modifier un paramètre de l'admin souhaité
struct admin * modifier_admin_details(struct admin* ad, int id_op)
{
    char choix[5], nouveau[25];
    saisi_char("\nQue souhaitez-vous modifier ? (nom / mdp) : ", choix);
    fullMaj(choix);
    if(strcmp(choix, "NOM") == 0)
    {
        saisi_char("Entrez le nouveau nom : ", nouveau);
        strcpy(ad[id_op].user, nouveau);
    }
    else if(strcmp(choix, "MDP") == 0)
    {
        saisi_char("Entrez le nouveau mot de passe : ", nouveau);
        strcpy(ad[id_op].mdp, nouveau);
    }
    else{
        printf("\nErreur : Entrez un parametre valide !\n\n");
        modifier_admin_details(ad, id_op);
    }

    printf("\nParametre modifie avec succes !\n\n\n");
    return ad;
};

// Fonction qui retourne l'indice de l'admin recherché. Si pas trouvé : retourne -1
int recherche(struct admin* ad, int max, char* op_recherche)
{
    int i;
    for(i=0; i<=max; i++)
    {
        if(strcmp(ad[i].user, op_recherche) == 0)
            return i;
    }
    return -1;
}

// Gestion des films (ajouter, supprimer, modifier)
void choix_admin_film(int action, struct film* fl, int* i_fl)
{
    if(supprimer_film_check(fl, *i_fl) && action != 0)
        affichage_film(fl, *i_fl);

    switch(action){

    case 0: break;
    case 1: ajout_film(fl, i_fl); break;
    case 2: supprimer_film(fl, i_fl); break;
    case 3: modifier_film(fl, *i_fl); break;

    default: printf("Erreur : Choix incorrect.\n\n"); break;
        }
}

// Ajout d'un film à la structure
void ajout_film(struct film* fl, int* i)
{
    printf("\nAJOUT D'UN FILM\n");
    fl[*i].id = *i;
    fflush(stdin);
    saisi_char_25("Titre : ", fl[*i].titre);
    fflush(stdin);
    saisi_char("Duree : ", fl[*i].duree);

    printf("Film %s (%s) ajoute avec succes ! \n\n", fl[*i].titre, fl[*i].duree);
    *i = *i + 1;
}

// Supprime un film de la structure
void supprimer_film(struct film* fl, int* i)
{
    if(supprimer_film_check(fl, *i)){
        char film_supp[25];
        int id_fl;

        printf("\nSUPPRESSION D'UN FILM\n");
        saisi_char_25("Titre : ", film_supp);
        id_fl = recherche_fl(fl, *i, film_supp);
        if(id_fl != -1)
        {
            printf("\nFilm '%s' supprime avec succes.\n\n\n", fl[id_fl].titre);
            arrangement_film(fl, i, id_fl);
        }
        else
            printf("\nErreur : Film inconnu.\n\n\n");
    }else
        printf("\nErreur : Aucun film encode.\n\n\n");
}

// Modifier un film (Titre - Durée)
void modifier_film(struct film* fl, int i) // Fonction pour modifier le nom ou le mdp d'un opérateur
{
    char film_mod[25];
    int id_fl, flag = 0;

    if(supprimer_film_check(fl, i)){
        fflush(stdin);
        printf("\nMODIFICATION D'UN FILM\n");
        saisi_char_25("Titre : ", film_mod);
        id_fl = recherche_fl(fl, i, film_mod); // Vérifier si le film existe, retourne son indice si trouvé. Sinon retourne -1
        if(id_fl != -1){
            modifier_film_details(fl, id_fl);
            flag = 1;
        }
        else
            printf("Erreur : Film inconnu.\n\n\n");
    }else
        printf("\nErreur : Aucun film encode.\n\n\n");

    if(flag)
        printf("\nModification effectuee avec succes.\n\n\n");
}

// Choix pour modifier un paramètre du film souhaitée
void modifier_film_details(struct film* fl, int id_fl)
{
    char choix[5], nouveau[25];
    saisi_char("Que souhaitez-vous modifier ? (titre / duree) : ", choix);
    fullMaj(choix);
    if(strcmp(choix, "TITRE") == 0)
    {
        fflush(stdin);
        saisi_char_25("Entrez le nouveau titre : ", nouveau);
        strcpy(fl[id_fl].titre, nouveau);
    }
    else if(strcmp(choix, "DUREE") == 0)
    {
        saisi_char_10("Entrez la nouvelle duree : ", nouveau);
        strcpy(fl[id_fl].duree, nouveau);
    }
    else{
        printf("Erreur : Entrez un parametre valide.\n\n");
        modifier_film_details(fl, id_fl);
    }
}

// Fonction regardant s'il y a des films encodées
bool supprimer_film_check(struct film* fl, int max)
{
    if(max == 0)
    {
        return false;
    }
    return true;
}

// Fonction arrageant l'identifiant des films en fonction de celui qu'on vient de supprimer.
void arrangement_film(struct film* p, int *max, int id) // Si un film est supprime, la fonction va arranger les ID des autres films pour pas laisser de trou.
{                                                       // Le film sera donc écrasé.
    int j;

    for (j = id; j < *max - 1; j++)
    {
        p[j] = p[j + 1];
        p[j].id--;
    }

    *max = *max - 1;
}

// Fonction qui retourne l'indice du film recherché. Si pas trouvé : retourne -1
int recherche_fl(struct film* fl, int max, char* fl_recherche)
{
    int i;

    for(i=0; i<max; i++)
    {
        if(strcmp(fl[i].titre, fl_recherche) == 0)
            return i;
    }
    return -1;
}

// Menu de gestion des salles
void choix_admin_salle(int action, struct salle* sa, int* i_sa)
{
    if(supprimer_salle_check(sa, *i_sa) && action != 0) // S'il y a au moins 1 salle & que le choix de l'utilisateur n'est pas 0
        affichage_salle(sa, *i_sa);

    switch(action){
    case 0: break; // Retour
    case 1: ajout_salle(sa, i_sa); break; // Ajouter
    case 2: supprimer_salle(sa, i_sa); break; // Supprimmer
    case 3: modifier_salle(sa, i_sa); break; // Modifier

    default: printf("Erreur : Choix incorrect.\n\n");
    }
}

// Ajout d'une salle
void ajout_salle(struct salle* sa, int* i)
{
    printf("\n\nAJOUT D'UNE SALLE\n");
    sa[*i].id = *i;
    sa[*i].capacite = saisieInt("Capacite : ", 40, 200);
    saisi_char_25("Type de siege (Standart - Confort) : ", sa[*i].type_siege);
    saisi_char_25("Type de son (Standart - ATMOS) : ", sa[*i].type_son);
    printf("\nLa salle %d a ete ajoute avec succes. ( %d | %s | %s )\n\n\n", *i, sa[*i].capacite, sa[*i].type_siege, sa[*i].type_son);
    *i = *i + 1;
}

// Supprimer une salle
void supprimer_salle(struct salle* sa, int * i)
{
    int salle_supp;
    int id_sa;

    printf("\n\nSUPPRESSION D'UNE SALLE");
    if(supprimer_salle_check(sa, *i))
    {
        salle_supp = saisieInt("\nID : ", 1, *i) - 1; // ID de la salle qu'on souhaite supprimer
        id_sa = recherche_sa(sa, *i, salle_supp);
        if(id_sa != -1)
        {
            printf("\nSalle %d supprimee avec succes.\n\n\n", sa[id_sa].id+1);
            arrangement_salle(sa, i, id_sa); // On arrange l'ID du reste des salles
        }
        else
            printf("\nErreur : Salle inconnue.\n\n");
    }else
        printf("\n\nErreur : Aucune salle encodee.\n\n\n");
}

// Fonction arrageant l'identifiant des salles en fonction de celle qu'on vient de supprimer.
void arrangement_salle(struct salle* sa, int *max, int id_sa)
{
    int j;

    for (j = id_sa; j < *max - 1; j++)
    {
        sa[j] = sa[j + 1];
        sa[j].id -= 1;
    }

    *max = *max - 1;
}

// Fonction regardant s'il y a des salles encodées
bool supprimer_salle_check(struct salle* sa, int max)
{
    if(max == 0)
    {
        return false;
    }
    return true;
}

// Modifier une salle (Siège - Son - Capacité)
void modifier_salle(struct salle* sa, int* i) // Fonction pour modifier le nom ou le mdp d'un opérateur
{
    int salle_mod, id_sa;
    printf("\nMODIFICATION D'UNE SALLE\n");
    if(supprimer_salle_check(sa, *i)){ // On regarde s'il y a des salles à supprimer
        salle_mod = saisieInt("ID :", 0, *i);

        id_sa = recherche_sa(sa, *i, salle_mod);
        if(id_sa != -1){
            modifier_salle_choix(sa, id_sa);
            printf("\nLe parametre a ete modifie avec succes.\n\n\n");
        }else
            printf("Erreur : Salle inconnue.\n\n\n");
    }else
        printf("\n\nErreur : Aucune salle encodee.\n\n\n");
}

// Choix pour modifier un paramètre de la salle souhaitée
void modifier_salle_choix(struct salle * sa, int id_sa)
{
    char choix[5], nouveau[25];
    int nouveau_int = 0;
    saisi_char("Que souhaitez-vous modifier ? (Capacite | Siege | Son) : ", choix);
    fullMaj(choix);
    if(strcmp(choix, "CAPACITE") == 0)
        sa[id_sa].capacite = saisieInt("Nouvelle capacite : ", 40, 200);
    else if(strcmp(choix, "SON") == 0){
        saisi_char_25("Nouveau type de son : ", nouveau);
        strcpy(sa[id_sa].type_son, nouveau);
    } else if(strcmp(choix, "SIEGE") == 0){
        saisi_char("Nouveau type de siege : ", nouveau);
        strcpy(sa[id_sa].type_siege, nouveau);
    } else{
        printf("Erreur : Parametre non trouve.\n\n");
        modifier_salle_choix(sa, id_sa);
    }
}

// Fonction qui retourne l'indice de la salle recherchée. Si pas trouvé : retourne -1
int recherche_sa(struct salle* sa, int max, int sa_recherche)
{
    int i;
    for(i=0; i<max; i++)
    {
        if(sa[i].id == sa_recherche)
            return i;
    }
    return -1;
}

// Affiche l'ensemble des salles
void affichage_salle(struct salle *p, int taille)
{
    int i;
    printf("\n"); barre(72);
    printf("%3s %13s %18s %20s %10s\n", "ID", "Capacite", "Type siege", "Type son", "Prix");
    barre(72);
    for(i=0;i<taille;i++)
    {
        if(p[i].id != -1)
            printf("%3d %10d %20s %20s %10d\n", p[i].id+1,p[i].capacite, p[i].type_siege, p[i].type_son, calcul(p[i].type_siege, p[i].type_son));
    }
    barre(72);
}

// Affiche l'ensemble des administrateurs
void affichage_admin(struct admin *p, int taille)
{
    int i;
    printf("\n"); barre(35);
    printf("%15s %12s", "Utilisateur", "MDP");
    printf("\n"); barre(35);
    for(i=0;i<taille;i++)
    {
        if(p[i].user[24] != '$')
            printf("%13s %15s\n", p[i].user,p[i].mdp);
    }
    barre(35);
}

// Affiche l'ensemble des films
void affichage_film(struct film *p, int taille)
{
    int i;
    printf("\n"); barre(50);
    printf("%5s %10s %20s\n", "ID", "Duree", "Titre");
    barre(50);
    for(i=0; i<taille; i++)
    {
        if(p[i].titre[24] != '$')
            printf("%5d %10s %30s\n", p[i].id+1, p[i].duree, p[i].titre);
    }
    barre(50);
}

// Affiche l'ensemble des séances
void affichage_seance(struct seance *p, int taille, struct film* fl, int i_fl, struct salle* sa, int i_sa)
{
    int i;
    printf("\n"); barre(78);
    printf("%3s %15s %25s %10s %10s %8s\n", "ID", "Titre", "Heure de debut", "Duree", "Salle", "Prix");
    barre(78);
    for(i=0; i<taille; i++)
    {
        if(p[i].id != -1)
            printf("%3d %-25s %10s %15s %7d %10d\n", p[i].id+1, fl[p[i].id_film].titre, p[i].heure_debut, fl[p[i].id_film].duree, sa[p[i].id_salle].id+1, calcul(sa[p[i].id_salle].type_siege, sa[p[i].id_salle].type_son));
    }
    barre(78);
}

// Affiche les séances en fonction de 2 critères
void affichage_seance_triee(struct seance *p, int taille, struct film* fl, int i_fl, struct salle* sa, int i_sa)
{
    int i, flag = 1;
    char crit_siege[10], crit_son[10];
    saisi_char_10("Quel type de siege voulez-vous ? (Standart - Confort) : ", crit_siege);
    saisi_char_10("Quel type de son voulez-vous ? (Standart - ATMOS) : ", crit_son);
    printf("\n"); barre(78);
    printf("%3s %15s %25s %10s %10s %8s\n", "ID", "Titre", "Heure de debut", "Duree", "Salle", "Prix");
    barre(78);
    for(i=0; i<taille; i++)
    {
        if(p[i].id != -1 && (strcmp(sa[p[i].id_salle].type_siege, crit_siege) == 0) && (strcmp(sa[p[i].id_salle].type_son, crit_son) == 0))
        {
            printf("%3d %-25s %10s %15s %7d %10d\n", p[i].id+1, fl[p[i].id_film].titre, p[i].heure_debut, fl[p[i].id_film].duree, sa[p[i].id_salle].id+1, calcul(sa[p[i].id_salle].type_siege, sa[p[i].id_salle].type_son));
            flag = 0;
        }
    }
    if(flag)
        printf("Aucune seance trouvee.\n");
    barre(78);
}

// Fonction pour saisir du texte avec un message
void saisi_char(char* msg, char* entree)
{
    printf("%s", msg);
    fflush(stdin);
    scanf("%s", entree);
}

// Fonction pour saisir une chaîne de 25 caractères avec un message
void saisi_char_25(char* msg, char* entree)
{
    printf("%s", msg);
    fflush(stdin);
    scanf("%24[^\n]", entree);
}

// Fonction pour saisir une chaîne de 10 caractères avec un message
void saisi_char_10(char* msg, char* entree)
{
    printf("%s", msg);
    fflush(stdin);
    scanf("%9[^\n]", entree);
}

// Fonction pour saisir un entier avec contrôle de validité
int saisieInt(char* texte, int min, int max){
    int flag,cpt=0,i=0;
    char masque[20]={"0123456789"}; // On indique toutes les valeurs qu'on accepte (les chiffres)
    char nb[15];
    do {
        flag = 0;
        printf("\n%s",texte);
        scanf("%s",nb);
        cpt = strlen(nb);
        fflush(stdin);
        for(i=0;i<cpt;i++)
        {
            if(strchr(masque,nb[i])==NULL) // On regarde si, dans la sélection (masque), notre chiffre est présent. Si non -> NULL, donc on rentre dans la condition.
            {
                flag=1;
            }
        }
        if(flag || atoi(nb) < min || atoi(nb) > max) // Vérifie que la valeur est dans les limites
        {
            printf("\nVeuillez entrer un nombre entre %d et %d.\n", min, max);
            flag=1;
        }
    }while(flag);

    return atoi(nb);
}

// Fonction pour afficher les menus et retourne le choix de l'utilisateur
int fonction_menu(char* V, int taille, int max, char* msg, char* spe)
{
    int i, j, choix;

    printf("%30s\n\n", msg);
    for(i=0 ; i<max ; i++)
    {
        printf("%d - %s %s\n",i+1, (V+i*taille), spe);
    }

    choix = saisieInt("Choix : ", 0, max);
    printf("\n");
    return choix;
}

// Retourne le prix d'une séance en fonction du type de siège et du type de son et de siège
int calcul(char* siege, char* son)
{
    int prix = 10;

    if(strcmp(siege, "Confort") == 0)
        prix += 2;

    if(strcmp(son, "ATMOS") == 0)
        prix += 3;

    return prix;

}

// Procédure affichant une barre de tiret
void barre(int nb)
{
    int i;
    for(i=0; i<nb; i++)
    {
        printf("-");
    }
    printf("\n");
}

// Procédure mettant tous les caractères d'une chaine de caractère en majuscule
void fullMaj(char *msg)
{
    int i = 0;
    while (msg[i] != '\0')
    {
        msg[i] = toupper(msg[i]);
        i++;
    }
}

//Chargement du fichier admins.dat
struct admin *chargement_ad(int *taille)
{
    FILE *f;
    struct admin tmp;
    struct admin *p=NULL,*ancien;
    int cpt=0,flag=0;
    f=fopen("admins.dat","rb");
    if(f)
    {
        fread(&tmp,sizeof(struct admin),1,f);
        while(!feof(f)&&!flag)
        {
            ancien=p;
            p=(struct admin*)realloc(p,(cpt+1)*sizeof(struct admin));
            if(p!=NULL)
            {
                p[cpt]=tmp;
                cpt++;
                fread(&tmp,sizeof(struct admin),1,f);
            }
            else
            {
                flag=1;
                p=ancien;


            }
       }
       fclose(f);
       *taille=cpt;
    }
    return p;
}

//Chargement du fichier films.dat
void chargement_fl(struct film* p, int *taille)
{
    FILE *f;
    int flag = 0;
    f = fopen("films.dat", "rb");
    if (f)
    {
        while (!feof(f) && !flag)
        {
            if(fread(&p[*taille], sizeof(struct film), 1, f) == 1)
            {
                *taille = *taille +1;
            }
            else
            {
                flag = 1;
            }
        }
        fclose(f);
    }
}

//Chargement du fichier seances.dat
void chargement_se(struct seance* p, int *taille)
{
    FILE *f;
    int flag = 0;
    f = fopen("seances.dat", "rb");
    if (f)
    {
        while (!feof(f) && !flag)
        {
            if (fread(&p[*taille], sizeof(struct seance), 1, f) == 1)
            {
                *taille = *taille +1;
            }
            else
            {
                flag = 1;
            }
        }
        fclose(f);
    }
}

//Chargement du fichier salles.dat
void chargement_sa(struct salle* p, int *taille)
{
    FILE *f;
    int flag = 0;
    f = fopen("salles.dat", "rb");
    if (f)
    {
        while (!feof(f) && !flag)
        {
            if (fread(&p[*taille], sizeof(struct salle), 1, f) == 1)
            {
                *taille = *taille + 1;
            }
            else
            {
                flag = 1;
            }
        }
        fclose(f);
    }
}

// Vérifie qu'un fichier existe
int fichier_existe(char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if(fichier){
        fclose(fichier);
        return 0; // Le fichier existe
    } else {
        return 1; // Le fichier n'existe pas
    }
}

// Vérifie que tous les fichiers nécessaires sont présents
int fichiers_presents()
{
    if((fichier_existe("admins.dat") || fichier_existe("salles.dat") || fichier_existe("seances.dat") || fichier_existe("films.dat")) == 1){
        printf("Demarrage impossible. Au moins un fichier est manquant.\nVeillez a avoir dans votre repertoire :\n- admins.dat \n- salles.dat \n- seances.dat \n- films.dat\n");
        return 0;
    }
    return 1;
}

// Enregistrement des données dans les fichiers
void sorties(struct salle *sa, int i_sa, struct seance* se, int i_se, struct film* fl, int i_fl, struct admin* ad, int i_ad)
{
    sortie_salle(sa, i_sa);
    sortie_seance(se, i_se);
    sortie_film(fl, i_fl);
    sortie_admin(ad, i_ad);
}

// Chargement des données vers le fichier salles.dat
void sortie_salle(struct salle *p, int taille)
{
    FILE *f;
    int i;
    f=fopen("temporaire.dat","wb");
    if(f)
    {
        for(i=0;i<taille;i++)
        {
            fwrite(&p[i],sizeof(struct salle),1,f);
        }
        fclose(f);
        remove("salles.dat");
        rename("temporaire.dat","salles.dat");
    }
}

// Chargement des données vers le fichier seances.dat
void sortie_seance(struct seance *p, int taille)
{
    FILE *f;
    int i;
    f=fopen("temporaire.dat","wb");
    if(f)
    {
        for(i=0;i<taille;i++)
        {
            fwrite(&p[i],sizeof(struct seance),1,f);
        }
        fclose(f);
        remove("seances.dat");
        rename("temporaire.dat","seances.dat");
    }
}

// Chargement des données vers le fichier films.dat
void sortie_film(struct film *p, int taille)
{
    FILE *f;
    int i;
    f=fopen("temporaire.dat","wb");
    if(f)
    {
        for(i=0;i<taille;i++)
        {
            fwrite(&p[i],sizeof(struct film),1,f);
        }
        fclose(f);
        remove("films.dat");
        rename("temporaire.dat","films.dat");
    }
}

// Chargement des données vers le fichier admins.dat
void sortie_admin(struct admin *p, int taille)
{
    FILE *f;
    int i;
    f=fopen("temporaire.dat","wb");
    if(f)
    {
        for(i=0;i<taille;i++)
        {
            fwrite(&p[i],sizeof(struct admin),1,f);
        }
        fclose(f);
        remove("admins.dat");
        rename("temporaire.dat","admins.dat");
    }
}

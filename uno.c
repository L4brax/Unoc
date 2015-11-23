#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ************************************
// Définition des types : liste chainée 
// ************************************

typedef struct _TCarte
{
	int valeur; // Numéro et valeur de la carte
	char couleur; // Couleur de la carte : R B J V S
	int type; // Type de la carte (Base, +2, +4...)
} TCarte;

//Structure stockant une carte et un pointeur vers une autre carte.
typedef struct _TCelluleCarte
{
	TCarte carte;
	struct _TCelluleCarte* suivant;
} TCelluleCarte;

typedef struct _TJoueur
{
	int noJ; // Identifie le joueur.
	char nom[15]; //Nom du joueur attribué en début de partie.
	int nbCartes; // Nombre de carte en main du joueur.
	TCelluleCarte* jmain; //Main du joueur.
	struct _TJoueur* jsuivant; //Pointeur permettant de passer au joueur suivant une fois le tour terminé.
} TJoueur;

TCelluleCarte* pioche; // Pioche principale du jeu. Gérer comme une pile.
TCelluleCarte* jeu; // Pile de TCelluleCarte sur laquelle les joueurs ajoutent les cartes qu'ils peuvent poser.
					// Cette pile est ensuite mélangée et placée dans la pioche si plus de carte dans la pioche.


// ************************
// Prototypes et fonctions 
// ************************

void piocherCarte(TJoueur* joueur); //Procédure permettant d'ajouter la carte en tête de pioche à la main du Joueur.
int verifierCouleur(TCarte carteJoueur,TCarte carteJeu); 	// Vérifie si les couleurs des deux cartes en parrametre sont identiques.
															// Renvoi 1 si vrai, 0 si faux.
int verifierValeur(TCarte,TCarte); 	// Vérifie si les valeurs des deux cartes en parametres sont identiques.
									// Renvoi 1 si vrai, 0 si faux.
void modifierNomJoueur(TJoueur* joueur); // Permet de changer le nom du joueur en paramètre.
void afficherNomJ(TJoueur joueur); // affiche le nom du joueur en paramètre.
void initJoueur(TJoueur* joueur); // Initialise le joueur.
int affichageMenu(TJoueur joueur);	// Affiche le menu principal et demande l'action à executer.
									// Retoune le choix de l'action à exectuer sous forme d'entier.
									// joueur1 en paramère est utilisé pour savoir si il sagit de la première partie ou non.
int nouvellePartie(TJoueur joueur)	// Retourne 1 si les noms des joueurs ne sont pas définit,
									// signifiant qu'aucune partie n'a été déjà jouée.
									// Le paramètre utilise le nom du joueur.


// ********************
// Programme principal
// ********************

int main()
{
	// Lexique
	int choixMenu;	// Variable de choix du menu.
	int end = 0;	// Variable utilisée pour mettre fin au programme dans la boucle principale.
	TJoueur* jtour; // Pointeur indiquant le joueur devant jouer une carte ou piocher.
	//int nbParties = 0;
	 
	// Initialisation
	TJoueur j1;
	TJoueur j2;
	TJoueur j3;
	initJoueur(&j1);
	initJoueur(&j2);
	initJoueur(&j3);
	j1.noJ = 1;
	j2.noJ = 2;
	j3.noJ = 3;
	//jtour = &j1; // On positionne le pointeur du tour sur le premier joueur.
	
	printf("================================================================\n");
    printf("===============      Prêt pour une nouvelle     ================\n");
    printf("===============          partie de UNO !        ================\n");
    printf("================================================================\n\n");
    
    while (choixMenu != 0) {
		choixMenu = affichageMenu(j1);

		if (choixMenu == 1) {
			if (nouvellePartie(j1)==1){
				modifierNomJoueur(j1);
				modifierNomJoueur(j2);
				modifierNomJoueur(j3);

			}
		}		
	}
	return 0;
}

// ************************
// Procédures et fonctions
// ************************

void piocherCarte(TJoueur* joueur){
	TCelluleCarte* aux;
	aux = pioche;
	pioche = pioche->suivant;
	aux->suivant = joueur->jmain;
	joueur->jmain=aux;
}

int verifierCouleur(TCarte carteJoueur, TCarte carteJeu){
	return 1;
}
	
int verifierValeur(TCarte carteJoueur, TCarte carteJeu){
	return 1;
}
	
void modifierNomJoueur(TJoueur* joueur){
	char numJoueur[9]; // Chaine de caractère identifiant le joueur 
	char nomTemp[15]; // Chaine de caractère tempon pour stocker le nom entré par l'utilisateur.
	
	if (joueur->noJ == 1){
		strcpy(numJoueur, "premier");
	} else if (joueur->noJ == 2) {
		strcpy(numJoueur, "second");
	} else {
		strcpy(numJoueur, "troisieme");
	}
	printf("Veuillez indiquer le nom du %s joueur : ",numJoueur);
	scanf("%s", nomTemp);
	strcpy(joueur->nom, nomTemp);
}

void afficherNomJ(TJoueur joueur){
	printf("%s \n",joueur.nom);
}

void initJoueur(TJoueur* joueur){
	joueur->jmain = NULL;
	joueur->jsuivant = NULL;
	joueur->nbCartes = 0;
	joueur->noJ = 0;
	strcpy(joueur->nom,"ok");
}
	
int affichageMenu(TJoueur joueur) {
	int choixMenu;
	printf("----------------------------------------------------------------\n");
	printf("---------------         Menu principal          ----------------\n");
	printf("----------------------------------------------------------------\n");
	printf(" 1 - Nouvelle partie \n");
	if (nouvellePartie(joueur)==1) {  // Si une partie a déjà été jouée, les joueurs ont déjà été déclarés.
		printf(" 2 - Changer les noms des joueurs\n");
	}
	printf(" 0 - Quitter\n");
	printf("----------------------------------------------------------------\n\n");
	
	if (nouvellePartie(joueur)==1){
		do {
			scanf("%d", &choixMenu);
		} while ((choixMenu<0) || (choixMenu>1));
	} else {
		do {
			scanf("%d", &choixMenu);
		} while ((choixMenu<0) || (choixMenu>2));
	}

	return choixMenu;
}
	
int nouvellePartie(TJoueur joueur){
	if (strcmp(joueur.nom," ")==0){
		return 1;
	} else {
		return 0;
	}
}
	
	
	
	
	
	
	

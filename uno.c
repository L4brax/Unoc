#include <stdio.h>
#include <stdlib.h>

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
// ********************
// Programme principal
// ********************

int main()
{
	printf("HELLO");
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	

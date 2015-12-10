#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ************************************
// Définition des types : liste chainée 
// ************************************

typedef struct _TCarte
{
	int valeur; // Numéro et valeur de la carte
	char couleur[2]; // Couleur de la carte : R B J V S
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
	int nbPoints; // Score du joueur.
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
int affichageMenu(TJoueur joueur, int nbManches);	// Affiche le menu principal et demande l'action à executer.
									// Retoune le choix de l'action à exectuer sous forme d'entier.
									// joueur1 en paramère est utilisé pour savoir si il sagit de la première partie ou non.
									// nbManches en paramètre permet de savoir si une partie est en cours ou non.
int nouveauJeu(TJoueur joueur);	// Retourne 1 si les noms des joueurs ne sont pas définit,
									// signifiant qu'aucune partie n'a été déjà jouée.
									// Le paramètre utilise le nom d'un joueur, en général le premier.
void jouerTour(TJoueur* joueur); 	// Procédures permettant au joueur de jouer son tour, c'est à dire jouer une carte,
									// appliquer ses effets ou piocher une carte.
void afficherUno();				// Affiche UNO pour indiquer que le joueur en Cours à gagné.
void compterPoints(TJoueur* joueur); 	// Compte les points de la main du joueur en paramètre et les ajoutes sont total de points.
										// Affiche aussi les points de la manche et de la partie en cours.
void afficherResultat(TJoueur joueur); // Affiche le résultat des points du joueur en paramètre pour cette manche et pour la partie.
void afficherVainqueur(TJoueur joueur1, TJoueur joueur2, TJoueur joueur3);  // Affiche le vainqueur 
int saisirEntre(int a, int b); 	// Demande un entier à un utilisateur entre a et b et le retourne.



// ********************
// Programme principal
// ********************

int main()
{
	// Lexique
	int choixMenu = 1;	// Variable de choix du menu. Initialisée à 1 pour entrer dans la première boucle.
	int finManche = 0;	// Variable utilisée pour mettre fin à la manche en cours.
	TJoueur* jtour; // Pointeur indiquant le joueur devant jouer une carte ou piocher.
	int nbManches = 0; // Utilisé pour compter le nombre de manches jouées.
	 
	// Initialisation
	TJoueur j1;
	TJoueur j2;
	TJoueur j3;
	initJoueur(&j1);
	initJoueur(&j2);
	initJoueur(&j3);
	j1.jsuivant = &j2;
	j2.jsuivant = &j3;
	j3.jsuivant = &j1;
	j1.noJ = 1;
	j2.noJ = 2;
	j3.noJ = 3;
	jtour = &j1; // On positionne le pointeur du tour sur le premier joueur.
	
	printf("================================================================\n");
    printf("===============      Prêt pour une nouvelle     ================\n");
    printf("===============          partie de UNO !        ================\n");
    printf("================================================================\n\n");
    
    while (choixMenu != 0) {
		choixMenu = affichageMenu(j1,nbManches);

		if ((choixMenu == 1) || (choixMenu == 2)) {
			if (choixMenu == 1){
				nbManches = 0;
			}
			if (nouveauJeu(j1)==1){
				printf("----------------------------------------------------------------\n");
				modifierNomJoueur(&j1);
				modifierNomJoueur(&j2);
				modifierNomJoueur(&j3);
				printf("----------------------------------------------------------------\n");
			}
			while (finManche == 0) {
				printf("%s à vous de jouer !\n",jtour->nom);
				jouerTour(jtour);
				if (jtour->jmain == NULL) {
					afficherUno();
					finManche = 1;
					compterPoints(&j1);
					compterPoints(&j2);
					compterPoints(&j3);
					nbManches =+ 1;
					if (nbManches == 3) {
						afficherVainqueur(j1,j2,j3);
					}
				}
				jtour = jtour->jsuivant;
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
	do {
		
		printf("Veuillez indiquer le nom du %s joueur : ",numJoueur);
		scanf("%s", nomTemp);
		if (strcmp(nomTemp," ")==0){
			printf("Veuillez saisir au moins un caractère.");
		} else {
			strcpy(joueur->nom, nomTemp);
		}
	} while (strcmp(nomTemp," ")==0);
}

void afficherNomJ(TJoueur joueur){
	printf("%s \n",joueur.nom);
}

void initJoueur(TJoueur* joueur){
	joueur->jmain = NULL;
	joueur->jsuivant = NULL;
	joueur->nbCartes = 0;
	joueur->noJ = 0;
	strcpy(joueur->nom," ");
}
	
int affichageMenu(TJoueur joueur, int nbManches) {
	int choixMenu;
	printf("----------------------------------------------------------------\n");
	printf("---------------         Menu principal          ----------------\n");
	printf("----------------------------------------------------------------\n");
	printf(" 1 - Nouvelle partie \n");
	if (nouveauJeu(joueur)==1) {  // Si une partie a déjà été jouée, les joueurs ont déjà été déclarés.
		printf(" 2 - Changer les noms des joueurs\n");
	}
	if (nbManches > 0) {
		printf(" 3 - CONTINUER LA PARTIE EN COURS\n");
	}
	printf(" 0 - Quitter\n");
	printf("----------------------------------------------------------------\n");
	
	if (nouveauJeu(joueur)==1){
		choixMenu = saisirEntre(0,1);
	} else if (nbManches>0){
		choixMenu = saisirEntre(0,3);
	} else {
		choixMenu = saisirEntre(0,2);
	}

	return choixMenu;
}
	
int nouveauJeu(TJoueur joueur){
	if (strcmp(joueur.nom," ")==0){
		return 1;
	} else {
		return 0;
	}
}

int saisirEntre(int a, int b){
	int ret;
	do {
		scanf("%d", &ret);
	} while ((ret<a) || (ret>b));
	return ret;
}

void jouerTour(TJoueur* joueur){

}

void afficherUno(){

}

void compterPoints(TJoueur* joueur) {

}

void afficherVainqueur(TJoueur joueur1, TJoueur joueur2, TJoueur joueur3){

}




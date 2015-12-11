#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ************************************
// Définition des types : liste chainée 
// ************************************

typedef struct _TCarte
{
	int valeur; // Numéro et valeur de la carte
	char couleur[2]; // Couleur de la carte : Ro Bl Ja Ve Sa
	int type; // Type de la carte (Base, +2, +4...)
} TCarte;
//Concernant les types :
//  0 = carte 0
//  1 = carte à valeur
//  2 = carte +2
//	3 = changement de sens
//  4 = passe tour
//  5 = joker couleur
//	6 = carte +4

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

TCelluleCarte* pioche = NULL; // Pioche principale du jeu. Gérer comme une pile.
TCelluleCarte* jeu = NULL; // Pile de TCelluleCarte sur laquelle les joueurs ajoutent les cartes qu'ils peuvent poser.
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
int affichageMenu(int nbManches);	// Affiche le menu principal et demande l'action à executer.
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
void initialiserJeu(); //Initialise toutes les cartes du jeu dans la pile Jeu non mélangées.
void ajoutSerie(int a, int b, char couleur[2], int type, int nb); // Permet d'ajouter une série de cartes à la pile Jeu.
						// Le paramètre a désigne la borne inférieur de l'itération de la valeur de la carte (a inclus)
						// Le paramètre b désigne la borne supérieur de l'itération de la valeur de la carte (b exclus)
						// Couleur désigne la couleur affectée aux cartes créées.
						// Type désigne le type affecté aux cartes crées.
						// nb désigne le nombre de séries à créer.
void afficherListe(*TCelluleCarte liste); 	//Affiche une liste de Carte.
											//Prend en paramètre un pointeur vers une TCelluleCarte, en générale une main.
											//Affiche plusieurs cartes sur une seule ligne.
void melangerPioche(); //Mélange les cartes du jeu dans la pioche.



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
	
	
	printf("================================================================\n");
    printf("===============      Prêt pour une nouvelle     ================\n");
    printf("===============          partie de UNO !        ================\n");
    printf("================================================================\n\n");
    
    while (choixMenu != 0) {
		choixMenu = affichageMenu(j1,nbManches);		
		if ((choixMenu == 1) || (choixMenu == 2)){
			jtour = &j1; // On positionne le pointeur du tour sur le premier joueur.
			if (choixMenu == 1) {
				nbManches = 0;
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
	
int affichageMenu(int nbManches) {
	int choixMenu;
	printf("----------------------------------------------------------------\n");
	printf("---------------         Menu principal          ----------------\n");
	printf("----------------------------------------------------------------\n");
	printf(" 1 - Nouvelle partie \n");
	if (nbManches != 0) {  //Si une partie a déjà été jouée, le nombre de manche est différent de 0.
		printf(" 2 - CONTINUER LA PARTIE EN COURS\n");
	}
	printf(" 0 - Quitter\n");
	printf("----------------------------------------------------------------\n");
	
	if (nbManches!=0){
		choixMenu = saisirEntre(0,2);
	} else {
		choixMenu = saisirEntre(0,1);
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
	printf("================================================================\n");
	printf("===============     #    #  #   #   ###      ===================\n");
	printf("===============     #    #  ##  #  #   #     ===================\n");
	printf("===============     #    #  # # #  #   #     ===================\n");
	printf("===============     #    #  #  ##  #   #     ===================\n");
	printf("===============      ####   #   #   ###      ===================\n");
	printf("================================================================\n");

}

void compterPoints(TJoueur* joueur) {

}

void afficherVainqueur(TJoueur joueur1, TJoueur joueur2, TJoueur joueur3){

}

void afficherListe(*TCelluleCarte liste){
	TCelluleCarte* aux = liste;
	int tailleFile = 0;
	int nbLignes = 0;
	
	while (aux != NULL) {
		tailleFile += 1;
		aux=aux->suivant;
	}

	nbLignes = tailleFile/8; //8 car je désire afficher 8 cartes par ligne.

	int i=0;
	int y=0;
	char string[56];
	char stringtemp[7];
	strcpy(string,"");
	strcpy(stringtemp,"");

	//Dans cette boucle on affiche les lignes complètes.
	for (i=0;i<nbLignes;i++){ // On itère pour chaque ligne
		
		strcpy(string,"");
		aux = liste;
		for (y=0;y<i*8;y++){	// à chaque ligne, il faut replacer le pointeur sur la bonne carte afin d'obtenir les bonnes infos
			aux=aux->suivant;
		}
		
		printf("  .--.  .--.  .--.  .--.  .--.  .--.  .--.  .--.\n");
		for (y=0;y<8;y++){
			if (aux->carte.type==1){
				sprintf(stringtemp, "  |0%d|",aux->carte.valeur);
			} else if (aux->carte.type==2){
				sprintf(stringtemp, "  |+2|");
			} else if (aux->carte.type==3){
				sprintf(stringtemp, "  |<>|");
			} else if (aux->carte.type==4){
				sprintf(stringtemp, "  |=>|");
			} else if (aux->carte.type==5){
				sprintf(stringtemp, "  |**|");
			} else if (aux->carte.type==6){
				sprintf(stringtemp, "  |+4|");
			} else {
				sprintf(stringtemp, "  |00|");
			}
			strcat(string,stringtemp);
			aux = aux->suivant;
		}
		printf("%s\n",string);
	
		strcpy(string,"");
		aux = liste;
		for (y=1;y<i*8+1;y++){
			aux=aux->suivant;
		}

		for (y=0;y<8;y++){
			if (strcmp(aux->carte.couleur,"Ro")==0){
				strcat(string,"  |Ro|");
			} else if (strcmp(aux->carte.couleur,"Bl")==0){
				strcat(string,"  |Bl|");
			} else if (strcmp(aux->carte.couleur,"Ve")==0){
				strcat(string,"  |Ve|");
			} else if (strcmp(aux->carte.couleur,"Ja")==0){
				strcat(string,"  |Ja|");
			} else {
				strcat(string,"  |##|");
			}
			aux = aux->suivant;
		}
		printf("%s\n",string);
		printf("  *--*  *--*  *--*  *--*  *--*  *--*  *--*  *--*\n");
	}

	char string1[56];
	char string2[56];
	char string3[56];
	char string4[56];
	strcpy(string1,"");
	strcpy(string2,"");
	strcpy(string3,"");
	strcpy(string4,"");
	
	//Enfin dans cette boucle on itère sur les dernières cartes restantes si il y en a.
	//Aux pointe déjà sur la bonne TCelluleCarte.
	if (aux != NULL){
		while (aux != NULL) {
			strcat(string1,"  .--.");
			if (aux->carte.type==1){
				sprintf(stringtemp, "  |0%d|",aux->carte.valeur);
			} else if (aux->carte.type==2){
				sprintf(stringtemp, "  |+2|");
			} else if (aux->carte.type==3){
				sprintf(stringtemp, "  |<>|");
			} else if (aux->carte.type==4){
				sprintf(stringtemp, "  |<=|");
			} else if (aux->carte.type==5){
				sprintf(stringtemp, "  |JK|");
			} else if (aux->carte.type==6){
				sprintf(stringtemp, "  |+4|");
			} else {
				sprintf(stringtemp, "  |00|");
			}
			strcat(string2,stringtemp);
			if (strcmp(aux->carte.couleur,"Ro")==0){
				strcat(string3,"  |Ro|");
			} else if (strcmp(aux->carte.couleur,"Bl")==0){
				 strcat(string3,"  |Bl|");
			} else if (strcmp(aux->carte.couleur,"Ve")==0){
				strcat(string3,"  |Ve|");
			} else if (strcmp(aux->carte.couleur,"Ja")==0){
				strcat(string3,"  |Ja|");
			} else {
				strcat(string3,"  |##|");
			}
			strcat(string4,"  *--*");
			aux=aux->suivant;
		}
		printf("%s\n",string1);
		printf("%s\n",string2);
		printf("%s\n",string3);
		printf("%s\n\n",string4);
	}
}

void melangerPioche(){
	TCelluleCarte* aux = jeu;
	TCelluleCarte* prec; 
	int i =0;
	int y =0;
	int select;
	int tailleFile = 0;

	while (aux != NULL) {
		tailleFile += 1;
		aux=aux->suivant;
	}

	for (i=tailleFile;i>0;i--){
		select = rand()%i;
		aux=jeu;
		prec=jeu;
		if (select==0) {
			jeu = aux->suivant;
			aux->suivant=pioche;
			pioche=aux;
		} else {
			for (y=0;y<select;y++){
				prec=aux;
				aux=aux->suivant;
			}
			prec->suivant = aux->suivant;
			aux->suivant = pioche;
			pioche = aux;
		}
	}
}

void initialiserJeu(){
	ajoutSerie(1,10,"Bl",1,2);
	ajoutSerie(1,10,"Ro",1,2);
	ajoutSerie(1,10,"Ja",1,2);
	ajoutSerie(1,10,"Ve",1,2);

	ajoutSerie(20,21,"Bl",2,2);
	ajoutSerie(20,21,"Ro",2,2);
	ajoutSerie(20,21,"Ja",2,2);
	ajoutSerie(20,21,"Ve",2,2);

	ajoutSerie(20,21,"Bl",3,2);
	ajoutSerie(20,21,"Ro",3,2);
	ajoutSerie(20,21,"Ja",3,2);
	ajoutSerie(20,21,"Ve",3,2);

	ajoutSerie(20,21,"Bl",4,2);
	ajoutSerie(20,21,"Ro",4,2);
	ajoutSerie(20,21,"Ja",4,2);
	ajoutSerie(20,21,"Ve",4,2);

	ajoutSerie(50,51,"Sa",5,4);
	ajoutSerie(50,51,"Sa",6,4);
	ajoutSerie(0,1,"Ve",0,1);
	ajoutSerie(0,1,"Ve",0,1);
	ajoutSerie(0,1,"Ve",0,1);
	ajoutSerie(0,1,"Ve",0,1);
}

void ajoutSerie(int a, int b, char couleur[], int type, int nb){
	int i;
	int y;
	for (y=0;y<nb;y++){
		for (i=a;i<b;i++) {
			TCelluleCarte* newC = (TCelluleCarte*) malloc(sizeof(TCelluleCarte));
			newC->carte.valeur = i;
			strcpy(newC->carte.couleur,couleur);
			newC->carte.type = type;
			newC->suivant = jeu;
			jeu = newC;
		}
	}
}
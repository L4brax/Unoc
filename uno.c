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
void afficherListe(TCelluleCarte* liste); 	//Affiche une liste de Carte.
											//Prend en paramètre un pointeur vers une TCelluleCarte, en générale une main.
											//Affiche plusieurs cartes sur une seule ligne.
void melangerPioche(); //Mélange les cartes du jeu dans la pioche.
void libererPioche(); //libère la pioche.
void libererJeu(); //Libère le jeu.
void libererMain(TJoueur* joueur); //Libere la main du joueur en paramètre.
void tirerCarte(); //Place la carte en tête de pioche sur la tête du jeu.
void pioche7(TJoueur* joueur); //Pioche 7 cartes pour le joueur en paramètre.


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
		choixMenu = affichageMenu(nbManches);		
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
			initialiserJeu();
			melangerPioche();
			tirerCarte();
			pioche7(&j1);
			pioche7(&j2);
			pioche7(&j3);
			while (finManche == 0) {
				if (pioche == NULL) {
					printf("----------------------------------------------------------------\n");
					printf("   	La pioche est vide !\n");
					printf("	Le jeu est mélangé, une nouvelle carte est tirée.\n");
					printf("----------------------------------------------------------------\n");
					melangerPioche();
					tirerCarte();
				}
				printf("%s à vous de jouer !\n",jtour->nom);
				jouerTour(jtour);
				if (jtour->jmain == NULL) {
					afficherUno();
					finManche = 1;
					printf("----------------------------------------------------------------\n");
					compterPoints(&j1);
					printf("\n");
					compterPoints(&j2);
					printf("\n");
					compterPoints(&j3);
					printf("----------------------------------------------------------------\n");
					libererJeu();
					libererPioche();
					libererMain(&j1);
					libererMain(&j2);
					libererMain(&j3);
					nbManches =+ 1;
					if (nbManches == 3) {
						afficherVainqueur(j1,j2,j3);
						nbManches=0;
						j1.nbPoints = 0;
						j2.nbPoints = 0;
						j3.nbPoints = 0;
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
	if ((strcmp(carteJoueur.couleur,carteJeu.couleur)==0)||(strcmp(carteJeu.couleur,"Sa")==0)){
		return 1;
	} else {
		return 0;
	}
}
	
int verifierValeur(TCarte carteJoueur, TCarte carteJeu){
	if (carteJoueur.valeur==carteJeu.valeur){
		return 1;
	} else {
		return 0;
	}
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
	
int saisirEntre(int a, int b){
	int ret;
	do {
		scanf("%d", &ret);
	} while ((ret<a) || (ret>b));
	return ret;
}

void jouerTour(TJoueur* joueur){
	TCelluleCarte* aux = joueur->jmain;
	TCelluleCarte* prec = joueur->jmain;
	int choixMax;
	int choixCarte;
	int choixOk = 0;
	int choixCouleur;
	char couleur[2];
	int i;

	// Affichage de la carte sur le jeu :
	printf("                   .--.\n");
	printf("La carte du jeu :  ");
	if (jeu->carte.type==1){
		printf("|0%d|\n",jeu->carte.valeur);
	} else if (jeu->carte.type==2){
		printf("|+2|\n");
	} else if (jeu->carte.type==3){
		printf("|<>|\n");
	} else if (jeu->carte.type==4){
		printf("|=>|\n");
	} else if (jeu->carte.type==5){
		printf("|**|\n");
	} else if (jeu->carte.type==6){
		printf("|+4|\n");
	} else {
		printf("|00|\n");
	}
	if (strcmp(jeu->carte.couleur,"Ro")==0){
		printf("                   |Ro|\n");
	} else if (strcmp(jeu->carte.couleur,"Bl")==0){
		printf("                   |Bl|\n");
	} else if (strcmp(jeu->carte.couleur,"Ve")==0){
		printf("                   |Ve|\n");
	} else if (strcmp(jeu->carte.couleur,"Ja")==0){
		printf("                   |Ja|\n");
	} else {
		printf("                   |##|\n");
	}
	printf("                   *--*\n\n");

	// Affichage de la main du joueur :
	printf(" Votre main est la suivante :\n");
	afficherListe(joueur->jmain);
	// On compte le nombre de cartes en main du joueur :
	while (aux != NULL) {
		choixMax += 1;
		aux=aux->suivant;
	}

	while (choixOk == 0) {
		printf(" \n Choisissez une carte en indiquant son numéro\n");
		printf("  (de gauche à droite en partant de 1)\n");
		printf("  0 pour piocher.");

		// Le joueur saisit la carte à jouer :
		choixCarte = saisirEntre(0,choixMax);
		if (choixCarte == 0) {
			piocherCarte(joueur);
			choixOk = 1;
		} else {
			// On place aux sur la carte choisie :
			aux = joueur->jmain;
			prec = joueur->jmain;
			if (choixCarte>1){
				for (i=0;i<choixCarte-1;i++){
					prec = aux;
					aux = aux->suivant;
				}
			}
			// On vérifie si cette carte est jouable et applique l'effet:
			// Cas d'une carte numérotée :
			if (aux->carte.type==1){
				if((verifierValeur(aux->carte,jeu->carte)==1)||(verifierCouleur(aux->carte,jeu->carte)==1)){
					if (choixCarte==1){
						joueur->jmain = aux->suivant;
						aux->suivant = jeu;
						jeu = aux;
					} else {
						prec->suivant = aux->suivant;
						aux->suivant = jeu;
						jeu = aux;
					}
					choixOk = 1;
				}
			// Cas d'un +2
			} else if (aux->carte.type==2) {
				if((jeu->carte.type==2)||(verifierCouleur(aux->carte,jeu->carte)==1)){
					if (choixCarte==1){
						joueur->jmain = aux->suivant;
						aux->suivant = jeu;
						jeu = aux;
					} else {
						prec->suivant = aux->suivant;
						aux->suivant = jeu;
						jeu = aux;
					}
					choixOk = 1;
					printf("  C'est un +2 !\n");
					piocherCarte(joueur->jsuivant);
					piocherCarte(joueur->jsuivant);
				}
			// Cas d'un pass tour
			} else if (aux->carte.type==4) {
				if((jeu->carte.type==3)||(verifierCouleur(aux->carte,jeu->carte)==1)){
					if (choixCarte==1){
						joueur->jmain = aux->suivant;
						aux->suivant = jeu;
						jeu = aux;
					} else {
						prec->suivant = aux->suivant;
						aux->suivant = jeu;
						jeu = aux;
					}
					choixOk = 1;
					printf("  C'est un pass tour !\n");
					joueur = joueur->jsuivant;
				}
			// Cas d'un changement de sens
			} else if (aux->carte.type==3) {
				if((jeu->carte.type==3)||(verifierCouleur(aux->carte,jeu->carte)==1)){
					if (choixCarte==1){
						joueur->jmain = aux->suivant;
						aux->suivant = jeu;
						jeu = aux;
					} else {
						prec->suivant = aux->suivant;
						aux->suivant = jeu;
						jeu = aux;
					}
					choixOk = 1;
					printf("  C'est un changement de sens !\n");
					joueur->jsuivant->jsuivant->jsuivant=joueur->jsuivant;
					joueur->jsuivant=joueur->jsuivant->jsuivant;
					joueur->jsuivant->jsuivant->jsuivant=joueur;
				}
			// Cas d'un +4
			} else if (aux->carte.type==6){
				if (choixCarte==1){
					joueur->jmain = aux->suivant;
					aux->suivant = jeu;
					jeu = aux;
				} else {
					prec->suivant = aux->suivant;
					aux->suivant = jeu;
					jeu = aux;
				}
				choixOk = 1;
				printf("  C'est un +4 !\n");
				piocherCarte(joueur->jsuivant);
				piocherCarte(joueur->jsuivant);
				piocherCarte(joueur->jsuivant);
				piocherCarte(joueur->jsuivant);
			// Cas d'un joker
			} else if (aux->carte.type==5){
				if (choixCarte==1){
					joueur->jmain = aux->suivant;
					aux->suivant = jeu;
					jeu = aux;
				} else {
					prec->suivant = aux->suivant;
					aux->suivant = jeu;
					jeu = aux;
				}
				choixOk = 1;
				printf("  C'est un JOKER !\n");
				printf("  Veuillez choisir une couleur : \n");
				printf("  1 - Rouge\n");
				printf("  2 - Vert\n");
				printf("  3 - Bleu\n");
				printf("  4 - Jaune\n");
				choixCouleur = saisirEntre(1,4);
				if (choixCouleur == 1){
					strcpy(couleur,"Ro");
					printf("%s a choisi du Rouge !",joueur->nom);
				} else if (choixCouleur == 2){
					strcpy(couleur,"Ve");
					printf("%s a choisi du Vert !",joueur->nom);
				} else if (choixCouleur == 3){
					strcpy(couleur,"Bl");
					printf("%s a choisi du Bleu !",joueur->nom);
				} else {
					strcpy(couleur,"Ja");
					printf("%s a choisi du Jaune !",joueur->nom);
				}
				strcpy(jeu->carte.couleur,couleur);
			} else {
				if((jeu->carte.type==0)||(verifierCouleur(aux->carte,jeu->carte)==1)){
					if (choixCarte==1){
						joueur->jmain = aux->suivant;
						aux->suivant = jeu;
						jeu = aux;
					} else {
						prec->suivant = aux->suivant;
						aux->suivant = jeu;
						jeu = aux;
					}
					choixOk = 1;
					printf("  C'est un Zero !\n");
					printf("  Vous pouvez échanger votre main, choisissez avec qui :\n");
					printf("  1 - %s",joueur->jsuivant->nom);
					printf("  2 - %s",joueur->jsuivant->jsuivant->nom);
					choixCouleur = saisirEntre(1,2);
					if (choixCouleur==1) {
						aux = joueur->jmain;
						joueur->jmain = joueur->jsuivant->jmain;
						joueur->jsuivant->jmain = aux;
					} else {
						aux = joueur->jmain;
						joueur->jmain = joueur->jsuivant->jsuivant->jmain;
						joueur->jsuivant->jsuivant->jmain = aux;
					}
				}
			}
		}
		if (choixOk==1){
			printf("  Vous avez joué !\n");
			printf("----------------------------------------------------------------\n");
		} else {
			printf("  La carte choisie n'est pas jouable !");
		}
	}
}

void afficherUno(){
	printf("================================================================\n");
	printf("===============     #    #  #   #   ###      ===================\n");
	printf("===============     #    #  ##  #  #   #     ===================\n");
	printf("===============     #    #  # # #  #   #     ===================\n");
	printf("===============     #    #  #  ##  #   #     ===================\n");
	printf("===============      ####   #   #   ###      ===================\n");
	printf("================================================================\n\n");

}

void compterPoints(TJoueur* joueur) {
	TCelluleCarte* aux = joueur->jmain;
	int pointsManche =0;
	while (aux != NULL){
		joueur->nbPoints += aux->carte.valeur;
		aux = aux->suivant;
		pointsManche += aux->carte.valeur;
	}
	printf("  %s, vous avez un score de %d sur cette manche.\n",joueur->nom,pointsManche);
	printf("  Vous avez un score total de : %d points\n",joueur->nbPoints);
}

void afficherVainqueur(TJoueur joueur1, TJoueur joueur2, TJoueur joueur3){
	printf("================================================================\n");
	if (joueur1.nbPoints>joueur2.nbPoints){
		if (joueur1.nbPoints>joueur3.nbPoints){
			printf("  Bravo %s, vous remportez la partie !",joueur1.nom);
		} else if (joueur3.nbPoints>joueur2.nbPoints) {
			printf("  Bravo %s, vous remportez la partie !",joueur3.nom);
		} else {
			printf("  Bravo %s, vous remportez la partie !",joueur2.nom);
		}
	}
	printf("================================================================\n");
}

void afficherListe(TCelluleCarte* liste){
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

void libererPioche(){
	TCelluleCarte* aux = pioche;
	while(aux != NULL){
		pioche = pioche->suivant;
		free(aux);
		aux=pioche;
	}
}

void libererJeu(){
	TCelluleCarte* aux = jeu;
	while(aux != NULL){
		jeu = jeu->suivant;
		free(aux);
		aux=jeu;
	}
}

void tirerCarte(){
	TCelluleCarte* aux = pioche;
	pioche = pioche->suivant;
	aux->suivant = jeu;
	jeu = aux;
}

void libererMain(TJoueur* joueur){
	TCelluleCarte* aux = joueur->jmain;
	while(aux != NULL){
		joueur->jmain = joueur->jmain->suivant;
		free(aux);
		aux=joueur->jmain;
	}
}

void pioche7(TJoueur* joueur){
	int i;
	for (i=0;i<7;i++){
		piocherCarte(joueur);
	}
}
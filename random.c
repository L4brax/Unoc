#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _TCarte
{
	int valeur; // Numéro et valeur de la carte
	char couleur[2]; // Couleur de la carte : R B J V S
	int type; // Type de la carte (Base, +2, +4...)
} TCarte;

typedef struct _TCelluleCarte
{
	TCarte carte;
	struct _TCelluleCarte* suivant;
} TCelluleCarte;

TCelluleCarte* pioche = NULL;
TCelluleCarte* jeu = NULL;

void initialiserJeu(); //Initialise toutes les cartes du jeu dans la pile Jeu non mélangées.
void ajoutSerie(int a, int b, char couleur[2], int type, int nb); // Permet d'ajouter une série de cartes à la pile Jeu.
						// Le paramètre a désigne la borne inférieur de l'itération de la valeur de la carte (a inclus)
						// Le paramètre b désigne la borne supérieur de l'itération de la valeur de la carte (b exclus)
						// Couleur désigne la couleur affectée aux cartes créées.
						// Type désigne le type affecté aux cartes crées.
						// nb désigne le nombre de séries à créer.
void afficherListe();
void afficherSuperListe();	
void melangerPioche();
void afficherSuperListePioche();


int main(){
	initialiserJeu();
	afficherSuperListe();
	melangerPioche();
	printf ("=================================\n");
	printf ("=================================\n");
	printf ("=================================\n");
	printf ("=================================\n");
	afficherSuperListe();
	afficherSuperListePioche();
	return 0;
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

void afficherListe(){
	TCelluleCarte* aux = jeu;
	//int i;
	while (aux != NULL) {
		if (aux->carte.type == 1){
			printf("  ----  \n");
			printf("  |0%d|  \n",aux->carte.valeur);
			printf("  |%s|  \n",aux->carte.couleur);
			printf("  ----  \n");
			printf("\n");
		}
		aux=aux->suivant;
	}
}

void afficherSuperListe(){
	TCelluleCarte* aux = jeu;
	int tailleFile = 0;
	int nbLignes = 0;
	
	while (aux != NULL) {
		tailleFile += 1;
		aux=aux->suivant;
	}

	nbLignes = tailleFile/8;

	int i=0;
	int y=0;
	char string[56];
	char stringtemp[7];
	strcpy(string,"");
	strcpy(stringtemp,"");

	
	for (i=0;i<nbLignes;i++){
		
		strcpy(string,"");
		aux = jeu;
		for (y=0;y<i*8;y++){
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
		aux = jeu;
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
				sprintf(stringtemp, "  |=>|");
			} else if (aux->carte.type==5){
				sprintf(stringtemp, "  |**|");
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

void afficherSuperListePioche(){
	TCelluleCarte* aux = pioche;
	int tailleFile = 0;
	int nbLignes = 0;
	
	while (aux != NULL) {
		tailleFile += 1;
		aux=aux->suivant;
	}

	nbLignes = tailleFile/8;

	int i=0;
	int y=0;
	char string[56];
	char stringtemp[7];
	strcpy(string,"");
	strcpy(stringtemp,"");

	
	for (i=0;i<nbLignes;i++){
		
		strcpy(string,"");
		aux = pioche;
		for (y=0;y<i*8;y++){
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
		aux = pioche;
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
				sprintf(stringtemp, "  |=>|");
			} else if (aux->carte.type==5){
				sprintf(stringtemp, "  |**|");
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


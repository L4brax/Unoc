#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

TCelluleCarte* pioche;
TCelluleCarte* jeu;

void initialiserJeu(); //Initialise toutes les cartes du jeu dans la pile Jeu non mélangées.
void ajoutSerie(int a, int b, char couleur[2], int type, int nb); // Permet d'ajouter une série de cartes à la pile Jeu.
						// Le paramètre a désigne la borne inférieur de l'itération de la valeur de la carte (a inclus)
						// Le paramètre b désigne la borne supérieur de l'itération de la valeur de la carte (b exclus)
						// Couleur désigne la couleur affectée aux cartes créées.
						// Type désigne le type affecté aux cartes crées.
						// nb désigne le nombre de séries à créer.
void afficherListe();		

int main(){
	initialiserJeu();
	afficherListe();
	char string[56] = "98";
	int a = 5;
	sprintf(string, "%d",a);
	printf("   %s",string);
	
	return 0;
}

void initialiserJeu(){
	ajoutSerie(1,10,"Bl",1,2);
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

/*void afficherSuperListe(){
	TCelluleCarte* aux = jeu;
	int tailleFile = 0;
	int nbLignes = 0;
	int reste = 0;
	
	while (aux != NULL) {
		tailleFile =+ 1;
		aux=aux->suivant;
	}

	nbLignes = taille/8;
	reste = taille%8;

	int i=0;
	int y=0;
	char string[56] = "";
	char stringtemp[7] = "";
	char valeur
	aux = jeu;
	for (i=0;i<nbLignes;i++){
		printf("   ----   ----   ----   ----   ----   ----   ----   ----\n");
		for (y=0;y<8;y++){
			if (aux->carte.type==1){
				sprintf(stringtemp, " %d:|0%d|",i*8+y,aux->carte.valeur);
			} else if (aux->carte.type==2){
				sprintf(stringtemp, " %d:|+2|",i*8+y);
			} else if (aux->carte.type==3){
				sprintf(stringtemp, " %d:|<>|",i*8+y);
			} else if (aux->carte.type==4){
				sprintf(stringtemp, " %d:|=>|",i*8+y);
			} else if (aux->carte.type==5){
				sprintf(stringtemp, " %d:|**|",i*8+y);
			} else if (aux->carte.type==6){
				sprintf(stringtemp, " %d:|+4|",i*8+y);
			} else {
				sprintf(stringtemp, " %d:|00|",i*8+y);
			}
			string = strcat(string,stringtemp);
			aux = aux->suivant;
		}
		printf("%s\n",string);

		string="";
		aux = jeu;
		for (y=0;y<i*8;y++){
			aux=aux->suivant;
		}

		for (y=0;y<8;y++){
			if (aux->carte.couleur=="Ro"){
				string = strcat(string,"   |Ro|");
			} else if (aux->carte.couleur=="Bl"){
				string = strcat(string,"   |Bl|");
			} else if (aux->carte.couleur=="Ve"){
				string = strcat(string,"   |Ve|");
			} else if (aux->carte.couleur=="Ja"){
				string = strcat(string,"   |Ja|");
			} else {
				string = strcat(string,"   |##|");
			}
			aux = aux->suivant;
		}
		printf("%s\n");
		printf("   ----   ----   ----   ----   ----   ----   ----   ----\n\n");
	}

	char string1[56];
	char string2[56];
	char string3[56];
	char string4[56];
	while (aux != NULL) {
		string1 = strcat(string,"   ----");
		if (aux->carte.type==1){
				sprintf(stringtemp, " %d:|0%d|",i*8+y,aux->carte.valeur);
			} else if (aux->carte.type==2){
				sprintf(stringtemp, " %d:|+2|",i*8+y);
			} else if (aux->carte.type==3){
				sprintf(stringtemp, " %d:|<>|",i*8+y);
			} else if (aux->carte.type==4){
				sprintf(stringtemp, " %d:|=>|",i*8+y);
			} else if (aux->carte.type==5){
				sprintf(stringtemp, " %d:|**|",i*8+y);
			} else if (aux->carte.type==6){
				sprintf(stringtemp, " %d:|+4|",i*8+y);
			} else {
				sprintf(stringtemp, " %d:|00|",i*8+y);
			}
			string = strcat(string,stringtemp);
	}
}*/
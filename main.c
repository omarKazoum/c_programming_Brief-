#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
//fonction utilisées
void fakeData();
void printDataSoFar();
void afficheLeMenuPricipale();
void introduireUnCompte();
void lireOption();
void introduirePlusieurComptes();
void header();
void clearScreen();
enum Choix prendreChoix();
void entrezqqChosePourOvrirMenuPrincipale();
//constants
enum Choix{OUI,NON};
#define MAX_NUMBER_OF_ACCOUNTS 1000
typedef struct Compte Compte ;
//variables globals
struct Co mpte
{
	int id;
	double sold;
	char nomProprietaire[20];
	char prenomProprietaire[20];
	char cin[20]; 
};

int open_accounts_count=0; 
int optionChoisis;
struct Compte comptes[MAX_NUMBER_OF_ACCOUNTS];

///////////////////////:start of main function
int main(){
	fakeData();
	afficheLeMenuPricipale();
	//printDataSoFar();
	return 0;
}
///////////////////////////end of main function
//generating fake data to feed our program
void fakeData(){
	for(int i=0;i<12;i++){
		struct Compte c;
		c.id=open_accounts_count;
		c.sold=rand();
		sprintf(c.nomProprietaire,"nom %d",i);
		sprintf(c.prenomProprietaire,"prenom %d",i);
		sprintf(c.cin,"JC%d",i);
		comptes[i]=c;
		open_accounts_count++;
		
	}
}
 
void printDataSoFar(){
	printf("\n--------------printing data contents-----------------\n");
	for(int i=0;i<open_accounts_count;i++){
		printf("\n%d->{ accountNbr:%d , name:\"%s %s\" , CIN:\"%s\" , balance:%f }\n",
			i,comptes[i].id,comptes[i].nomProprietaire,comptes[i].prenomProprietaire,comptes[i].cin,comptes[i].sold);
	}
	printf("\n-----------------------------------------------------");
}

void insertAccount(struct Compte c,int position){
	comptes[position]=c;
}

void afficheLeMenuPricipale(){
	system("cls");
	header();
	printf("\n1> introduire un compte");
	printf("\n2> introduire pleusieur comptes");
	printf("\n3> Operations ");
	printf("\n4> Affichage");
	printf("\n5> Fidelisation");
	printf("\n6> Quitter l'application");
	printf("\nentrez le nombre qui correspond a votre choix\n");
	lireOption();

	switch(optionChoisis){
		case 1:
			clearScreen();
			header();
			introduireUnCompte(); 
			entrezqqChosePourOvrirMenuPrincipale();
			afficheLeMenuPricipale();
		;break;
		case 2:
			clearScreen();
			introduirePlusieurComptes();
			afficheLeMenuPricipale();
		;break;
		case 3:
		
		;break;
		case 4:
		
		;break;
		case 5:
		
		;break;
		case 6:
		
		;break;
		default:
		afficheLeMenuPricipale();
	}

}

void introduireUnCompte(){
	Compte c;
	printf("\nCreation d'un compte");
	printf("\nentrez le nom \n");
	scanf("%s",c.nomProprietaire);
	printf("\nentrez le prenom \n");
	scanf("%s",c.prenomProprietaire);
	printf("\nentrez le numero de la carte nationale d'identite \n");
	scanf("%s",c.nomProprietaire);
	printf("\nsold initial \n");
	scanf("%d",&c.sold);
	c.id=open_accounts_count;
	bool sortir=true;
	do{
		sortir=true;
		printf("etes vous sur de vouloir enregistrer ce compte?\n");
		enum Choix choix=prendreChoix();
		switch (choix){
			case OUI:
				comptes[open_accounts_count-1]=c;
				open_accounts_count++;
				
			break;
			case NON:
			break;
			default:
			sortir=false;
			break;
		}
	}while (!sortir);
	

}
void entrezqqChosePourOvrirMenuPrincipale(){
	printf("compte bien ajoute tapez qq chose pour revenir au menu principale\n");
				getch();
}
void introduirePlusieurComptes(){
	header();
	printf("Introduire plusieurs comptes\n");
	CREER_COMPTE:
	introduireUnCompte();
	printf("\nsouhaitez vous creer un autre compte?\n");
	enum Choix choix=prendreChoix();
	switch(choix){
		case OUI:
			goto CREER_COMPTE;
		break;
		case NON:
		break;
	}
}
enum Choix prendreChoix(){
	while(true){
	printf("\nEntrez 1 pour Oui ou 2 pour Non");
	lireOption();
		if(optionChoisis==1){
			return OUI;
		}else if(optionChoisis==2){
			return NON;
		};
	}
}
void clearScreen(){
	system("cls");
};
void lireOption(){
	scanf("%d",&optionChoisis);
	fflush(stdin);
}
void header(){
	printf("\n-------------------------Bonjour Dans La Bank Du Maroc------------------------------\n");
}
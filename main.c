#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
//constants et variables
enum Choix{OUI,NON};
enum OperationSurCompte{DEPOT=0,RETRAIT=1};
#define MAX_NUMBER_OF_ACCOUNTS 1000
typedef struct Compte Compte ;
//variables globals
struct Compte
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
void afficherMenuOperations();
void afficherMenuOperationDepotRetrait(int op);
void demmanderLechoix();
int choisirUnComptePourOperation();
Compte* chercherComptesParCin(char cin[]);//recherche les comptes ayant le cin donné
///////////////////////:start of main function
int main(){
	fakeData();
	//afficheLeMenuPricipale();
	printDataSoFar();
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
		case 1://créer un seul compte
			clearScreen();
			header();
			introduireUnCompte(); 
			entrezqqChosePourOvrirMenuPrincipale();
			afficheLeMenuPricipale();
		;break;
		case 2://créer plusieurs comptes
			clearScreen();
			introduirePlusieurComptes();
			afficheLeMenuPricipale();
		;break;
		case 3://effectuer une operation sur un compte (depot/retrait)
			clearScreen();
			header();
			afficherMenuOperations();
		;break;
		case 4://Affichage des 
		
		;break;
		case 5://Fidelisation
		
		;break;
		case 6://Quitter l'application
		
		;break;
		default:// si l'utlisateur entre un choix qui n'est pas difinie le menu principale va se reafficher
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
			//ne rien faire
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
void afficherMenuOperations(){
	printf("\n1 > Retrait");
	printf("\n2 > Depot");
	printf("\n3 > Menu principale");
	CHOISIR_OPERATION:
	demmanderLechoix();
	lireOption();
	switch(optionChoisis){
		case 1:
			clearScreen();
			header();
			afficherMenuOperationDepotRetrait(RETRAIT);
		break;
		case 2:
			clearScreen();
			header();
			afficherMenuOperationDepotRetrait(DEPOT);
		break;
		case 3:
			afficheLeMenuPricipale();
		break;
		default:
			goto CHOISIR_OPERATION;
	}

}
void afficherMenuOperationDepotRetrait(int op){
	//TODO:: costumize depending on the type of the operation
	int nbrCompteATraiter=choisirUnComptePourOperation();
}
int choisirUnComptePourOperation(){
	printf("\npour effectuer un operation il faut d'abord choisir un compte svp entrez votre cin");
	char cin[20];
	scanf("%s",cin);
	//TODO:: continue this find the equivalent accoounts with cin
}
Compte* chercherComptesParCin(char cin[]){
	//maintenet on doit savoir le nombre des comptes ayant ce CIN
	int count=0;
	for(int i=0;i<open_accounts_count;i++){
		if(strcmp(comptes[i].cin,cin)==0)
			count++;
	}

	static Compte foundAccounts[count];
	int insertingIndex=0;
	for(int i=0;i<open_accounts_count;i++){
		if(strcmp(comptes[i].cin,cin)==0){
			foundAccounts[insertingIndex++]=comptes[i];
		}
	}
	return foundAccounts;

}

void demmanderLechoix(){
	printf("\nentrez le nombre correspondant a votre choix puis tapez entrer ");
}

void header(){
	printf("\n-------------------------Bonjour Dans La Bank Du Maroc------------------------------\n");
}
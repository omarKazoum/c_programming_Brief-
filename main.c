#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
//fonction utilisées
void fakeData();
void printDataSoFar();
void afficheLeMenuPricipale();
//constants
#define MAX_NUMBER_OF_ACCOUNTS 1000

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
struct Compte comptes[MAX_NUMBER_OF_ACCOUNTS];

///////////////////////:start of main function
int main(){
	fakeData();
	
	return 0;
}
///////////////////////////end of main function
//ge erating fake data to feed our program
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
	printf("\n-----------printing data contents--------------------\n");
	for(int i=0;i<open_accounts_count;i++){
		printf("\n%d->{ accountNbr:%d , name:\"%s %s\" , CIN:\"%s\" , balance:%d }\n",
			i,comptes[i].id,comptes[i].nomProprietaire,comptes[i].prenomProprietaire,comptes[i].cin,comptes[i].sold);
	}
	printf("\n-----------------------------------------------------");
}

void insertAccount(struct Compte c,int position){
	comptes[position]=c;
}
void afficherOption(int option){
	//switch()

}

void afficheLeMenuPricipale(){
	printf("///////////////////////////Bonjour Dans La Bank Du Maroc\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("\nentrez le nombre qui correspond a votre choix\n");
	printf("\n1> introduire un compte");
	printf("\n2> Opérations :");
	printf("\n3> Affichage");
	printf("\n4> Fidelisation");
	printf("\n5> Quitter l'application");
}

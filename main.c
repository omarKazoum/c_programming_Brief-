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
	float sold;
	char nomProprietaire[20];
	char prenomProprietaire[20];
	char cin[20]; 
};

int open_accounts_count=0; 
int optionChoisis;
struct Compte comptes[MAX_NUMBER_OF_ACCOUNTS];
#define MAX_ACCOUNST_NUMBER_PER_CIN 10 
int nbrDesComptesTrouvesApresRecheche=-1;
int idCompteChoisis=-1;
//fonction utilisées
void fakeData();
void loadData();
void saveData();
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
void addToAccount(int accountId,float amount);
float lireMontanatDeLUtilisateur(int op);
void trierLesComptesParSold(struct Compte comptesATrier[],int length,int order/*0 for ascending and 1 for descending*/);
// takes a cin {char[]}, comptes Compte[]
void chercherComptesParCin(char cin[],Compte c[]);//recherche les comptes ayant le cin donné
void afficherMenuAffichage();
void afficherDesComptes(struct Compte comptesATraiter[],int length);
void afficherUnCompte(struct Compte compteAAfficher);
void afficherUnCompte(struct Compte compteAAfficher);
float lireNombreAFIltrerLesComptes();
int compterLesNombresSuperieurA(struct Compte comptesAUtliser[],int lengh,float soldMin);
void retournerLeComptesAyantLeSoldSuperieurA(struct Compte comptesAUtliser[],int lengh,struct Compte tableARemplire[],int nombreDesComptesARemplir,float minSold);
void afficherMenuFedelisation();
///////////////////////:start of main function
int main(){
	//loadData();
	//printDataSoFar();
	//getch();
	fakeData();
	afficheLeMenuPricipale();
	//saveData();
	return 0;
}
///////////////////////////end of main function
void loadData(){
	 //store the count of elemnts
	 FILE* fileCP;
	if(fileCP=fopen("count.db","r")){
		fread(&open_accounts_count,sizeof(int),1,fileCP);
	}else{
		open_accounts_count=0;
	}
	fclose(fileCP);
	FILE* fileP;
	if(fileP=fopen("data.db","r")){;
		int size=fread(comptes,sizeof(struct Compte),open_accounts_count,fileP);
		printf("data read from data.db %d bytes",size);
		fclose(fileP);
		}
};
void saveData(){
	//store the count of elemnts
	FILE* fileCP=fopen("count.db","w");
	fwrite(&open_accounts_count,sizeof(int),1,fileCP);
	fclose(fileCP);

	FILE* fileP=fopen("data.db","w");
	int size=fwrite(comptes,sizeof(struct Compte),open_accounts_count,fileP);
	printf("data write in data.db %d bytes",size);
	fclose(fileP);
};

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
		;break;
		case 2://créer plusieurs comptes
			clearScreen();
			introduirePlusieurComptes();
			entrezqqChosePourOvrirMenuPrincipale();
		;break;
		case 3://effectuer une operation sur un compte (depot/retrait)
			clearScreen();
			header();
			afficherMenuOperations();
		;break;
		case 4://Affichage 
			clearScreen();
			header();
			afficherMenuAffichage();
		;break;
		case 5://Fidelisation
		clearScreen();
		header();
		afficherMenuFedelisation();
		;break;
		case 6://Quitter l'application
				printf("\nenregistrement encore ...");
				//saveData();
				printf("Au Revoir !");
		;break;
		default:// si l'utlisateur entre un choix qui n'est pas difinie le menu principale va se reafficher
			afficheLeMenuPricipale();
	}
}
void afficherMenuFedelisation(){
	printf("\nFedelasation\n");
	printf("\ncette option vous permet de ajouter 1.3%% aux 3 comptes ayant le plus grand balance\n");
	printf("\nvoici les trois comptes a fedeliser");
	//TODO continue;
	// on prend les comptes valabale on les met dans une table puis les trie par montant asendant
	struct Compte comptesDisponibleAtrier[open_accounts_count];
		for(int i=0;i<open_accounts_count;i++){
			comptesDisponibleAtrier[i]=comptes[i];
		};
		trierLesComptesParSold(comptesDisponibleAtrier,open_accounts_count,1);
			// printing a table contaning the accounts info and indices
	printf("\n--------------------------------------------------------------------------------------------");
	printf("\n#\t N compte\t\t Nom complet \t\t\t   Cin \t\t   Sold\t");
	printf("\n--------------------------------------------------------------------------------------------");
	int nbrDesCompteAFediliser=(open_accounts_count>3)?3:open_accounts_count;
	for(int i=0;i<nbrDesCompteAFediliser;i++){
		printf("\n%i \t %i \t\t\t %-8s %-8s \t\t %-8s \t %.2f\t",
			i+1,comptesDisponibleAtrier[i].id,comptesDisponibleAtrier[i].nomProprietaire,comptesDisponibleAtrier[i].prenomProprietaire,comptesDisponibleAtrier[i].cin,comptesDisponibleAtrier[i].sold);
	}
	printf("\n--------------------------------------------------------------------------------------------\n");
	// now lets take user input to chouse which user acount to work on
	printf("\netes vous sur de vouloir ajouter 1.3%% au sold de ces comptes?");
	enum Choix cho=prendreChoix();
	if(cho==OUI){
		// on va fedeliser ces comptes
		for(int i=0;i<nbrDesCompteAFediliser;i++){
			// check if the changes actually affect the original table the global one	
			for(int j=0;j<open_accounts_count;j++){
				if(comptes[j].id==comptesDisponibleAtrier[i].id){
					comptes[j].sold+=comptes[j].sold*0.013;
					printf("\n=>fedelisation de compte avec nbr #%d",comptes[j].id);
					printf("\n=>sold apres fedilisation Du compte #%d est %fDH",comptes[j].id,comptes[j].sold);
				}
			}
		}
		printf("\n---operation reussit---");
		entrezqqChosePourOvrirMenuPrincipale();
	}else{
		entrezqqChosePourOvrirMenuPrincipale();
	}
};
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
	scanf("%f",&c.sold);
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
				printf("Compte N #%d  est bien cree !",c.id);
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
	printf("\ntapez qq chose pour revenir au menu principale \n");
	getch();
	afficheLeMenuPricipale();
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
	printf("\nEntrez 1 pour Oui ou 2 pour Non  ");
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
	int nbrCompteATraiter=choisirUnComptePourOperation();
	//printf("utlisateura choisis le compte avec id %d",nbrCompteATraiter); 
	if(nbrCompteATraiter==-1){
		//si l'utilisateur n'a pas de compte
		entrezqqChosePourOvrirMenuPrincipale();
	}else{
		//un compte existant est selectione on effectue l'opeartion
		float mt=lireMontanatDeLUtilisateur(op);
		//printf("\nentred amount is %f",mt);
		printf("etes vous sur de vouloir %s le montant de %f %s compte avec l'identifiant %d ?\n"
		,(op==DEPOT?"deposer ":"retirer"),mt,(op==DEPOT?"dans":"du"),nbrCompteATraiter);
		if(op==RETRAIT)
			mt=-mt;

		enum Choix c=prendreChoix();
		switch (c)
		{
		case OUI:
			addToAccount(nbrCompteATraiter,mt);
			printf("\nle montant a bien ete %s\n",(op==DEPOT?"depose":"retire"));
			entrezqqChosePourOvrirMenuPrincipale();
			break;
		case NON:
			afficheLeMenuPricipale();
			break;
		}
		
	}
}
float lireMontanatDeLUtilisateur(int op){
	printf("entrez le montant que vous voulez %s dans le compte ",(op==DEPOT)?"deposer":"retirer");
	float montant;
	scanf("%f",&montant);
	return montant;
};
int choisirUnComptePourOperation(){
	printf("\nPour effectuer une operation il faut d'abord choisir un compte svp entrez votre cin  ");
	char cin[20];
	scanf("%s",cin);
	Compte comptesTrouves[MAX_ACCOUNST_NUMBER_PER_CIN];
	chercherComptesParCin(cin,comptesTrouves);
	CHOISIR_UN_COMPTE:
	if(nbrDesComptesTrouvesApresRecheche>0){
			printf("\nchoisir un compte\n");
			printf("#\tNumero Du Compte\tNom et Prenom\tSold\n");
		for(int i=0;i<nbrDesComptesTrouvesApresRecheche;i++){
			printf("%d\t%d\t\t%s %s\t%f\n",i+1,comptesTrouves[i].id,comptesTrouves[i].nomProprietaire,comptesTrouves[i].prenomProprietaire,comptesTrouves[i].sold);
		}
		printf("\nentrez le nombre correspondant au compte de votre choix ");
		lireOption();
		if(optionChoisis>=1 && optionChoisis<=nbrDesComptesTrouvesApresRecheche){
			// donc id du compte est valide
			return optionChoisis-1;
		}else{
			//sinon on lui demande de rentrer le nombre correspondant au compte
			goto CHOISIR_UN_COMPTE;
		}
	}else{
			printf("\nLe client avec le cin:%s ne dispose pas de compte!\n",cin);
			return -1;
	}


}
void chercherComptesParCin(char cin[],Compte cmpts[] ){
	//maintenet on doit savoir le nombre des comptes ayant ce CIN
	int count=0;
	nbrDesComptesTrouvesApresRecheche=0;
	for(int i=0;i<open_accounts_count;i++){
		if(strcmp(comptes[i].cin,cin)==0)
			count++;
	}
	int insertingIndex=0;
	for(int i=0;i<open_accounts_count&& i<MAX_ACCOUNST_NUMBER_PER_CIN;i++){
		if(strcmp(comptes[i].cin,cin)==0){
			cmpts[insertingIndex]=comptes[i];
			insertingIndex++;
		}
	}
	nbrDesComptesTrouvesApresRecheche=insertingIndex;

}
void addToAccount(int accountId,float amount){
	comptes[accountId].sold+=amount;
}
void afficherMenuAffichage(){
	printf("\n1>Par Ordre Ascendant");
	printf("\n2>Par Ordre Descendant");
	printf("\n3>Par Ordre Ascendant (les comptes bancaires ayant un montant supérieur à un chiffre introduit)");
	printf("\n4>Par Ordre Descendant (les comptes bancaires ayant un montant supérieur à un chiffre introduit)");
	printf("\n5>Recherche par CIN");
	printf("\n6>Retour au menu principale");
	// on prend les comptes valabale on les met dans une table puis les trie par montant asendant
	struct Compte comptesDisponibleAtrier[open_accounts_count];
		for(int i=0;i<open_accounts_count;i++){
			comptesDisponibleAtrier[i]=comptes[i];
		};
		//FOR_TESTING
		printf("\ncompte existant %d cin du premier %s",open_accounts_count,comptesDisponibleAtrier[0].cin);
	
	MENU_AFFICHAGE_DEMANDER_CHOIX:
	printf("\nVotreChoix: ");
	lireOption();
	float nombreAFiltrerLesComptes;//to stored filter number intered by the user
	if(optionChoisis==1){//Par Ordre Ascendant
			trierLesComptesParSold(comptesDisponibleAtrier,open_accounts_count,0);
			afficherDesComptes(comptesDisponibleAtrier,open_accounts_count);
	}else if(optionChoisis==2){//Par Ordre Descendant
			trierLesComptesParSold(comptesDisponibleAtrier,open_accounts_count,1);
			afficherDesComptes(comptesDisponibleAtrier,open_accounts_count);
	} else if(optionChoisis==3){//Par Ordre Ascendant (les comptes bancaires ayant un montant supérieur à un chiffre introduit)
			nombreAFiltrerLesComptes=lireNombreAFIltrerLesComptes();
			trierLesComptesParSold(comptesDisponibleAtrier,open_accounts_count,0);
			int nbrsdesCoumptesSuperA=compterLesNombresSuperieurA(comptesDisponibleAtrier,open_accounts_count,nombreAFiltrerLesComptes);
			struct Compte comptesSuperieurA[nbrsdesCoumptesSuperA];
			retournerLeComptesAyantLeSoldSuperieurA(comptesDisponibleAtrier,open_accounts_count,comptesSuperieurA,nbrsdesCoumptesSuperA,nombreAFiltrerLesComptes);
			afficherDesComptes(comptesSuperieurA,nbrsdesCoumptesSuperA);
	}else if(optionChoisis==4){//Par Ordre Descendant (les comptes bancaires ayant un montant supérieur à un chiffre introduit
			nombreAFiltrerLesComptes=lireNombreAFIltrerLesComptes();
			trierLesComptesParSold(comptesDisponibleAtrier,open_accounts_count,1);
			int nbrsdesCoumptesSuperA=compterLesNombresSuperieurA(comptesDisponibleAtrier,open_accounts_count,nombreAFiltrerLesComptes);
			struct Compte comptesSuperieurA[nbrsdesCoumptesSuperA];
			retournerLeComptesAyantLeSoldSuperieurA(comptesDisponibleAtrier,open_accounts_count,comptesSuperieurA,nbrsdesCoumptesSuperA,nombreAFiltrerLesComptes);
			afficherDesComptes(comptesSuperieurA,nbrsdesCoumptesSuperA);
	}else if(optionChoisis==5){//Recherche par CIN
		printf("Entrez un Cin ");
		char cin[20];
		scanf("%s",cin);
		Compte comptesTrouves[MAX_ACCOUNST_NUMBER_PER_CIN];
		chercherComptesParCin(cin,comptesTrouves);
		afficherDesComptes(comptesTrouves,nbrDesComptesTrouvesApresRecheche);
	
	}else if(optionChoisis==6){//Retour au menu principale
			afficheLeMenuPricipale();
	}else{
		//si le choix entre est pas valide on recommence
		goto MENU_AFFICHAGE_DEMANDER_CHOIX;
	}
}
void retournerLeComptesAyantLeSoldSuperieurA(struct Compte comptesAUtliser[],int lengh,struct Compte tableARemplire[],int nombreDesComptesARemplir,float minSold){
	int indiceRemplissage=0;
	for(int i=0;i<lengh;i++){
		if(comptesAUtliser[i].sold>minSold){
			tableARemplire[indiceRemplissage]=comptesAUtliser[i];
			indiceRemplissage++;
			if(indiceRemplissage>nombreDesComptesARemplir)
			break;
		}

	}


}
int compterLesNombresSuperieurA(struct Compte comptesAUtliser[],int length,float soldMin){
	int count=0;
	for(int i=0;i<length;i++){
			if(comptesAUtliser[i].sold>soldMin)
				count++;
	}
	return count;
};
void afficherDesComptes(struct Compte comptesATraiter[],int length){
	/*
	on va d'abord afficher les comptes trouver puis  donner la possibilite de en choisir un puis l'afficher
	*/
	// printing a table contaning the accounts info and indices
	printf("\n--------------------------------------------------------------------------------------------");
	printf("\n#\t N compte\t\t Nom complet \t\t\t   Cin \t\t   Sold\t");
	printf("\n--------------------------------------------------------------------------------------------");
	for(int i=0;i<length;i++){
		printf("\n%i \t %i \t\t\t %-8s %-8s \t\t %-8s \t %.2f\t",
			i+1,comptesATraiter[i].id,comptesATraiter[i].nomProprietaire,comptesATraiter[i].prenomProprietaire,comptesATraiter[i].cin,comptesATraiter[i].sold);
	}
	printf("\n--------------------------------------------------------------------------------------------\n");
	// now lets take user input to chouse which user acount to work on
	MENU_AFFICHAGE_DEMANDER_CHOIX_DU_COMPTE:
	optionChoisis=-1;
	do{
		printf("\nentrez 0 pour revenir au menu principale");
		demmanderLechoix();
		lireOption();
	}while(optionChoisis<0 || optionChoisis>length);

	if(optionChoisis==0){
		afficheLeMenuPricipale();
	}else{
		afficherUnCompte(comptesATraiter[optionChoisis-1]);
		//pause the programm
		entrezqqChosePourOvrirMenuPrincipale();
	}
}
void afficherUnCompte(struct Compte compteAAfficher){
	printf("\n--------------------------------------------------------------------------------------------");
	printf("\n                      Affichage du compte N:#%d                         ",compteAAfficher.id);
	printf("\n--------------------------------------------------------------------------------------------");
	printf("\nNumero Du Compte:               %d",compteAAfficher.id);
	printf("\nNom Du Proprietaire:            %s",compteAAfficher.nomProprietaire);
	printf("\nPrenom Du Proprietaire:         %s",compteAAfficher.prenomProprietaire);
	printf("\nNumero De La Carte Nationale:   %s",compteAAfficher.cin);
	printf("\nMontant Disponible:             %f",compteAAfficher.sold);
	printf("\n--------------------------------------------------------------------------------------------");
}
void trierLesComptesParSold(struct Compte comptesATrier[],int length,int order){
	if(order==0)
		//asending order
	for(int j=length-2;j>=0;j--){
		for(int i=0;i<=j;i++){
			if(comptesATrier[i].sold>comptesATrier[i+1].sold){
				struct Compte temp=comptesATrier[i];
				comptesATrier[i]=comptesATrier[i+1];
				comptesATrier[i+1]=temp;
			}
		}
	}
	//descending order
	else
		for(int j=length-2;j>=0;j--){
		for(int i=0;i<=j;i++){
			if(comptesATrier[i].sold<comptesATrier[i+1].sold){
				struct Compte temp=comptesATrier[i];
				comptesATrier[i]=comptesATrier[i+1];
				comptesATrier[i+1]=temp;
			}
		}
	}
}
void demmanderLechoix(){
	printf("\nentrez le nombre correspondant a votre choix puis tapez entrer ");
}
void header(){
	printf("\n-------------------------Bonjour Dans La Bank Du Maroc------------------------------\n");
}
float lireNombreAFIltrerLesComptes(){
	printf("\nentrez le nombre pour filtrer les comptes (on va afficher just les comptes ayant un sold superieur a ce nombre) ");
	float filter;
	scanf("%f",&filter);
	return filter;
};
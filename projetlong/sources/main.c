#include "read_item.h"
#include "convertisseur.h"
#include "tools.h"
#include "calcul_arith.h"
#include <stdio.h>
#include <stdlib.h>


void print_accueil(){
puts("##################################################################");
puts("	  ________ ________   ___________ 	                 ");
puts("	 /  ___/  |  \\____ \\_/ __ \\_  __ \\				 ");
puts("	 \\___ \\|  |  /  |_> >  ___/|  | \\/				 ");
puts("	/____  >____/|   __/ \\___  >__|   							 ");
puts("	     \\/      |__|        \\/       					     ");
puts("              .__               .__          __  		     ");              
puts("  ____ _____  |  |   ____  __ __|  | _____ _/  |_  ___________ ");
puts("_/ ___\\\\__  \\ |  | _/ ___\\|  |  \\  | \\__  \\\\   __\\/  _ \\_  __ \\");
puts("\\  \\___ / __ \\|  |_\\  \\___|  |  /  |__/ __ \\|  | (  <_> )  | \\/");
puts(" \\___  >____  /____/\\___  >____/|____(____  /__|  \\____/|__|   ");
puts("     \\/     \\/          \\/                \\/                   ");
puts("##################################################################");
}

int main(){

	char car;
	int valeur;
	int codeRet;
	int erreur;
	int resultat;
	Linear_Struct ident;
	Linear_Struct expr;
	
	// Pour faire joli
	print_accueil();
  
 	while(1){
 	
	 	ident = creer();
	 	expr = creer();
	 	
	 	// Lis des caracteres jusqu'a ce que l'utilisateur ait termine sa saisie
		puts("\nMerci de bien vouloir saisir une expression :");
	 	do{
	 		// On lis un item
	 		codeRet = read_item(&car,&valeur);
	 		
	 		// On traite l'item
	 		erreur = creer_pile_expr(valeur, car, codeRet, &expr);
	
		// On stop a la fin de l'expression, ou si une erreur est survenue
	 	}while(codeRet!=0 && erreur==CDE_ERREUR_00);
		// On vide le buffer
	 	while(codeRet!=0) codeRet = read_item(&car,&valeur);

		// Si aucune erreur ne s'est produite
	 	if(erreur==CDE_ERREUR_00) {

			erreur = conversion(&expr, &ident);	
			if(erreur==CDE_ERREUR_00) erreur = calcul_arith(expr, ident, &resultat);
		}
		
		// Si une erreur s'est produite
		if(erreur!=CDE_ERREUR_00) {
			// Si l'erreur n'a pas ete indiquee en interne par le module
			if(!AFFICHAGE_MESSAGES){
		 		puts("Attention, une erreur c'est produite");
		 		printf("Numero de l'erreur : %d\n", erreur);
			}
	 	}
	 	else printf("Resultat : %d\n", resultat);
 	}
 	
	return 0;
}

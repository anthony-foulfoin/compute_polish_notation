#include "tools.h"
#include "elem.h"
#include <stdlib.h>
#include <stdio.h>

/* Procédure 'remplacer_ident':                                  
 * permet de remplacer les identificateurs de l'expression contenue dans la pile expr par une valeur
 * entiere saisie par l'utilisateur.
 * 
 * Paramètres:                                             
 * (in) 'ident'		: pile contenant la liste des identificateurs presents dans l'expression
 * (in/out) 'expr'	: pile contenant l'expression polonaise pour laquelle on souhaite remplacer les identificateurs par leur
 * 					valeur entiere.
 *
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur remplacer_ident(Linear_Struct ident, Linear_Struct *expr){
	
	Elem elementIdent=NULL;	// Variable permettant de stocker un element de la pile ident
	Elem elementExpr=NULL; // Variable permettant de stocker un element de la pile expr

	Code_retour codeIdent;	// Variable permettant d'indiquer si la pile ident est vide
	Code_Erreur code_erreur = CDE_ERREUR_00;	// Code retourne par la fonction
	int valeur;	// Variable permettant de stocker les valeurs entieres saisies par l'utilisateur

	// On obtient un identificateur
	codeIdent = depiler(&ident, (ELT) &elementIdent);

	// Tant que l'on n'a pas traite tous les identificateurs
	while(codeIdent!=KO){
		
		// On demande a l'utilisateur de saisir la valeur correspondant a l'identificateur en cours
		printf("%s%c\n",MESSAGE_ENTIER, getChar(elementIdent));
		valeur = getInEntier();
		// On parcourt expr pour rechercher l'identificateur en cours
		// On obtient un element qui contient cet identificateur
		elementExpr = chercher(*expr, elementIdent, comparer_char);
		while(elementExpr!=NULL){	

			// On a trouve un identificateur
			// On le remplace par sa valeur entiere
			setInt(elementExpr, valeur);
			setChar(elementExpr, NUM);

			// On passe a l'element suivant
			elementExpr = chercher(*expr, elementIdent, comparer_char);
		}
		// On libere la memoire utilisee par l'identificateur
		free(elementIdent);
		// Puis on passe a l'identificateur suivant
		codeIdent = depiler(&ident, (ELT) &elementIdent);
	}
	return code_erreur;
}

/* Procédure 'calculer':                                  
 * permet d'appliquer l'operateur passe en parametre sur les 2 premieres operandes de la pile.
 * Le resultat est empile au sommet de la pile.
 * 
 * Paramètres:                                             
 * (in/out) 'calcul': pile contenant les operandes sur lesquelles appliquer les operateurs
 * (in) 'char'		: operateur a appliquer sur les 2 operandes
 *
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur calculer(Linear_Struct *calcul, char operateur){
	
	int *op1 = NULL;	// Premiere operande
	int *op2 = NULL;	// Seconde operande
	int *resultat = NULL; // Resultat du calcul
	Code_Erreur code_erreur = CDE_ERREUR_00;
	Code_retour code_ret = OK;

	resultat = (int *) malloc(sizeof(int));

	// On verifie si l'allocation a reussie
	if(resultat != NULL){

		// On verifie que les parametres sont correctes
		if(calcul!=NULL){
	
			// On obtient la premiere operande
			depiler(calcul, (ELT *) &op1);
			
			// On obtient la seconde operande
			depiler(calcul, (ELT *) &op2);
			
			// On verifie que les 2 operandes sont non nulles
			if(op1 != NULL && op2 != NULL){
			
				switch(operateur){
					case '+' : *resultat= (*op1) + (*op2);
								break;
					case '-' : *resultat= (*op2) - (*op1);
								break;
					case '*' : *resultat= (*op1) * (*op2);
								break;
					case '/' : 	// On s'assure de ne pas faire de division par 0
								if(*op1==0){
									code_erreur = CDE_ERREUR_10;
									afficher_message(MSG_ERREUR_10);
								} else *resultat= (*op2) / (*op1);
								break;
					default	 : 	code_erreur = CDE_ERREUR_08;
								afficher_message(MSG_ERREUR_08);
								break;
				}
				// S'il n'y a pas eu d'erreur
				if(code_erreur == CDE_ERREUR_00){ 
					code_ret = empiler(calcul,resultat);
					if(code_ret == KO){			
						code_erreur = CDE_ERREUR_09;
						afficher_message(MSG_ERREUR_09);
					}
				}
			}
			else{
				code_erreur = CDE_ERREUR_07;
				afficher_message(MSG_ERREUR_07);	
			}
		}
		else{
			code_erreur = CDE_ERREUR_01;
			afficher_message(MSG_ERREUR_01);		
		}
	}
	else{
		code_erreur = CDE_ERREUR_06;
		afficher_message(MSG_ERREUR_06);
	}
	return code_erreur;
}

/* Procédure 'print_elem_int':                                  
 * permet d'afficher un element pour une pile contenant des elements de type int
 * 
 * Paramètres:                                             
 * (in) 'i'		: element a afficher
 * Résultat:                                               
 * void
 */ 
void print_elem_int(ELT i){

	int *val = (int *) i;
	printf("%d ",*((int *) val));
}

/* Procédure 'calcul_arith':                                  
 * permet d'evaluer une expression arithmetique representee en notation polonaise postfixee
 * 
 * Paramètres:                                             
 * (in) 'expr'		: l'expression arithmetique en notation polonaise a evaluer
 * (in) 'ident'		: pile contenant la liste de tous les identificateurs presents dans l'expression a evaluer
 * (out) 'result'	: variable destinee a recevoir le resultat du calcul
 * 
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur calcul_arith(Linear_Struct expr, Linear_Struct ident, int *result){
	
	Linear_Struct calcul = creer(); // Pile temporaire servant a stocker les elements depiles de la pile expr
	Elem element = NULL;	// Variable permettant de stocker les elements depiles de la pile expr
	Code_retour code;	// Variable permettant d'indiquer si expr est vide ou non
	Code_Erreur code_erreur = CDE_ERREUR_00;	// code retourne par la fonction
	int *val = NULL;
	int *res = NULL;
	
	// On verifie si les parametres sont correctes
	if(result!=NULL){
	
		// On parcours la pile des identificateurs, et on les remplace par leur valeur dans la pile expr
		remplacer_ident(ident, &expr);
	
		// On depile un item de l'expression
		code = depiler(&expr, (void *) &element);
		
		// Tant que toute la pile expr n'a pas ete parcourue et qu'il n'y a pas d'erreur
		while(code!=KO && code_erreur==CDE_ERREUR_00){
				
			// S'il s'agit d'un entier
			// On "transvase" l'element dans la pile temporaire
			if(getChar(element)==NUM){
				val = (int *) malloc(sizeof(int));
				// On verifie si l'allocation a reussie
				if(val !=NULL){
					*val = getInt(element);
					code = empiler(&calcul, val);
					
					if(code == KO){			
						code_erreur = CDE_ERREUR_09;
						afficher_message(MSG_ERREUR_09);
					}
				}
				else{
					code_erreur = CDE_ERREUR_06;
					afficher_message(MSG_ERREUR_06);
				}
			}
			// s'il s'agit d'un operateur, on effectue alors le calcul
			else {
				code_erreur = calculer(&calcul, getChar(element));
			}
			// On libere la memoire
			free(element);
			// On passe a l'element suivant
			code = depiler(&expr, (void *) &element);
		}
		// S'il n'y a eu aucune erreur, on peut poursuivre
		if(code_erreur == CDE_ERREUR_00){
			// Le resultat se trouve au fond de la pile temporaire	
			code = depiler(&calcul, (ELT *) &res);
			if(code==OK){
				*result = *res;
			}
			else{
				code_erreur = CDE_ERREUR_09;
				afficher_message(MSG_ERREUR_09);
			}
		}
	}
	else{
		code_erreur = CDE_ERREUR_01;
		afficher_message(MSG_ERREUR_01);
	}
	return code_erreur;
}
#include "tools.h"
#include "elem.h"
#include <stdio.h>
#include <stdlib.h>

/* Procédure 'getInEntier':                                  
 * permet d'obtenir un entier de la part de l'utilisateur via l'entree par defaut
 *
 * Résultat:                                               
 * l'entier saisi par l'utilisateur
 */ 
int getInEntier(){ 
	int nb;
	int n;
	do{	
		nb=scanf("%d",&n);
		while(getchar()!='\n');
		if(nb!=1) puts(MESSAGE_ENTIER_ERREUR);
	}while(nb!=1);
	return n;
}

/* Procédure 'transferer':                                  
 * permet de transferer le contenu de la pile1 dans la pile2
 *
 * Paramètres:                                     
 * (in/out) 'pile1': pile dont on souhaite transferer les elements dans pile2
 * (in/out) 'pile2': pile qui doit recevoir les nouveaux elements       
 * 
 * 
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur transferer(Linear_Struct *pile1, Linear_Struct *pile2){
	
	// On transfere le contenu de la pile 1 dans la pile 2
	ELT element=NULL;
	Code_retour code = depiler(pile1, &element);
	Code_Erreur code_erreur = CDE_ERREUR_00;
	
	if(pile1 != NULL && pile2!=NULL){
	
		// On "transvase" la pile 1 dans la pile 2 jusqu'à la fin de la pile 1
		while(code!=KO){
			code = empiler(pile2, element);
			if(code==OK) code = depiler(pile1, &element);
		}
	}
	else{
		code_erreur = CDE_ERREUR_01;
		afficher_message(MSG_ERREUR_01);
	}
	return code_erreur;
}

/* Procédure 'creer_pile_expr':                                  
 * permet de crrer une pile modelisant une expression arithmetique sous forme infixe
 * 
 * Paramètres:  
 * (in)  	'valChar' 	: contient l'item a traiter si celui-ci est de type char
 * (in)  	'valInt'	: contient l'item a traiter si celui-ci est de type int                         
 * (in)  	'codeRet'	: code retourne par la fonction read_item indiquant ce que represente l'item traite                                    
 * (in/out) 'expr'		: pile contenant l'expression infixe a la fin du traitement. Une pile vide doit 
 * 						etre fournie lors du premier appel de la fonction, cette meme pile devant ensuite etre fournie pour
 * 						chaque nouvel item de l'expression traite.
 * 
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur creer_pile_expr(int valInt, char valChar, enum type_item codeRet, Linear_Struct *expr){
	
	int code_erreur = CDE_ERREUR_00;
	Code_retour code = OK;
	Elem elem; // item insere dans la pile expr
	Linear_Struct tmp = creer();

	// Si on doit traiter un entier
	if(codeRet==entier){
		// On cree un nouvel Elem qui contient l'entier et on le stock dans la pile expr
		elem = creerElem();
		setInt(elem, valInt);
		setChar(elem, NUM);
		code = empiler(expr, elem);
		if(code == KO) {
			code_erreur = CDE_ERREUR_09;
			afficher_message(MSG_ERREUR_09);
		}
	}
	// Si on doit traiter une erreur
	else if(codeRet==error){
		code_erreur = CDE_ERREUR_14;
		afficher_message(MSG_ERREUR_14);	
	}
	else if(codeRet==eol){
		if(tester_vide(*expr)==OK){
			code_erreur = CDE_ERREUR_15;
			afficher_message(MSG_ERREUR_15);
		}
		// On inverse la pile pour avoir l'expression dans le bon sens
		else {
			code_erreur = transferer(expr,&tmp);
			free(*expr);
			*expr = tmp;
		}
	}
	else {
		// On cree un nouvel Elem qui contient le caractere et on le stock dans la pile expr
		elem = creerElem();
		setChar(elem, valChar);
		code = empiler(expr, elem);
		if(code == KO) {
			code_erreur = CDE_ERREUR_09;
			afficher_message(MSG_ERREUR_09);
		}
	}
	return code_erreur;
}
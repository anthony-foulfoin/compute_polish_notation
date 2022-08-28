#include "convertisseur.h"
#include "elem.h"
#include "tools.h"
#include <stdlib.h>
#include <stdio.h>

/* Procédure 'ajouter_elem':                                  
 * permet d'ajouter un element de type int ou char a une pile contenant des elements de type Elem
 * 
 * Paramètres:                                             
 * (in/out) 'pile'	: pile a laquelle on souhaite ajouter un element
 * (in) 'valInt'	: entier a ajouter a la pile
 * (in) 'valChar'	: caractere a ajouter a la pile. Si on souhaite ajouter un entier a la pile (valInt), valChar doit etre fixe avec
 * 					la valeur '\0', sinon valChar est pris par defaut.
 *
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur ajouter_elem(Linear_Struct *pile, int valInt, char valChar){

	Code_Erreur code_erreur = CDE_ERREUR_00; // code retourne par la fonction
	Code_retour code_ret = OK;

	// On verifie si les parametres sont correctes
	if(pile!=NULL){
		
		// On cree un nouvel element de type Elem
		Elem val = creerElem();
		
		// Si l'allocation a reussie
		if(val!=NULL){
			
			// On fixe les valeurs de l'element
			setInt(val, valInt);
			setChar(val, valChar);
		
			// Puis on empile l'element
			code_ret = empiler(pile,val);
			
			// Si l'empilement a echoue
			if(code_ret==KO){
				code_erreur = CDE_ERREUR_09;
				afficher_message(MSG_ERREUR_09);
			}
		}
		// Si l'allocation a echouee
		else{
			// Erreur
			code_erreur = CDE_ERREUR_06;
			afficher_message(MSG_ERREUR_06);	
		}
	}
	else{
		code_erreur = CDE_ERREUR_01;
		afficher_message(MSG_ERREUR_01);	
	}
	
	return code_erreur;
}

/* Procédure 'ajouter_ident':                                  
 * permet d'ajouter un identificateur a la liste des identificateurs
 * 
 * Paramètres:                                             
 * (in/out) 'pile1'		: pile temporaire contenant certains items de l'expression a traiter.
 * (in/out) 'pile2'		: pile contenant l'expression polonaise a la fin de la conversion.
 * (in)		'ident'		: l'operateur qui provoque le depilement
 * 
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur ajouter_ident(Linear_Struct *ident, char i){
	Code_Erreur code_erreur = CDE_ERREUR_00; 	// Code retourne par la fonction
	Code_retour code_ret = OK;
	ELT ret;				// Element retourne par la fonction de recherche
	char *val;				// Valeur a stocker dans la pile des identificateurs
	
	// On verifie si les parametres sont correctes
	if(ident!=NULL){
		// on cree un char *
		val = (char *) malloc(sizeof(char));
		
		// Si l'allocation a reussi
		if(val!=NULL){
			
			// On precise la valeur du char *
			*val = i;
			
			// On verifie si la valeur n'est pas deja presente dans la pile
			ret = chercher(*ident,val,comparer_char);
			
			// Si l'element n'est pas deja present dans la liste des identificateurs
			if(ret==NULL) {
				code_ret = empiler(ident,val);
				// Si l'empilement a echoue
				if(code_ret == KO) {
					code_erreur = CDE_ERREUR_09;
					afficher_message(MSG_ERREUR_09);
				}
			}
		}
		// Si echec de l'allocation
		else{
			code_erreur = CDE_ERREUR_06;
			afficher_message(MSG_ERREUR_06);	
		}
	}else{
		code_erreur = CDE_ERREUR_01;
		afficher_message(MSG_ERREUR_01);	
	}
	return code_erreur;
}

/* Procédure 'depiler_op':                                  
 * permet de gerer le depilement de la pile temporaire lorsque l'on rencontre un operateur (ou une parenthese fermante) 
 * 
 * Paramètres:                                             
 * (in/out) 'pile1'		: pile temporaire contenant certains items de l'expression a traiter.
 * (in/out) 'pile2'		: pile contenant l'expression polonaise a la fin de la conversion.
 * (in)		'ident'		: l'operateur qui provoque le depilement
 * 
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur depiler_op(Linear_Struct *pile1,Linear_Struct *pile2, char op){
	
	Elem element;
	Code_retour code = sommet(*pile1, (ELT) &element);
	Code_Erreur code_erreur = CDE_ERREUR_00;
	
	if(pile1!=NULL && pile2 != NULL){
		// On "transvase" la pile 1 dans la pile 2 jusqu'à la rencontre d'un operateur de priorite inferieure
		switch (op){
			case '+':
			case '-':	// Tant que la pile n'est pas vide ou que l'on ne rencontre pas de parenthese ouvrante
						while(code!=KO && getChar(element)!='('){
							// On depile un element de pile1
							code = depiler(pile1, (ELT) &element);
							// On l'empile dans pile2
							if(code == OK) code = empiler(pile2, element);
							
							// Si une erreur c'est produite pendant l'empilement ou le depilement
							if(code == KO){			
								code_erreur = CDE_ERREUR_09;
								afficher_message(MSG_ERREUR_09);
							}
							// On consulte l'element suivant poiur verifier s'il s'agit d'une parenthese
							else code = sommet(*pile1, (ELT) &element);
						}
						break;
			case '*':
			case '/':	// Tant que la pile n'est pas vide ou que l'on ne rencontre pas de parenthese ouvrante ou d'operateurs
						// de priorite inferieure
						while(code!=KO && getChar(element)!='(' && getChar(element)!='+' && getChar(element)!='-'){
							// On depile un element de pile1
							code = depiler(pile1, (ELT) &element);
							// On l'empile dans pile2
							if(code == OK) code = empiler(pile2, element);
							
							// Si une erreur c'est produite pendant l'empilement ou le depilement
							if(code == KO){
								code_erreur = CDE_ERREUR_09;
								afficher_message(MSG_ERREUR_09);
							}
							// On consulte l'element suivant poiur verifier s'il s'agit d'une parenthese
							else code = sommet(*pile1, (ELT) &element);
						} 
						break;
			case ')':	// Tant que la pile n'est pas vide ou que l'on ne rencontre pas de parenthese ouvrante
						while(code!=KO && getChar(element)!='('){
							// On depile un element de pile1
							code = depiler(pile1, (ELT) &element);
							// On l'empile dans pile2
							if(code == OK) code = empiler(pile2, element);
							
							// Si une erreur c'est produite pendant l'empilement ou le depilement
							if(code == KO){
								code_erreur = CDE_ERREUR_09;
								afficher_message(MSG_ERREUR_09);
							}
							// On consulte l'element suivant poiur verifier s'il s'agit d'une parenthese
							else code = sommet(*pile1, (ELT) &element);
						}
						// Si la parenthese a ete trouvee
						if(code!=KO){
							// On depile la parenthese
							code = depiler(pile1, (ELT) &element);
							
							// On libere la memoire utilisee par la parenthese
							free(element);
							
							// Si une erreur c'est produite pendant le depilement
							if(code == KO){
								code_erreur = CDE_ERREUR_09;
								afficher_message(MSG_ERREUR_09);
							}
						}
						// Sinon probleme de parenthesage
						else{
							code_erreur = CDE_ERREUR_02;
							afficher_message(MSG_ERREUR_02);
						}
		}
	}else{
		code_erreur = CDE_ERREUR_01;
		afficher_message(MSG_ERREUR_01);	
	}
	
	return code_erreur;
}

/* Procédure 'traiterItemCar':                                  
 * permet de traiter un item de type caractere  
 * 
 * Paramètres:                                             
 * (in)  	'element' 	: contient l'item a traiter               
 * (in/out) 'pile1'		: pile temporaire contenant certains items de l'expression a traiter.
 * (in/out) 'pile2'		: pile contenant l'expression polonaise a la fin de la conversion.
 * (in/out) 'identif'	: pile contenant la liste de tous les identificateurs de l'expression. 
 * 
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur traiterItemCar(Elem element, Linear_Struct *pile1, Linear_Struct *pile2, Linear_Struct *identif){
	
	Code_Erreur code_erreur = CDE_ERREUR_00; // Code retourne par la fonction
	int valChar;
	
	// On verifie si les parametres sont correctes
	if(pile1!=NULL && pile2 != NULL && identif != NULL && element!= NULL){	
		valChar = getChar(element);
		// S'il s'agit d'un identificateur
		if(estIdentificateur(element)) {
			// On l'empile directement dans la pile 2
			code_erreur = ajouter_elem(pile2, 0, valChar);
			// On l'ajoute a la liste des identificateurs
			code_erreur = ajouter_ident(identif,valChar);
		}
		// S'il s'agit d'un operateur
		else if(estOperateur(element)){					
			// Pour tous les autres operateurs, on appelle une fonction qui gere le depilement
			code_erreur = depiler_op(pile1, pile2, valChar);
			// Puis on empile l'operateur
			if(code_erreur==CDE_ERREUR_00) code_erreur = ajouter_elem(pile1,0,valChar);
		}
		else if(getChar(element)=='('){
			// Dans le cas d'une parenthese ouvrante, on l'empile directement dans la pile1
			code_erreur = ajouter_elem(pile1,0,valChar);
		}
		else if(getChar(element)==')'){
			// Dans le cas d'une parenthese fermante, on appelle une fonction qui gere le depilement
			code_erreur = depiler_op(pile1,pile2, valChar);
		}
		// Dans tous les autres cas, il y a une erreur
		else {
			code_erreur = CDE_ERREUR_03;
		 	afficher_message(MSG_ERREUR_03);
		}
	}else{
		code_erreur = CDE_ERREUR_01; 
		afficher_message(MSG_ERREUR_01);	
	}
	
	return code_erreur;
}

/* Procédure 'verif_syntaxe':                    
 * permet de verifier la syntaxe d'une expression artihmetique sous forme infixe.
 *      
 * Paramètres:                                             
 * (in) 'expr'	: pile contenant l'expression infixe a verifier
 * 
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur verif_syntaxe(Linear_Struct expr){
	
	Code_Erreur code_erreur = CDE_ERREUR_00;	// Code retournee par la fonction
	
	Linear_Struct tmp; // Pile temporaire servant a sauvegarder les elements de l'expression
	Elem precedent = NULL;
	Elem courant = NULL;
	Elem suivant = NULL;
	
	// Si la pile est vide on ne fait rien
	if(tester_vide(expr)==KO){
	
		tmp = creer();
		
		// On depile un element
		depiler(&expr, (ELT) &courant);
		// On l'empile dans tmp pour le sauvegarder
		empiler(&tmp, courant);
		
		// On depile un second element
		depiler(&expr, (ELT) &suivant);
		// On l'empile dans tmp pour le sauvegarder
		if(suivant != NULL) empiler(&tmp, suivant);

		do{
			// Si l'element courant est un operateur
			if(estOperateur(courant)){
				
				// S'il s'agit du premier element de l'expression
				if(precedent == NULL){
					// Il y a une erreur
					code_erreur = CDE_ERREUR_11;
					afficher_message(MSG_ERREUR_11);	
				}
				// S'il s'agit du dernier element de l'expression
				else if(suivant==NULL){
					// Il y a une erreur
					code_erreur = CDE_ERREUR_12;
					afficher_message(MSG_ERREUR_12);	
				}
				else{
					// Sinon l'operateur doit etre suivi d'un entier ou parenthese ouvrante
					if(getChar(suivant)!=NUM && !(estIdentificateur(suivant))){
						
						// Cela doit imperativement etre une parenthese ouvrante
						if(getChar(suivant)!='('){
							code_erreur = CDE_ERREUR_13;
							afficher_message(MSG_ERREUR_13);	
						}
					}
					
					// Il doit etre precede d'une parenthese fermante ou d'un entier
					if((code_erreur==CDE_ERREUR_00) && getChar(precedent)!=NUM && !(estIdentificateur(precedent))){
						
						// Cela doit imperativement etre une parenthese fermante
						if(getChar(precedent)!=')'){
							code_erreur = CDE_ERREUR_13;
							afficher_message(MSG_ERREUR_13);	
						}
					}
				}		
			}
			// Si l'element courant est une parenthese ouvrante
			else if(getChar(courant)=='('){	
				// S'il s'agit du dernier element de l'expression
				if(suivant==NULL){
					// Erreur
					code_erreur = CDE_ERREUR_02;
					afficher_message(MSG_ERREUR_02);
				}
				// S'il s'agit du premier element de l'expression
				else if(precedent == NULL){
					
					// Alors l'element suivant doit etre soit un entier, soit une parenthese ouvrante
					if(getChar(suivant)!=NUM && !(estIdentificateur(suivant))){
						// Cela doit imperativement etre une parenthese ouvrante
						if(getChar(suivant)!='('){
							code_erreur = CDE_ERREUR_02;
							afficher_message(MSG_ERREUR_02);	
						}
					}
				}
				else{
					// Alors l'element suivant doit etre soit un entier, soit une parenthese ouvrante
					if(getChar(suivant)!=NUM && !(estIdentificateur(suivant))){
						// Cela doit imperativement etre une parenthese ouvrante
						if(getChar(suivant)!='('){
							code_erreur = CDE_ERREUR_02;
							afficher_message(MSG_ERREUR_02);	
						}
						
					}
					// L'element precedent est soit un operateur, soit une parenthese ouvrante
					if((code_erreur==CDE_ERREUR_00) && !(estOperateur(precedent)) && !(getChar(precedent)=='(')){
						code_erreur = CDE_ERREUR_02;
						afficher_message(MSG_ERREUR_02);	
					}
				}
			}
			// Si l'element courant est une parenthese fermante
			else if(getChar(courant)==')'){
				// S'il s'agit du premier element de l'expression
				if(precedent == NULL){
					code_erreur = CDE_ERREUR_02;
					afficher_message(MSG_ERREUR_02);	
				}
				// S'il s'agit du dernier element de l'expression
				else if(suivant==NULL){
					// L'element precedent est soit un un nombre, soit une parenthese fermante
					if(!((getChar(precedent)==NUM) || estIdentificateur(precedent)) && !(getChar(precedent)==')')){
						code_erreur = CDE_ERREUR_02;
						afficher_message(MSG_ERREUR_02);	
					}
				}
				else{
					// L'element precedent est soit un un nombre, soit une parenthese fermante
					if(!((getChar(precedent)==NUM) || estIdentificateur(precedent)) && !(getChar(precedent)==')')){
						code_erreur = CDE_ERREUR_02;
						afficher_message(MSG_ERREUR_02);	
					}
					// L'element suivant est soit un operateur, soit une parenthese fermante
					if((code_erreur==CDE_ERREUR_00) && !(estOperateur(suivant)) && !(getChar(suivant)==')')){
						code_erreur = CDE_ERREUR_02;
						afficher_message(MSG_ERREUR_02);	
					}
				}
			}
			// S'il s'agit d'un nombre
			else if(estIdentificateur(courant) || getChar(courant)==NUM){
				
				if(suivant!=NULL){
					// L'element suivant ne doit pas etre un nombre
					if((getChar(suivant)==NUM) || estIdentificateur(suivant)){
						code_erreur = CDE_ERREUR_13;
						afficher_message(MSG_ERREUR_13);	
					}
				}
				
				if((code_erreur==CDE_ERREUR_00) && precedent != NULL){
					// L'element suivant ne doit pas etre un nombre
					if((getChar(precedent)==NUM) || estIdentificateur(precedent)){
						code_erreur = CDE_ERREUR_13;
						afficher_message(MSG_ERREUR_13);	
					}
				}
			}
			
			// On traite l'item suivant
			precedent = courant;
			courant = suivant;
			suivant = NULL;
			
			// On depile un nouvel element
			depiler(&expr, (ELT) &suivant);
			// On l'empile dans tmp pour le sauvegarder
			if(suivant != NULL) empiler(&tmp, suivant);
			
		}while(courant!=NULL && code_erreur==CDE_ERREUR_00);
		
		// On inverse la pile
		if(code_erreur == CDE_ERREUR_00) {
			code_erreur = transferer(&tmp,&expr);
			free(tmp);
		}
	}
	return code_erreur;
}

/* Procédure 'fin':  
 *                                 
 * permet de traiter les 2 piles utilisees pour la conversion lorsque tous les items de l'expression ont ete lus.
 * Elle transfert nottemment le contenu de la pile temporaire dans la pile contenant le resultat, et verifie si
 * des parenthèses non depilees figurent dans la pile temporaire. Cette procedure permet egalement d'inverser la pile
 * de resultat afin d'obtenir l'expression polonaise "dans le bon sens"    
 *      
 * Paramètres:                                             
 * (in/out) 'pile1'		: pile temporaire contenant certains items de l'expression a traiter.
 * (in/out) 'pile2'		: pile contenant l'expression polonaise a la fin de la conversion.
 * 
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur fin(Linear_Struct *pile1,Linear_Struct *pile2){
	
	Elem element=NULL; 	// Element depile de la pile 1
	Code_retour code;	// Code permettant de savoir lorsque la pile1 a ete entierement depilee
	Code_Erreur code_erreur = CDE_ERREUR_00;	// Code retournee par la fonction
	Linear_Struct tmp = creer();
	
	// On verifie si les parametres sont correctes
	if(pile1!=NULL && pile2 != NULL){
		
		// On depile un element de la pile1
		code = depiler(pile1, (ELT) &element);
		
		// On "transvase" la pile 1 dans la pile 2 jusqu'à la rencontre d'une parenthèse ouvrante
		while(code!=KO && code_erreur!=CDE_ERREUR_02){
			// On verifie s'il y a des parentheses ouvrantes restantes dans la pile
			if(getChar(element)=='('){
				// Erreur
				code_erreur=CDE_ERREUR_02;
				afficher_message(MSG_ERREUR_02);
			}
			else{
				// Ok, on transfert
				code = empiler(pile2, element);
				
				// Si une erreur c'est produite pendant l'empilement
				if(code == KO){
					code_erreur = CDE_ERREUR_09;
					afficher_message(MSG_ERREUR_09);
				}
				// On depile l'element suivant
				else code = depiler(pile1, (ELT) &element);
			}
		}
		
		// On inverse la pile pour avoir l'expression dans le bon sens
		// Si aucune erreur ne s'est produite
		if(code_erreur==CDE_ERREUR_00) {
			code_erreur = transferer(pile2,&tmp);
			free(*pile2);
			*pile2 = tmp;
		}
		
	}else{
		code_erreur = CDE_ERREUR_01; 
		afficher_message(MSG_ERREUR_01);
	}
	
	return code_erreur;
}

/* Procédure 'conversion':                                  
 * traite un item de l'expression a convertir   
 *          
 * Paramètres:                                             
 * (in/out) 'expr'		: pile contenant l'expression polonaise a la fin de la conversion. C'est egalement cette pile qui
 * 						fournie l'expression infixe a convertir.
 * (in/out) 'ident'		: pile contenant la liste de tous les identificateurs de l'expression. Une pile vide doit 
 * 						etre fournie lors de l'appel de la fonction.
 * 
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */                                         
Code_Erreur conversion(Linear_Struct *expr, Linear_Struct *ident){
	 	int code_erreur = CDE_ERREUR_00;
	 	Linear_Struct pile1; // pile temporaire
	 	Linear_Struct pile2; // pile temporaire contenant l'expression polonaise a la fin de la conversion
	 	Elem element;
	 	Code_retour code = KO; 
	 	
	 	// On verifie si les parametres sont correctes
	 	if(expr!=NULL && ident != NULL){	
	 		
	 		// On verifie si l'expression est syntaxiquement correcte
	 		code_erreur = verif_syntaxe(*expr);
	 		pile1 = creer();
	 		pile2 = creer();

			// Pour chaque element de l'expression
	 		while(tester_vide(*expr)==KO && code_erreur==CDE_ERREUR_00){
	 			code = depiler(expr, (ELT) &element);
	 			if(code != KO){
	 				// Si on doit traiter un entier
	 				if(getChar(element)==NUM) code_erreur = ajouter_elem(&pile2, getInt(element), NUM);
	 				// Si on doit traiter un caractere
	 				else code_erreur=traiterItemCar(element, &pile1, &pile2, ident);
	 			}
	 			
	 		}
	 		// Lorsque toute l'expression a ete traitee
	 		if(code_erreur==CDE_ERREUR_00) {
	 			code_erreur = fin(&pile1,&pile2);
	 			// L'expression polonaise se trouve dans pile2.
	 			*expr = pile2;	
	 		}
	 	}
	 	else{
	 		code_erreur = CDE_ERREUR_01;
	 		afficher_message(MSG_ERREUR_01);	
	 	}
		return code_erreur;
}


	
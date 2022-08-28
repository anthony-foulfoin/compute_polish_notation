#include "elem.h"
#include <stdio.h>
#include <stdlib.h>

struct _elem{
	char valChar;
	int valInt;
};

/* Procédure 'creerElem':                                  
 * permet de creer uen nouvelle structure de type Elem
 * 
 * Paramètres:                                             
 * (in) 'e'		: la structure dont on souhaite obtenir la valeur de type char
 *
 * Résultat:                                               
 * valeur de type char de la structure
 */ 
Elem creerElem(){
	
	return (Elem) malloc(sizeof(struct _elem));
	
}

/* Procédure 'getChar':                                  
 * permet d'obtenir l'attribut de type char d'un Elem
 * 
 * Paramètres:                                             
 * (in) 'e'		: la structure dont on souhaite obtenir la valeur de type char
 *
 * Résultat:                                               
 * valeur de type char de la structure
 */ 
char getChar(Elem e){
	
	return e->valChar;
		
}

/* Procédure 'getInt':                                  
 * permet d'obtenir l'attribut de type entier d'un Elem
 * 
 * Paramètres:                                             
 * (in) 'e'		: la structure dont on souhaite obtenir la valeur entiere
 *
 * Résultat:                                               
 * valeur entiere de la structure
 */ 
int getInt(Elem e){
	
	return e->valInt;
	
}

/* Procédure 'setInt':                                  
 * permet de fixer la valeur de type entier d'un Elem
 * 
 * Paramètres:                                             
 * (in) 'e'		: la structure dont on souhaite fixer la valeur entiere
 * (in) 'i'		: valeur entiere destinee a renseigner l'attribut entier de la structure
 *
 * Résultat:                                               
 * void
 */ 
void setInt(Elem e, int i){

	e->valInt = i;
		
}

/* Procédure 'setChar':                                  
 * permet de fixer la valeur de type char d'un Elem
 * 
 * Paramètres:                                             
 * (in) 'e'		: la structure dont on souhaite fixer la valeur entiere
 * (in) 'i'		: valeur de type char destinee a renseigner l'attribut de type char de la structure
 *
 * Résultat:                                               
 * void
 */ 
void setChar(Elem e, char i){

	e->valChar = i;
		
}

/* Procédure 'print_elem':                                  
 * permet d'afficher le contenu d'une structure de type Elem
 * 
 * Paramètres:                                             
 * (in) 'i'		: la structure dont on souhaite afficher le contenu
 *
 * Résultat:                                               
 * void
 */ 
void print_elem(ELT i){

	Elem val = (Elem) i;

	// S'il s'agit d'un entier
	if(val->valChar==NUM){
		printf("%d",val->valInt);
	}
	// S'il s'agit d'un caractere
	else printf("%c",val->valChar);
	
}

/* Procédure 'comparer_char':                                  
 * permet de comparer un element de type Elem d'une pile avec un caractere
 * 
 * Paramètres:                                             
 * (in) 'elem1'		: l'element de type Elem en provenance de la pile
 * (in) 'car'		: l'element de type char * dont on recherche une occurence dans la pile
 *
 * Résultat:                                               
 * - OK si l'element se trouve dans la pile                         
 * - KO sinon 
 */ 
Code_retour comparer_char(ELT elem, ELT car){
	
	// S'il s'agit d'un entier, les elements ne sont pas egaux
	if(getChar(elem) == NUM) return KO;
	
	// S'il s'agit d'un char, on verifie si les elements sont egaux
	else if (getChar(elem)==*(char *) car) return OK;
	
	else return KO;
	
}

/* Procédure 'estOperateur':                                  
 * permet de savoir si elem represente un operateur
 * 
 * Paramètres:                                             
 * (in) 'e'		: element dont on souhaite connaitre ce qu'il represente
 *
 * Résultat:                                               
 * - 1 si e est un operateur
 * - 0 sinon
 */ 
int estOperateur(Elem e){
	
	int result = 0;
	
	if(getChar(e)!=NUM){
		if(getChar(e)=='-' || getChar(e)=='+' 
				|| getChar(e)=='*' || getChar(e)=='/'){
			result = 1;	
		}	
	}
	
	return result;
}

/* Procédure 'estIdentificateur':                                  
 * permet de savoir si elem represente un identificateur
 * 
 * Paramètres:                                             
 * (in) 'e'		: element dont on souhaite connaitre ce qu'il represente
 *
 * Résultat:                                               
 * - 1 si e est un identificateur
 * - 0 sinon
 */ 
int estIdentificateur(Elem e){

	int result = 0;
	
	if(!estOperateur(e) && getChar(e)!='(' && getChar(e)!=')') result = 1;
	
	return result;
	
}
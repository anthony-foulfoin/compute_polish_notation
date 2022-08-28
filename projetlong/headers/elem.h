/* Ce module permet de definir le type Elem, structure manipulee par les modules convertisseur et calcul_arith,
 * servant de support de stockage aux informations empilees dans les Linear_Struct. Il definit egalement l'ensemble des 
 * methodes permettant de manipuler ces elements.
 */

#ifndef ELM_TOOLS_H_
#define ELM_TOOLS_H_

#include "linear_struct.h"

#define NUM '\0'	// Si un Elem stocke un entier, alors son attribut de type char doit etre fixe avec cette valeur

typedef struct _elem *Elem;	// Structure destinee a etre stocker au sein de piles

/* Procédure 'print_elem':                                  
 * permet d'afficher le contenu d'une structure de type Elem
 * 
 * Paramètres:                                             
 * (in) 'i'		: la structure dont on souhaite afficher le contenu
 *
 * Résultat:                                               
 * void
 */ 
void print_elem(ELT i);

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
Code_retour comparer_char(ELT elem, ELT car);

/* Procédure 'creerElem':                                  
 * permet de creer uen nouvelle structure de type Elem
 * 
 * Paramètres:                                             
 * (in) 'e'		: la structure dont on souhaite obtenir la valeur de type char
 *
 * Résultat:                                               
 * valeur de type char de la structure
 */ 
Elem creerElem();

/* Procédure 'getChar':                                  
 * permet d'obtenir l'attribut de type char d'un Elem
 * 
 * Paramètres:                                             
 * (in) 'e'		: la structure dont on souhaite obtenir la valeur de type char
 *
 * Résultat:                                               
 * valeur de type char de la structure
 */ 
char getChar(Elem e);

/* Procédure 'getInt':                                  
 * permet d'obtenir l'attribut de type entier d'un Elem
 * 
 * Paramètres:                                             
 * (in) 'e'		: la structure dont on souhaite obtenir la valeur entiere
 *
 * Résultat:                                               
 * valeur entiere de la structure
 */ 
int getInt(Elem e);

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
void setInt(Elem e, int i);

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
void setChar(Elem e, char i);

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
int estOperateur(Elem e);

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
int estIdentificateur(Elem e);

#endif /*ELM_TOOLS_H_*/

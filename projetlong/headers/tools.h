#ifndef TOOLS_H_
#define TOOLS_H_

#include "linear_struct.h"
#include "messages.h"
#include "type_item.h"

/* Procédure 'getInEntier':                                  
 * permet d'obtenir un entier de la part de l'utilisateur via l'entree par defaut
 * 
 *
 * Résultat:                                               
 * l'entier saisi par l'utilisateur
 */ 
int getInEntier();

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
Code_Erreur transferer(Linear_Struct *pile1,Linear_Struct *pile2);

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
Code_Erreur creer_pile_expr(int valInt, char valChar, enum type_item codeRet, Linear_Struct *expr);

#endif /*TOOLS_H_*/

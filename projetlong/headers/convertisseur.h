#ifndef CONVERTISSEUR_H_
#define CONVERTISSEUR_H_

#include "messages.h"
#include "linear_struct.h"

/* Procédure 'traiterItem':                                  
 * traite un item de l'expression a convertir   
 *          
 * Paramètres:                                             
 * (in)  	'valChar' 	: contient l'item a traiter si celui-ci est de type char
 * (in)  	'valInt'	: contient l'item a traiter si celui-ci est de type int                         
 * (in)  	'codeRet'	: code retourne par la fonction read_item indiquant ce que represente l'item traite  
 * (in/out) 'pile1'		: pile temporaire contenant certains items de l'expression a traiter. Une pile vide doit 
 * 						etre fournie lors du premier appel de la fonction, cette meme pile devant ensuite etre fournie pour
 * 						chaque nouvel item de l'expression traite.
 * (in/out) 'pile2'		: pile contenant l'expression polonaise a la fin de la conversion. Une pile vide doit 
 * 						etre fournie lors du premier appel de la fonction, cette meme pile devant ensuite etre fournie pour
 * 						chaque nouvel item de l'expression traite.
 * (in/out) 'ident'		: pile contenant la liste de tous les identificateurs de l'expression. Une pile vide doit 
 * 						etre fournie lors du premier appel de la fonction, cette meme pile devant ensuite etre fournie pour
 * 						chaque nouvel item de l'expression traite.
 * 
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur conversion(Linear_Struct *expr, Linear_Struct *ident);

#endif /*CONVERTISSEUR_H_*/



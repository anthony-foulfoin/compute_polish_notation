#include "messages.h"
#include <stdio.h>

 /* Procédure 'afficher_message':                                  
 * affiche l'erreur passe en parametre si la constante AFFICHAGE_ERREUR est positionnee a 1
 *          
 * Paramètres:                                             
 * (in)  'message' 	: message d'erreur a afficher
 * 
 * Résultat:                                               
 * void
 */  
void afficher_message(char *message){
	if(AFFICHAGE_MESSAGES){
		printf("%s\n", message);
	}
}
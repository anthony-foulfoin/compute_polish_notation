#include "linear_struct.h"
#include "messages.h"
#include <stdlib.h>
#include <stdio.h>

struct _chainon{
	ELT valeur;
	struct _chainon *suivant;
};

/* Opérations communes sur une linear_struct       */

/* Procédure 'tester_vide':                        */
/* teste si une linear_struct est vide ou non      */
/* Paramètres:                                     */
/* (in)  'q' : la linear_struct à tester           */
/* Résultat:                                       */
/* - KO si 'q' n'est pas vide                      */
/* - OK sinon                                      */

Code_retour tester_vide(Linear_Struct q){
	if(q==NULL) return OK;
	else return KO;
}

/* Procédure 'creer':                                      */
/* crée une linear_struct initialement vide                */

Linear_Struct creer(){
	return NULL;
}

/* Opérations sur une linear_struct vue comme un liste     */
/* afficher qui affiche tous les éléments                  */
/* chercher qui recherche un élément vérifiant un prédicat */

/* Procédure 'afficher':                                   */
/* affiche successivement les élements de la linear_struct */
/* en appelant une procédure d'affichage de ces            */
/* éléments                                                */
/* Paramètres:                                             */
/* (in) 'q': la linear_struct à afficher                   */
/* (in) 'print_elem': la procédure d'affichage des éléments*/
/*           Paramètres:                                   */
/*           (in)  'e' : l'élément courant                 */
/*           Résultat: void                                */
/* Résultat: void                                          */


void afficher(Linear_Struct q, void (*print_elem)(ELT e)){
	
	if(tester_vide(q)==OK) puts(MESSAGE_STRUCT_EMPTY);

	while(q!=NULL){
		print_elem(q->valeur);
		q = q-> suivant;
	}
}

/* Procédure 'chercher':                                   */
/* cherche et renvoie le premier élément d'une             */
/* linear_struct égal à un élément donné 'e'               */
/* Paramètres:                                             */
/* (in)  'q' : la linear_struct où l'on cherche un élément */ 
/* (in)  'e' : l'élément cherché                           */
/* (in)  'p' : la fonction de comparaison                  */
/*             Paramètres:                                 */
/*             (in)  'e1':  un élément                     */
/*             (in)  'e2':  un autre élément               */
/*             Résultat:                                   */
/*             - OK si les éléments sont égaux             */
/*             - KO sinon                                  */
/* Résultat:                                               */
/* - le premier élément de la linear_struct vérifiant      */
/*   égale à e s'il existe                                 */
/* - NULL sinon                                            */

ELT chercher(Linear_Struct q, ELT e, Code_retour (*cmp)(ELT e1,ELT e2)){

	while(q!=NULL){

		if(cmp(q->valeur,e)==OK) return q->valeur;
		else q = q-> suivant;
	}
	
	return NULL;
}

/* Opérations sur la linear_struct vue comme une pile.     */
/* Insertion et retrait se font sur une seule              */
/* extrémité de la linear_struct, en première position     */

/* Procédure 'empiler' :                                   */
/* ajout d'un élément dans une pile                        */
/* Paramètres:                                             */
/* (in/out) '*q': la pile modifiée par l'insertion         */
/* (in)     'e' : l'élément à insérer dans '*q'            */
/* Résultat:                                               */
/* - KO si l'insertion a échoué. La linear_struct '*q'     */
/*      n'est pas modifiée dans ce cas                     */
/* - OK sinon                                              */

Code_retour empiler(Linear_Struct *q, ELT e){
	
	Code_retour code = KO;

	Linear_Struct tmp = *q;	
	// On insere le nouvel element en tete de la structure
	*q = (Linear_Struct) malloc(sizeof(struct _chainon));

	if(*q!=NULL){
		(*q)->valeur = e;
		(*q)->suivant = tmp;
		code = OK;
	}

	return code;
}

/* Procédure 'depiler' :                           */
/* retrait d'un élément dans une pile              */
/* Paramètres:                                     */
/* (in/out) '*q': la pile modifiée par le retrait  */
/* (out)    '*e': l'élément retiré de '*q'         */
/* Résultat:                                       */
/* - KO si le retrait a échoué. '*q' et '*e'       */
/*      ne sont pas modifiés dans ce cas           */
/* - OK sinon                                      */

Code_retour depiler(Linear_Struct *q, ELT *e){

	Code_retour code = KO;
	Linear_Struct suivant;
	// On depile le premier element de la structure
	if(*q!=NULL){
		*e = (*q)->valeur;
		suivant = (*q)->suivant;
		// On libere la memoire utilisee par le chainon depile
		free(*q);
		*q = suivant;
		code = OK;
	}

	return code;
}

/* Procédure 'sommet' :                            */
/* donne le sommet d'une pile                      */
/* Paramètres:                                     */
/* (in)  'q' : la pile                             */
/* (out) '*e': l'élément sommet de 'q'             */
/* Résultat:                                       */
/* - KO si la pile est vide. L'élément '*e'        */
/*      n'est pas modifié dans ce cas              */
/* - OK sinon                                      */

Code_retour sommet(Linear_Struct q, ELT *e){
	Code_retour code = KO;

	if(q!=NULL){
		*e=q->valeur;
		code=OK;
	}

	return code;
}

/* Ce module permet de definir l'ensemble des messages affiches par les modules convertisseur et 
 * calcul_arith ainsi que les codes d'erreurs renvoyes. Il definit egalement une methode afficher_erreur
 * qui n'affiche le message d'erreur souhaite que si la constante AFFICHAGE_ERREUR est positionnee a 1
 */

#ifndef MESSAGES_H_
#define MESSAGES_H_

// Si cette variable est positionnee a 1, les modules convertisseur et calcul_arith sont autorises a afficher les erreurs a l'ecran.
// Dans le cas contraire, seul le code d'erreur est retourne. Ce dernier est retourne dans tous les cas.
#define AFFICHAGE_MESSAGES	1

#define	MSG_ERREUR_01	"*Attention, les pointeurs passes en parametre doivent etre non nuls*"
#define	MSG_ERREUR_02	"*Attention, votre expression est mal parenthesée*"
#define	MSG_ERREUR_03	"*Attention, veuillez verifier les parametres de votre expression*"
#define	MSG_ERREUR_06	"*Attention, echec de l'allocation de memoire*"
#define	MSG_ERREUR_07	"*Attention, expression incorrecte, nombre d'operandes insufisant*"
#define	MSG_ERREUR_08	"*Attention, operateur inconnu*"
#define	MSG_ERREUR_09	"*Attention, une erreur inconnue c'est produite*"
#define	MSG_ERREUR_10	"*Attention, division par 0*"
#define	MSG_ERREUR_11	"*Attention, l'expression ne peut pas debuter par un operateur*"
#define	MSG_ERREUR_12	"*Attention, l'expression ne peut pas terminer par un operateur*"
#define	MSG_ERREUR_13	"*Attention, un operateur est mal place ou manquant*"
#define	MSG_ERREUR_14	"*Attention, symbole inconnu*"
#define	MSG_ERREUR_15	"*Attention, vous devez taper une expression*"

// Codes associes aux messages d'erreur

typedef enum code_erreur {CDE_ERREUR_00=0, CDE_ERREUR_01=1, CDE_ERREUR_02=2, CDE_ERREUR_03=3,CDE_ERREUR_06=6,CDE_ERREUR_07=7,
	CDE_ERREUR_08=8, CDE_ERREUR_09=9,CDE_ERREUR_10=10,CDE_ERREUR_11=11,CDE_ERREUR_12=12,CDE_ERREUR_13=13,CDE_ERREUR_14=14,
	CDE_ERREUR_15=15} Code_Erreur;

#define MESSAGE_ENTIER "Merci de saisir la valeur associee a : "
#define MESSAGE_ENTIER_ERREUR "Une erreur s'est produite, merci de bien vouloir ressaisir un ENTIER : "
#define MESSAGE_STRUCT_EMPTY "Attention, la structure est vide"

/* Procédure 'afficher_message':                                  
 * affiche le message d'erreur passe en parametre si la constante AFFICHAGE_ERREUR est positionnee a 1
 *          
 * Paramètres:                                             
 * (in)  'message' 	: message d'erreur a afficher
 * 
 * Résultat:                                               
 * void
 */  
void afficher_message(char *message);
#endif /*MESSAGES_H_*/

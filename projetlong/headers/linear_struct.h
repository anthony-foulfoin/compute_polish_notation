/* Une linear_struct est une structure de données linéaire */
/* que l'on peut manipuler comme une pile ou bien          */
/* comme une liste à accès aléatoire des éléments          */

/* Le type pseudo-générique des éléments présents  */
/* dans une linear_struct                          */

#ifndef LINEAR
#define LINEAR

#define ELT void *

/* Le type des codes de retour des différentes     */
/* opérations sur les linear_structs.              */
/* OK: l'exécution s'est passée normalement        */
/* KO: impossible d'exécuter l'opération           */

typedef enum { OK, KO } Code_retour;

/* Le type privé Linear_Struct                     */

typedef struct _chainon *Linear_Struct;

#endif

/* Opérations communes sur une linear_struct       */

/* Procédure 'tester_vide':                        */
/* teste si une linear_struct est vide ou non      */
/* Paramètres:                                     */
/* (in)  'q' : la linear_struct à tester           */
/* Résultat:                                       */
/* - KO si 'q' n'est pas vide                      */
/* - OK sinon                                      */

Code_retour tester_vide(Linear_Struct q);

/* Procédure 'creer':                                      */
/* crée une linear_struct initialement vide                */

Linear_Struct creer();

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


void afficher(Linear_Struct q, void (*print_elem)(ELT e));

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

ELT chercher(Linear_Struct q, ELT e, Code_retour (*cmp)(ELT e1,ELT e2));

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

Code_retour empiler(Linear_Struct *q, ELT e);

/* Procédure 'depiler' :                           */
/* retrait d'un élément dans une pile              */
/* Paramètres:                                     */
/* (in/out) '*q': la pile modifiée par le retrait  */
/* (out)    '*e': l'élément retiré de '*q'         */
/* Résultat:                                       */
/* - KO si le retrait a échoué. '*q' et '*e'       */
/*      ne sont pas modifiés dans ce cas           */
/* - OK sinon                                      */

Code_retour depiler(Linear_Struct *q, ELT *e);

/* Procédure 'sommet' :                            */
/* donne le sommet d'une pile                      */
/* Paramètres:                                     */
/* (in)  'q' : la pile                             */
/* (out) '*e': l'élément sommet de 'q'             */
/* Résultat:                                       */
/* - KO si la pile est vide. L'élément '*e'        */
/*      n'est pas modifié dans ce cas              */
/* - OK sinon                                      */

Code_retour sommet(Linear_Struct q, ELT *e);

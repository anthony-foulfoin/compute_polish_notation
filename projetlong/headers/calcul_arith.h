#ifndef CALCUL_ARITH_H_
#define CALCUL_ARITH_H_

/* Procédure 'calcul_arith':                                  
 * permet d'evaluer une expression arithmetique representee en notation polonaise postfixee
 * 
 * Paramètres:                                             
 * (in) 'expr'		: l'expression arithmetique en notation polonaise a evaluer
 * (in) 'ident'		: pile contenant la liste de tous les identificateurs presents dans l'expression a evaluer
 * (out) 'result'	: variable destinee a recevoir le resultat du calcul
 * 
 * Résultat:                                               
 * CDE_ERREUR_00 si le traitement a reussi                              
 * CDE_ERREUR_xx indiquant l'erreur rencontree sinon
 */ 
Code_Erreur calcul_arith(Linear_Struct expr, Linear_Struct ident, int *result);

#endif /*CALCUL_ARITH_H_*/

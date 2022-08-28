#include "linear_struct.h"
#include <stdio.h>

void print_int(ELT i){

	int *val = (int *) i;
	printf("%d ",*((int *) val));
}

Code_retour comparer_int(ELT elem, ELT ent){
	
	if(*((int *) elem) == *((int *) ent)) return OK;
	else return KO;
	
}

/* Cette methode permet de lancer une phase de test testant chacune des 
 * fonctions proposees par le module linear_struct
 */
int tester(){
	
	int elem1;
	int elem2;
	int *tmp;
	Linear_Struct test;
	
	elem1 = 2;
	elem2 = 3;
	
	// Test 1
	test = creer();
	puts("\nOn cree une nouvelle pile");
	if(test == NULL) puts("Création OK");
	else puts("Création NOK");
	
	// Test 2
	puts("\nOn test si elle est vide");
	if(tester_vide(test)==OK) puts("tester_vide OK");
	else puts("tester_vide NOK");
	
	// Test 3
	puts("\nOn empile 2");
	if(empiler(&test, &elem1)==OK) puts("empiler OK");
	else puts("empiler NOK");
	
	puts("\nOn empile 3");
	if(empiler(&test, &elem2)==OK) puts("empiler OK");
	else puts("empiler NOK");
	
	// Test 4
	puts("\nOn test si elle est vide");
	if(tester_vide(test)==KO) puts("tester_vide OK");
	else puts("tester_vide NOK");
	
	// Test 5
	puts("\nOn consulte son sommet");
	if(sommet(test, (ELT) &tmp)==OK) puts("sommet  OK");
	else puts("sommet NOK");
	
	if(*tmp==3) printf("Valeur attendue : 3. Valeur obtenue : %d", *tmp);
	else printf("Erreur, valeur attendue : 3. Valeur obtenue : %d", *tmp);
	
	
	// Test 6
	puts("\n\nOn recherche la valeur 2 avec la methode chercher");
	if((tmp=chercher(test, &elem1, comparer_int))==&elem1) puts("recherche OK");
	else puts("recherche NOK");
	printf("Valeur attendue : 2. Valeur obtenue : %d", *tmp);
	
	// Test7
	puts("\n\nOn test la fonction afficher. Contenu de la pile :");
	afficher(test, print_int);
	
	// Test 8
	puts("\n\nOn depile 3");
	if(depiler(&test, (ELT) &tmp)==OK) puts("depiler OK");
	else puts("depiler NOK");
	printf("Valeur attendue : 3. Valeur obtenue : %d", *tmp);
	
	// Test 9
	puts("\n\nOn depile 2");
	if(depiler(&test, (ELT) &tmp)==OK) puts("depiler OK");
	else puts("depiler NOK");
	printf("Valeur attendue : 2. Valeur obtenue : %d", *tmp);
	
	// Test 10
	puts("\n\nOn test si la pile est vide");
	if(tester_vide(test)==OK) puts("tester_vide OK");
	else puts("tester_vide NOK");
	
	// Test 11
	puts("\nOn test la fonction afficher. Contenu de la pile :");
	afficher(test, print_int);
	
	// Test 12
	puts("\nOn consulte son sommet");
	if(sommet(test, (ELT) &tmp)==KO) puts("sommet  OK");
	else puts("sommet NOK");
	
	// Test 13
	puts("\nOn depile la pile vide");
	if(empiler(&test, tmp)==OK) puts("depiler OK");
	else puts("depiler NOK");
	
	return 0;	
}
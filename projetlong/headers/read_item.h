
#include "type_item.h"


/* read_item lit un item sur stdin
   renvoie le type de l'item lu
   passe sa valeur par référence dans val si c'est un entier
   dans op_ou_ident si c'est un caractère
   renvoie errident si caractère non conforme                     */

enum type_item read_item(char *op_ou_ident, int *valeur);

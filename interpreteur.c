
/* Exemple d'utilisation de l'analyse lexicale : 
    Affichage d'une sequence de lexemes            */

#include <stdlib.h> 
#include <stdio.h>

#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"

#define N 15

int main (int argc, char *argv[]) {
   char s[100];
   identificateur tab_idf[N];
   
   if (argc > 1) 
   {
   	analyser(argv[1], tab_idf);
   }
   else if (argc == 1)
   {
     FILE* f;
     
     f = fopen("temps.txt", "w");
     fgets(s, 100, stdin);
	   fputs(s, f);
     fclose(f);
     analyser("temps.txt", tab_idf);
   } 
   else 
   {
  	printf("Erreur : arguments incorrects\n") ;
  	return 1 ; 
   } ; 

;
	
   return 0 ;
}

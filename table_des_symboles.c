#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_des_symboles.h"


void afficher_table(identificateur* tab, int n)
{
  int i;

  printf("Liste des identificateur :\n");
  for (i = 0; i < n; i++)
  {
    printf("%s = %f ;\n", tab[i].nom, tab[i].valeur);
  }

}

int rechercher_identificateur(identificateur* tab, char* idf, int n)
{
  int i = 0;
  while(i < n)
  {
    if(strcmp(idf, tab[i].nom) == 0)
    {
      return i ;
    }
    i++;
  }
  return -1 ;
}

float valeur_idf(identificateur* tab, char* nom, int n)
{
  int i = 0;
  
  while(i < n)
  {
  
    if(strcmp(nom, tab[i].nom) == 0)
    {
      return tab[i].valeur ;
    }
    i++;
  }
  

  return -1 ;
}
	
    
    

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
    
  

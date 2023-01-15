
#include <stdio.h>
#include "type_ast.h"

void aff_operateur(TypeOperateur op){
	switch (op) {
		case N_PLUS:
			printf("+") ;
			break;
		case N_MOINS:
			printf("-") ;
			break;
		case N_MUL:
			printf("*") ;
			break;
		case N_DIV:
			printf("/");
			break;
    case N_INF:
      printf("<");
      break;
    case N_INF_E:
      printf("<=");
      break;
    case N_EGAL:
      printf("==");
      break;
    case N_DIF:
      printf("!=");
      break;
    case N_SUP_E:
      printf(">=");
      break;
    case N_SUP:
      printf(">");
      break;
     
	} 
}

void afficher_arbre(Ast expr) {
	switch (expr->nature) {
               case OPERATION:
                        aff_operateur(expr->operateur) ;
                        printf("(");
                        afficher_arbre(expr->gauche);
                        printf(", ");
                        afficher_arbre(expr->droite);
                        printf(")");
			break ;
               case VALEUR:
                  	printf("%d", expr->valeur);
			break ;
	}
}

int evaluation(Ast expr) 
{
	  int res = -1;		
		
      if(expr->nature == OPERATION)
      {
      		switch(expr->operateur)
      		{
      			case N_PLUS:
      				res = evaluation(expr->gauche) + evaluation(expr->droite);
      				break;
      			case N_MOINS:
      				res = evaluation(expr->gauche) - evaluation(expr->droite);
      				break;
      			case N_MUL:
      				res = evaluation(expr->gauche) * evaluation(expr->droite);
      				break;
      			case N_DIV:
      				res = evaluation(expr->gauche) / evaluation(expr->droite);
      				break;
            case N_INF:
              res = evaluation(expr->gauche) < evaluation(expr->droite);
              break;
            case N_INF_E:
              res = evaluation(expr->gauche) <= evaluation(expr->droite);
              break;
            case N_EGAL:
              res = evaluation(expr->gauche) == evaluation(expr->droite);
              break;
            case N_DIF:
              res = evaluation(expr->gauche) != evaluation(expr->droite);
              break;
            case N_SUP_E:
              res = evaluation(expr->gauche) >= evaluation(expr->droite);
              break;
            case N_SUP:
              res = evaluation(expr->gauche) > evaluation(expr->droite);
              break;              
   				
      		}
      }
      else
      {
      		res = expr->valeur;
	  }
	  
	  return res;
} 	
      			



      		


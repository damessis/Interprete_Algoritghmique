#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"

#include "type_ast.h"
#include "ast_construction.h"
#include "ast_parcours.h"

int i = 0, la = 0;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rec_op2(TypeOperateur *Op)
{
	if(lexeme_courant().nature == MUL){ 	
		*Op = N_MUL;
		avancer();
	}
	else if(lexeme_courant().nature == DIV){
		*Op = N_DIV;
		avancer();
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rec_op1(TypeOperateur *Op)
{
	if(lexeme_courant().nature == PLUS){ 	
		*Op = N_PLUS;
		avancer();
	}
	else if(lexeme_courant().nature == MOINS){
		*Op = N_MOINS;
		avancer();
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rec_facteur(Ast *A1,  identificateur *tab_idf)
{
	char nom_idf[15];
	float val = 99;
	Lexeme l = lexeme_courant() ;
	
	switch(lexeme_courant().nature)
	{
		case ENTIER : 
			*A1 = creer_valeur(lexeme_courant().valeur);
			avancer();
      
      
      
			break;
		case IDF :
			strcpy(nom_idf, l.chaine);
      
			val = valeur_idf(tab_idf, nom_idf, i);
			//printf("%s\n", nom_idf);
			if(val == -1)
			{
			    printf("Erreur : variable inconnue\n");
			    exit(0);
			}
			
			*A1 = creer_valeur(val);
 		  avancer();
   		break;
		case PARENTH_OUVRANTE : 
			avancer();
			Rec_eag(A1, tab_idf);
			if (lexeme_courant().nature != PARENTH_FERMANTE)
				exit(0);
			avancer();
			break;
		default : 
			printf("Erreur_Syntaxique: pb avec facteur\n") ;
			exit(0);
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rec_seq_facteur(Ast *A2,  identificateur *tab_idf)
{
	Ast A1;
	Rec_facteur(&A1, tab_idf);
	Rec_suite_seq_facteur(A1, A2, tab_idf);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rec_suite_seq_facteur(Ast A1, Ast *A2,  identificateur *tab_idf)
{
	Ast A3;
	TypeOperateur Op = N_PLUS;
	TypeOperateur Opb = N_PLUS;
	Rec_op2(&Op);
	if (Op != Opb){
		Rec_facteur(&A3, tab_idf);
		Rec_suite_seq_facteur(A3, A2, tab_idf);
		*A2 = creer_operation(Op, A1, *A2);
	}
	else{
		*A2 = A1;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rec_terme(Ast *A, identificateur *tab_idf)
{
	Rec_seq_facteur(A, tab_idf);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rec_suite_seq_terme(Ast A1,Ast *A2,  identificateur *tab_idf)
{
	Ast A3;
	TypeOperateur Op = N_MUL;
	TypeOperateur Opb = N_MUL;
	Rec_op1(&Op);
	if (Op != Opb){
		Rec_terme(&A3, tab_idf);
		Rec_suite_seq_terme(A3, A2, tab_idf);
		*A2 = creer_operation(Op, A1, *A2);
	}
	else{
		*A2 = A1;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rec_seq_terme(Ast *A, identificateur *tab_idf)
{
	Ast A1;
	Rec_terme(&A1, tab_idf);
	Rec_suite_seq_terme(A1,A, tab_idf);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rec_eag(Ast *A,  identificateur *tab_idf)
{
	Rec_seq_terme(A, tab_idf);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rec_affectation(Ast *A, identificateur *tab_idf)
{ 
  	int res = -1;
    int i_mod = 0;
    Lexeme l = lexeme_courant() ;
  	switch(lexeme_courant().nature)
  	{
  		case IDF: 
        i_mod = rechercher_identificateur(tab_idf, l.chaine, i);
        if(i_mod == -1)
        {
    			strcpy(tab_idf[i].nom, l.chaine);
    			avancer();
        }
        else
        {
          avancer();
        }
  			if(lexeme_courant().nature == AFF)
  			{	
  				avancer();
  				Rec_eag(A, tab_idf);
  				res = evaluation(*A);
          if(i_mod == -1)
          {
  				  tab_idf[i].valeur = res ;
            i++;                                
          }
          else
            tab_idf[i_mod].valeur = res;
            
  				if(lexeme_courant().nature == SEPINST)
  				{
  					avancer();
  				}
  				else
  				{
  					printf("Erreur : point virgule\n");
  					exit(0);
  				}
  			}
  			else
  			{
  				printf("Erreur : operateur affectation\n");
  				exit(0);
  			}
  			break;
  		default:
  			printf("Erreur : affectation\n");
  			exit (0);
  	}
   
     
   
}



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Rec_condition(Ast *Ac, identificateur *tab_idf)
{
  int res = -1;
  int val = -7;
  
  Ast *A1 = malloc (sizeof(Ast));
  Ast *A2 = malloc (sizeof(Ast));
  Ast *A3 = malloc (sizeof(Ast));
  Ast *A4 = malloc (sizeof(Ast));
 	TypeOperateur Op;

  
  switch(lexeme_courant().nature)
  {
    case ENTIER :
    case IDF:
      

      
    
      Rec_eag(A1, tab_idf);
      val = evaluation(*A1);
      *A2 = creer_valeur(val);
    
      
                  
    
  		switch(lexeme_courant().nature)
  		{
        case INF:
          Op = N_INF;
          avancer();
          break;
        case INF_E:
          Op = N_INF_E;
          avancer();
          break;
        case EGAL:
          Op = N_EGAL;
          avancer();
          break;
        case DIF:
          Op = N_DIF;
          avancer();
          break;
        case SUP_E:
          Op = N_SUP_E;
          avancer();
          break;
        case SUP:
          Op = N_SUP;
          avancer();
          break;    
        default:
          printf("Erreur condition 1\n");
          exit(0);
      }
      


      
  		switch(lexeme_courant().nature)
      {
        case ENTIER:
        case IDF:
          Rec_eag(A3, tab_idf);
          val = evaluation(*A3);    
          *A4 = creer_valeur(val);
        
          break;
          
        default:
          printf("Erreur condition 2\n");
          exit(0);
      }
      

      
      *Ac = creer_operation(Op, *A2, *A4);
      res = evaluation(*Ac);
      
      
      break;
      
    default:
      printf("Erreur condition 3\n");
  }  
      
  free(A1);
  free(A2);
  free(A3);
  free(A4);
  
  return res;
}
      

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rec_inst(Ast *A, identificateur *tab_idf, int a_executer)
{

    Lexeme l = lexeme_courant() ;
    Ast *Ac = malloc (sizeof(Ast));
    int res = -7;
    

    
    switch(l.nature)
    {
      case MOT_CLE:
        if(strcmp(l.chaine, "if") == 0)
        {
          avancer();
          res = Rec_condition(Ac, tab_idf);

          
          l = lexeme_courant() ;

          if(strcmp(l.chaine, "then") == 0)
          {  
            avancer();
          }
          else
          {
            printf("Erreur : then\n");
            exit(0);
          }

          if(res)
          {
            Rec_affectation(A, tab_idf);
          }
          else
          {
            while(lexeme_courant().nature != SEPINST)
            {
              avancer();
            }
            avancer();
          }
                
          l = lexeme_courant() ;
          if(strcmp(l.chaine, "else") == 0)
          {
            avancer();
          }
          else
          {
            printf("Erreur : else\n");
            exit(0);
          }

          if(!res)
          {
            Rec_affectation(A, tab_idf);
          }
          else
          {
            while(lexeme_courant().nature != SEPINST)          
            {
              avancer();                            
            }
            avancer();
          }
          
          
          l = lexeme_courant() ;
          if(strcmp(l.chaine, "fi") == 0)
          {
            avancer();
          }
          else
          {
            printf("Erreur : fi\n");
            exit(0);
          }
        }
        else
        {
          printf("Erreur : if\n");
          exit(0);
        }
        break;
        
      case IDF:
        if(a_executer)
        { 
          Rec_affectation(A, tab_idf);
        }
        break;
        
        
      default:
        printf("Erreur : syntaxe incorrect\n");
        exit(0);
    }
  
  
  
}



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void programme(Ast *A, identificateur *tab_idf, int a_executer)
{
    while(!fin_de_sequence())
    {
      Rec_inst(A, tab_idf, a_executer); 
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void analyser(char *nom_fichier, identificateur *tab_idf) 
{
	Ast *A = malloc (sizeof(Ast));
  int a_executer = 1;
	
	demarrer (nom_fichier);
	
  programme(A, tab_idf, a_executer);
 
  afficher_table(tab_idf, i);
}



























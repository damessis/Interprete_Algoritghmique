/* ------------------------------------------------------------------------
-- module analyse_lexicale
--
-- analyse lexicale d'une expression arithmetique
--
-- J-P. Peyrin, G. Serasset (version initiale) : janvier 1999
-- P.Habraken - 18/01/2010
--
-- 10 juin 2006 - PH :
-- remplacement record a champs variants par record "plat"
-- remplacement traitement iteratif par automate
--
-- Aout 2016 - LM : version C
------------------------------------------------------------------------ */


#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

   /* --------------------------------------------------------------------- */


/* Les variables et fonctions locales au module */

   Lexeme lexeme_en_cours ;	/* le lexeme courant */

   void ajouter_caractere (char *s, char c);
   int est_separateur(char c ) ;
   int est_identificateur(char c ) ;
   int est_chiffre(char c ) ;
   int est_symbole(char c ) ;
   int est_lettre(char c ) ;
   int est_mot_cle(char c);
   void reconnaitre_lexeme();

   /* --------------------------------------------------------------------- */

   void demarrer(char *nom_fichier) {
      demarrer_car(nom_fichier);
      avancer();
   }

   /* --------------------------------------------------------------------- */

   void avancer() {
      reconnaitre_lexeme();
   } 

   /* --------------------------------------------------------------------- */

   Lexeme lexeme_courant() {
      return lexeme_en_cours;
   } 

   /* --------------------------------------------------------------------- */

   int fin_de_sequence() {
      return lexeme_en_cours.nature == FIN_SEQUENCE;
   }

   /* --------------------------------------------------------------------- */

   void arreter() {
      arreter_car() ;
   }

   /* --------------------------------------------------------------------- */


   // reconnaissance d'un nouveau lexeme
   // etat initial : le caractere courant est soit separateur 
   //                soit le 1er caractere d'un lexeme
   // etat final : 
   //       - un nouveau lexeme est reconnu dans lexeme_en_cours
   //       - le caractere courant est soit la fin de fichier, 
   //		soit un separateur,  soit le 1er caractere d'un lexeme

   void reconnaitre_lexeme() 
   {
      typedef enum {E_INIT, E_IDF, E_ENTIER, E_MOT_CLE, E_OP_EGAL, E_OP_SUP_EGAL, E_OP_INF_EGAL, E_OP_DIF, E_FIN} Etat_Automate ;
      Etat_Automate etat = E_INIT;

     // on commence par lire les separateurs
     while ( est_separateur( caractere_courant() ) ) 
     {
       avancer_car() ;
     }

     lexeme_en_cours.chaine[0] = '\0' ;

     // on utilise ensuite un automate pour reconnaitre le prochain lexeme

     while (etat != E_FIN) 
     {
	      switch (etat) 
	      {
             
		    	case E_INIT:
    				if (fin_de_sequence_car() != 0) 
    				{
              lexeme_en_cours.nature = FIN_SEQUENCE;
              etat = E_FIN;
    				} 
    				else if(est_chiffre(caractere_courant())) 
    		    {
              lexeme_en_cours.nature = ENTIER;
              lexeme_en_cours.ligne = numero_ligne();
              lexeme_en_cours.colonne = numero_colonne();
  					  ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
              lexeme_en_cours.valeur = caractere_courant() - '0';
              etat = E_ENTIER;
    					     
              avancer_car() ;
            } 
    		    else if(est_lettre(caractere_courant())) 
  			    {
              lexeme_en_cours.nature = IDF;
  		        lexeme_en_cours.ligne = numero_ligne();
  		        lexeme_en_cours.colonne = numero_colonne();
  			      ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
  		        lexeme_en_cours.valeur = caractere_courant() - '0';
  			      etat = E_IDF;
                             
              avancer_car() ;            
               
 	          } 
            else if(est_mot_cle(caractere_courant()))
            {
              lexeme_en_cours.nature = MOT_CLE;
  		        lexeme_en_cours.ligne = numero_ligne();
  		        lexeme_en_cours.colonne = numero_colonne();
  			      ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
  		        lexeme_en_cours.valeur = caractere_courant() - '0';
  			      etat = E_MOT_CLE;
                             
              avancer_car() ;   
            }
            else if(est_symbole(caractere_courant())) 
     			  { 
                lexeme_en_cours.ligne = numero_ligne();
               	lexeme_en_cours.colonne = numero_colonne();
                ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
         	      switch (caractere_courant()) 
               	{
                  case '+':
                    lexeme_en_cours.nature = PLUS;
          			    etat = E_FIN;
   	                break;
             		  case '-':
                    lexeme_en_cours.nature = MOINS;
             			  etat = E_FIN;
   		              break;
             		  case '*':
             			  lexeme_en_cours.nature = MUL;
             			  etat = E_FIN;
   		              break;
               		case '/':
               			lexeme_en_cours.nature = DIV;
               			etat = E_FIN;
               			break;
               		case '(':
               			lexeme_en_cours.nature = PARENTH_OUVRANTE;
               			etat = E_FIN;
  			            break;
               		case ')':
               			lexeme_en_cours.nature = PARENTH_FERMANTE;
               			etat = E_FIN;
  			            break;
               		case '=':
               			lexeme_en_cours.nature = AFF;
               			etat = E_OP_EGAL;
                    break;
                  case '<':
                    lexeme_en_cours.nature = INF;
                    etat = E_OP_INF_EGAL;
  		            	break;	
                  case '>':
                    lexeme_en_cours.nature = SUP;
                    etat = E_OP_SUP_EGAL;
                    break;
                  case '!':
                    etat = E_OP_DIF;
                    break;
               		case ';':
               			lexeme_en_cours.nature = SEPINST;
               			etat = E_FIN;
  			            break;				   								   						
  					   		default:
    								printf("Erreur lexicale \n") ;
    				 				exit(0) ;
                }
                              
                avancer_car() ; 
  				   } 
             else 
             {
                printf("Erreur lexicale \n") ;
                exit(0) ;
  		       }
             
             break ;

    			case E_IDF:
            if (est_identificateur(caractere_courant())) 
            { 
              ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
             	lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
             	etat = E_IDF ;
             	avancer_car ();
         	  } 
         	  else
         	  {
        	  	etat = E_FIN ;
         	  }
                   	  
         	  break;
                        
			    case E_ENTIER:
            if (est_chiffre(caractere_courant())) 
            { 
              ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
             	lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
             	etat = E_ENTIER ;
             	avancer_car ();
         	  } 
         	  else
         	  {
        	  	etat = E_FIN ;
         	  }
               	  
         	  break;
              
         case E_MOT_CLE:
            if (est_mot_cle(caractere_courant())) 
            { 
              ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
             	lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
             	etat = E_MOT_CLE ;
             	avancer_car ();
         	  } 
         	  else
         	  {
        	  	etat = E_FIN ;
         	  }
               	  
         	  break;         
         
          
          case E_OP_EGAL:
            if (caractere_courant() == '=')
            {
              ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
             	lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
              lexeme_en_cours.nature = EGAL;
             	etat = E_FIN ;
             	avancer_car ();  
            }
            else
            {
              etat = E_FIN ;
            }    
            
            break; 
            
          case E_OP_SUP_EGAL:
            if (caractere_courant() == '=')
            {
              ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
             	lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
              lexeme_en_cours.nature = SUP_E;
             	etat = E_FIN ;
             	avancer_car ();  
            }
            else
            {
              etat = E_FIN ;
            }
            
            break;
            
          case E_OP_INF_EGAL:
            if (caractere_courant() == '=')
            {
              ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
             	lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
              lexeme_en_cours.nature = INF_E;
             	etat = E_FIN ;
             	avancer_car ();  
            }
            else
            {
              etat = E_FIN ;
            }
            
            break;
            
            case E_OP_DIF:
            if (caractere_courant() == '=')
            {
              ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
             	lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
              lexeme_en_cours.nature = DIF;
             	etat = E_FIN ;
             	avancer_car ();  
            }
            else
            {
              etat = E_FIN ;
            }
            
            break;
               	           
	      	case E_FIN: 
				    break ;
        }
                       
	   } 
	 }
	 


   /* --------------------------------------------------------------------- */

   // cette fonction ajoute le caractere c a la fin de la chaine s 
   // (la chaine s est donc modifiee)
 
   void ajouter_caractere (char *s, char c) 
   {
  	int l ;
  	
  	l = strlen(s) ;
  	s[l] = c ;
  	s[l+1] = '\0' ;
   } 

   /* --------------------------------------------------------------------- */

   // vaut vrai ssi c designe un caractere separateur
   int est_separateur(char c) 
   { 
      return c == ' ' || c == '\t' || c == '\n';
   }

   /* --------------------------------------------------------------------- */

   // vaut vrai ssi c designe un caractere chiffre
   int est_identificateur(char c) 
   {
      return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z');
   }
   
   int est_lettre(char c) 
   {
      return (c >= 'A' && c <= 'Z');
   }
   
   
   int est_chiffre(char c) 
   {
      return (c >= '0' && c <= '9');
   }
   
   int est_mot_cle(char c)
   {
      return (c >= 'a' && c <= 'z'); 
   }

   /* --------------------------------------------------------------------- */

   // vaut vrai ssi c designe un caractere correspondant a un symbole arithmetique
   int est_symbole(char c)  
   {
      switch (c) 
      {
         case '+':  
    		 case '-':  
    		 case '*':
    		 case '/':
    		 case '(':
    		 case ')':
    		 case '=':
    		 case ';':
         case '<':
         case '>':
         case '!':       
          
            return 1;
          
         default:
            return 0;
      } 
   }

   /* --------------------------------------------------------------------- */

   // renvoie la chaine de caracteres correspondant a la nature du lexeme
   char *Nature_vers_Chaine (Nature_Lexeme nature) 
   {
	switch (nature) 
	{
          case ENTIER: return "ENTIER";
      		case IDF: return "IDF" ;
      		case PLUS: return "PLUS" ;
      		case MOINS: return "MOINS" ;            
      		case MUL: return "MUL" ;  
      		case DIV: return "DIV" ; 
      		case PARENTH_OUVRANTE: return "PARENTH_OUVRANTE" ;  
      		case PARENTH_FERMANTE: return "PARENTH_FERMANTE" ;             
      		case AFF: return "AFF" ; 
      		case SEPINST: return "SEPINST" ; 
      		case FIN_SEQUENCE: return "FIN_SEQUENCE" ;
          case INF: return "INF";
          case INF_E: return "INF_E";
          case EGAL: return "EGAL";
          case DIF: return "DIF";
          case SUP_E: return "SUP_E";
          case SUP: return "SUP";
          case MOT_CLE: return "MOT_CLE";                
      		default: return "ERREUR" ;            
	} 
   } 

   /* --------------------------------------------------------------------- */

   // affiche a l'ecran le lexeme l
   void afficher(Lexeme l) {

      switch (l.nature) {
         case FIN_SEQUENCE: 
            break;
         default: 
            printf("(ligne %d, ", l.ligne);
            printf("colonne %d) : ",l.colonne);
	    printf("[") ;
            printf("nature = %s", Nature_vers_Chaine(l.nature)) ;
            printf(", chaine = %s, ", l.chaine) ;
            switch(l.nature) {
                 case ENTIER:
                      printf("valeur = %d", l.valeur);
                 default:
                      break;
            } ;
	    printf("]") ;
	} ;
   }

   
   


















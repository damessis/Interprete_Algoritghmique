
#ifndef __TYPE_AST__
#define __TYPE_AST__ 

typedef enum {OPERATION, VALEUR} TypeAst ;
typedef enum {N_PLUS, N_MUL, N_MOINS, N_DIV, N_AFF, N_INF, N_INF_E, N_EGAL, N_DIF, N_SUP_E, N_SUP} TypeOperateur ;

typedef struct noeud { 
	TypeAst nature ;
	TypeOperateur operateur ;
	struct noeud *gauche, *droite ;
      	int valeur ;
} NoeudAst ;

typedef NoeudAst *Ast ;

#endif  

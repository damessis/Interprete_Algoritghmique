
#include "type_ast.h"
#include "ast_construction.h"
#include "ast_parcours.h"

void analyser(char *nom_fichier, identificateur *tab_idf); 

void programme(Ast *A, identificateur *tab_idf, int a_executer);

void Rec_inst(Ast *A, identificateur *tab_idf, int a_executer);

int Rec_condition(Ast *Ac, identificateur *tab_idf);

void Rec_affectation(Ast *A, identificateur *tab_idf);

void Rec_eag(Ast *A, identificateur *tab_idf);

void Rec_seq_terme(Ast *A, identificateur *tab_idf);

void Rec_terme(Ast *A, identificateur *tab_idf);

void Rec_seq_facteur(Ast *A2,  identificateur *tab_idf);

void Rec_facteur(Ast *A1, identificateur *tab_idf);

void Rec_suite_seq_facteur(Ast A1, Ast *A2,  identificateur *tab_idf);

void Rec_suite_seq_terme(Ast A1, Ast *A2, identificateur *tab_idf);

void Rec_op1(TypeOperateur *Op);

void Rec_op2(TypeOperateur *Op);





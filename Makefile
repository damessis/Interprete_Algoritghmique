all: test_lexeme interpreteur

test_lexeme: analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o
	gcc -g -Wall -o test_lexeme analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o
	
interpreteur : interpreteur.o analyse_syntaxique.o lecture_caracteres.o analyse_lexicale.o ast_construction.o ast_parcours.o table_des_symboles.o
	gcc -g -Wall -o interpreteur interpreteur.o analyse_syntaxique.o lecture_caracteres.o analyse_lexicale.o ast_construction.o ast_parcours.o table_des_symboles.o
	
essai_ast : essai_ast.o ast_construction.o ast_parcours.o
	gcc -g -Wall -o essai_ast essai_ast.o ast_construction.o ast_parcours.o

analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h table_des_symboles.h 
	gcc -g -Wall -c analyse_lexicale.c

lecture_caracteres.o: lecture_caracteres.h lecture_caracteres.c
	gcc -g -Wall -c lecture_caracteres.c
	
analyse_syntaxique.o: analyse_syntaxique.c analyse_syntaxique.h lecture_caracteres.h analyse_lexicale.h ast_construction.h type_ast.h ast_parcours.h
	gcc -g -Wall -c analyse_syntaxique.c

test_lexeme.c: analyse_lexicale.h
	gcc -g -Wall -c test_lexeme.c
	
interpreteur.o : interpreteur.c analyse_lexicale.h analyse_syntaxique.h ast_construction.o
	gcc -g -Wall -c interpreteur.c

ast_construction.o : ast_construction.c type_ast.h
	gcc -g -Wall -c ast_construction.c
	
ast_parcours.o : ast_parcours.c type_ast.h
	gcc -g -Wall -c ast_parcours.c
	
essai_ast.o : essai_ast.c ast_construction.h ast_parcours.h
	gcc -g -Wall -c essai_ast.c
	
table_des_symboles.o : table_des_symboles.c table_des_symboles.h 
	gcc -g -Wall -c table_des_symboles.c

clean:
	rm -f  test_lexeme *.o



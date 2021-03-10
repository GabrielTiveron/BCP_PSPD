#ifndef BCP_STRUCTURE_H
#define BCP_STRUCTURE_H
#include<stdio.h>
#include<stdlib.h>

// Estrutura que define uma variável
typedef struct bpc_var{
  int index;
  int is_positive;
}BCP_VAR;

// Estrutura que define a uma cláusula
typedef struct bcp_str{
  BCP_VAR * vars;
  struct bcp_str * prox;
}BCP_STR;

// Lista de cláusulas
typedef struct bcp_lst{
  BCP_STR *clausula; 
  struct bcp_lst * prox;
}BCP_LST;

// Métodos de cláusulas
void ler_clausulas(BCP_LST*, int, int);
BCP_VAR * criar_no(int);
void insere_var(BCP_STR*, BCP_VAR*);
void insere_clausula(BCP_LST*,BCP_STR*);

#endif

#include"../header/BCP_structure.h"

void ler_clausulas(BCP_LST* head, int nmr_var, int nmr_clausula){
  head->prox = NULL;

  for(int i = 0; i < nmr_clausula; i++){
    int aux;
    BCP_STR * new_clausula = malloc(sizeof(BCP_STR));
    while(scanf("%d", &aux) == 1 && aux != 0){
      BCP_VAR * new_var = criar_no(aux);
      insere_var(new_clausula, new_var);
    }
    insere_clausula(head, new_clausula);
  }

}

BCP_VAR * criar_no(int index){
  BCP_VAR * new = malloc(sizeof(BCP_VAR));
  new->index = index > 0 ? index : (index * -1);
  new->is_positive = index > 0;

  return new;
}

void insere_var(BCP_STR* clausula, BCP_VAR*var){
  BCP_STR * new = malloc(sizeof(BCP_STR));
  new->vars = var; 
  if(clausula == NULL){
    clausula = new;
    clausula->prox = NULL;
  }
  else{
    BCP_STR * aux = clausula;
    while(aux->prox != NULL){
      aux = aux->prox;
    }
    aux->prox = new;
    new->prox = NULL;
    
  }
}

void insere_clausula(BCP_LST*head, BCP_STR * clausula){
  BCP_LST * new = malloc(sizeof(BCP_LST));
  new->clausula = clausula;
  if(head == NULL){
    head = new;
    head->prox = NULL;
  }
  else{
    BCP_LST * aux = head;
    while(aux->prox != NULL){
      aux = aux->prox;
    }
    aux->prox = new;
    new->prox = NULL;
  }
}

#include<stdlib.h>
#include "../header/BCP_structure.h"

int main(){
  int nmr_clausulas, nmr_var;

  scanf("%d %d", &nmr_var, &nmr_clausulas);

  BCP_LST *head = NULL;

  ler_clausulas(head, nmr_var, nmr_clausulas);

  return 0;
}

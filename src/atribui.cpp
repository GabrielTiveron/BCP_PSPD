#include "../inc/atribui.hpp"
#include<iostream>

using namespace std;

void para_verdadeiro(int var, Full * full) {
  int index = to_index(var);
  full->vars[index].valor = true;
  int len = full->vars[index].index;
  for(int i = 0; i < len; i++){
    int _index = full->vars[index].clausulas[i];
    full->clausulas[_index].valor = true;
  }
}

void para_falso(int var, Full * full) {
  int index = to_index(var);
  full->vars[index].valor = false;
  int len = full->vars[index].index;
  for(int i = 0; i < len; i++){
    int _index = full->vars[index].clausulas[i];
    verifica_clausula(&full->clausulas[_index], full->vars);
  }
}

void flip_variavel(int var, to_print *prnt, Full* full) {
  if(variaveis[to_index(var)].valor == true) {
    para_falso(var, full);
    para_verdadeiro(var *-1, full);
  } else {
    para_verdadeiro(var, full);
    para_falso(var * -1, full);
  }
  verifica_formula(prnt, full);
}

#include "../inc/atribui.hpp"

void para_verdadeiro(int var) {
  variaveis[to_index(var)].valor = true;
  variaveis[to_index(var * -1)].valor = false;
}

void para_falso(int var) {
  variaveis[to_index(var)].valor = false;
  variaveis[to_index(var * -1)].valor = true;
}

void flip_variavel(int var) {
  if(variaveis[to_index(var)].valor == true) {
    para_falso(var);
  } else {
    para_verdadeiro(var);
  }
}

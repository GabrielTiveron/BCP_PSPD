#include "../inc/atribui.hpp"
#include<iostream>

using namespace std;

void para_verdadeiro(int var, Variavel * variaveis_arg) {
  variaveis_arg[to_index(var)].valor = true;
  // cout << "entrou aqui -> " << to_index(var) << endl;
  //   cout << "Fuck\n";
  variaveis_arg[to_index(var * -1)].valor = false;
}

void para_falso(int var, Variavel * variaveis_arg) {
  variaveis_arg[to_index(var)].valor = false;
  variaveis_arg[to_index(var * -1)].valor = true;
}

void flip_variavel(int var, Variavel * variaveis_arg) {
  if(variaveis_arg[to_index(var)].valor == true) {
    para_falso(var, variaveis_arg);
  } else {
    para_verdadeiro(var, variaveis_arg);
  }
}

#include "../inc/global.hpp"

int to_index(int t) {
  return t > 0 ? (t - 1) : (numero_variaveis + (-1 * t) - 1);
}

Variavel *variaveis;
Clausula *clausulas;

int numero_clausulas, numero_variaveis;
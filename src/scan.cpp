#include "../inc/scan.hpp"

void scan_clausulas() {
  variaveis = (Variavel *)malloc(numero_variaveis * 2 * sizeof(Variavel));
  clausulas = (Clausula *)malloc(numero_clausulas * sizeof(Clausula));

  for (int i = 0; i < numero_clausulas; i++) {
    int valor_variavel;
    while ((cin >> valor_variavel) && (valor_variavel != 0)) {
      int indice_variavel = to_index(valor_variavel);
      clausulas[i].variaveis.push_back(&variaveis[indice_variavel]);
      variaveis[indice_variavel].clausulas.push_back(&clausulas[i]);
    }
  }
}
#include "../inc/scan.hpp"

#include <vector>
vector<int> valores;
int valores_size;
void scan_clausulas() {
  variaveis = (Variavel *)malloc(numero_variaveis * 2 * sizeof(Variavel));
  clausulas = (Clausula *)malloc(numero_clausulas * sizeof(Clausula));

  for (int i = 0; i < numero_clausulas; i++) {
    int valor_variavel;
    while ((cin >> valor_variavel) && (valor_variavel != 0)) {
      valores.push_back(valor_variavel);
      int indice_variavel = to_index(valor_variavel);
      clausulas[i].variaveis.push_back(&variaveis[indice_variavel]);
      variaveis[indice_variavel].clausulas.push_back(&clausulas[i]);
    }
  }
  valores_size = valores.size();
}

void map_clausulas(Variavel *variaveis_arg, Clausula *clausulas_arg) {
  variaveis_arg = (Variavel *)malloc(numero_variaveis * 2 * sizeof(Variavel));
  clausulas_arg = (Clausula *)malloc(numero_clausulas * sizeof(Clausula));

  if (variaveis_arg == NULL || clausulas_arg == NULL) {
    cout << "It won't fit, step bro!\n";
  } else {
    cout << "It's fine!\n";
  }

  for (int i = 0; i < numero_clausulas; i++) {
    for (int j = 0; j < valores_size; j++) {
      // cout << valores_size << " " << j << " " <<f <<" donk\n";
      int indice_variavel = to_index(valores[i]);
      clausulas_arg[i].variaveis.push_back(&variaveis_arg[indice_variavel]);
      variaveis_arg[indice_variavel].clausulas.push_back(&clausulas_arg[i]);
    }
  }
}
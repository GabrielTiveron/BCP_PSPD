#include "../inc/verifica.hpp"

void verifica_clausula() {
  bool resultado_final = true;
  for (int i = 0; i < numero_clausulas; i++) {
    bool resultado_clausula = false;
    int tamanho = clausulas[i].variaveis.size();
    for (int j = 0; j < tamanho; j++) {
      resultado_clausula =
      resultado_clausula | clausulas[i].variaveis[j]->valor;
      if (resultado_clausula) break;
    }
    if (resultado_clausula) {
      clausulas[i].valor = resultado_clausula;
    }
    resultado_final = (resultado_final && resultado_clausula);
    if (!resultado_final) break;
  }

//   cout << resultado_final << endl;
}

void verifica_todas_as_clausula() {
  bool resultado_final = true;
  for (int i = 0; i < numero_clausulas; i++) {
    bool resultado_clausula = false;
    int tamanho = clausulas[i].variaveis.size();
    for (int j = 0; j < tamanho; j++) {
      resultado_clausula =
      resultado_clausula | clausulas[i].variaveis[j]->valor;
      if (resultado_clausula) break;
    }
    if (resultado_clausula) {
      clausulas[i].valor = resultado_clausula;
    }
  }
}

void reavalia_variavel(int var) {
    // variaveis[to_index(var)].clausulas
}
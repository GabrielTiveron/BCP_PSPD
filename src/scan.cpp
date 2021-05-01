#include "../inc/scan.hpp"

void scan_clausulas() {
  variaveis = (Variavel *)malloc(numero_variaveis * 2 * sizeof(Variavel));
  clausulas = (Clausula *)malloc(numero_clausulas * sizeof(Clausula));
  //std::cout << "entrou nmr_var = " << numero_variaveis << '\n';
  for(int i = 0; i < 2*numero_variaveis; i++){
   variaveis[i] = Variavel();
  }
  for (int i = 0; i < numero_clausulas; i++) {
    clausulas[i] = Clausula();
    int valor_variavel;
    //cout << "alocou" << '\n';
    while ((cin >> valor_variavel) && (valor_variavel != 0)) {
      //cout << "valor " << valor_variavel  << endl;
      int indice_variavel = to_index(valor_variavel);
      //cout << "dps indice " << indice_variavel << endl;
      Variavel * v = &variaveis[indice_variavel];
      //cout << "alias var" << endl;
      clausulas[i].variaveis.push_back(indice_variavel);
      //cout << "add to clause " << v->index << endl;
      v->clausulas.push_back(i);
      //cout << "add to var " << v->index << endl;
      v->index++;
      clausulas[i].index++;
    }
  }
}

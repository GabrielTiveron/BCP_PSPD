#include <iostream>
#include <string>
#include <vector>

#include "../inc/global.hpp"

using namespace std;

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

void para_verdadeiro(int var){
  variaveis[to_index(var)].valor = true;
  variaveis[to_index(var * -1)].valor = false;
}

void verifica_clausula(){
  bool resultado_final = true;
  for(int i = 0; i < numero_clausulas; i++){
    int tamanho = clausulas[i].variaveis.size();
    bool resultado_clausula = false;
    for(int j = 0; j < tamanho; j++){
      resultado_clausula = resultado_clausula | clausulas[i].variaveis[j]->valor;
      if(resultado_clausula)break;
    }
    if(resultado_clausula){
      clausulas[i].valor = resultado_clausula;
    }
    resultado_final = resultado_final & resultado_clausula;
    if(!resultado_final)break;
  }

  cout << resultado_final << endl;

}

void comando_full(){
  for(int i = 0; i < numero_variaveis; i++){
    int var;
    cin >> var;
    para_verdadeiro(var);
  }
  verifica_clausula();
}

void comando_flip(){

}

int main() {
  int numero_clausulas, numero_variaveis;
  cin >> numero_variaveis >> numero_clausulas;

  scan_clausulas();

  string comando;

  while(cin >> comando){
    if(comando.compare("full") == 0){
      comando_full();
    }
    else if(comando.compare("flip") == 0){
      comando_flip();
    }
  }

}

#include "../inc/verifica.hpp"

bool verifica_clausula(Clausula *c) {
  bool resultado_clausula = false;
  int tam = c->variaveis.size();
  for(int i = 0; i < tam; i++){
    resultado_clausula = resultado_clausula || c->variaveis[i]->valor;
    if (resultado_clausula) break;
  }

  c->valor = resultado_clausula;

  return c->valor;
}

void verifica_todas_as_clausula() {
  bool resultado_final = true;
  int *falsa = (int*) malloc(numero_clausulas * sizeof(int)), cont = 0;
  for (int i = 0; i < numero_clausulas; i++) {
    bool res = verifica_clausula(&clausulas[i]);
    resultado_final = resultado_final && res;
    if(!clausulas[i].valor)falsa[cont++] = i;
  }
  if(resultado_final)cout << "SAT" << endl;
  else{
    cout << "[" << cont << " clausulas falsas]";
    for(int i = 0; i < cont; i++)
      cout << " " << falsa[i];

    cout << endl;
  }
}

void verifica_formula(){
  bool resultado_final = true;
  int *falsa = (int*) malloc(numero_clausulas * sizeof(int)), cont = 0;
  for (int i = 0; i < numero_clausulas; i++) {
    resultado_final = resultado_final && clausulas[i].valor;
    if(!clausulas[i].valor)falsa[cont++] = i;
  }
  
  if(resultado_final)cout << "SAT" << endl;
  else{
    cout << "[" << cont << " clausulas falsas]";
    for(int i = 0; i < cont; i++)
      cout << " " << falsa[i];

    cout << endl;
  }

}

void reavalia_variavel(int var) {
  int index1 = to_index(var);
  int index2 = to_index(var * -1);
  int total_clausulas_1 = variaveis[index1].clausulas.size();
  int total_clausulas_2 = variaveis[index2].clausulas.size();

  for(int i = 0; i < total_clausulas_1; i++){
    variaveis[index1].clausulas[i]->valor = verifica_clausula(variaveis[index1].clausulas[i]);
  }

  for(int i = 0; i < total_clausulas_2; i++){
    variaveis[index2].clausulas[i]->valor = verifica_clausula(variaveis[index2].clausulas[i]);
  }

  verifica_formula();
}

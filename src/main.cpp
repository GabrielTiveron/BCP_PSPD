#include <iostream>
#include <string>
#include <vector>
#include <thread>

#include "../inc/scan.hpp"
#include "../inc/global.hpp"
#include "../inc/atribui.hpp"
#include "../inc/verifica.hpp"

#define MAX_THREAD 2

using namespace std;

int index = 0, index_flip = 0, qtd_thread = 0, index_print = 0;

void print_vars(){
  //cout << "==============================" << endl;
  for(int i = 0; i < numero_variaveis*2; i++){
    //cout << from_index(i) << " : " << variaveis[to_index(from_index(i))].valor << endl;
  }
  //cout << "==============================" << endl;
}

void solve_cmd(Full cmd, to_print* prnt){
  for(int i = 0; i < numero_variaveis; i++){
    para_verdadeiro(cmd.true_vars[i]);
  }
  
  verifica_todas_as_clausula(prnt);

  int qtd_flips = cmd.flips.size();

  for(int i = 0; i < qtd_flips-1;i++){
    flip_variavel(cmd.flips[i].var);
    reavalia_variavel(cmd.flips[i].var, prnt);
  }

  qtd_thread--;

}

int main() {
  cin >> numero_variaveis >> numero_clausulas;
  scan_clausulas();

  string comando;

  while (cin >> comando) {
    if (comando.compare("full") == 0) {
      fulls.push_back(Full());
      fulls[index].flips.push_back(Flip());
      index_flip = 0;
      for(int i = 0;i < numero_variaveis;i++){
        int var;
        cin >> var;
        fulls[index].true_vars.push_back(var);
      }
      index++;
    } else if (comando.compare("flip") == 0) {
      int var;
      cin >> var;
      fulls[index-1].flips.push_back(Flip());
      fulls[index-1].flips[index_flip++].var = var;
    }
  }
  
  vector<thread> t;
  metadata = new vector<to_print>();
  for(int i = 0; i < index; i++){
    metadata->push_back(new to_print());
    solve_cmd(fulls[i], &metadata[i]);

    // TODO paralelizar a solução  

  }
  free(variaveis);
  free(clausulas);

  cout << "teste" << endl;
  
  for(int i = 0; i < index; i++){
    cout << "for " << i << endl;
  //  t[i].join();
    if(metadata[i]->sat){
      cout << "SAT" << endl;
    }else{
      cout << "else" << endl;
      cout << "[" << metadata[i].qtd_clauses << "clausulas falsas]";
      for(int j = 0; j < metadata[i].qtd_clauses; j++){
        cout << " " << metadata[i].clauses[j];
      }
      cout << endl;
    }
  }

  // TODO printar solução

  return 0;

}

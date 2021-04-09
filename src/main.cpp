#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "../inc/atribui.hpp"
#include "../inc/global.hpp"
#include "../inc/scan.hpp"
#include "../inc/verifica.hpp"

#define MAX_THREAD 2

using namespace std;

int index = 0, index_flip = 0, qtd_thread = 0, index_print = 0;

void print_vars() {
  // cout << "==============================" << endl;
  for (int i = 0; i < numero_variaveis * 2; i++) {
    // cout << from_index(i) << " : " <<
    // variaveis[to_index(from_index(i))].valor << endl;
  }
  // cout << "==============================" << endl;
}

void solve_cmd(Full cmd, Metadata* ptr_met) {
  for (int i = 0; i < numero_variaveis; i++) {
    para_verdadeiro(cmd.true_vars[i]);
  }
  ptr_met->mtdt.push_back(new to_print());

  verifica_todas_as_clausula(ptr_met->mtdt[ptr_met->indexes++]);

  int qtd_flips = cmd.flips.size();

  for (int i = 0; i < qtd_flips - 1; i++) {
    flip_variavel(cmd.flips[i].var);
    ptr_met->mtdt.push_back(new to_print());
    reavalia_variavel(cmd.flips[i].var, ptr_met->mtdt[ptr_met->indexes++]);
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
      for (int i = 0; i < numero_variaveis; i++) {
        int var;
        cin >> var;
        fulls[index].true_vars.push_back(var);
      }
      index++;
    } else if (comando.compare("flip") == 0) {
      int var;
      cin >> var;
      fulls[index - 1].flips.push_back(Flip());
      fulls[index - 1].flips[index_flip++].var = var;
    }
  }

  vector<thread> t;
  for (int i = 0; i < index; i++) {
    metadata.push_back(new Metadata());
    // t.push_back(move(thread(solve_cmd, fulls[i], metadata[i])));
    solve_cmd(fulls[i], metadata[i]);
  }
  // for (int i = 0; i < index; i++) {
  //   t[i].join();
  // }
  free(variaveis);
  free(clausulas);

  for (int j = 0; j < index; j++) {
    for (int i = 0; i < metadata[j]->indexes; i++) {
      if (metadata[j]->mtdt[i]->sat) {
        cout << "SAT" << endl;
      } else {
        cout << "[" << metadata[j]->mtdt[i]->qtd_clauses
             << " clausulas falsas]";
        for (int k = 0; k < metadata[j]->mtdt[i]->qtd_clauses; k++) {
          cout << " " << metadata[j]->mtdt[i]->clauses[k];
        }
        cout << endl;

        cout << "[lits]";
        // int lits_size = metadata[j]->mtdt[i]->lits.size();
        // for (map<const int, int>::iterator k =
        //          metadata[j]->mtdt[i]->lits.begin();
        //      k != metadata[j]->mtdt[i]->lits.end(); ++k) {
        //   cout << " " << k->first;
        // }
        cout << endl;
      }
    }
  }

  // TODO printar solução

  return 0;
}

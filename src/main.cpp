#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "../inc/atribui.hpp"
#include "../inc/global.hpp"
#include "../inc/scan.hpp"
#include "../inc/verifica.hpp"

//#define MAX_THREAD 2

using namespace std;

int index_ = 0, index_flip = 0, qtd_thread = 0, index_print = 0;
pthread_t main_thread;

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

  verifica_todas_as_clausula(ptr_met->mtdt[ptr_met->indexes++]);  // n*m

  int qtd_flips = cmd.flips.size();

  for (int i = 0; i < qtd_flips - 1; i++) {
    flip_variavel(cmd.flips[i].var);
    ptr_met->mtdt.push_back(new to_print());
    reavalia_variavel(cmd.flips[i].var,
                      ptr_met->mtdt[ptr_met->indexes++]);  // 2n*m
  }

  pthread_kill(main_thread, SIGUSR1);
  // qtd_thread--;
}

bool sort_lits(const pair<int, int>& a, pair<int, int>& b) {
  return a.second != b.second ? a.second > b.second
                              : abs(a.first) > abs(b.first);
}

void free_thread(int sig) { qtd_thread--; }

int main(int argc, char** argv) {
  main_thread = pthread_self();
  signal(SIGUSR1, free_thread);

  int MAX_THREAD = atoi(argv[1]);
  cin >> numero_variaveis >> numero_clausulas;
  scan_clausulas();

  string comando;

  while (cin >> comando) {
    if (comando.compare("full") == 0) {
      fulls.push_back(Full());
      fulls[index_].flips.push_back(Flip());
      index_flip = 0;
      for (int i = 0; i < numero_variaveis; i++) {
        int var;
        cin >> var;
        fulls[index_].true_vars.push_back(var);
      }
      index_++;
    } else if (comando.compare("flip") == 0) {
      int var;
      cin >> var;
      fulls[index_ - 1].flips.push_back(Flip());
      fulls[index_ - 1].flips[index_flip++].var = var;
    }
  }

  vector<thread> t;
  for (int i = 0; i < index_; i++) {
    metadata.push_back(new Metadata());
    while (qtd_thread > MAX_THREAD) {
    }
    qtd_thread++;
    thread th(solve_cmd, fulls[i], metadata[i]);  // 3(n*m)
    t.push_back(move(th));
    // solve_cmd(fulls[i], metadata[i]);
  }
  for (thread& tt : t) {
    if (tt.joinable()) tt.join();
  }
  free(variaveis);
  free(clausulas);

  for (int j = 0; j < index_; j++) {                  // k  k*(y*(m+n*log(n)+n))
    for (int i = 0; i < metadata[j]->indexes; i++) {  // m
      if (metadata[j]->mtdt[i]->sat) {
        cout << "SAT" << endl;
      } else {
        cout << "[" << metadata[j]->mtdt[i]->qtd_clauses
             << " clausulas falsas]";
        for (int k = 0; k < metadata[j]->mtdt[i]->qtd_clauses; k++) {  // m
          cout << " " << metadata[j]->mtdt[i]->clauses[k];
        }
        cout << endl;

        cout << "[lits]";
        sort(metadata[j]->mtdt[i]->lits.begin(),
             metadata[j]->mtdt[i]->lits.end(), sort_lits);  // nlog(n)
        for (pair<int, int> it : metadata[j]->mtdt[i]->lits) {
          cout << " " << it.first;
        }
        cout << endl;
      }
    }
  }

  // TODO printar solução

  return 0;
}

#include <pthread.h>
#include <unistd.h>

#include <csignal>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>
#include <vector>

#include "../inc/atribui.hpp"
#include "../inc/global.hpp"
#include "../inc/scan.hpp"
#include "../inc/verifica.hpp"

#define MAX_THREAD 2

using namespace std;
void copy_dynamic_variaveis(Variavel *src, Variavel **dest) {
  *dest = (Variavel *)malloc(numero_variaveis * sizeof(Variavel));

  for (int i = 0; i < numero_variaveis; i++) {
    *dest[i] = src[i];
  }
}

void copy_dynamic_clausulas(Clausula *src, Clausula **dest) {
  *dest = (Clausula *)malloc(numero_clausulas * sizeof(Clausula));

  for (int i = 0; i < numero_clausulas; i++) {
    *dest[i] = src[i];
  }
}

int index_ = 0, index_flip = 0, qtd_thread = 0, index_print = 0,
    index_consumer = 0;
pthread_t main_thread;

void print_vars() {
  // cout << "==============================" << endl;
  for (int i = 0; i < numero_variaveis * 2; i++) {
    // cout << from_index(i) << " : " <<
    // variaveis[to_index(from_index(i))].valor << endl;
  }
  // cout << "==============================" << endl;
}

void solve_cmd(Full *cmd, Metadata *ptr_met) {
  // for (int i = 0; i < numero_variaveis; i++) {
  //   para_verdadeiro(cmd->true_vars[i]);
  // }
  // cout << "hehe" << "\n";
  ptr_met->mtdt.push_back(new to_print());
  ptr_met->indexes = 0;
  // std::cout << "/* message */" << '\n';

  verifica_formula(ptr_met->mtdt[ptr_met->indexes++], cmd);
  // std::cout << "/* message */" << '\n';

  int qtd_flips = cmd->flips.size();

  for (int i = 0; i < qtd_flips - 1; i++) {
    ptr_met->mtdt.push_back(new to_print());
    flip_variavel(cmd->flips[i].var, ptr_met->mtdt[ptr_met->indexes++], cmd);
    // reavalia_variavel(cmd.flips[i].var, ptr_met->mtdt[ptr_met->indexes++]);
  }
  // delete[] cmd->clausulas;
  // delete[] cmd->vars;
  // if(h > 0)
  //    delete(cmd);
  // cout << "shnk\n";
  pthread_kill(main_thread, SIGUSR1);

  // cout << "seageragnk\n";
}

bool sort_lits(const pair<int, int> &a, pair<int, int> &b) {
  return a.second != b.second ? a.second > b.second
                              : abs(a.first) > abs(b.first);
}

void dec_thread(int h) {
  // std::cout << "recebeu sinal = " << qtd_thread-- << '\n';
  qtd_thread--;
}

int main(int argc, char **argv) {
  main_thread = pthread_self();
  signal(SIGUSR1, dec_thread);
  // int MAX_THREAD = atoi(argv[1]);
  cin >> numero_variaveis >> numero_clausulas;
  scan_clausulas();
  // cout << "Dps scan" << endl;
  string comando;
  vector<thread> consumers;
  bool after_second = false;

  while (cin >> comando) {
    if (comando[1] == 'u') {
      // if(after_second && qtd_thread < MAX_THREAD){
      //   std::cout << "threadou" << '\n';
      //  metadata.push_back(new Metadata());
      //  thread th(solve_cmd, &fulls[index_consumer],
      //  metadata[index_consumer]); index_consumer++;
      //  cout << "index_consumer: " << index_consumer << endl;
      //  qtd_thread++;
      //  consumers.push_back(move(th));
      // }
      fulls.push_back(Full());
      // cout << "fick\n";
      fulls[index_].flips.push_back(Flip());
      index_flip = 0;
      fulls[index_].vars =
          (Variavel *)malloc(numero_variaveis * sizeof(Variavel) * 2);
      for (int i = 0; i < numero_variaveis; i++) {
        fulls[index_].vars[i] = variaveis[i];
      }
      fulls[index_].clausulas =
          (Clausula *)malloc(numero_clausulas * sizeof(Clausula));
      for (int i = 0; i < numero_clausulas; i++) {
        fulls[index_].clausulas[i] = clausulas[i];
      }
  //     // copy_dynamic_variaveis(variaveis, &fulls[index_].vars);
  //     // copy_dynamic_clausulas(clausulas, &fulls[index_].clausulas);
  //     // fulls[index_].vars = variaveis;
  //     // fulls[index_].clausulas = clausulas;
      for (int i = 0; i < numero_variaveis; i++) {
        int var;
        cin >> var;

        para_verdadeiro(var, &fulls[index_]);

      }
      after_second = true;
      index_++;
    } else if (comando[1] == 'l') {
      int var;
      cin >> var;
      fulls[index_ - 1].flips.push_back(Flip());
      fulls[index_ - 1].flips[index_flip++].var = var;
    }
  }
  
  // cout << "Dps full e flip" << '\n';
  for (int i = index_consumer; i < index_; i++) {
    metadata.push_back(new Metadata());
    while(qtd_thread > MAX_THREAD){
      usleep(1);
    }
   //   std::cout << "mais uma thread = " << qtd_thread++ << "\nI = " << i <<
  //  "\nMax = " << index_ << '\n';
    qtd_thread++;
    thread th(solve_cmd, &fulls[i], metadata[i]);
    consumers.push_back(move(th));
    //solve_cmd(&fulls[i], metadata[i]);
  }
  for(thread& tt: consumers) {
   if(tt.joinable())
     tt.join();
  }
  // cout << "Finished processing" << '\n';
  free(variaveis);
  free(clausulas);

  for (int j = 0; j < index_; j++) {
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
        sort(metadata[j]->mtdt[i]->lits.begin(),
        metadata[j]->mtdt[i]->lits.end(), sort_lits); for(pair<int,int> it:
        metadata[j]->mtdt[i]->lits){
          cout << " " << it.first;
        }
        cout << endl;
      }
    }
  }

  // TODO printar solução

  return 0;
}

#include "../inc/atribui.hpp"

#include <unistd.h>

#include <iostream>

using namespace std;

void work_verdadeiro(int len, Full* full, int index, int ind_flip) {
  // cout << "lol\n";
  for (int i = 0; i < len; i++) {
    int _index = full->vars[index].clausulas[i];
    full->clausulas[_index].valor = true;
    full->clausulas[_index].last_update = ind_flip;
  }
  pthread_kill(main_thread, SIGUSR1);
}

void work_falso(int len, Full* full, int index, int ind_flip) {
  for (int i = 0; i < len; i++) {
    int _index = full->vars[index].clausulas[i];
    verifica_clausula(&full->clausulas[_index], full->vars);
    if(full->clausulas[_index].last_update != ind_flip)
      verifica_clausula(&full->clausulas[_index], full->vars);
  }
  pthread_kill(main_thread, SIGUSR1);
}

void para_verdadeiro_p(int var, Full* full, int ind_flip) {
  // cout << "lol2\n";
  int index = to_index(var);
  full->vars[index].valor = true;
  int len = full->vars[index].index;

  while (qtd_thread > MAX_THREAD) {
    usleep(1);
  }
  qtd_thread++;

  thread th(work_verdadeiro, len, full, index, ind_flip);
  workers.push_back(move(th));
}

void para_falso_p(int var, Full* full,int ind_flip) {
  int index = to_index(var);
  full->vars[index].valor = false;
  int len = full->vars[index].index;

  while (qtd_thread > MAX_THREAD) {
    usleep(1);
  }
  qtd_thread++;

  thread th(work_falso, len, full, index, ind_flip);
  workers.push_back(move(th));
}


void para_verdadeiro(int var, Full * full, int ind_flip) {
  int index = to_index(var);
  full->vars[index].valor = true;
  int len = full->vars[index].index;
  for(int i = 0; i < len; i++){
    int _index = full->vars[index].clausulas[i];
    full->clausulas[_index].valor = true;
    full->clausulas[_index].last_update = ind_flip;
  }
}

void para_falso(int var, Full * full,int ind_flip) {
  int index = to_index(var);
  full->vars[index].valor = false;
  int len = full->vars[index].index;
  for(int i = 0; i < len; i++){
    int _index = full->vars[index].clausulas[i];
    if(full->clausulas[_index].last_update != ind_flip)
      verifica_clausula(&full->clausulas[_index], full->vars);
  }
}

void flip_variavel(int var, to_print *prnt, Full* full, int ind_flip) {
  if(full->vars[to_index(var)].valor == true) {
    para_verdadeiro(var *-1, full,ind_flip);
    para_falso(var, full,ind_flip);
  } else {
    para_verdadeiro(var, full,ind_flip);
    para_falso(var * -1, full,ind_flip);
  }
  verifica_formula(prnt, full);
}

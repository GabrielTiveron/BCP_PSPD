#include "../inc/verifica.hpp"

bool verifica_clausula(Clausula *c) {
  bool resultado_clausula = false;
  int tam = c->variaveis.size();
  for (int i = 0; i < tam; i++) {
    resultado_clausula = resultado_clausula || c->variaveis[i]->valor;
    if (resultado_clausula) break;
  }

  c->valor = resultado_clausula;

  return c->valor;
}

void make_lits(to_print *prnt, Variavel * variaveis_arg) {
  for (int i = 0; i < numero_variaveis * 2; i++) {
    if (!variaveis_arg[i].valor) {
      int qtd_falsa = 0;
      int numero_de_clausulas = variaveis_arg[i].clausulas.size();

      for (int j = 0; j < numero_de_clausulas; j++) {
        if (!variaveis_arg[i].clausulas[j]->valor) {
          //variaveis[i].qtd_clausulas_falsas++;
          qtd_falsa++;
        }
      }
      if(qtd_falsa > 0)
        prnt->lits.push_back(pair<int, int>(from_index(i), qtd_falsa));
    }
  }
}

void verifica_todas_as_clausula(to_print *prnt, Variavel * variaveis_arg, Clausula * clausulas_arg) {
  bool resultado_final = true;
  int *falsa = (int *)malloc(numero_clausulas * sizeof(int)), cont = 0;
  for (int i = 0; i < numero_clausulas; i++) {
    bool res = verifica_clausula(&clausulas_arg[i]);
    resultado_final = resultado_final && res;
    if (!clausulas_arg[i].valor) falsa[cont++] = i;
  }
  if (resultado_final) {
    prnt->sat = true;
  } else {
    prnt->sat = false;
    prnt->qtd_clauses = cont;
    for (int i = 0; i < cont; i++) {
      prnt->clauses.push_back(falsa[i]);
    }

    make_lits(prnt, variaveis_arg);

  }
  free(falsa);
}

void verifica_formula(to_print *prnt, Variavel * variaveis_arg, Clausula * clausulas_arg) {
  bool resultado_final = true;
  int *falsa = (int *)malloc(numero_clausulas * sizeof(int)), cont = 0;
  for (int i = 0; i < numero_clausulas; i++) {
    resultado_final = resultado_final && clausulas_arg[i].valor;
    if (!clausulas_arg[i].valor) falsa[cont++] = i;
  }

  if (resultado_final) {
    // cout << "SAT" << endl;
    prnt->sat = true;
  } else {
    prnt->sat = false;
    prnt->qtd_clauses = cont;
    // cout << "[" << cont << " clausulas falsas]";
    for (int i = 0; i < cont; i++) {
      // cout << " " << falsa[i];
      prnt->clauses.push_back(falsa[i]);
    }

    make_lits(prnt, variaveis_arg);

    // cout << endl;
  }

  free(falsa);
}

void reavalia_variavel(int var, to_print *prnt, Variavel * variaveis_arg, Clausula * clausulas_arg) {
  int index1 = to_index(var);
  int index2 = to_index(var * -1);
  int total_clausulas_1 = variaveis_arg[index1].clausulas.size();
  int total_clausulas_2 = variaveis_arg[index2].clausulas.size();

  for (int i = 0; i < total_clausulas_1; i++) {
    variaveis_arg[index1].clausulas[i]->valor =
        verifica_clausula(variaveis_arg[index1].clausulas[i]);
  }

  for (int i = 0; i < total_clausulas_2; i++) {
    variaveis_arg[index2].clausulas[i]->valor =
        verifica_clausula(variaveis_arg[index2].clausulas[i]);
  }

  verifica_formula(prnt, variaveis_arg, clausulas_arg);
}

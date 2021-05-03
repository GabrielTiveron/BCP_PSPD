#include "../inc/verifica.hpp"

bool verifica_clausula(Clausula *c, vector<Variavel> variaveis) {
  bool resultado_clausula = false;
  int tam = c->index;
  for (int i = 0; i < tam; i++) {
    int var = c->variaveis[i];
    resultado_clausula = resultado_clausula || variaveis[var].valor;
    if (resultado_clausula) break;
  }

  c->valor = resultado_clausula;

  return c->valor;
}

void make_lits(to_print *prnt, Full * f) {
  for (int i = 0; i < numero_variaveis * 2; i++) {
    if (!f->vars[i].valor) {
      int qtd_falsa = 0;
      int numero_de_clausulas = f->vars[i].index;

      for (int j = 0; j < numero_de_clausulas; j++) {
        int cla_index = f->vars[i].clausulas[j];
        if (!clausulas[cla_index].valor) {
          //variaveis[i].qtd_clausulas_falsas++;
          qtd_falsa++;
        }
      }
      if(qtd_falsa > 0)
        prnt->lits.push_back(pair<int, int>(from_index(i), qtd_falsa));
    }
  }
}

void verifica_todas_as_clausula(to_print *prnt, Full * full) {
  bool resultado_final = true;
  int *falsa = (int *)malloc(numero_clausulas * sizeof(int)), cont = 0;
  for (int i = 0; i < numero_clausulas; i++) {
    bool res = verifica_clausula(&full->clausulas[i], full->vars);
    resultado_final = resultado_final && res;
    if (!(full->clausulas[i].valor)) falsa[cont++] = i;
  }
  if (resultado_final) {
    prnt->sat = true;
  } else {
    prnt->sat = false;
    prnt->qtd_clauses = cont;
    for (int i = 0; i < cont; i++) {
      prnt->clauses.push_back(falsa[i]);
    }

    make_lits(prnt, full);

  }
  free(falsa);
}

void verifica_formula(to_print *prnt, Full * full) {
  bool resultado_final = true;
  int *falsa = (int *)malloc(numero_clausulas * sizeof(int)), cont = 0;
  for (int i = 0; i < numero_clausulas; i++) {
    resultado_final = resultado_final && full->clausulas[i].valor;
    if (!(full->clausulas[i].valor)) falsa[cont++] = i;
  }

  if (resultado_final) {
    prnt->sat = true;
  } else {
    prnt->sat = false;
    prnt->qtd_clauses = cont;
    for (int i = 0; i < cont; i++) {
      prnt->clauses.push_back(falsa[i]);
    }

    make_lits(prnt, full);
  }

  free(falsa);
}

// void reavalia_variavel(int var, to_print *prnt) {
//   int index1 = to_index(var);
//   int index2 = to_index(var * -1);
//   int total_clausulas_1 = variaveis[index1].index;
//   int total_clausulas_2 = variaveis[index2].index;
//
//   for (int i = 0; i < total_clausulas_1; i++) {
//     variaveis[index1].clausulas[i]->valor =
//         verifica_clausula(variaveis[index1].clausulas[i]);
//   }
//
//   for (int i = 0; i < total_clausulas_2; i++) {
//     variaveis[index2].clausulas[i]->valor =
//         verifica_clausula(variaveis[index2].clausulas[i]);
//   }
//
//   verifica_formula(prnt);
// }

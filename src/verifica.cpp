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

bool compare_lits(int a, int b) {
  return variaveis[to_index(a)].clausulas.size() <
         variaveis[to_index(b)].clausulas.size();
}

void make_lits(to_print *prnt) {
  for (int i = 0; i < numero_variaveis * 2; i++) {
    // cout << "fonk " << from_index(i) << endl;
    if (!variaveis[i].valor) prnt->lits.push_back(from_index(i));
  }

  sort(prnt->lits.begin(), prnt->lits.end(), compare_lits);
}

void verifica_todas_as_clausula(to_print *prnt) {
  // cout << "entrou verf claus" << endl;
  bool resultado_final = true;
  int *falsa = (int *)malloc(numero_clausulas * sizeof(int)), cont = 0;
  // cout << "dps malloc" << endl;
  for (int i = 0; i < numero_clausulas; i++) {
    bool res = verifica_clausula(&clausulas[i]);
    resultado_final = resultado_final && res;
    if (!clausulas[i].valor) falsa[cont++] = i;
  }
  // cout << "dps for" << endl;
  if (resultado_final) {
    //    cout << "SAT" << endl;
    prnt->sat = true;
  } else {
    prnt->sat = false;
    prnt->qtd_clauses = cont;
    //  cout << "[" << cont << " clausulas falsas]";
    for (int i = 0; i < cont; i++) {
      //  cout << " " << falsa[i];
      prnt->clauses.push_back(falsa[i]);
    }

    make_lits(prnt);

    // cout << endl;
  }
  free(falsa);
}

void verifica_formula(to_print *prnt) {
  bool resultado_final = true;
  int *falsa = (int *)malloc(numero_clausulas * sizeof(int)), cont = 0;
  for (int i = 0; i < numero_clausulas; i++) {
    resultado_final = resultado_final && clausulas[i].valor;
    if (!clausulas[i].valor) falsa[cont++] = i;
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

    make_lits(prnt);

    // cout << endl;
  }

  free(falsa);
}

void reavalia_variavel(int var, to_print *prnt) {
  int index1 = to_index(var);
  int index2 = to_index(var * -1);
  int total_clausulas_1 = variaveis[index1].clausulas.size();
  int total_clausulas_2 = variaveis[index2].clausulas.size();

  for (int i = 0; i < total_clausulas_1; i++) {
    variaveis[index1].clausulas[i]->valor =
        verifica_clausula(variaveis[index1].clausulas[i]);
  }

  for (int i = 0; i < total_clausulas_2; i++) {
    variaveis[index2].clausulas[i]->valor =
        verifica_clausula(variaveis[index2].clausulas[i]);
  }

  verifica_formula(prnt);
}

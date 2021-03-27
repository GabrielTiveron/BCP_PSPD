#include <iostream>
#include <string>
#include <vector>

#include "../inc/scan.hpp"
#include "../inc/global.hpp"
#include "../inc/atribui.hpp"
#include "../inc/verifica.hpp"

using namespace std;


void comando_full() {
  for (int i = 0; i < numero_variaveis; i++) {
    int var;
    cin >> var;
    para_verdadeiro(var);
  }
  verifica_todas_as_clausula();
}

void comando_flip() {
  int to_flip;
  cin >> to_flip;
  flip_variavel(to_flip);
  reavalia_variavel(to_flip);
  
}

int main() {
  scanf("%d %d", &numero_variaveis, &numero_clausulas);
  scan_clausulas();

  string comando;

  while (cin >> comando) {
    if (comando.compare("full") == 0) {
      comando_full();
    } else if (comando.compare("flip") == 0) {
      comando_flip();
    }
  }
}

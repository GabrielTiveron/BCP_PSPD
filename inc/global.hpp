#ifndef _GOBAL_
#define _GOBAL_
#include <vector>

using namespace std;

struct Variavel;
struct Clausula;

typedef struct Variavel {
  vector<Clausula *> clausulas;
  bool valor;
} Variavel;

typedef struct Clausula {
  vector<Variavel *> variaveis;
  bool valor;
} Clausula;

extern int to_index(int t);

extern Variavel *variaveis;
extern Clausula *clausulas;

extern int numero_clausulas, numero_variaveis;

#endif
#ifndef _GOBAL_
#define _GOBAL_
#include <vector>
#include <unordered_map>
#include <map>
#include <utility> 

using namespace std;

struct Variavel;
struct Clausula;

typedef struct Variavel {
  vector<Clausula *> clausulas;
  int qtd_clausulas_falsas = 0;
  bool valor;
} Variavel;

typedef struct Clausula {
  vector<Variavel *> variaveis;
  bool valor;
} Clausula;

typedef struct Flip{
  int var;
}Flip;

typedef struct full{
  vector<int> true_vars;
  vector<Flip> flips;
  Variavel *variaveis;
  Clausula *clausulas;
}Full;

typedef struct to_print{
  int qtd_clauses;
  vector<int> clauses;
  vector<pair<int, int>> lits;
  bool sat = false;
  int index = 0;
}to_print;

typedef struct metadata{
  vector<to_print*> mtdt;
  int indexes;
}Metadata;

extern int to_index(int t);
extern int from_index(int t);

extern Variavel *variaveis;
extern Clausula *clausulas;
extern vector<Full> fulls;
extern vector<Metadata*> metadata;

extern int numero_clausulas, numero_variaveis;

#endif

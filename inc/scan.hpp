#ifndef _SCAN_
#define _SCAN_
#include <iostream>
#include "../inc/global.hpp"
using namespace std;
extern vector<int> valores;
extern int valores_size;
void scan_clausulas();

void map_clausulas(Variavel * variaveis_arg, Clausula * clausulas_arg);

#endif
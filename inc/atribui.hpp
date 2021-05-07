#ifndef _ATRIBUI_
#define _ATRIBUI_
#include "global.hpp"
#include "verifica.hpp"
#include <pthread.h>
#include <csignal>

using namespace std;

void para_verdadeiro(int var, Full*full, int);

void para_verdadeiro_p(int var, Full*full, int);

void para_falso_p(int var, Full*full, int);

void para_falso(int var, Full*full, int);

void flip_variavel(int var,to_print *prnt,Full*full, int);

#endif

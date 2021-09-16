#ifndef _MONTADOR_CUBO
#define _MONTADOR_CUBO
#include "def_cubo.h"
typedef struct{
    char idLado;
    char direcao;
} Movimento;

 Movimento* montaCubo(Cubomagico* cubo);







#endif
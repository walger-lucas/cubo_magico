#include <stdlib.h>
#include "def_cubo.h"

struct cubomagico {

    char lados[54];
    char ladoAtual;
    int movimentosFeitos;

};

Cubomagico* criaCubo(char pecas[54])
{
    Cubomagico* cubo = (Cubomagico*) malloc(sizeof(Cubomagico));
    cubo->ladoAtual= pecas[0];
    int i;
    for(i=0;i<54;i++)
        (*cubo).lados[i]=pecas[i];
    cubo->movimentosFeitos=0;
    return cubo;
}
void destroiCubo(Cubomagico* cubo)
{
    free(cubo);
}





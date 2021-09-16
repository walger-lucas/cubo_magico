#include "def_cubo.h"
#include "io_cubo.h"
#include "montador_cubo.h"
#include <stdio.h>
int main()
{
    //char oi[55] ="WYOWWWGWBGBOOYYGWGRRWGWGWOBBBOBBRGROOOYYRGBGYYORYYBRRR";
    char cubo[54];
    leCubo(cubo);
    escreveCubo(cubo);
    printf("\nfazendo cubo\n\n\n");
    Cubomagico* cubot;
    cubot =criaCubo(cubo);
    

    Movimento* moves;
    
    moves = montaCubo(cubot);
    int i;
    char nome[10];
    for(i=0;i<pegaMovs(cubot);i++)
    {
        idToString(nome,corDaPecaPeloId(cubot,moves[i].idLado));
        printf("%s %s\n",nome,(moves[i].direcao)? "Horario":"Anti-Horario");

    }
    escreveCubo(pegaStringCubo(cubot));
    for(i=0;i<54;i++)
        cubo[i]=corDaPecaPeloId(cubot,i);
    printf("%s",cubo);
    return 0;
}
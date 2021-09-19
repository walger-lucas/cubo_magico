#include "def_cubo.h"
#include "io_cubo.h"
#include "montador_cubo.h"
#include <stdio.h>
int main()
{
    //char cubo[55] ="WYRROGGYBGBRBROBOYRWBBWGORBBYYYWBGWOOOYOWGGRWYGYWRWGRO";
    char cubo[54];
    leCubo(cubo);
    escreveCubo(cubo);
    printf("\nfazendo cubo\n\n\n");
    Cubomagico* cubot;
    cubot =criaCubo(cubo);
    

    Movimento* moves;
    
    moves = montaCubo(cubot);
    int i,j=0;
    char nome[10];
    printf("%d\n\n",pegaMovs(cubot));
    for(i=0;i<pegaMovs(cubot);i++)
    {
        printf("%f /100\n",i/(float)pegaMovs(cubot)*100);
        
            idToString(nome,corDaPecaPeloId(cubot,moves[i].idLado));
            printf("%s %s\n",nome,(moves[i].direcao)? "Horario":"Anti-Horario");
        getchar();
        

    }
    escreveCubo(pegaStringCubo(cubot));
    for(i=0;i<54;i++)
        cubo[i]=corDaPecaPeloId(cubot,i);
    printf("%s",cubo);
    return 0;
}
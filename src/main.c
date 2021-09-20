#include "def_cubo.h"
#include "io_cubo.h"
#include "montador_cubo.h"
#include <stdio.h>
int main()
{
    //char cubo[55] ="WBOGBYGRWGWBORROWYROGOYYGGOBBWYORRRROGWWBWGBRYYYGYBWOB";
    char cubo[54];
    leCubo(cubo);
    escreveCubo(cubo);
    printf("%s",cubo);
    printf("\nfazendo cubo\n\n\n");
    Cubomagico* cubot;
    cubot =criaCubo(cubo);
    if(cubot ==NULL)
    {
        printf("error\n");
        return 1;
    }
    Movimento* moves;
    int pontosFinais[7];
    moves = montaCubo(cubot,pontosFinais);
    int i;
    char nome[10];
    printf("%d\n\n",pegaMovs(cubot));
    for(i=0;i<pegaMovs(cubot);i++)
    {
        printf("%f /100\n",i/(float)pegaMovs(cubot)*100);
        idToString(nome,corDaPecaPeloId(cubot,moves[i].idLado));
        printf("%s %s\n",nome,(moves[i].direcao)? "Horario":"Anti-Horario");

        if(i==pontosFinais[0])
            printf("Cruz Inicial Terminada\n");
        else if(i==pontosFinais[1]-1)
            printf("Lado Inicial Terminado\n");
        else if(i==pontosFinais[2]-1)
            printf("Segundo Andar Terminado\n");
        else if(i==pontosFinais[3]-1)
            printf("Cruz Final Terminada\n");
        else if(i==pontosFinais[4]-1)
            printf("Lado Final Completo\n");
        else if(i==pontosFinais[5]-1)
            printf("Quinas Ajustadas\n");
        else if(i==pontosFinais[6]-1)
            printf("Cubo Completo\n");
        getchar();
        

    }
    escreveCubo(pegaStringCubo(cubot));
    for(i=0;i<54;i++)
        cubo[i]=corDaPecaPeloId(cubot,i);
    printf("%s",cubo);
    return 0;
}
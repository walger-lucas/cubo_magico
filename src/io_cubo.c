#include <stdlib.h>
#include <stdio.h>
#include "io_cubo.h"
#include "def.h"


void limpaTerminal()
{
    #if WINDOWS
        system(“cls”);
    #else
        system("clear");
    #endif
}

void leCubo(char lados[54])
{
    printf("Sendo\n W: White: Branco \t G: Green: Verde \t R: Red: Vermelho\n B: Blue: Azul \t O: Orange: Laranja \t Y: Yellow: Amarelo\n");
    printf("Escreva a cor do topo do cubo");
    scanf("%c",&lados[0]);
    printf("Escreva a cor da base do cubo");
    scanf("%c",&lados[45]);
    printf("Escreva a cor da parte traseira do cubo");
    scanf("%c",&lados[9]);
    printf("Escreva a cor da parte frontal do cubo");
    scanf("%c",&lados[27]);
    printf("Escreva a cor da parte esquerda do cubo");
    scanf("%c",&lados[18]);
    printf("Escreva a cor da parte direita do cubo");
    scanf("%c",&lados[36]);


}
void leLado(char lados[54],char idLado)
{
    scanf("%c",lados);
}

void idToString(char cor[10],char idCor)
{
    char cores[6][10]={"Branco","Verde","Azul","Vermelho","Laranja","Amarelo"};
    char id;
    if(idCor=='W')
        id=0;
    else if(idCor=='G')
        id=1;
    else if(idCor=='B')
        id=2;
    else if(idCor=='R')
        id=3;
    else if(idCor=='O')
        id=4;
    else
        id=5;
    int i;
    for(i=0;cores[id][i]!='\0';i++)
        cor[i]=cores[id][i];
    cor[i]='\0';
}
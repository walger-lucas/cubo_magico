#include <stdlib.h>
#include <stdio.h>
#include "io_cubo.h"
#include "def_cubo.h"

void leLado(char lados[54],char idLado);
//le os lados do cubo
void leCubo(char lados[54])
{
    printf("Sendo\n W: White: Branco \t G: Green: Verde \t R: Red: Vermelho\n B: Blue: Azul \t O: Orange: Laranja \t Y: Yellow: Amarelo\n");
    printf("Escreva a cor do topo do cubo: ");
    scanf(" %c",&lados[0]);
    printf("Escreva a cor da base do cubo: ");
    scanf(" %c",&lados[45]);
    printf("Escreva a cor da parte traseira do cubo: ");
    scanf(" %c",&lados[9]);
    printf("Escreva a cor da parte frontal do cubo: ");
    scanf(" %c",&lados[27]);
    printf("Escreva a cor da parte esquerda do cubo: ");
    scanf(" %c",&lados[18]);
    printf("Escreva a cor da parte direita do cubo: ");
    scanf(" %c",&lados[36]);

    char cor1[10],cor2[10];
    char i;
    idToString(cor1,lados[0]);
    idToString(cor2,lados[9]);
    printf("Escreva o lado da cor %s, considerando a parte de cima apontada para a cor %s\n\n",cor1,cor2);
    leLado(lados,0);
    printf("\n\n");
    for(i=9;i<45;i+=9)
    {
        idToString(cor2,lados[(int)i]);
        printf("Escreva o lado da cor %s, considerando a parte de cima apontada para a cor %s\n\n",cor2,cor1);
        leLado(lados,i);
        printf("\n\n");
    }
    idToString(cor1,lados[45]);
    idToString(cor2,lados[9]);
    printf("Escreva o lado da cor %s, considerando a parte de cima apontada para a cor %s\n\n",cor1,cor2);
    leLado(lados,45);
    printf("\n\n");


}
/*une os lados, considerando que todos que podem tem o cima como o lado cima, e o resto tem cima como o lado tras,
cada array deve dar o as cores na sequencia:
012
345
678 
o array lados tem 0: como cima, 1: tras 2: esquerda 3:frente 4:direita 5:baixo
sendo que a direção cima, eh aquela onde esta o lado cima, caso seja o proprio lado cima, ou o lado baixo, essa direcao eh onde
esta o lado tras
o arrayCubo eh o array resultante que pode ser utilizado para criar um cubo
*/
void UneLadosEmArray(char arrayCubo[54],char lados[6][9])
{
    char ladoIds[9]= {2,1,8,3,0,7,4,5,6};
    int i,j;
    for (i=0;i<6;i++)
    {
        for(j=0;j<9;j++)
        {
            arrayCubo[i*9+ladoIds[j]] =lados[i][j];
        }
    }
}
//le o cubo na orientacao correta
void leLado(char lados[54],char idLado)
{
    char ladoIds[9]= {2,1,8,3,0,7,4,5,6};
    int i;
    for (i=0;i<9;i++)
    {
        scanf(" %c",&lados[idLado+ladoIds[i]]);
        
    }
    
}
//pega o id char e transforma em uma string
void idToString(char cor[10],char idCor)
{
    char cores[6][10]={"Branco","Verde","Azul","Vermelho","Laranja","Amarelo"};
    int id;
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
//printa todos os lados do cubo
void  escreveCubo(char* lados)
{
    printf("\n\n");
    int i;
    for(i=0;i<54;i+=9)
    {
        printf("  %c  \n",lados[(int)dirPeloLado((char)i,(char)i,0)]);
        printf(" %c%c%c \n",lados[i+2],lados[i+1],lados[i+8]);
        printf("%c",lados[(int)dirPeloLado((char)i,(char)i,1)]);
        printf("%c%c%c",lados[i+3],lados[i],lados[i+7]);
        printf("%c\n",lados[(int)dirPeloLado((char)i,(char)i,3)]);
        printf(" %c%c%c \n",lados[i+4],lados[i+5],lados[i+6]);
        printf("  %c  \n\n\n",lados[(int)dirPeloLado((char)i,(char)i,2)]);
    }
}
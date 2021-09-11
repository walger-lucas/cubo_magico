#include <stdlib.h>
#include "def_cubo.h"

char encontraLado(Cubomagico* cubo,char corLado);

//representa o cubo magico
struct cubomagico {

    //de | 0-8 : Cima | 9-17:Tras | 18-26: Esquerda  |27-35: Frente | 36-44: Direita | 45-53: Baixo
    //os restos apos serem divididos por 9 representam: 0, o centro, impares as pecas cerne, pares as da ponta
    //de 1 a 8, sao pegos na direcao antihoraria do cubo de um lado, comecando na parte superior, considerando o lado cima como ponto superior
    //para os lados CIMA e Baixo que nao possuem esse ponteiro, o "Cima" eh o lado Tras
    char lados[54];
    char ladoAtual;//lado centralizado atual
    int movimentosFeitos;//quantidade de movimentos feitos giros totais nao sao contados
    int girosFeitos;//quantidade de giros

};
//aloca espaco para um cubo magico, inicializando seus valores
/** OBS: A FUNCAO NO FUTURO RETORNARA NULO QUANDO NAO FOR UMA CUBO VALIDO*/
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
//Desaloca cubo
void destroiCubo(Cubomagico* cubo)
{
    free(cubo);
}
//pega o valor fixo do lado em que idLado esta
char corDoLadoDoIdDaPessa(Cubomagico* cubo,char idLado)
{
    return (*cubo).lados[(idLado/9)*9];
}
//pega o simbolo de cor do id dado no cubo
char corDaPecaPeloId(Cubomagico* cubo,char idLado)
{
    return (*cubo).lados[idLado];
}
//pega todo o cubo como um array de char
char* pegaStringCubo(Cubomagico* cubo)
{
    char* pecas;
    pecas = (char*) malloc(sizeof(char)*54);
    int i;
    for(i=0;i<54;i++)
    {
        pecas[i] = (*cubo).lados[i];
    }
    return pecas;
}

char* pegaPeca(Cubomagico* cubo, char lado,char dirCima, char id)
{
    
}
//pega a cor do lado contrario do lado dado
char ladoContrarioDe(Cubomagico* cubo,char corLado)
{
    char id = encontraLado(&cubo,corLado);
    if(id==0)
        return 45;
    if(id==45)
        return 0;
    if(id<27)
        return id+18;
    if(id<45)
        return id-18;
    return 100;
}
//encontra o id do lado com a cor correspondente
char encontraLado(Cubomagico* cubo,char corLado)
{
    char i;
    for(i=0;i<54;i+=9)
    {
        if((*cubo).lados[i]==corLado)
            return i;
    }
    return 100;

}
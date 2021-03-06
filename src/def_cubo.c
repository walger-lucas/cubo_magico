#include <stdlib.h>
#include <stdio.h>
#include "def_cubo.h"
//representa o cubo magico
struct cubomagico {

    //de | 0-8 : Cima | 9-17:Tras | 18-26: Esquerda  |27-35: Frente | 36-44: Direita | 45-53: Baixo
    //os restos apos serem divididos por 9 representam: 0, o centro, impares as pecas cerne, pares as da ponta
    //de 1 a 8, sao pegos na direcao antihoraria do cubo de um lado, comecando na parte superior, considerando o lado cima como ponto superior
    //para os lados CIMA e Baixo que nao possuem esse ponteiro, o "Cima" eh o lado Tras
    char lados[54];
    int movimentosFeitos;//quantidade de movimentos feitos 

};
const char dirLados[6][4]= {{9,18,27,36},{0,36,45,18},{0,9,45,27},
                      {0,18,45,36},{0,27,45,9},{9,36,27,18}};
//aloca espaco para um cubo magico, inicializando seus valores
/** OBS: A FUNCAO NO FUTURO RETORNARA NULO QUANDO NAO FOR UMA CUBO VALIDO*/
Cubomagico* criaCubo(char pecas[54])
{
    Cubomagico* cubo = (Cubomagico*) malloc(sizeof(Cubomagico));
    int i,j;
    int quantPecas[6]= {0};
    char corPecas[6];
    int cores=0,novaCor;

    for(i=0;i<54;i++)
    {
        novaCor=1;
        for(j=0;j<cores && j<6;j++)
        {
            
            if(pecas[i]==corPecas[j])
            {
                quantPecas[j]++;
                novaCor=0;
            }
        }
        if(novaCor)
        {
            if(cores==6)
            {
                cores++;
                break;
            }
            corPecas[cores]= pecas[i];
            quantPecas[cores]++;
            cores++;
        }
        (*cubo).lados[i]=pecas[i];
    }
    if(cores!=6)
        return NULL;
    for(i=0;i<6;i++)
    {
        if(quantPecas[i]!=9)
            return NULL;
    }

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
    return (*cubo).lados[(int)idLado];
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
//pega todo um lado e o coloca em um vetor
char* pegaLado(Cubomagico* cubo,char idLado)
{
    char* lado;
    lado = (char*) malloc(sizeof(char)*9);
    int i;
    for(i=0;i<9;i++)
    {
        lado[i] = (*cubo).lados[idLado+i];
    }
    return lado;
}
//gira anel no proprio cubo 90 graus, sem mudancas no array anel dir=0 anti horario, dir=1 horario
void giraAnel(Cubomagico* cubo,char* anel, char dir)
{
    char anelCor[12];
    int i;
    for(i=0;i<12;i++)
    {
        anelCor[i]=corDaPecaPeloId(cubo,anel[i]);
    }
    if(dir==0)
    {
        for(i=0;i<12;i++)
        {
            (*cubo).lados[(int) anel[i]]= anelCor[(i+3)%12];
        }

    }
    else
    {
        for(i=3;i<15;i++)
        {
            (*cubo).lados[(int)anel[i%12]]= anelCor[(i-3)];
        } 
    }

}
//gira em 90 graus anti horario caso 0, ou 90 graus horario caso 1, considerando olhar de cima e na dire????o comum
void giraLado(char lado[9], int dir)
{
    //faz copia do vetor e depois o utiliza para girar
    char ladoaux[9];
    int i;
    for(i=0;i<9;i++)
    {
        ladoaux[i]=lado[i];
    }
    if(dir==0)
    {
        for(i=1;i<7;i++)
        {
            lado[i+2]=ladoaux[i];
        }
        lado[1]= ladoaux[7];
        lado[2]= ladoaux[8];
    }
    else
    {
        for(i=8;i>2;i--)
        {
            lado[i-2]=ladoaux[i];
        }
        lado[7]=ladoaux[1];
        lado[8]=ladoaux[2];
    }


}
//gira o lado parte na direcao direcao. 0 antihorario 1 horario.
void giraParte(Cubomagico* cubo,char parte, char direcao)
{
    char* anel;
    char* lado;
    anel = pegaAnel(cubo,1,parte);//pega o anel que sera girado
    lado = pegaLado(cubo,parte);//pega o lado que sera girado
    giraAnel(cubo,anel,direcao);//gira o anel na direcao
    giraLado(lado,direcao); // gira o lado na direcao
    int i;
    for(i=0;i<9;i++)//coloca o lado novamente no cubo
    {
        (*cubo).lados[i+parte]=lado[i];
    }
    free(anel);
    free(lado);
    cubo->movimentosFeitos++;
}
//pega o id do lado com a cor especificada
char ladoDaCor(Cubomagico* cubo, char cor)
{
    int i =0;
    for(i=0;i<54;i+=9)
    {
        if(cor == corDaPecaPeloId(cubo,i))
            return i;
    }
    printf("erro no Lado da cor");
    return 100;

}
//pega peca dado o cubo, um lado, id do lado, o lado da dire??ao de cima, e o id do local da pe??a considerando a orientacao
char pegaPeca(Cubomagico* cubo, char lado,char dirCima, char id)
{
    int dir;
    for(dir=0;dir<4;dir++)
    {
        if(dirLados[lado/9][dir]==dirCima)
            break;
    }
    //caso n??o encontre o lado retorna 100 como erro
     if(dir==4)
        return 100;
    int idReal;
    //calcula o id real da peca, girando a peca ate que o lado fique alinhado com opostamente ao lado original
    if(id==0)
        idReal=0;
    else if(id+2*dir>8)
        idReal = id+2*dir-8;
    else
        idReal = id+2*dir;
   //retorna o id
    return lado+idReal;
}
//pega o lado que esta na direcao relativa relativeDir, do lado sideId, tendo como cima o lado upDir
//0 cima 1 esquerda 2 baixo 3 direita
char dirPeloLado(char sideId,char upDir,char relativeDir)
{
    if(upDir==sideId)
        return (char) dirLados[sideId/9][(int)relativeDir];
    char dir;
    //encontra a direcao cima procurando entre as direcoes possiveis
    for(dir=0;dir<4;dir++)
        if(dirLados[sideId/9][(int)dir]==upDir)
            break;
    if(dir==4)
    {
        printf("erro dir pelo lado");
        return 100;
    }
        

    return (char) dirLados[sideId/9][(dir+relativeDir<4)? dir+relativeDir : (dir+relativeDir)%4];


}
int pegaMovs(Cubomagico* cubo)
{
    return cubo->movimentosFeitos;
}
int direcaoDoLado( int ladoAtual,int ladoCima, int ladoEncontrar)
{
    int i;
    for(i=0;i<4;i++)
    {
        if(dirPeloLado(ladoAtual,ladoCima,i)==ladoEncontrar)
            return i;
    }
    printf("erro direcao do lado");
    return 100;
}

//pega a cor do lado contrario do lado dado
char ladoContrarioDe(Cubomagico* cubo,char corLado)
{
    char id = ladoDaCor(cubo,corLado);
    if(id==0)
        return 45;
    if(id==45)
        return 0;
    if(id<27)
        return id+18;
    if(id<45)
        return id-18;
    printf("erro lado contrario");
    return 100;
}
char ladoContrarioDoLado(Cubomagico* cubo,char id)
{
    if(id==0)
        return 45;
    if(id==45)
        return 0;
    if(id<27)
        return id+18;
    if(id<45)
        return id-18;
         printf("erro lado contrario");
    return 100;
}
//pega o anel de pecas naquele andar(1,2 ou 3) e transforma em um array de char,considerando o lado como o andar 0
char* pegaAnel(Cubomagico* cubo, char andar,char lado)
{
    char* anel;
    char pecas[3];
    char ladoAtual=dirLados[lado/9][0];
    anel = (char*) malloc(sizeof(char)*12);
    if(andar==1)//seta os ids dos aneis que devem ser pegos em cada lado
    {
        pecas[0]= 8;
        pecas[1]=1;
        pecas[2]= 2;
    }
    else if(andar==2)
    {
        pecas[0]= 7;
        pecas[1]=0;
        pecas[2]= 3;
    }
    else
    {
        pecas[0]= 6;
        pecas[1]=5;
        pecas[2]= 4;
    }
    
    int i,j;
    for (i=0;i<4;i++)
    {
        for(j=0;j<3;j++)//pega todas as pessas de um lado do anel
            anel[i*3+j]= pegaPeca(cubo,ladoAtual,lado,pecas[j]);
        ladoAtual = dirPeloLado(ladoAtual,lado,1);//muda o lado observado para a esquerda
    }
    return anel;
}
//dado um lado de uma peca, pega os outros, dando o numero de lados
char* pegaOutrosLados(Cubomagico* cubo,char idAtual, int* lados)
{
    
    if(idAtual%9==0)
    {
        *lados = 0;
         printf("erro pega outros lados");
        return NULL;
    }
    char* outLads;
    *lados= 2-idAtual%9%2;
    outLads= (char*) malloc(sizeof(char)*(*lados));
    if(*lados==1)
    {
        outLads[0]=pegaPeca(cubo,dirLados[idAtual/9][idAtual%9/2],idAtual/9*9,1);
    }
    else
    {
        if(idAtual%9==2)
        {
           outLads[0]=pegaPeca(cubo,dirLados[idAtual/9][1],idAtual/9*9,2); 
           outLads[1]=pegaPeca(cubo,dirLados[idAtual/9][0],idAtual/9*9,8); 
        }
        else if(idAtual%9==4)
        {
           outLads[0]=pegaPeca(cubo,dirLados[idAtual/9][1],idAtual/9*9,8); 
           outLads[1]=pegaPeca(cubo,dirLados[idAtual/9][2],idAtual/9*9,2); 
        }
        else if(idAtual%9==6)
        {
           outLads[0]=pegaPeca(cubo,dirLados[idAtual/9][3],idAtual/9*9,2); 
           outLads[1]=pegaPeca(cubo,dirLados[idAtual/9][2],idAtual/9*9,8); 
        }
        else
        {
          outLads[0]=pegaPeca(cubo,dirLados[idAtual/9][3],idAtual/9*9,8); 
          outLads[1]=pegaPeca(cubo,dirLados[idAtual/9][0],idAtual/9*9,2);   
        }
        
    }

    return outLads;

}
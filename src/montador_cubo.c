#include <stdlib.h>
#include "montador_cubo.h"
int montaCruzInicial(Cubomagico* cubo,Movimento* moves);
void movimenta(Cubomagico* cubo, Movimento* moves,char idLado, char dir);
void gira(Cubomagico* cubo, Movimento* moves,char idLado,char ladoDir,char ladoFin);
 Movimento* montaCubo(Cubomagico* cubo)
 {
     Movimento* moves;
     moves = (Movimento*) malloc(sizeof(Movimento)*1000);
    montaCruzInicial(cubo,moves);
    return moves;

 }
 //monta a cruz inicial
 int montaCruzInicial(Cubomagico* cubo,Movimento* moves)
 {
    int i,lados;
    char *segundaCor;
    char ladoSegCor;
    char corSegCor;
    for(i=1;i<9;i+=2)
    {
        segundaCor= pegaOutrosLados(cubo,i,&lados);
        //caso seja uma peca branca no topo que esta no lado errado ou tenha um lado com branco, tire do topo
        if((corDaPecaPeloId(cubo,i)==corDaPecaPeloId(cubo,0)&& corDaPecaPeloId(cubo,segundaCor[0])!=corDoLadoDoIdDaPessa(cubo,segundaCor[0]))
        || corDaPecaPeloId(cubo,segundaCor[0])==corDaPecaPeloId(cubo,0))
        {
            movimenta(cubo,moves,(segundaCor[0]/9)*9,0);
        }      
        free(segundaCor);
    }
    for(i=1;i<9;i+=2)
    {
        segundaCor= pegaOutrosLados(cubo,45+i,&lados);
        ladoSegCor=(segundaCor[0]/9)*9;
        corSegCor= corDaPecaPeloId(cubo,segundaCor[0]);
        if(corDaPecaPeloId(cubo,45+i)==corDaPecaPeloId(cubo,0))
        {
            gira(cubo,moves,0,ladoDaCor(cubo,corSegCor),ladoSegCor);
            movimenta(cubo,moves,ladoSegCor,0);
            movimenta(cubo,moves,ladoSegCor,0);
            gira(cubo,moves,0,ladoSegCor,ladoDaCor(cubo,corSegCor));
        }
        else if(corDaPecaPeloId(cubo,segundaCor[0])==corDaPecaPeloId(cubo,0))
        {
            corSegCor= corDaPecaPeloId(cubo,45+i);
            gira(cubo,moves,0,ladoDaCor(cubo,corSegCor),ladoSegCor);
            movimenta(cubo,moves,ladoSegCor,0);
            gira(cubo,moves,0,ladoSegCor,ladoDaCor(cubo,corSegCor));
        }
        free(segundaCor);
    }
    int j,idPeca;
    for(i=0;i<4;i++)
    {
        for(j=3;j<8;j+=4)
        {
            idPeca=pegaPeca(cubo,dirPeloLado(0,0,i),0,j);
            if(corDaPecaPeloId(cubo,idPeca)==corDaPecaPeloId(cubo,0))
            {
                segundaCor= pegaOutrosLados(cubo,idPeca,&lados);
                ladoSegCor=(segundaCor[0]/9)*9;
                corSegCor= corDaPecaPeloId(cubo,segundaCor[0]);
                gira(cubo,moves,0,ladoDaCor(cubo,corSegCor),ladoSegCor);
                gira(cubo,moves,ladoSegCor,(idPeca/9)*9,0);
                gira(cubo,moves,0,ladoSegCor,ladoDaCor(cubo,corSegCor));
                free(segundaCor);
            }
        }
    }
    int correto=1;
    for(i=1;i<9 && correto;i+=2)
    {
        segundaCor= pegaOutrosLados(cubo,i,&lados);
        if((corDaPecaPeloId(cubo,i)==corDaPecaPeloId(cubo,0)&& corDaPecaPeloId(cubo,segundaCor[0])!=corDaPecaPeloId(cubo,segundaCor[0]/9*9))
        || corDaPecaPeloId(cubo,i)!=corDaPecaPeloId(cubo,0))
        {
            correto=0;
        }
        free(segundaCor);
    }
    if(!correto)
    {
        montaCruzInicial(cubo,moves);
    }
    return pegaMovs(cubo);
 }
 void movimenta(Cubomagico* cubo, Movimento* moves,char idLado, char dir)
 {
     moves[pegaMovs(cubo)].direcao= dir;
     moves[pegaMovs(cubo)].idLado= idLado;
     giraParte(cubo,idLado,dir);
 }
//gira o cubo para que o lado dir aponte para o lado Fin
 void gira(Cubomagico* cubo, Movimento* moves,char idLado,char ladoDir,char ladoFin)
 {
     int dir;
     dir = direcaoDoLado(idLado,ladoDir,ladoFin);
     if(dir==1)
     {
         movimenta(cubo,moves,idLado,0);
     }
     else if(dir==3)
     {
         movimenta(cubo,moves,idLado,1);
     }
     else if(dir==2)
     {
         movimenta(cubo,moves,idLado,0);
         movimenta(cubo,moves,idLado,0);
     }

 }


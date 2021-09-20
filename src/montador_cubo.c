#include <stdlib.h>
#include "montador_cubo.h"
int montaCruzInicial(Cubomagico* cubo,Movimento* moves);
void movimenta(Cubomagico* cubo, Movimento* moves,char idLado, char dir);
int montaSegAndar(Cubomagico* cubo, Movimento* moves);
void gira(Cubomagico* cubo, Movimento* moves,char idLado,char ladoDir,char ladoFin);
char pecaNoLado(char *peca,int lado);
char pecaForaDoLado(char *peca,int lado);
 int montaPrimAndar(Cubomagico* cubo, Movimento* moves);
 int montaCruzAmarela(Cubomagico* cubo, Movimento* moves);
 int montaLateralAmarela(Cubomagico* cubo, Movimento* moves);
 int montaQuinas(Cubomagico* cubo, Movimento* moves);
 int finalizaCubo(Cubomagico* cubo, Movimento* moves);
 Movimento* montaCubo(Cubomagico* cubo,int pontosFinais[7])
 {
     Movimento* moves;
     moves = (Movimento*) malloc(sizeof(Movimento)*500);
    pontosFinais[0] =montaCruzInicial(cubo,moves);
    pontosFinais[1] =montaPrimAndar(cubo,moves);
    pontosFinais[2] =montaSegAndar(cubo,moves);
    pontosFinais[3] =montaCruzAmarela(cubo, moves);
    pontosFinais[4] =montaLateralAmarela(cubo,moves);
    pontosFinais[5] =montaQuinas(cubo,moves);
    pontosFinais[6] =finalizaCubo(cubo,moves);
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
    //procura no 4 e no 3 andar e os coloca na posicao correta
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
    //procura no 2 andar
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
    //analisa se tudo esta correto
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
 int montaPrimAndar(Cubomagico* cubo, Movimento* moves)
 {
     //busca no 3 andar por possiveis giros
     char* outPecas;
     char corOut[2], pecaAtual;
     int i,j,lados;
     for(i=0;i<4;i++)
    {
        for(j=4;j<8;j+=2)
        {
            pecaAtual= pegaPeca(cubo,dirPeloLado(0,0,i),0,j);
            outPecas= pegaOutrosLados(cubo,pecaAtual,&lados);
            corOut[0]=corDaPecaPeloId(cubo,pecaForaDoLado(outPecas,45));
            corOut[1]=corDaPecaPeloId(cubo,pecaNoLado(outPecas,45));
            if(corDaPecaPeloId(cubo,pecaAtual)==corDaPecaPeloId(cubo,0))
            {
                gira(cubo,moves,45,pecaForaDoLado(outPecas,45)/9*9,ladoDaCor(cubo,corOut[0]));
                gira(cubo,moves,ladoDaCor(cubo,corOut[1]),ladoDaCor(cubo,corOut[0]),45);
                gira(cubo,moves,45,ladoDaCor(cubo,corOut[1]),ladoDaCor(cubo,corOut[0]));
                gira(cubo,moves,ladoDaCor(cubo,corOut[1]),ladoDaCor(cubo,corOut[0]),0);
            }
            free(outPecas);
        }

    }
    //tira do topo
    for(i=2;i<9;i+=2)
    {
        if(corDaPecaPeloId(cubo,45+i)==corDaPecaPeloId(cubo,0))
        {
            outPecas= pegaOutrosLados(cubo,45+i,&lados);
            corOut[0]=corDaPecaPeloId(cubo,outPecas[0]);
            corOut[1]=corDaPecaPeloId(cubo,outPecas[1]);
            gira(cubo,moves,45,outPecas[0]/9*9,ladoDaCor(cubo,corOut[1]));
            gira(cubo,moves,ladoDaCor(cubo,corOut[0]),ladoDaCor(cubo,corOut[1]),45);
            movimenta(cubo,moves,45,0);
            movimenta(cubo,moves,45,0);
            gira(cubo,moves,ladoDaCor(cubo,corOut[0]),ladoDaCor(cubo,corOut[1]),0);
            free(outPecas);
        }
    }
    
    char aux;
    int corretos=0;
    //conta os corretos e tira so errados da base
     for(i=2;i<9;i+=2)
    {
        outPecas= pegaOutrosLados(cubo,i,&lados);
        corOut[0]=corDaPecaPeloId(cubo,outPecas[0]);
        corOut[1]=corDaPecaPeloId(cubo,outPecas[1]);
        if(corDaPecaPeloId(cubo,i)==corDaPecaPeloId(cubo,0) 
        && corOut[0]==corDaPecaPeloId(cubo,outPecas[0]/9*9) 
        && corOut[1]==corDaPecaPeloId(cubo,outPecas[1]/9*9))
        {
            corretos++;
        } 
        else if(corDaPecaPeloId(cubo,i)==corDaPecaPeloId(cubo,0) 
        && (corOut[0]!=corDaPecaPeloId(cubo,outPecas[0]/9*9) 
        || corOut[1]!=corDaPecaPeloId(cubo,outPecas[1]/9*9)))
        {
            gira(cubo,moves,outPecas[0]/9*9,0,outPecas[1]/9*9);
            movimenta(cubo,moves,45,0);
            gira(cubo,moves,outPecas[0]/9*9,45,outPecas[1]/9*9);
        }
        else if(corOut[0]==corDaPecaPeloId(cubo,0)||corOut[0]==corDaPecaPeloId(cubo,0))
        {
            if(corOut[1]==corDaPecaPeloId(cubo,0))
            {
                aux=outPecas[0];
                outPecas[0]=outPecas[1];
                outPecas[1]=aux;
            }
            gira(cubo,moves,outPecas[0]/9*9,outPecas[1]/9*9,45);
            movimenta(cubo,moves,45,0);
            movimenta(cubo,moves,45,0);
            gira(cubo,moves,outPecas[0]/9*9,outPecas[1]/9*9,0);
        }
        free(outPecas);
    }
    if(corretos!=4)
        montaPrimAndar(cubo,moves);
    return pegaMovs(cubo);
 }
 //movimentos para o segundo andar
void movimentoSegAndar(Cubomagico* cubo, Movimento* moves, char ladoFrente,char ladoCorFrente,char ladoCorCima)
{
    gira(cubo,moves,45,ladoFrente,ladoContrarioDoLado(cubo,ladoCorCima));
    gira(cubo,moves,ladoCorCima,ladoCorFrente,45);
    gira(cubo,moves,45,ladoContrarioDoLado(cubo,ladoCorCima),ladoCorFrente);
    gira(cubo,moves,ladoCorCima,45,ladoCorFrente);
    movimenta(cubo,moves,45,0);
    movimenta(cubo,moves,45,0);
    gira(cubo,moves,ladoCorFrente,0,ladoCorCima);
    movimenta(cubo,moves,45,0);
    movimenta(cubo,moves,45,0);
    gira(cubo,moves,ladoCorFrente,ladoCorCima,0);
}
//monta o segundo andar
int montaSegAndar(Cubomagico* cubo, Movimento* moves)
{
    char ladoFrente,ladoCorFrente,ladoCorCima,*outLados;
    int i,j,lados;
    //procura no terceiro anel e os monta, procura 4 vezes para encontrar todos
    for(j=0;j<4;j++)
    {
         for(i=1;i<8;i+=2)
         {
            outLados =pegaOutrosLados(cubo,45+i,&lados);
            ladoFrente= outLados[0]/9*9;
            ladoCorCima=ladoDaCor(cubo,corDaPecaPeloId(cubo,45+i));
            ladoCorFrente=ladoDaCor(cubo,corDaPecaPeloId(cubo,outLados[0]));
             if(corDaPecaPeloId(cubo,45+i)!=corDaPecaPeloId(cubo,45)&&corDaPecaPeloId(cubo,outLados[0])!=corDaPecaPeloId(cubo,45))
             {
                  movimentoSegAndar(cubo,moves,ladoFrente,ladoCorFrente,ladoCorCima);
             }
          free(outLados);
         }
    }
    int pecaAtual;
    //procura por pecas erradas no seg andar, dps as troca e coloca a certa
    for(i=0;i<4;i++)
    {
        pecaAtual=pegaPeca(cubo,dirPeloLado(0,0,i),45,3); 
        outLados= pegaOutrosLados(cubo,pecaAtual,&lados);
        if(corDaPecaPeloId(cubo,pecaAtual)!=corDaPecaPeloId(cubo,pecaAtual/9*9)||
        corDaPecaPeloId(cubo,outLados[0])!=corDaPecaPeloId(cubo,outLados[0]/9*9))
        {
            movimentoSegAndar(cubo,moves,9,pecaAtual/9*9,outLados[0]/9*9);
            free(outLados);
            for(j=1;j<8;j+=2)
            {
                 outLados =pegaOutrosLados(cubo,45+j,&lados);
                 ladoFrente= outLados[0]/9*9;
                 ladoCorCima=ladoDaCor(cubo,corDaPecaPeloId(cubo,45+j));
                 ladoCorFrente=ladoDaCor(cubo,corDaPecaPeloId(cubo,outLados[0]));
                   if(corDaPecaPeloId(cubo,45+j)!=corDaPecaPeloId(cubo,45)&&corDaPecaPeloId(cubo,outLados[0])!=corDaPecaPeloId(cubo,45))
                   {
                        movimentoSegAndar(cubo,moves,ladoFrente,ladoCorFrente,ladoCorCima);
                        free(outLados);
                        break;
                   }
                free(outLados);
             }
        
        }
    }
    return pegaMovs(cubo);
}
//sequencia de movimentos da cruz amarela
void movimentosCruzAmarela(Cubomagico* cubo, Movimento* moves,char frente, char cima)
{
    movimenta(cubo,moves,frente,1);
    movimenta(cubo,moves,dirPeloLado(frente,cima,3),1);
    movimenta(cubo,moves,cima,1);
    movimenta(cubo,moves,dirPeloLado(frente,cima,3),0);
    movimenta(cubo,moves,cima,0);
    movimenta(cubo,moves,frente,0);

}
//monta a cruz amarela no topo
int montaCruzAmarela(Cubomagico* cubo, Movimento* moves)
{
    //caso so haja o centro pronto fazer o movimento uma vez
    if(corDaPecaPeloId(cubo,45+1)!=corDaPecaPeloId(cubo,45) &&
    corDaPecaPeloId(cubo,45+3)!=corDaPecaPeloId(cubo,45) &&
    corDaPecaPeloId(cubo,45+5)!=corDaPecaPeloId(cubo,45) &&
    corDaPecaPeloId(cubo,45+7)!=corDaPecaPeloId(cubo,45))
        movimentosCruzAmarela(cubo,moves,9,0);

    int i;
    //tenta encontrar o L invertido na orientação certa
    for(i=0;i<4;i++)
    {
        if(corDaPecaPeloId(cubo,pegaPeca(cubo,45,dirPeloLado(45,45,i),5))==corDaPecaPeloId(cubo,45) &&
        corDaPecaPeloId(cubo,pegaPeca(cubo,45,dirPeloLado(45,45,i),7))==corDaPecaPeloId(cubo,45) &&
        corDaPecaPeloId(cubo,pegaPeca(cubo,45,dirPeloLado(45,45,i),1))!=corDaPecaPeloId(cubo,45) &&
        corDaPecaPeloId(cubo,pegaPeca(cubo,45,dirPeloLado(45,45,i),3))!=corDaPecaPeloId(cubo,45))
        {
            movimentosCruzAmarela(cubo,moves,dirPeloLado(45,45,i),45);
            break;
        }   
    }
    // tenta encontrar uma linha reta amarela na orientação certa e faz o movimento
    for(i=0;i<4;i++)
    {
        if(corDaPecaPeloId(cubo,pegaPeca(cubo,45,dirPeloLado(45,45,i),3))==corDaPecaPeloId(cubo,45) &&
        corDaPecaPeloId(cubo,pegaPeca(cubo,45,dirPeloLado(45,45,i),7))==corDaPecaPeloId(cubo,45) &&
        corDaPecaPeloId(cubo,pegaPeca(cubo,45,dirPeloLado(45,45,i),1))!=corDaPecaPeloId(cubo,45) &&
        corDaPecaPeloId(cubo,pegaPeca(cubo,45,dirPeloLado(45,45,i),5))!=corDaPecaPeloId(cubo,45))
        {
            movimentosCruzAmarela(cubo,moves,dirPeloLado(45,45,i),45);
            break;
        }   
    }
    return pegaMovs(cubo);
}
//sequencia de movimentos lateral amarela
void movimentosLateralAmarela(Cubomagico* cubo, Movimento* moves,char frente, char cima)
{
    char direita= dirPeloLado(frente,cima,3);
    movimenta(cubo,moves,direita,1);
    movimenta(cubo,moves,cima,1);
    movimenta(cubo,moves,direita,0);
    movimenta(cubo,moves,cima,1);
    movimenta(cubo,moves,direita,1);
    movimenta(cubo,moves,cima,1);
    movimenta(cubo,moves,cima,1);
    movimenta(cubo,moves,direita,0);
}
int montaLateralAmarela(Cubomagico* cubo, Movimento* moves)
{
    int i;
    char frente;
    for(i=0;i<4;i++)
    {
        //se encontrar os casos 1, 2, 3, 4 ou 5, faça o movimento na orientação encontrada OBS: a orientacao eh de ponta cabeca
        frente = dirPeloLado(45,45,i);
        if((corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,2)) == corDaPecaPeloId(cubo,45) //1
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,6)) == corDaPecaPeloId(cubo,45)   
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,4)) != corDaPecaPeloId(cubo,45)   
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,8)) != corDaPecaPeloId(cubo,45)) || //2  
        (corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,2)) == corDaPecaPeloId(cubo,45) 
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,4)) == corDaPecaPeloId(cubo,45)
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,6)) != corDaPecaPeloId(cubo,45)
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,frente,45,2)) == corDaPecaPeloId(cubo,45)) || //3
        (corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,4)) == corDaPecaPeloId(cubo,45) 
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,6)) == corDaPecaPeloId(cubo,45)
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,2)) != corDaPecaPeloId(cubo,45)
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,frente,45,2)) == corDaPecaPeloId(cubo,45)) || //4 E 5
        (corDaPecaPeloId(cubo,pegaPeca(cubo,dirPeloLado(45,frente,3),45,8)) == corDaPecaPeloId(cubo,45) 
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,2)) != corDaPecaPeloId(cubo,45)
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,4)) != corDaPecaPeloId(cubo,45)
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,dirPeloLado(45,frente,3),45,2)) == corDaPecaPeloId(cubo,45))) 
        {
            movimentosLateralAmarela(cubo,moves,frente,45);
            break;
        }
    }
    int j;
    for(j=0;j<2;j++)//tenta encontrar a posicao 6 e 7 duas vezes, e faz o movimento da lateral amarela
    {
        for(i=0;i<4;i++)
        {
           frente = dirPeloLado(45,45,i);
           if(corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,8)) == corDaPecaPeloId(cubo,45) 
           &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,6)) != corDaPecaPeloId(cubo,45)
           &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,2)) != corDaPecaPeloId(cubo,45)
           &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,4)) != corDaPecaPeloId(cubo,45))
           {
               movimentosLateralAmarela(cubo,moves,frente,45);
               break;
           }
        }
    }
    return pegaMovs(cubo);
}
void movimentosQuinas(Cubomagico* cubo, Movimento* moves,char base);
int montaQuinas(Cubomagico* cubo, Movimento* moves)
{
    int i,prontas=0;
    char ladoAtual,ladoPossivel;
    //tenta encontrar um lado com duas cores iguais, no terceiro anel, e o marca como lado possivel, tambem guarda quantos casos possiveis estao prontos
    for(i=0;i<4;i++)
    {
        ladoAtual= dirPeloLado(45,45,i);
        if(corDaPecaPeloId(cubo,pegaPeca(cubo,ladoAtual,45,2))==corDaPecaPeloId(cubo,pegaPeca(cubo,ladoAtual,45,8)))
        {
           prontas++;
           ladoPossivel=ladoAtual; 
        }
    }
    //caso nem todas as quinas estiverem prontas, mas ao menos uma estar, faz o movimento nesse lado possivel
    if(prontas>0 && prontas<4)
    {
        movimentosQuinas(cubo,moves,ladoPossivel);
        gira(cubo,moves,45,9,ladoDaCor(cubo,corDaPecaPeloId(cubo,13)));//deixa os lados nos lados certos
    }
    else if(prontas==4) // caso esteja tudo pronto, apenas deixa os lados apontando para os locais certos
    {
        gira(cubo,moves,45,9,ladoDaCor(cubo,corDaPecaPeloId(cubo,13)));
    }
    else //caso nada esteja certo, faz o movimento com o lado qualquer e pede que tudo seja feito novamente
    {
        movimentosQuinas(cubo,moves,9);
        montaQuinas(cubo,moves);
    }
    return pegaMovs(cubo);
    
}
//sequencia de movimentos para montar as quinas
void movimentosQuinas(Cubomagico* cubo, Movimento* moves,char baixo)
{
    char direita = dirPeloLado(baixo,45,3);
    char cima = ladoContrarioDoLado(cubo,baixo);
    movimenta(cubo,moves,direita,1);
    movimenta(cubo,moves,cima,0);
    movimenta(cubo,moves,direita,1);
    movimenta(cubo,moves,baixo,0);
    movimenta(cubo,moves,baixo,0);
    movimenta(cubo,moves,direita,0);
    movimenta(cubo,moves,cima,1);
    movimenta(cubo,moves,direita,1);
    movimenta(cubo,moves,baixo,0);
    movimenta(cubo,moves,baixo,0);
    movimenta(cubo,moves,direita,0);
    movimenta(cubo,moves,direita,0);
}
void movimentoFinalizador(Cubomagico* cubo, Movimento* moves,char fundo);
int finalizaCubo(Cubomagico* cubo, Movimento* moves)
{
    int i,encontrou=0;
    char ladoAtual;
    for(i=0;i<4;i++)// tenta encontrar um lado completo e faz os movimentos finais
    {
        ladoAtual = dirPeloLado(45,45,i);
        if(corDaPecaPeloId(cubo,pegaPeca(cubo,ladoAtual,45,1))==corDaPecaPeloId(cubo,ladoAtual))
        {
            encontrou = 1;
            movimentoFinalizador(cubo,moves,ladoAtual);
            break;
        } 
    }
    if(!encontrou)// caso nao encontre, faz o movimento em qualquer lado
    {
        movimentoFinalizador(cubo,moves,9);
        finalizaCubo(cubo,moves);
    }
    return pegaMovs(cubo);
}
//sequencia final para terminar o cubo
void movimentoFinalizador(Cubomagico* cubo, Movimento* moves,char fundo)
{
    char face= ladoContrarioDoLado(cubo,fundo);
    char esquerda=dirPeloLado(face,45,1);
    char direita =dirPeloLado(face,45,3);
    char ladoMeio;
    if(corDaPecaPeloId(cubo,face)==corDaPecaPeloId(cubo,pegaPeca(cubo,esquerda,45,1)))
    {
        ladoMeio = esquerda;
    }
    else
    {
        ladoMeio = direita;
    }

    movimenta(cubo,moves,face,0);
    movimenta(cubo,moves,face,0);
    gira(cubo,moves,45,ladoMeio,face);
    gira(cubo,moves,direita,45,face);
    gira(cubo,moves,esquerda,45,face);
    movimenta(cubo,moves,face,0);
    movimenta(cubo,moves,face,0);
    gira(cubo,moves,direita,face,45);
    gira(cubo,moves,esquerda,face,45);
    gira(cubo,moves,45,ladoMeio,face);
    movimenta(cubo,moves,face,0);
    movimenta(cubo,moves,face,0);

}
 char pecaNoLado(char *peca,int lado)
 {
    if(peca[0]/9*9==lado)
        return peca[0];
    if(peca[1]/9*9==lado)
        return peca[1];
    return 100;
 }
 char pecaForaDoLado(char *peca,int lado)
 {
     if(peca[0]/9*9!=lado)
        return peca[0];
    if(peca[1]/9*9!=lado)
        return peca[1];
    return 100;
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


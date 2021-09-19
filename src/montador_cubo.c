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
 Movimento* montaCubo(Cubomagico* cubo)
 {
     Movimento* moves;
     moves = (Movimento*) malloc(sizeof(Movimento)*1000);
    montaCruzInicial(cubo,moves);
    montaPrimAndar(cubo,moves);
    montaSegAndar(cubo,moves);
    montaCruzAmarela(cubo, moves);
    montaLateralAmarela(cubo,moves);
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

int montaSegAndar(Cubomagico* cubo, Movimento* moves)
{
    char ladoFrente,ladoCorFrente,ladoCorCima,*outLados;
    int i,lados;
    for(i=1;i<8;i+=2)
    {
        outLados =pegaOutrosLados(cubo,45+i,&lados);
        ladoFrente= outLados[0]/9*9;
        ladoCorCima=ladoDaCor(cubo,corDaPecaPeloId(cubo,45+i));
        ladoCorFrente=ladoDaCor(cubo,corDaPecaPeloId(cubo,outLados[0]));
        if(corDaPecaPeloId(cubo,45+i)!=corDaPecaPeloId(cubo,45)&&corDaPecaPeloId(cubo,outLados[0])!=corDaPecaPeloId(cubo,45))
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
        free(outLados);
    }
    int corretos=0,pecaAtual;
    for(i=0;i<4;i++)
    {
        pecaAtual=pegaPeca(cubo,dirPeloLado(0,0,i),0,3); 
        outLados= pegaOutrosLados(cubo,pecaAtual,&lados);
        if(corDaPecaPeloId(cubo,pecaAtual)==corDoLadoDoIdDaPessa(cubo,pecaAtual)
        &&corDaPecaPeloId(cubo,outLados[0])==corDoLadoDoIdDaPessa(cubo,outLados[0]))
        {
            corretos++;
        }
        else if(corDaPecaPeloId(cubo,pecaAtual)!=corDaPecaPeloId(cubo,45) 
        && corDaPecaPeloId(cubo,outLados[0])!=corDaPecaPeloId(cubo,45))
        {
            ladoCorFrente=ladoDaCor(cubo,corDaPecaPeloId(cubo,pecaAtual/9*9));
            ladoCorCima=ladoDaCor(cubo,corDaPecaPeloId(cubo,outLados[0]/9*9));
            free(outLados);
            break;
        }
        free(outLados);
    }
    
    if(corretos!=4)
    {
        for(i=1;i<8;i+=2)
        {
            outLados =pegaOutrosLados(cubo,45+i,&lados); 
            if(corDaPecaPeloId(cubo,45+i)==corDaPecaPeloId(cubo,45) 
        || corDaPecaPeloId(cubo,outLados[0])==corDaPecaPeloId(cubo,45))
            {
                ladoFrente= outLados[0]/9*9;
                free(outLados);
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
                 
                break;
            }
            free(outLados);
        }
        montaSegAndar(cubo,moves);
    }
    return pegaMovs(cubo);

}
void movimentosCruzAmarela(Cubomagico* cubo, Movimento* moves,char frente, char cima)
{
    movimenta(cubo,moves,frente,1);
    movimenta(cubo,moves,dirPeloLado(frente,cima,3),1);
    movimenta(cubo,moves,cima,1);
    movimenta(cubo,moves,dirPeloLado(frente,cima,3),0);
    movimenta(cubo,moves,cima,0);
    movimenta(cubo,moves,frente,0);

}
int montaCruzAmarela(Cubomagico* cubo, Movimento* moves)
{
    if(corDaPecaPeloId(cubo,45+1)!=corDaPecaPeloId(cubo,45) &&
    corDaPecaPeloId(cubo,45+3)!=corDaPecaPeloId(cubo,45) &&
    corDaPecaPeloId(cubo,45+5)!=corDaPecaPeloId(cubo,45) &&
    corDaPecaPeloId(cubo,45+7)!=corDaPecaPeloId(cubo,45))
        movimentosCruzAmarela(cubo,moves,9,0);

    int i;
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
        (corDaPecaPeloId(cubo,pegaPeca(cubo,dirPeloLado(45,frente,1),45,8)) == corDaPecaPeloId(cubo,45) 
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,6)) != corDaPecaPeloId(cubo,45)
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,45,frente,8)) != corDaPecaPeloId(cubo,45)
        &&corDaPecaPeloId(cubo,pegaPeca(cubo,dirPeloLado(45,frente,1),45,2)) == corDaPecaPeloId(cubo,45))) 
        {
            movimentosLateralAmarela(cubo,moves,frente,45);
            break;
        }
    }
    int j;
    for(j=0;j<2;j++)
    {
        for(i=0;i<4;i++)
        {
           frente = dirPeloLado(45,45,i%4);
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


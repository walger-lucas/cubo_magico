// definicoes e caracteristicas de um cubo magico com os possiveis movimentos

#ifndef _DEF_CUBO
#define _DEF_CUBO


typedef struct cubomagico Cubomagico;


char dirPeloLado(char sideId,char upDir,char relativeDir);


//cria um cubo com as pecas dadas, devolve nulo caso nao seja valido
Cubomagico* criaCubo(char pecas[54]);
void destroiCubo(Cubomagico* cubo);
char* pegaOutrosLados(Cubomagico* cubo,char idAtual, int* lados);
int direcaoDoLado(int ladoAtual,int ladoCima, int ladoEncontrar);
int pegaMovs(Cubomagico* cubo);
char ladoDaCor(Cubomagico* cubo, char cor);
char* pegaStringCubo(Cubomagico* cubo);
char* pegaLado(Cubomagico* cubo, char idLado);
char* pegaAnel(Cubomagico* cubo, char andar,char lado);
//id 0: 1 lado, id impar:2 lados, id par: 3 lados
char pegaPeca(Cubomagico* cubo, char lado,char dirCima, char id);
char corDaPecaPeloId(Cubomagico* cubo,char idLado);
char corDoLadoDoIdDaPessa(Cubomagico* cubo,char idLado);
void giraParte(Cubomagico* cubo,char parte, char direcao);

char ladoContrarioDe(Cubomagico* cubo,char corLado);

#endif
// definicoes e caracteristicas de um cubo magico com os possiveis movimentos

#ifndef _DEF_CUBO
#define _DEF_CUBO


typedef struct cubomagico Cubomagico;

//cria um cubo com as pecas dadas, devolve nulo caso nao seja valido
Cubomagico* criaCubo(char pecas[54]);
void destroiCubo(Cubomagico* cubo);

void centraCuboEm(Cubomagico* cubo, char cor);
void giraCuboNaDirecao(Cubomagico* cubo, char direcao);


char* pegaStringCubo(Cubomagico* cubo);
char* pegaLado(Cubomagico* cubo, char corDoLado);
char* pegaAnel(Cubomagico* cubo, char andar);
//id 0: 1 lado, id impar:2 lados, id par: 3 lados
char* pegaPeca(Cubomagico* cubo, char lado,char dirCima, char id);
char corDaPecapeloId(Cubomagico* cubo,char idLado);
char corDoLadoDoIdDaPessa(Cubomagico* cubo,char idLado);
char encontraIdDaPeca(Cubomagico* cubo,char* ladosPeca,char tam);
void giraParte(Cubomagico* cubo,char parte, char direcao);

#endif
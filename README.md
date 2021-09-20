# cubo_magico
Programa que ajuda a resolver um cubo mágico
Para utilizar, o diretorio, use o comando
    make clean
e depois
    make all
para fazer uma build na sua maquina,
depois, inicialize entrando no diretorio e utilizando o comando
    ./CuboMagico
ou com sua IDE de preferência.

Após isso, você será pedido para colocar um cubo mágico.
Siga as instruções, e lembre-se de colocar os caracteres:
W: para Branco
Y: para Amarelo
R: para Vermelho
G: para Verde
O: para Laranja
B: para Azul
Após colocar os lados, o programa falhará caso você tenha colocado um lado errado, ou se o cubo for um cubo impossível, mas caso esteja tudo certo, ele mostrará um numero, um codigo e todos os lados do cubo que voce colocou.
    O codigo eh o array do cubo, que pode ser guardado e utilizado em um debug depois.
Entao, diversos comandos surgiram na tela siga-os.
Para aparecer mais comandos, aperte enter.
Quando terminar, o seu cubo estará completo, e o cubo completo deve aparecer na tela.


Se você quer utilizar isso em um projeto seu, pegue todos os .h e .c, menos a main.
siga as instruções a baixo:
-Copie e cole para o seu Makefile a parte marcada no Makefile do projeto, troque $(OBJ_DIR) pelo diretorio dos objetos, também coloque um (Diretorio onde estao os .c e .h)/ atrás de todos os .c e .h
-coloque no makefile, na produção do projeto, os prerequisitos:
     (diretorio objetos)/def_cubo.c
     (diretorio objetos)/montador_cubo.c
     (diretorio objetos)/io_cubo.c

-Ao utilizar em um .c, inclua io_cubo, caso apenar irá ler o cubo, ou o montador_cubo caso ira apenas montá-lo, caso seja os dois, inclua os dois. Assim:
    #include "io_cubo.h"
    #include "montador_cubo.h"
- Crie um vetor de char com 54 posicoes.
- Utilize esse vetor na funcao void leCubo(char cubo[54]) para ler o cubo dado por um humano
caso nao seja direto de um humano utilize a função 
    void UneLadosEmArray(char arrayCubo[54],char lados[6][9])
utilizando a funcao com 54 lados em arrayCubo.
-Depois utilize essa base:
    Cubomagico* cubo;
    cubo =criaCubo(ArrayCubo);
    Movimento* moves;
    int pontosFinais[7];
    moves = montaCubo(cubot,pontosFinais);
-moves eh um array de movimentos, com tamanho escrito em pontosFinais[6]
cada movimento tem um idLado e uma direcao, o idLado dividido por nove, possui o mesmo codigo da funcao UneLadosemArray, ou voce pode lembrar, 0: cima 9: tras 18: esquerda 27: frente 36: direita 45: baixo
a direcao, 1 eh horario e 0 eh anti-horario
-pontosFinais guarda o movimento o qual termina uma das 7 partes da montacao do cubo
-depois de terminar, lembre-se de liberar moves, com
    free(moves);

Caso use esse projeto, lembre-se de dar os créditos, colocando o link do repositório do github, meu nome e meu email: 

    Lucas Walger do Nascimento
    walger.profissional@gmail.com
    https://github.com/walger-lucas/cubo_magico


Caso encontre um bug, me informe, enviando um email:
walger.profissional@gmail.com

Agradecimentos ao Renan Cerpe do site:
    cubovelocidade.com.br
Por ter me ensinado a resolver o cubo mágico



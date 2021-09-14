#include "def_cubo.h"
#include "io_cubo.h"
#include <stdio.h>
int main()
{
    char oi[55] ="WYYWWWWWYGGGGRYRYORRBBGGGRRBBBBOYGBBOOOOYRYORYOBGORWWW";
    //char cubo[54];
   // leCubo(cubo);
    
    escreveCubo(oi);
    printf("\nRotacionando Branco antihorario\n\n\n");
    Cubomagico* cubot;
    cubot =criaCubo(oi);
    giraParte(cubot,ladoDaCor(cubot,'W'),0);
    escreveCubo(pegaStringCubo(cubot));
    
    return 0;
}
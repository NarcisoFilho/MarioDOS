#ifndef __INCLUDES_LIST_H_
#define __INCLUDES_LIST_H_

    /// Headers Nativos de C
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <ctype.h>
    #include <time.h>

    /// Headers da Biblioteca Gráfica
    #include "raylib.h"  // Arquivo de cabeçalho da Biblioteca RAYLIB

    /// Headers Particulares
        // Inicialização
        #include "definitions.h"    // Reúne as definições do jogo
        #include "structs.h"    // Reúne as definições de TIPOS DE DADOS
        #include "inicializar.h"    // Declaração das funções de inicialização

        // Lógica
        #include "menu_logica.h"    // Funções de backend do menu
        #include "uteis.h" // Miscelânea de funções úteis
        #include "booleanas.h" // Miscelânea de funções úteis
        #include "logica_jogo.h" // Miscelânea de funções úteis

        // Desenho
        #include "menu_desenho.h"   // Funções de desenho do menu
        #include "desenha_jogo.h" // Funções de desenho do jogo



#endif // __INCLUDES_LIST_H_

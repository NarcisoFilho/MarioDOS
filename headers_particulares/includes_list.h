#ifndef __INCLUDES_LIST_H_
#define __INCLUDES_LIST_H_

    /// Headers Nativos de C
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <ctype.h>
    #include <time.h>

    /// Headers da Biblioteca Gr�fica
    #include "raylib.h"  // Arquivo de cabe�alho da Biblioteca RAYLIB

    /// Headers Particulares
        // Inicializa��o
        #include "definitions.h"    // Re�ne as defini��es do jogo
        #include "structs.h"    // Re�ne as defini��es de TIPOS DE DADOS
        #include "inicializar.h"    // Declara��o das fun��es de inicializa��o

        // L�gica
        #include "menu_logica.h"    // Fun��es de backend do menu
        #include "uteis.h" // Miscel�nea de fun��es �teis
        #include "booleanas.h" // Miscel�nea de fun��es �teis
        #include "logica_jogo.h" // Miscel�nea de fun��es �teis

        // Desenho
        #include "menu_desenho.h"   // Fun��es de desenho do menu
        #include "desenha_jogo.h" // Fun��es de desenho do jogo



#endif // __INCLUDES_LIST_H_

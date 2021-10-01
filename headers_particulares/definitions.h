#ifndef __DEFINITIONS_H_
#define __DEFINITIONS_H_

    #include "includes_list.h"

    /** DEFINIÇÕES DO JOGO **/

    // GERAL
    #define FPS 60
    #define EXIT_KEY KEY_F4
    #define MONITOR_COD_DEF 0
    #define MAX_MONITORES 3

    #define DELAY_SAIDA 2
        // OBJETOS
        #define V2_NULL (Vector2){ 0 , 0 }

        // DIREÇÃO
        #define DIREITA 1
        #define ESQUERDA -1

    // JOGABILIDADE GERAL
    #define GRAVIDADE 5

    // ÁREA DE JOGO
        //Cores
        #define COR_FUNDO_JOGO BLACK

    // TELA
    #define TELA_LARGURA_DEF 1200
    #define TELA_ALTURA_DEF 700

    // MENU
    #define QTD_ITENS_MENU 7
    #define MENU_TITULO_DELTA_VERTICAL_RAZ ( 1.0 / 4 )
    #define MENU_ANGULO_EFEITO 15
    #define MENU_PASSO_Y_EFEITO 4
    #define MENU_TITULO_DST_RAZ (Vector2){ 2.0 / 3 , 1.0 / 4 }

        // Cores MENU
        #define COR_FUNDO_MENU BLACK
        #define COR_ITEM_MENU_DEF RAYWHITE
        #define COR_ITEM_MENU_SELECTED SKYBLUE

        // Design
        #define MENU_ITEM_0_Y_RAZ 2.2 / 5
        #define MENU_DELTA_Y_ITEM 50
        #define MENU_TAM_FONTE_ITEM 30
        #define MENU_SPACING_FONTE_ITEM 4

        // Sub-Menu
        #define SUBMENU_TAM_FONTE 20
        #define COR_SUBMENU COR_ITEM_MENU_DEF
        #define SUBMENU_TAM_FONTE_ENT 25
        #define SUBMENU_SPACING_FONTE_ENT 4
        #define COR_SUBMENU_ENT COR_ITEM_MENU_SELECTED
        #define COR_SUBMENU_OPACO GRAY
        #define ESPESSURA_CS 3

    // MARIO
    #define QTD_VIDAS_DEF 3
    #define MARIO_X_INICIAL 30
    #define MARIO_LARG 50
    #define MARIO_ALT 80
    #define MARIO_PASSO 4
    #define MARIO_PULO_ENERGIA 160
    #define QTD_MARIO_STATUS 5
    #define DELAY_FRAME 4
    #define SRC_DELTA_SENTIDO 30

        // STATUS MARIO
        #define SM_PARADO 0
        #define SM_ANDANDO 1
        #define SM_PULANDO 2
        #define SM_CAINDO 3
        #define SM_MORRENDO 4

    // PLATAFORMAS
    #define MAX_PLATAFORMAS 10
    #define ALT_PLATAFORMAS 20
    #define DELTA_EFEITO_PLATF 200
    #define DElAY_EFEITO_PLATF .27
    #define COR_PLATAFORMA BLUE

        // Ground
        #define GROUND_ALT 50

        // Modo de Renderização
//        #define PLATAFORMA_ESPASSA
        #ifndef PLATAFORMA_ESPASSA
            #define PLATAFORMA_CONTINUA
        #endif

        // Modo de Renderização do Efeito de Distorção ( *Uma opção* )
//        #define MODO_ESPASSO
//        #define MODO_ESPASSO_INVERSO
//        #define MODO_DISCRETO
        #define MODO_CONTINUO

    // SPAWNS
    #define MAX_SPAWNS 9
    #define LARG_SPAWNS 216
    #define ALT_SPAWNS 108
    #define DELTA_SPAWNS_ESQ 20
        // Retorno
        #define TOL_RET 10
        #define LARG_RET 144
        #define ALT_RET 72
        #define DELTA_RET_ESQ 20

    // FASES
    #define QTD_FASES 5
    #define TEMPO_EXIBIR_NOME_FASE 5
    #define COLOR_EXIBIR_NOME_FASE GREEN

        // Arquivo
        #define QTD_LINES_ARQ 29
        #define QTD_COLS_ARQ 120
        #define ESC_ARQ (Vector2){ 10 , 25 }


    // SAIR
    #define TAM_FONTE_SAIR 30

    // INIMIGOS
    #define PASSO_INIMIGO 1.5
    #define MAX_INIMIGOS_FASE 20
    #define LARG_T1 55
    #define ALT_T1 45
    #define LARG_T2 55
    #define ALT_T2 45
    #define QTD_T1_STATUS 2
    #define QTD_T2_STATUS 3
    #define SUBIDA_INIMIGO 65
    #define SUBIDA_SPAWMN_INIMIGO 35
        // STATUS INIMIGOS
        #define SI_VULNERAVEL 0
        #define SI_ANDANDO 1
        #define SI_FURIOSO 2

    // IMAGENS SOURCE DEFINITIONS
    #define BLOCOS_GROUND_SRC (Rectangle){ 5 , 293 , 255 , 15 }
    #define POWER_SRC (Rectangle){ 133 , 243 , 16 , 16 }

    #define MENU_TITULO_SRC (Rectangle){ 21 , 10 , 200 , 72 }
    #define CANO_SPAWN_SRC (Rectangle){ 51 , 246 , 48 , 30 }
    #define RET_SPAWN_SRC (Rectangle){ 11 , 258 , 32 , 18 }
    #define HUD_LIFE_SRC (Rectangle){ 7 , 592 , 8 , 6 }
    #define AGUA_SRC (Rectangle){ 9 , 8 , 148 , 48 }

    // ATAQUE DO MARIO
    #define TOL_GOLPE (Vector2){ 54 , ALT_PLATAFORMAS + 30 }
    #define TOL_FATAL (Vector2){ 40 , 10 }

    // EFEITO ÁGUA
    #define LARG_EFEITO_AGUA 180
    #define ALT_EFEITO_AGUA 60

    // TECLAS
//    #define TECLA_CIMA KEY_KP_8
//    #define TECLA_BAIXO KEY_KP_5
//    #define TECLA_ESQUERDA KEY_KP_4
//    #define TECLA_DIREITA KEY_KP_6
//    #define TECLA_PULAR KEY_KP_0
    #define TECLA_CIMA KEY_UP
    #define TECLA_BAIXO KEY_DOWN
    #define TECLA_ESQUERDA KEY_LEFT
    #define TECLA_DIREITA KEY_RIGHT
    #define TECLA_PULAR KEY_D

    #define SB ( PlaySound( jogo.src.som_sel_menu ) )

#endif // __DEFINITIONS_H_

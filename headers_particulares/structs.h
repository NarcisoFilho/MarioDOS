#ifndef __STRUCTS_H_
#define __STRUCTS_H_

    #include "includes_list.h"

    // Dados de um monitor
    typedef struct{
        float alt;
        float larg;
    }MONITOR;

    // Dados da tela
    typedef struct{
        Vector2 pos;
        float alt;
        float larg;
    }TELA;

    // Dados do periféricos de saída( Monitores, caixas de som , etc )
    typedef struct{
        int qtd_monitores;
        MONITOR monitores[ MAX_MONITORES ];
        TELA tela;
    }OUTPUT_DEVICES;

    typedef struct{
        Rectangle pos;
        int sentido;
        int tipo;   // 1-> Tartaruga , 2-> Caranguejo
        int status; // 0 -> Andando , 1-> Vulnerável , 2->Furioso
        bool vivo;

        int frame_atual;
        int energia_cinetica_pulo;
        Color cor;
    }INIMIGO;

    // Estrutura para dados do jogador / partida
    typedef struct{
        Rectangle pos;
        int sentido;    // DIREITA -> 1 , ESQUERDA -> -1
        int energia_cinetica_pulo;
        int vidas;
        int pontos;
        int fase;
        Color cor;
        char nome[ 30 ]; // Nome do jogador

        int frame_atual;
        int status;     // Parado -> 0 , Andando -> 1 , Pulando - > 2 , Caindo - > 3 , Morrendo - > 4
        Vector2 pt_choque;

        int B_P;
    }MARIO;

    // Recursos do jogo
    typedef struct{
        // Texturas
        Texture2D sprite_geral;
        Texture2D sprite_agua;

        // Fontes
        Font fonte_mario;

        // Som
        Sound som_sel_menu;
        Sound som_pulo;
        Sound som_virar;
        Sound som_coin;
        Sound som_agua;
        Sound som_inicio;
        Sound som_dano;


    }SRC;

    // Dados do menu principal
    typedef struct{
        // Código da Seleção atual do menu
        int selected;

        // Flags de Encerramento
        bool flag_sair;

        // Caixa de Seleção do Nome do Usuário
        Rectangle caixa_sel;
    }MENU;

    typedef struct{
        float x_0;
        float x_f;
        float y;
        Rectangle dst;
    }PLATAFORMA;

    typedef struct{
        float ground;
        float teto;
        Rectangle hud;
        Rectangle blocos_ground;
        Rectangle titulo_dest;
    }INFO_GAME_AREA;

    typedef struct{
        int QTD_FRAMES_MARIO[ QTD_MARIO_STATUS ];
        int QTD_FRAMES_T1[ QTD_T1_STATUS ];
        int QTD_FRAMES_T2[ QTD_T2_STATUS ];
        Rectangle MARIO_SRC[ QTD_MARIO_STATUS ];
        Rectangle T1_SRC[ QTD_T1_STATUS ];
        Rectangle T2_SRC[ QTD_T2_STATUS ];
    }INFO_SPRITES;

    typedef struct{
        Vector2 pos;
        Vector2 pos_ret;
        int sentido;
    }SPAWN;

    typedef struct{
        Vector2 pos_mario;

        int qtd_plataformas;
        PLATAFORMA plataformas[ MAX_PLATAFORMAS ];

        int qtd_spawns;
        SPAWN spawns[ MAX_SPAWNS ];

        int qtd_inimigo_t1;
        int qtd_inimigo_t2;
        int delay_spawn;    // Em segundos

        char nome[ 30 ];
    }FASE;

    // Variável que agrupa todas as informações do jogo
    typedef struct{
        MARIO mario;
        MENU menu;
        SRC src;
        OUTPUT_DEVICES output_devices;
        INFO_GAME_AREA info_game_area;
        INFO_SPRITES info_sprites;
        FASE fases_camp[ QTD_FASES ];
        FASE fase_atual;
        int ini_abtd_fase_atual;
        int ini_lib_fase_atual[ 3 ];
        int delay_spawn_decorrido;
        INIMIGO inimigos[ MAX_INIMIGOS_FASE ];
    }JOGO;


#endif // __STRUCTS_H_

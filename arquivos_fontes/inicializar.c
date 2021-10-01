
#include "..\headers_particulares\inicializar.h"

JOGO inicializar_pre_jogo( void ){
    JOGO pre_jogo;

    // Configurações Gerais
    pre_jogo.output_devices = obter_dados_output_devices();
    redefinir_tela( &pre_jogo.output_devices.tela , &pre_jogo.output_devices.monitores[ MONITOR_COD_DEF ] );
    alterar_exit_key();
    ocultar_cursor();
    srand( time( NULL ) );

    // Menu
    pre_jogo.menu.selected = 0;
    pre_jogo.menu.flag_sair = false;
        //Título
        pre_jogo.info_game_area.titulo_dest.width = pre_jogo.output_devices.tela.larg * MENU_TITULO_DST_RAZ.x;
        pre_jogo.info_game_area.titulo_dest.height = pre_jogo.output_devices.tela.alt * MENU_TITULO_DST_RAZ.y;
        pre_jogo.info_game_area.titulo_dest.x = pre_jogo.output_devices.tela.larg / 2.0;
        pre_jogo.info_game_area.titulo_dest.y = pre_jogo.info_game_area.titulo_dest.height * ( MENU_TITULO_DELTA_VERTICAL_RAZ + 1.0 / 2 );


        // Sub-Menu Selecionar Nome
        pre_jogo.menu.caixa_sel.height = pre_jogo.output_devices.tela.alt / 10;
        pre_jogo.menu.caixa_sel.width = 4 * pre_jogo.output_devices.tela.larg / 5;
        pre_jogo.menu.caixa_sel.x =
            ( pre_jogo.output_devices.tela.larg - pre_jogo.menu.caixa_sel.width ) / 2.0;
        pre_jogo.menu.caixa_sel.y =
            ( pre_jogo.output_devices.tela.alt - pre_jogo.menu.caixa_sel.height ) / 2.0;

    // SRC
    carregar_recursos( &pre_jogo );

    // INFORMAÇÕES SOBRE A ÁREA DO JOGO
    pre_jogo.info_game_area.blocos_ground.width = pre_jogo.output_devices.tela.larg;
    pre_jogo.info_game_area.blocos_ground.height = GROUND_ALT;
    pre_jogo.info_game_area.blocos_ground.y = pre_jogo.output_devices.tela.alt - GROUND_ALT;
    pre_jogo.info_game_area.blocos_ground.x = 0;
    pre_jogo.info_game_area.ground = pre_jogo.info_game_area.blocos_ground.y;

    // INFORMAÇÕES SOBRE AS SPRITES
    int qtd_frames_mario[] = { 1 , 4 , 1 , 1 , 2 };
    Rectangle mario_src[] = {
        (Rectangle){ 3 , 603 , 16 , 21 },
        (Rectangle){ 3 , 603 , 16 , 21 },
        (Rectangle){ 93 , 603 , 15 , 21 },
        (Rectangle){ 73 , 602 , 15 , 21 },
        (Rectangle){ 113 , 604 , 16 , 21 }
    };

    int qtd_frames_t1[] = { 1 , 5 };
    Rectangle t1_src[] = {
//        (Rectangle){ 234 , 337 , 12 , 11 },
        (Rectangle){ 232 , 332 , 16 , 16 },
        (Rectangle){ 7 , 332 , 16 , 16 }
    };

    int qtd_frames_t2[] = { 1 , 2 , 2 };
    Rectangle t2_src[] = {
        (Rectangle){ 109 , 417 , 15 , 16 },
        (Rectangle){ 6 , 422 , 16 , 13 },
        (Rectangle){ 56 , 419 , 16 , 16 }
    };

    for( int i = 0 ; i < QTD_MARIO_STATUS ; i++ ){
        pre_jogo.info_sprites.QTD_FRAMES_MARIO[ i ] = qtd_frames_mario[ i ];
        pre_jogo.info_sprites.MARIO_SRC[ i ] = mario_src[ i ];
    }
    for( int i = 0 ; i < QTD_T1_STATUS ; i++ ){
        pre_jogo.info_sprites.QTD_FRAMES_T1[ i ] = qtd_frames_t1[ i ];
        pre_jogo.info_sprites.T1_SRC[ i ] = t1_src[ i ];
    }
    for( int i = 0 ; i < QTD_T2_STATUS ; i++ ){
        pre_jogo.info_sprites.QTD_FRAMES_T2[ i ] = qtd_frames_t2[ i ];
        pre_jogo.info_sprites.T2_SRC[ i ] = t2_src[ i ];
    }

    // CARREGAR FASES
    carregar_fases_da_campanha( &pre_jogo );

    return pre_jogo;
}

void inicializar_dados_mario( JOGO *jogo ){

    // Limpa o campo de nome
    TextCopy( jogo->mario.nome , "" );

    // Restaura o número de vidas ao padrão inicial
    jogo->mario.vidas = QTD_VIDAS_DEF;

    // Zera a quantidade de pontos
    jogo->mario.pontos = 0;

    // Inicializa na fase 0
    jogo->mario.fase = 0;

    // Inicializa dimensão do mario
    jogo->mario.pos.width = MARIO_LARG;
    jogo->mario.pos.height = MARIO_ALT;

    // Inicializa posição do mario
    jogo->mario.pos.x = MARIO_X_INICIAL;
    jogo->mario.pos.y = jogo->info_game_area.ground - jogo->mario.pos.height;

    // Inicializa cor do mario
    jogo->mario.cor = WHITE;

    // Zerar energia cinética
    jogo->mario.energia_cinetica_pulo = 0;

    // Zerar Status Mario
    jogo->mario.status = 0;

    // Inicializar Sentido Mario
    jogo->mario.sentido = DIREITA;

    // Inicializar Ponto de Choque
    jogo->mario.pt_choque.x = -999;
    jogo->mario.pt_choque.y = -999;

    // POWER
    jogo->mario.B_P = 3;

}

void inicializar_fase_nova( JOGO *jogo , FASE fase ){
//    exibir_mensagem_level_novo();
    jogo->ini_abtd_fase_atual = 0;
    jogo->ini_lib_fase_atual[ 0 ] = 0;
    jogo->ini_lib_fase_atual[ 1 ] = 0;
    jogo->ini_lib_fase_atual[ 2 ] = 0;
    jogo->fase_atual = fase;

    jogo->mario.pos.x = fase.pos_mario.x;
    jogo->mario.pos.y = fase.pos_mario.y;

    jogo->delay_spawn_decorrido = 1.5 * FPS;
    PlaySound( jogo->src.som_inicio );

//    jogo->qtd_moedas = 0;
}

void carregar_recursos( JOGO *jogo ){

    // Carrega o arquivo das sprites
    jogo->src.sprite_geral = LoadTexture( "imagens/sprite_geral.png" );
    jogo->src.sprite_agua = LoadTexture( "imagens/sprite_efeito_agua.png" );

    // Fontes de Texto
    jogo->src.fonte_mario = LoadFont( "fontes_texto/SuperMario256.ttf");

    // Som
    jogo->src.som_sel_menu = LoadSound( "som/sel_menu.mp3");
    jogo->src.som_pulo = LoadSound( "som/pulo.wav");
    jogo->src.som_virar = LoadSound( "som/virar.wav");
    jogo->src.som_coin = LoadSound( "som/smb_coin.wav");
    jogo->src.som_agua = LoadSound( "som/agua.wav");
    jogo->src.som_inicio = LoadSound( "som/inicio.wav");
    jogo->src.som_dano = LoadSound( "som/dano.wav");

}

void alterar_exit_key( void ){
    SetExitKey( EXIT_KEY );
}

void ocultar_cursor( void ){
    HideCursor();
}

void exibir_cursor( void ){
    ShowCursor();
}

OUTPUT_DEVICES obter_dados_output_devices( void ){
    OUTPUT_DEVICES outD;

    // Tela
    outD.tela = obter_dados_tela();
    outD.qtd_monitores = GetMonitorCount();

    // Monitores
    for( int i = 0 ; i < outD.qtd_monitores ; i++ ){
        outD.monitores[ i ].alt = GetMonitorHeight( i );
        outD.monitores[ i ].larg = GetMonitorWidth( i );
    }

    return outD;
}

TELA obter_dados_tela( void ){
   TELA tela;

   tela.pos = GetWindowPosition();
   tela.larg = GetScreenWidth();
   tela.alt = GetScreenHeight();

   return tela;
}

MONITOR obter_dados_monitor( int cod ){
    MONITOR monitor;

    monitor.larg = GetMonitorPhysicalWidth( cod );
    monitor.alt = GetMonitorPhysicalHeight( cod );

    return monitor;
}

void redefinir_tela( TELA *tela , MONITOR *monitor ){
    tela->alt = TELA_ALTURA_DEF;
    tela->larg = TELA_LARGURA_DEF;
    tela->pos.x = ( monitor->larg - tela->larg ) / 2;
    tela->pos.y = ( monitor->alt - tela->alt ) / 2;

    SetWindowSize( tela->larg , tela->alt );
    SetWindowPosition( tela->pos.x , tela->pos.y );
}

FASE carregar_fase( char *nome ){
    FASE fase = { 0 };
    FILE *arq = fopen( nome , "r" );
    char cop[ QTD_LINES_ARQ ][ QTD_COLS_ARQ + 1 ] = { 0 };
    int i , j;
    i = j = 0;

    while( !feof( arq ) && i < QTD_LINES_ARQ - 1 ){
        fscanf( arq , "%s" , cop[ i ] );
        i++;
    }

    fscanf( arq , "%d %d %d" , &fase.qtd_inimigo_t1 , &fase.qtd_inimigo_t2 , &fase.delay_spawn );

    fclose( arq );

    TextCopy( fase.nome , nome );



    int anterior;

    for( i = 0 ; i < QTD_LINES_ARQ - 1 ; i++ ){
        anterior = '\n';
        for( j = 0 ; j < QTD_COLS_ARQ ; j++ ){
            switch( cop[ i ][ j ] ){
                case 'b':
                    break;
                case 'p':
                    if( anterior != 'p' ){
                        fase.plataformas[ fase.qtd_plataformas ].x_0 = j * ESC_ARQ.x;
                        fase.plataformas[ fase.qtd_plataformas ].dst.x = fase.plataformas[ fase.qtd_plataformas ].x_0;
                        fase.plataformas[ fase.qtd_plataformas ].y = i * ESC_ARQ.y;
                        fase.plataformas[ fase.qtd_plataformas ].dst.y = fase.plataformas[ fase.qtd_plataformas ].y;
                        fase.plataformas[ fase.qtd_plataformas ].dst.height = ALT_PLATAFORMAS;
                    }

                    if( cop[ i ][ j + 1 ] != 'p'  ||  j == QTD_COLS_ARQ - 1 ){
                        fase.plataformas[ fase.qtd_plataformas ].x_f = ( j + 1 ) * ESC_ARQ.x;
                        fase.plataformas[ fase.qtd_plataformas ].dst.width = fase.plataformas[ fase.qtd_plataformas ].x_f - fase.plataformas[ fase.qtd_plataformas ].x_0;

                        fase.qtd_plataformas++;
                    }
                    break;
                case 'm':
                    fase.pos_mario.x = j * ESC_ARQ.x;
                    fase.pos_mario.y = i * ESC_ARQ.y - MARIO_ALT;
                    break;
                case 's':
                    fase.spawns[ fase.qtd_spawns ].sentido = ( j < QTD_COLS_ARQ / 2.0 ) ? DIREITA : ESQUERDA;
                    fase.spawns[ fase.qtd_spawns ].pos.x = j * ESC_ARQ.x;
                    fase.spawns[ fase.qtd_spawns ].pos.y = i * ESC_ARQ.y;
                    fase.qtd_spawns++;
                    break;
                case '1' ... '9':
                    fase.spawns[ tolower( cop[ i ][ j ] ) - '0' - 1 ].pos_ret.x = j * ESC_ARQ.x;
                    fase.spawns[ tolower( cop[ i ][ j ] ) - '0' - 1 ].pos_ret.y = i * ESC_ARQ.y;
                    break;
            }

            anterior = tolower( cop[ i ][ j ] );
        }
    }
    return fase;
}

void carregar_fases_da_campanha( JOGO *jogo ){
    char cmd[ 40 ] = "";

    for( int i = 0 ; i < QTD_FASES ; i++ ){
        sprintf( cmd , "%s%d%s" , "fases\\fase" , i + 1 , ".txt" );
        jogo->fases_camp[ i ] = carregar_fase( cmd );
    }

}


#include "..\headers_particulares\menu_logica.h"

char *nome_itens_menu( int cod_item ){
    static char itens[][ 20 ] = {
        "Novo Jogo",
        "Continuar",
        "Carregar Mapa",
        "Ranking",
        "Ajuda",
        "Sobre",
        "Sair"
    };

    return itens[ cod_item ];
}

void atualiza_select( int *selected ){
    static Sound som;
    static int flag = 1;
    if( flag ){
        som = LoadSound( "som/seta_menu.wav");
        flag = 0;
    }

    if( IsKeyPressed( TECLA_BAIXO ) )
        if( *selected < QTD_ITENS_MENU - 1 ){
            (*selected)++;
            PlaySound( som );
        }
    if( IsKeyPressed( TECLA_CIMA ) )
        if( *selected ){
            (*selected)--;
            PlaySound( som );
        }
}

/// Items do Menu ---------------------------------------------------------------------------

void novo_jogo( JOGO *jogo ){
    char ent[ 25 ];
    TextCopy( ent , coletar_nome( jogo ) ); // Invoca tela de coleta de nome do usuário e atribui retorno a ent

    if( !TextIsEqual( ent , "voltar" ) ){
        inicializar_dados_mario( jogo );
        inicializar_fase_nova( jogo , jogo->fases_camp[ jogo->mario.fase ] );

        TextCopy( jogo->mario.nome , ent );

        do{
            desenhar_jogo( *jogo );
            atualiza_jogo( jogo );
        }while( checar_fim_jogo() != true );
    }
}

void continuar( JOGO *jogo ){
    printf("\nContinuar");
}

void carregar_mapa( JOGO *jogo ){
    printf("\nCarregar Mapa");
}

void ajuda( JOGO *jogo ){
    printf("\nAjuda");
}

void sobre( JOGO *jogo ){
    printf("\nSobre");
}

void sair( JOGO *jogo ){
        char txt[] = "Obrigado por jogar :)";
        for( int i = (int)( FPS * DELAY_SAIDA ) ; i ; i-- ){
            BeginDrawing();
                ClearBackground( COR_FUNDO_MENU );
                DrawText(
                         txt ,
                         centraliza_texto( txt , jogo->output_devices.tela.larg , TAM_FONTE_SAIR ) ,
                         ( jogo->output_devices.tela.alt - TAM_FONTE_SAIR ) / 2 ,
                         TAM_FONTE_SAIR ,
                         GREEN
                 );

                jogo->menu.flag_sair = true;

            EndDrawing();
        }
}


char *coletar_nome ( JOGO* jogo ){
    char txt[] = "Digite seu nome:";
    static char ent[ 25 ] = "";
    int tecla;
    bool flag_modo_voltar = 0;
    bool flag_encerrar_loop = 0;
    int roundness = 0;      // Auxiliar para gerar efeito legal de suavização das bordas

    exibir_cursor();
    TextCopy( ent , "" );   // Limpar Entrada
    do{
        BeginDrawing();

            ClearBackground( COR_FUNDO_MENU );
            DrawText(
                     txt ,
                     centraliza_texto( txt , jogo->output_devices.tela.larg , SUBMENU_TAM_FONTE ) ,
                     ( jogo->output_devices.tela.alt -  SUBMENU_TAM_FONTE ) / 3 ,
                     SUBMENU_TAM_FONTE ,
                     COR_SUBMENU
             );

            DrawText(
                     "VOLTAR" ,
                     centraliza_texto( "VOLTAR" , jogo->output_devices.tela.larg , SUBMENU_TAM_FONTE ) ,
                     jogo->output_devices.tela.alt -  2 * SUBMENU_TAM_FONTE  ,
                     SUBMENU_TAM_FONTE ,
                     flag_modo_voltar ? COR_SUBMENU_ENT : COR_SUBMENU_OPACO
             );

            DrawRectangleRoundedLines( jogo->menu.caixa_sel , roundness / 80.0 , 10 , ESPESSURA_CS , flag_modo_voltar ? COR_SUBMENU_OPACO : COR_SUBMENU_ENT );

            DrawText(
                ent ,
                jogo->menu.caixa_sel.x + centraliza_texto( ent , jogo->menu.caixa_sel.width , SUBMENU_TAM_FONTE_ENT )  ,
                jogo->menu.caixa_sel.y + ( jogo->menu.caixa_sel.height - SUBMENU_TAM_FONTE_ENT ) / 2  ,
                SUBMENU_TAM_FONTE_ENT ,
                flag_modo_voltar ? COR_SUBMENU_OPACO : COR_SUBMENU_ENT
            );

        EndDrawing();

        // Checa Tecla Pressionada Pelo Usuário
        tecla =  GetKeyPressed();    // Checa tecla pressionada, já capitalizando-a caso seja uma tecla

        // Alterna entre modo DIGITAR NOME e modo VOLTAR
        switch( tecla ){
            // Setas para cima e para baixo( Alternam entre modo inserir nome e modo voltar )
            case KEY_DOWN:
                flag_modo_voltar = true;
                break;
            case KEY_UP:
                flag_modo_voltar = false;
                break;

            case KEY_ENTER:
                flag_encerrar_loop = true;
                break;
            case KEY_ESCAPE:
                flag_encerrar_loop = true;
                flag_modo_voltar = true;
                break;

            // Tecla alfabética
            case KEY_A ... KEY_Z:
            case KEY_SPACE:
                ent[ TextLength( ent ) + 1 ] = '\0';
                ent[ TextLength( ent ) ] = tecla;
                break;

            // Tecla Para Apagar
            case KEY_BACKSPACE:
                ent[ TextLength( ent ) - 1 ] = '\0';
        }

        if( flag_modo_voltar ){
            if( roundness > 0 )
                roundness--;
        }
        else
            if( roundness < 125 )
                roundness++;

    }while( !flag_encerrar_loop );

    //Retorno
    if( flag_modo_voltar )
        return "voltar";        // Caso o usuário tenha apertado enter no modo VOLTAR
    else
        return ent;             // Caso o usuário tenha apertado enter no modo INSERIR NOME

}

/** MarioDOS
    @version 1.0
    @date september/2021
    @author Narciso Filho
    */


#include "headers_particulares/includes_list.h"

int main()
{
    // Declarações
    JOGO jogo;  // Dados gerais do Jogo
    void ( *itens_menu[ QTD_ITENS_MENU ] )( JOGO* ) = {
        novo_jogo , continuar , carregar_mapa , ajuda , sobre , sair        // Funções de cada item do menu
    };

    // Inicialização
    InitWindow( TELA_LARGURA_DEF , TELA_ALTURA_DEF , "MarioDOS 1.0");    // Inicializa a janela no contexto openGL
    InitAudioDevice();
    SetTargetFPS( FPS );    // Define a taxa de atualização da janela. FPS - Frames per seconds ( Quadros por segundo )1
    jogo = inicializar_pre_jogo();

    while ( !WindowShouldClose() && !jogo.menu.flag_sair )    // Detect window close button or ESC key
    {
        // TESTES

        // Atualização do Menu
        atualiza_select( &jogo.menu.selected );
        if( IsKeyPressed( KEY_ENTER ) )
            SB , itens_menu[ jogo.menu.selected ]( &jogo );

        // Desenho do Menu
        BeginDrawing();
            ClearBackground( COR_FUNDO_MENU );
            desenhar_titulo( jogo );
            desenhar_menu( jogo );
        EndDrawing();
    }

    // Encerramento do Programa
    CloseAudioDevice();
    CloseWindow();  // Fechar janela openGL e encerrar execução


    return 0;
}

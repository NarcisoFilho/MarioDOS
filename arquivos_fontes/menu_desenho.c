
#include "../headers_particulares/menu_desenho.h"

void desenhar_menu( JOGO jogo ){
    static Color cor_d = RAYWHITE;
    static Color cor_s = SKYBLUE;
    static int transp = 0;

    cor_d.a = transp;
    cor_s.a = transp;

    for( int i = 0 ; i < QTD_ITENS_MENU ; i++ )
        DrawTextEx(
            jogo.src.fonte_mario ,
            nome_itens_menu( i ) ,
            (Vector2){
                centraliza_textoEX( nome_itens_menu( i ) , jogo.output_devices.tela.larg , jogo.src.fonte_mario , MENU_TAM_FONTE_ITEM , MENU_SPACING_FONTE_ITEM ) ,
                MENU_ITEM_0_Y_RAZ * jogo.output_devices.tela.alt + MENU_DELTA_Y_ITEM * i
            } ,
            MENU_TAM_FONTE_ITEM ,
            MENU_SPACING_FONTE_ITEM ,
            jogo.menu.selected == i ? cor_s : cor_d
        );

    if( transp < 255 )
        transp++;
}

void desenhar_titulo( JOGO jogo ){
        static int dy = MENU_PASSO_Y_EFEITO * 70 , r = MENU_ANGULO_EFEITO , flag_c_r = 0;
        static float amortecimento_pendulo = 1.0;

        DrawTexturePro(
            jogo.src.sprite_geral ,
            MENU_TITULO_SRC ,
            jogo.info_game_area.titulo_dest ,
            (Vector2){
                jogo.info_game_area.titulo_dest.width / 2  ,
                jogo.info_game_area.titulo_dest.height / 2 - dy,
            } ,
            r / pow( amortecimento_pendulo , 3 )  ,
            WHITE
        );

        if( dy ) dy -= MENU_PASSO_Y_EFEITO;

        if( !flag_c_r ) r --;
        else r++;

        if( abs( r ) == MENU_ANGULO_EFEITO ) flag_c_r =  flag_c_r ? 0 : 1;

        if( !dy )
            if( amortecimento_pendulo < 10000 )
                amortecimento_pendulo += 0.03 ;

}

#ifndef __MENU_LOGICA_H_
#define __MENU_LOGICA_H_

    #include "includes_list.h"

    char *nome_itens_menu( int );
    void atualiza_select( int* );

    // Itens do Menu
    void novo_jogo( JOGO* );
    void continuar( JOGO* );
    void carregar_mapa( JOGO* );
    void ajuda( JOGO* );
    void sobre( JOGO* );
    void sair( JOGO* );

    // Funções dos Sub-Menus
    char *coletar_nome ( JOGO* jogo );

#endif // __MENU_LOGICA_H_

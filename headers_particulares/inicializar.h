#ifndef __INICIALIZAR_H_
#define __INICIALIZAR_H_

    #include "includes_list.h"

    void carregar_recursos( JOGO* );
    JOGO inicializar_pre_jogo( void );
    void inicializar_dados_mario( JOGO* );
    void inicializar_fase_nova( JOGO*, FASE );
    FASE carregar_fase( char* );
    void carregar_fases_da_campanha( JOGO *jogo );

    void alterar_exit_key( void );
    void ocultar_cursor( void );
    void exibir_cursor( void );

    // Read
    OUTPUT_DEVICES obter_dados_output_devices( void );
    TELA obter_dados_tela( void );
    MONITOR obter_dados_monitor( int cod );

    // Write
    void redefinir_tela( TELA* , MONITOR* );





#endif // __INICIALIZAR_H_

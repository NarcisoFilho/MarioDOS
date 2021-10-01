#ifndef __LOGICA_JOGO_H_
#define __Lflag_andarOGICA_JOGO_H_

    #include "includes_list.h"

    void atualiza_jogo( JOGO* );

    void atualiza_mov_mario( JOGO* );
    void atualiza_mov_inimigos( JOGO* );
    void atualiza_retorno_inimigos( JOGO* );
    void atualiza_mov_moedas( JOGO* );

    void atualiza_salto_mario( JOGO* );

    void aplicar_gravidade( JOGO* );
    void aplicar_gravidade_inimigos( JOGO* );

    void atualiza_dano_mario( JOGO* );
    void atualiza_dano_inimigos( JOGO* );
    void atualiza_coleta_moedas( JOGO* );

    void gerar_inimigos( JOGO* );
    void gerar_moeda( JOGO* );

    void atualiza_sprite_mario( JOGO* );
    void atualiza_sprite_inimigos( JOGO* );

    bool checar_contato_inferior_plataforma( JOGO , FASE , Rectangle );
    bool checar_contato_superior_plataforma( JOGO , FASE , Rectangle );
    bool checar_contato_lateral_plataforma( JOGO , FASE , Rectangle );


    void atualiza_fim_fase( JOGO* );
    void volta_ao_jogo( JOGO *jogo );

#endif // __LOGICA_JOGO_H_

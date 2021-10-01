
#include "../headers_particulares/logica_jogo.h"
#define IFMNM if( jogo->mario.status != SM_MORRENDO )
#define QMM if( jogo->mario.status == SM_MORRENDO )
void atualiza_jogo( JOGO *jogo ){
    // Fase
    atualiza_fim_fase( jogo );
    exibe_nome_nova_fase( *jogo );

    // Movimento
    IFMNM atualiza_mov_mario( jogo );
    atualiza_mov_inimigos( jogo );
    atualiza_retorno_inimigos( jogo );
    atualiza_mov_moedas( jogo );
    QMM volta_ao_jogo( jogo );

    // Gravidade
    aplicar_gravidade( jogo );
    aplicar_gravidade_inimigos( jogo );

    // Salto
    IFMNM atualiza_salto_mario( jogo );

    // Colisão
    IFMNM atualiza_dano_mario( jogo );
    IFMNM atualiza_dano_inimigos( jogo );
    IFMNM atualiza_coleta_moedas( jogo );

    // Atualização da sprite
    atualiza_sprite_mario( jogo );
    atualiza_sprite_inimigos( jogo );

    // Spawn
    gerar_inimigos( jogo );
//    gerar_moeda( jogo );


}


int flag_pulo = 0;
int flag_andar = 0;
void atualiza_mov_mario( JOGO *jogo ){
    Rectangle mr_pos = jogo->mario.pos;

    if( IsKeyDown( TECLA_DIREITA ) ){
        flag_andar = 4;
        mr_pos.x += MARIO_PASSO;
        if( !checar_contato_lateral_plataforma( *jogo , jogo->fase_atual , mr_pos ) ){
            jogo->mario.pos.x += MARIO_PASSO;
            jogo->mario.sentido = DIREITA;
            if( jogo->mario.pos.x + 2 * jogo->mario.pos.width / 3.0 > jogo->output_devices.tela.larg )
                jogo->mario.pos.x = - 1 * jogo->mario.pos.width / 3.0;
        }
        mr_pos.x -= MARIO_PASSO;
    }

    if( IsKeyDown( TECLA_ESQUERDA ) ){
        flag_andar = 4;

        mr_pos.x -= MARIO_PASSO;
        if( !checar_contato_lateral_plataforma( *jogo , jogo->fase_atual , mr_pos ) ){
            jogo->mario.pos.x -= MARIO_PASSO;
            jogo->mario.sentido = ESQUERDA;
            if( jogo->mario.pos.x + 1 * jogo->mario.pos.width / 3.0  < 0 )
                jogo->mario.pos.x = jogo->output_devices.tela.larg - 2 * jogo->mario.pos.width / 3.0;
        }
        mr_pos.x += MARIO_PASSO;
    }

    if( flag_andar ){
        jogo->mario.status = SM_ANDANDO;
        flag_andar--;
    }else{
        if( !flag_pulo ){
            jogo->mario.cor = WHITE;
            jogo->mario.status = SM_PARADO;
        }
    }
}



void atualiza_salto_mario( JOGO *jogo ){

    if( IsKeyPressed( TECLA_PULAR ) ){
        if( jogo->mario.status != SM_CAINDO )
            if( jogo->mario.status != SM_PULANDO )
                if( !jogo->mario.energia_cinetica_pulo ){
                    jogo->mario.energia_cinetica_pulo = MARIO_PULO_ENERGIA;
                    flag_pulo = 7;
                    PlaySound( jogo->src.som_pulo );
                }
    }

    if( flag_pulo ){
        flag_pulo--;
    }else{
        if( !flag_andar )
            jogo->mario.cor = WHITE;
    }

}


void aplicar_gravidade( JOGO* jogo ){
    float subida;

    jogo->mario.pt_choque.x = -999;
    jogo->mario.pt_choque.y = -999;
    if( jogo->mario.energia_cinetica_pulo  && jogo->mario.status != SM_MORRENDO ){
        if( !checar_contato_superior_plataforma( *jogo , jogo->fase_atual , jogo->mario.pos   ) ){
            subida = jogo->mario.energia_cinetica_pulo > GRAVIDADE ? GRAVIDADE : jogo->mario.energia_cinetica_pulo;
            jogo->mario.pos.y -= subida;
            jogo->mario.energia_cinetica_pulo -= subida;
            jogo->mario.status = SM_PULANDO;
        }else{
            jogo->mario.energia_cinetica_pulo = 0;
            jogo->mario.status = SM_CAINDO;
            jogo->mario.pt_choque.x = jogo->mario.pos.x + jogo->mario.pos.width / 2;
            jogo->mario.pt_choque.y = jogo->mario.pos.y - ALT_PLATAFORMAS;
        }

    }else{
        if( !checar_contato_inferior_plataforma( *jogo , jogo->fase_atual , jogo->mario.pos ) ||  jogo->mario.status == SM_MORRENDO ){
            jogo->mario.pos.y += GRAVIDADE;
            if( jogo->mario.status != SM_MORRENDO )
                jogo->mario.status = SM_CAINDO;
        }

    }

}



void aplicar_gravidade_inimigos( JOGO* jogo ){
    float subida;


    for( int i = 0 ; i < jogo->ini_lib_fase_atual[ 2 ] ; i++ ){
    //        if( jogo->inimigos[ i ].vivo ){
        if( jogo->inimigos[ i ].pos.y <= jogo->output_devices.tela.alt ){
            if( jogo->inimigos[ i ].energia_cinetica_pulo ){
//                if( !checar_contato_superior_plataforma( *jogo , jogo->fase_atual , jogo->inimigos[ i ].pos ) ){
                if( !checar_contato_superior_plataforma( *jogo , jogo->fase_atual , jogo->inimigos[ i ].pos ) ){
                    subida = jogo->inimigos[ i ].energia_cinetica_pulo > GRAVIDADE ? GRAVIDADE : jogo->inimigos[ i ].energia_cinetica_pulo;
                    jogo->inimigos[ i ].pos.y -= subida;
                    jogo->inimigos[ i ].energia_cinetica_pulo -= subida;



    //                jogo->inimigos[ i ].status = SM_PULANDO;
                }else{
                    jogo->inimigos[ i ].energia_cinetica_pulo = 0;
    //                jogo->inimigos[ i ].status = SM_CAINDO;
                }

            }else{
//                if( jogo->inimigos[ i ].vivo == true ){
                    if( !checar_contato_inferior_plataforma( *jogo , jogo->fase_atual , jogo->inimigos[ i ].pos ) || jogo->inimigos[ i ].vivo == false ){
                        jogo->inimigos[ i ].pos.y += GRAVIDADE;
                    }
//                }
            }
        }
    }

}

void atualiza_mov_inimigos( JOGO* jogo ){
    int passo;
    Rectangle aux;
    Rectangle aux2;

    for( int i = 0 ; i < jogo->ini_lib_fase_atual[ 2 ] ; i++ ){
        if( jogo->inimigos[ i ].vivo == true ){
            if( jogo->inimigos[ i ].status != SI_VULNERAVEL ){
                passo = jogo->inimigos[ i ].status * PASSO_INIMIGO;

                aux = jogo->inimigos[ i ].pos;
                aux2 = aux;
                aux.x += 2 * passo*jogo->inimigos[ i ].sentido;
                aux2.y += 2 * GRAVIDADE;
                for( int j = 0 ; j < jogo->ini_lib_fase_atual[ 2 ] ; j++ )
                    if( j != i ){
                        if( CheckCollisionRecs( aux , jogo->inimigos[ j ].pos ) )
                                jogo->inimigos[ i ].sentido *= -1;
                        else{
                            for( int k = 0 ; k < jogo->ini_lib_fase_atual[ 2 ] ; k++ )
                                if( k != i )
                                    if( CheckCollisionRecs( aux2 , jogo->inimigos[ k ].pos ) )
                                        jogo->inimigos[ i ].energia_cinetica_pulo = SUBIDA_INIMIGO;
                        }

                    }


                jogo->inimigos[ i ].pos.x += jogo->inimigos[ i ].sentido * passo;


                if( jogo->inimigos[ i ].sentido == DIREITA ){
                    if( jogo->inimigos[ i ].pos.x + 2 * jogo->inimigos[ i ].pos.width / 3.0 > jogo->output_devices.tela.larg )
                        jogo->inimigos[ i ].pos.x = - 1 * jogo->inimigos[ i ].pos.width / 3.0;
                }else{
                    if( jogo->inimigos[ i ].pos.x + 1 * jogo->inimigos[ i ].pos.width / 3.0  < 0 )
                        jogo->inimigos[ i ].pos.x = jogo->output_devices.tela.larg - 2 * jogo->inimigos[ i ].pos.width / 3.0;
                }

            }
        }
    }
}


void atualiza_retorno_inimigos( JOGO* jogo ){
    for( int i = 0 ; i < jogo->ini_lib_fase_atual[ 2 ] ; i++ ){
        if( jogo->inimigos[ i ].vivo == true ){
            for( int j = 0 ; j < jogo->fase_atual.qtd_spawns ; j++ ){
                if( fabs( jogo->inimigos[ i ].pos.x - jogo->fase_atual.spawns[ j ].pos_ret.x ) <= TOL_RET )
                    if( fabs( jogo->inimigos[ i ].pos.y - jogo->fase_atual.spawns[ j ].pos_ret.y ) <= 3 * TOL_RET ){
                        jogo->inimigos[ i ].pos.x = jogo->fase_atual.spawns[ j ].pos.x;
                        jogo->inimigos[ i ].pos.y = jogo->fase_atual.spawns[ j ].pos.y;
                        jogo->inimigos[ i ].sentido = jogo->fase_atual.spawns[ j ].sentido;

                    }


            }
        }
    }
}


void atualiza_mov_moedas( JOGO* jogo ){

}

void atualiza_dano_mario( JOGO* jogo ){
    for( int i = 0 ; i < jogo->ini_lib_fase_atual[ 2 ] ; i++ ){
        if( jogo->inimigos[ i ].vivo ){
            if( jogo->inimigos[ i ].status != SI_VULNERAVEL ){
                if( CheckCollisionRecs( jogo->mario.pos , jogo->inimigos[ i ].pos ) ){
                    jogo->mario.vidas--;
                    jogo->mario.status = SM_MORRENDO;
                    PlaySound( jogo->src.som_dano );

                }
            }
        }
    }

}


void atualiza_dano_inimigos( JOGO* jogo ){
    for( int i = 0 ; i < jogo->ini_lib_fase_atual[ 2 ] ; i++ ){
        if( jogo->inimigos[ i ].vivo ){

            if( fabs( jogo->inimigos[ i ].pos.x + jogo->inimigos[ i ].pos.width / 2 - jogo->mario.pt_choque.x ) <= TOL_GOLPE.x )
                if( fabs( jogo->inimigos[ i ].pos.y - jogo->mario.pt_choque.y ) <= TOL_GOLPE.y ){
                    jogo->mario.pontos += 10;
                    jogo->inimigos[ i ].status++;
                    PlaySound( jogo->src.som_virar );

                    if( jogo->inimigos[ i ].tipo == 1 ){
                        if( jogo->inimigos[ i ].status >= QTD_T1_STATUS )
                            jogo->inimigos[ i ].status = 0;
                    }else{
                        if( jogo->inimigos[ i ].status >= QTD_T1_STATUS + 1 )
                            jogo->inimigos[ i ].status = 0;
                    }

                    jogo->inimigos[ i ].energia_cinetica_pulo = SUBIDA_INIMIGO;
                }

            if( jogo->inimigos[ i ].status == SI_VULNERAVEL ){
                if( CheckCollisionRecs( jogo->mario.pos , jogo->inimigos[ i ].pos ) ){
                    jogo->inimigos[ i ].vivo = false;
                    PlaySound( jogo->src.som_coin );
                    jogo->mario.pontos += 800;
                    jogo->ini_abtd_fase_atual++;
                }
            }
        }
    }
}


void atualiza_coleta_moedas( JOGO* jogo ){

}

void gerar_inimigos( JOGO* jogo ){
    int spw;
    int ini = jogo->ini_lib_fase_atual[ 2 ];
    if( !jogo->delay_spawn_decorrido ){
        if( ini < jogo->fase_atual.qtd_inimigo_t1 + jogo->fase_atual.qtd_inimigo_t2 ){
            spw = nmr_rand( 0 , jogo->fase_atual.qtd_spawns - 1 );

            if( jogo->ini_lib_fase_atual[ 0 ] >= jogo->fase_atual.qtd_inimigo_t1 ){
                    jogo->inimigos[ ini ].tipo = 2;
            }else{
                if( jogo->ini_lib_fase_atual[ 1 ] >= jogo->fase_atual.qtd_inimigo_t2 ){
                    jogo->inimigos[ ini ].tipo = 1;
                }else{
                    if( nmr_rand( 0 , 1 ) )
                        jogo->inimigos[ ini ].tipo = 1;
                    else
                        jogo->inimigos[ ini ].tipo = 2;
                }
            }

            jogo->inimigos[ ini ].pos.x =
            jogo->fase_atual.spawns[ spw ].pos.x;
            jogo->inimigos[ ini ].pos.y =
            jogo->fase_atual.spawns[ spw ].pos.y;
            if( jogo->inimigos[ ini ].tipo == 1 ){
                jogo->inimigos[ ini ].pos.width = LARG_T1;
                jogo->inimigos[ ini ].pos.height = ALT_T1;
            }
            if( jogo->inimigos[ ini ].tipo == 2 ){
                jogo->inimigos[ ini ].pos.width = LARG_T2;
                jogo->inimigos[ ini ].pos.height = ALT_T2;
            }

            jogo->inimigos[ ini ].sentido =
            jogo->fase_atual.spawns[ spw ].sentido;

            jogo->inimigos[ ini ].status = SI_ANDANDO;
            jogo->inimigos[ ini ].vivo = true;
            jogo->inimigos[ ini ].cor = WHITE;
            jogo->inimigos[ ini ].frame_atual = 0;
            jogo->inimigos[ ini ].energia_cinetica_pulo = SUBIDA_SPAWMN_INIMIGO;

            jogo->ini_lib_fase_atual[ jogo->inimigos[ ini ].tipo - 1 ]++;
            jogo->ini_lib_fase_atual[ 2 ]++;
            jogo->delay_spawn_decorrido = jogo->fase_atual.delay_spawn * FPS;
        }
    }else{
        jogo->delay_spawn_decorrido--;
    }
}



void atualiza_sprite_mario( JOGO* jogo ){
    static int delay_frame = 0;
    static int status_anterior = SM_PARADO;

    if( jogo->mario.status != status_anterior  ){
        delay_frame = 0;
        jogo->mario.frame_atual = 0;
    }

    if( delay_frame )
        delay_frame--;
    else{
        jogo->mario.frame_atual++;
        delay_frame = DELAY_FRAME;
        if( jogo->mario.frame_atual >= jogo->info_sprites.QTD_FRAMES_MARIO[ jogo->mario.status ] )
            jogo->mario.frame_atual = 0;
    }

    status_anterior = jogo->mario.status;
}

void atualiza_sprite_inimigos( JOGO* jogo ){
    static int delay_frame[ MAX_INIMIGOS_FASE ] = { 0 };
    static int status_anterior[ MAX_INIMIGOS_FASE ] = { SI_ANDANDO };

    for( int i = 0 ; i < jogo->ini_lib_fase_atual[ 2 ] ; i++ ){
        if( jogo->inimigos[ i ].vivo ){
            if( jogo->inimigos[ i ].status != status_anterior[ i ]  ){
                delay_frame[ i ] = 0;
                jogo->inimigos[ i ].frame_atual = 0;
            }

            if( delay_frame[ i ] )
                delay_frame[ i ]--;
            else{
                jogo->inimigos[ i ].frame_atual++;
                delay_frame[ i ] = DELAY_FRAME;
                if( jogo->inimigos[ i ].tipo == 1 )
                    if( jogo->inimigos[ i ].frame_atual >= jogo->info_sprites.QTD_FRAMES_T1[ jogo->inimigos[ i ].status ] )
                        jogo->inimigos[ i ].frame_atual = 0;
                if( jogo->inimigos[ i ].tipo == 2 )
                    if( jogo->inimigos[ i ].frame_atual >= jogo->info_sprites.QTD_FRAMES_T2[ jogo->inimigos[ i ].status ] )
                        jogo->inimigos[ i ].frame_atual = 0;
            }

            status_anterior[ i ] = jogo->inimigos[ i ].status;
        }
    }
}


bool checar_contato_superior_plataforma( JOGO jogo , FASE fase , Rectangle obj ){
    // Plataformas
    for( int i = 0 ; i < fase.qtd_plataformas ; i++ ){
        if( obj.x + obj.width >= fase.plataformas[ i ].x_0 )
            if( obj.x <= fase.plataformas[ i ].x_f )
                if( obj.y == fase.plataformas[ i ].y + ALT_PLATAFORMAS )
                    return true;
    }

    return false;
}


bool checar_contato_lateral_plataforma( JOGO jogo , FASE fase , Rectangle obj ){
    // Plataformas
    for( int i = 0 ; i < fase.qtd_plataformas ; i++ )
        if( CheckCollisionRecs( obj , jogo.fase_atual.plataformas[ i ].dst ) )
            return true;

    return false;
}


bool checar_contato_inferior_plataforma( JOGO jogo , FASE fase , Rectangle obj ){
    // Plataformas
    for( int i = 0 ; i < fase.qtd_plataformas ; i++ ){
        if( obj.x + obj.width >= fase.plataformas[ i ].x_0 )
            if( obj.x <= fase.plataformas[ i ].x_f )
                if( obj.y + obj.height == fase.plataformas[ i ].y )
                    return true;
    }

    // Ground
    if( obj.y + obj.height == jogo.info_game_area.ground )
        return true;
    else
        return false;
}


void atualiza_fim_fase( JOGO *jogo ){
    static int flag = -1;

    if( jogo->ini_abtd_fase_atual >= jogo->fase_atual.qtd_inimigo_t1 + jogo->fase_atual.qtd_inimigo_t2  && flag == -1 ){
        exibir_mensagem_sucesso_fase( *jogo );
        flag = FPS * TEMPO_EXIBIR_NOME_FASE;

    }

    if( !flag ){
        jogo->mario.fase++;
        inicializar_fase_nova( jogo , jogo->fases_camp[ jogo->mario.fase ] );
    }

    if( flag > -1 )
        flag--;
}


void volta_ao_jogo( JOGO *jogo ){
    if( jogo->mario.status == SM_MORRENDO ){
        if( jogo->mario.pos.y > jogo->output_devices.tela.alt ){
            jogo->mario.pos.x = jogo->fase_atual.pos_mario.x;
            jogo->mario.pos.y = jogo->fase_atual.pos_mario.y;
            jogo->mario.status = SM_PARADO;
        }
    }
}

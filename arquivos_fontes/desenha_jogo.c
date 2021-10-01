
#include "../headers_particulares/desenha_jogo.h"

void desenhar_jogo( JOGO jogo ){
    BeginDrawing();
        ClearBackground( COR_FUNDO_JOGO );

        desenhar_ground( jogo );
        desenhar_power( jogo );
        desenhar_canos( jogo );
        desenhar_retornos( jogo );
        desenhar_hud( jogo );
        desenhar_plataformas( jogo );
        efeito_plataforma_distorcida( jogo );
        desenhar_moedas( jogo );
        desenhar_inimigos( jogo );
        desenhar_mario( jogo );
        efeito_agua( jogo );

//        DrawText( TextFormat("POSM( %.1f , %.1f )   TDS=%ds   INL[0]=%d   INL[1]=%d  INL[2]=%d   PCQ=(%.1f,%.1f)" , jogo.mario.pos.x , jogo.mario.pos.y , jogo.fase_atual.delay_spawn , jogo.ini_lib_fase_atual[ 0 ] , jogo.ini_lib_fase_atual[ 1 ] , jogo.ini_lib_fase_atual[ 2 ] , jogo.mario.pt_choque.x , jogo.mario.pt_choque.y ) , 150 , 20 , 20 , GREEN );
    EndDrawing();
}



void desenhar_ground( JOGO jogo ){
    DrawTexturePro(
        jogo.src.sprite_geral ,
        BLOCOS_GROUND_SRC ,
        jogo.info_game_area.blocos_ground ,
        (Vector2){
            0 ,
            0
        } ,
        0 ,
        WHITE
    );
}

void desenhar_power( JOGO jogo ){
    Rectangle aux = POWER_SRC;

    if( jogo.mario.B_P){
        aux.x += abs( 3 - jogo.mario.B_P ) * 20;

        DrawTexturePro(
            jogo.src.sprite_geral ,
            aux ,
            (Rectangle){ 570 , 470 , 60 , 60 } ,
            (Vector2){
                0 ,
                0
            } ,
            0 ,
            WHITE
        );
    }
}



void desenhar_canos( JOGO jogo ){
    Rectangle src;
    int sentido;
    for( int i = 0 ; i < jogo.fase_atual.qtd_spawns ; i++ ){
        src = CANO_SPAWN_SRC;
        sentido = jogo.fase_atual.spawns[ i ].sentido;

        if( sentido == ESQUERDA )
            src.y -= 43;

        DrawTexturePro(
            jogo.src.sprite_geral ,
            src ,
            (Rectangle){
                jogo.fase_atual.spawns[ i ].pos.x + ( ( sentido == ESQUERDA ) ? LARG_SPAWNS : 0 ) ,
                jogo.fase_atual.spawns[ i ].pos.y  ,
                LARG_SPAWNS ,
                ALT_SPAWNS
            }  ,
            (Vector2){
                LARG_SPAWNS - ( ( sentido == ESQUERDA ) ? DELTA_SPAWNS_ESQ : 0 ),
                ALT_SPAWNS / 3.0 - 7
            } ,
            0 ,
            WHITE );

    }
}

void desenhar_retornos( JOGO jogo ){
    Rectangle src;
    int sentido;
    for( int i = 0 ; i < jogo.fase_atual.qtd_spawns ; i++ ){
        src = RET_SPAWN_SRC;
        sentido = jogo.fase_atual.spawns[ i ].sentido;

        if( jogo.fase_atual.spawns[ i ].pos_ret.x < jogo.output_devices.tela.larg / 2 )
            src.y -= 43;


        DrawTexturePro(
            jogo.src.sprite_geral ,
            src ,
            (Rectangle){
                jogo.fase_atual.spawns[ i ].pos_ret.x + ( ( sentido == ESQUERDA ) ? LARG_RET : 0 ) ,
                jogo.fase_atual.spawns[ i ].pos_ret.y  ,
                LARG_RET ,
                ALT_RET
            }  ,
            (Vector2){
                LARG_RET - ( ( sentido == ESQUERDA ) ? DELTA_RET_ESQ : 0 ),
                ALT_RET / 3.0 - 7
            } ,
            0 ,
            WHITE );

    }
}



void desenhar_hud( JOGO jogo ){
    for( int i = 0 ; i < jogo.mario.vidas ; i++ ){
        DrawTexturePro( jogo.src.sprite_geral , HUD_LIFE_SRC , (Rectangle){ 20 + ( 45 ) * ( i ) , 10 , 32 , 24 } , V2_NULL , 0 , WHITE  );
    }
    DrawTextEx(
        jogo.src.fonte_mario ,
        TextFormat( "              Pontos : %d    FASE : %d" , jogo.mario.pontos , jogo.mario.fase + 1 ) ,
        (Vector2){ 10 , 10 },
        30 ,
        4 ,
        GREEN
   );
}




void desenhar_plataformas( JOGO jogo ){
    static bool flag_efeito = false;
    static int plat_efeito;
    static Vector2 pt_choque_efeito;
    static int delay_efeito = 0;
    static int delta = 0;
    float cent;
    float formula_kernel;
    const float fator = 1.8;
    int x0;
    int xf;
    int jr;

    #ifdef MODO_DISCRETO
        const int g_len = 13;
    #endif // MODO_DISCRETO
    #ifdef MODO_ESPASSO
        const int e_len = 20;
    #endif // MODO_ESPASSO
    #ifdef MODO_ESPASSO_INVERSO
        const int e_len_i = 2;
    #endif // MODO_ESPASSO_INVERSO
    #ifdef PLATAFORMA_ESPASSA
        const int e_len_i = 15;
    #endif // MODO_ESPASSO_INVERSO

    for( int i = 0 ; i < jogo.fase_atual.qtd_plataformas ; i++ ){
        if( CheckCollisionRecs( jogo.fase_atual.plataformas[ i ].dst , (Rectangle){ jogo.mario.pt_choque.x , jogo.mario.pt_choque.y , 2 * TOL_GOLPE.x , ALT_PLATAFORMAS } ) ){
            flag_efeito = true;
            delay_efeito = DElAY_EFEITO_PLATF * FPS;
            pt_choque_efeito = jogo.mario.pt_choque;
            plat_efeito = i;
            delta = 0;
        }
        if( !( flag_efeito && plat_efeito == i ) ){
                DrawRectangleRec( jogo.fase_atual.plataformas[ i ].dst , COR_PLATAFORMA );
            #ifdef PLATAFORMA_ESPASSA
                for( int j = jogo.fase_atual.plataformas[ i ].x_0 ; j < jogo.fase_atual.plataformas[ i ].x_f ; j++ ){
                    for( int i_a = jogo.fase_atual.plataformas[ i ].y ; i_a < jogo.fase_atual.plataformas[ i ].y + ALT_PLATAFORMAS ; i_a++ ){
                        if( !( j % e_len_i ) ){
                            DrawPixelV( (Vector2){ j , i_a } , COR_FUNDO_JOGO );
                        }
                    }
                }
            #endif
        }else{
            DrawRectangle(
                jogo.fase_atual.plataformas[ i ].x_0 ,
                jogo.fase_atual.plataformas[ i ].y ,
                pt_choque_efeito.x - TOL_GOLPE.x - jogo.fase_atual.plataformas[ i ].x_0  ,
                ALT_PLATAFORMAS ,
                COR_PLATAFORMA
            );

            #ifdef PLATAFORMA_ESPASSA
                for( int j = jogo.fase_atual.plataformas[ i ].x_0 ; j < pt_choque_efeito.x - TOL_GOLPE.x - jogo.fase_atual.plataformas[ i ].x_0 ; j++ ){
                    for( int i_a = jogo.fase_atual.plataformas[ i ].y ; i_a < jogo.fase_atual.plataformas[ i ].y + ALT_PLATAFORMAS ; i_a++ ){
                        if( !( j % e_len_i ) ){
                            DrawPixelV( (Vector2){ j , i_a } , COR_FUNDO_JOGO );
                        }
                    }
                }
            #endif

            DrawRectangle(
                pt_choque_efeito.x + TOL_GOLPE.x ,
                jogo.fase_atual.plataformas[ i ].y ,
                jogo.fase_atual.plataformas[ i ].x_f - ( pt_choque_efeito.x + TOL_GOLPE.x )  ,
                ALT_PLATAFORMAS ,
                COR_PLATAFORMA
            );

            #ifdef PLATAFORMA_ESPASSA
                for( int j = pt_choque_efeito.x + TOL_GOLPE.x ; j < jogo.fase_atual.plataformas[ i ].x_f - ( pt_choque_efeito.x + TOL_GOLPE.x ) ; j++ ){
                    for( int i_a = jogo.fase_atual.plataformas[ i ].y ; i_a < jogo.fase_atual.plataformas[ i ].y + ALT_PLATAFORMAS ; i_a++ ){
                        if( !( j % e_len_i ) ){
                            DrawPixelV( (Vector2){ j , i_a } , COR_FUNDO_JOGO );
                        }
                    }
                }
            #endif

            if( pt_choque_efeito.x - TOL_GOLPE.x > jogo.fase_atual.plataformas[ i ].x_0 )
                x0 = pt_choque_efeito.x - TOL_GOLPE.x;
            else
                x0 = jogo.fase_atual.plataformas[ i ].x_0;

            if( pt_choque_efeito.x + TOL_GOLPE.x < jogo.fase_atual.plataformas[ i ].x_f )
                xf = pt_choque_efeito.x + TOL_GOLPE.x;
            else
                xf = jogo.fase_atual.plataformas[ i ].x_f;

            cent = ( xf - x0 ) / 2.0;


            for( int j = x0 ; j < xf ; j++ ){
                for( int i_a = pt_choque_efeito.y ; i_a < pt_choque_efeito.y + ALT_PLATAFORMAS ; i_a++ ){
                    #ifdef MODO_DISCRETO
                        jr = ( j / g_len ) * g_len;
                        if( jr < x0 ) jr = x0;
                    #else
                        jr = j;
                    #endif

                    if( xf - x0 == 2 * TOL_GOLPE.x ){
//                        formula_kernel = ( ( cent - fabs( jr - x0 - cent ) ) / cent );
                        formula_kernel = 1 - pow( ( fabs( jr - x0 - cent ) / TOL_GOLPE.x ) , fator );
                    }else{
                        if( fabs( pt_choque_efeito.x - jogo.fase_atual.plataformas[ plat_efeito ].x_0 ) > fabs( pt_choque_efeito.x - jogo.fase_atual.plataformas[ plat_efeito ].x_f )  ){
                            formula_kernel = ( jr - x0 ) ;
                        }else{
                            formula_kernel = ( xf - jr );
                        }
                        formula_kernel /= (float)( xf - x0 );
                        formula_kernel = pow( formula_kernel , fator );
                    }

                    #ifdef MODO_ESPASSO
                        if( j % e_len )
                    #endif // MODO_ESPASSO

                    #ifdef MODO_ESPASSO_INVERSO
                        if( !( j % e_len_i ) )
                    #endif // MODO_ESPASSO

                    DrawPixelV( (Vector2){ j , i_a - ( delta * formula_kernel ) } , COR_PLATAFORMA );

                }
            }

        }
    }

    if( delay_efeito ){
        delay_efeito--;
        delta = 2 * ( (int)( DElAY_EFEITO_PLATF * FPS ) - abs( delay_efeito - (int)( DElAY_EFEITO_PLATF * FPS ) ) );
    }
    else flag_efeito = false;
}


void efeito_plataforma_distorcida( JOGO jogo ){
//    static bool flag_ativo = false;
//    static bool flag_cres = true;
//    static int delta = -1;
//
//    if( jogo.mario.pt_choque.x != -999 ){
//        flag_ativo = true;
//        flag_cres = true;
//        delta = 0;
//    }
//
//    if( flag_ativo ){
//
//        DrawRectangle(
//            jogo.mario.pt_choque.x - TOL_GOLPE.x ,
//            jogo.mario.pt_choque.y ,
//            TOL_GOLPE.x ,
//            ALT_PLATAFORMAS ,
//            BLACK
//        );
//        for( int j = jogo.mario.pt_choque.x - TOL_GOLPE.x ; j < jogo.mario.pt_choque.x + TOL_GOLPE.x ; j++ ){
//            for( int i = jogo.mario.pt_choque.y ; i <= jogo.mario.pt_choque.y + ALT_PLATAFORMAS ; i++ ){
////                DrawPixelV( (Vector2){ j , i } , GREEN );
//                DrawPixelV( (Vector2){ j , i + delta * ( jogo.mario.pt_choque.x - abs( ( jogo.mario.pt_choque.x - j ) ) / jogo.mario.pt_choque.x ) } , BLUE );
//            }
//        }
//        if( delta == DELTA_EFEITO_PLATF ) flag_cres = false;
//
//        delta += flag_cres ? 1 : -1;
//
//        if( delta == -1 ) flag_ativo = false;
//    }
}



void desenhar_moedas( JOGO jogo ){

}



void desenhar_inimigos( JOGO jogo ){
    Rectangle src , dst;
    Texture2D textura = jogo.src.sprite_geral;

    for( int i = 0 ; i < jogo.ini_lib_fase_atual[ 2 ] ; i++ ){
//        if( jogo.inimigos[ i ].vivo == true ){
        if( jogo.inimigos[ i ].pos.y <= jogo.output_devices.tela.alt ){
            if( jogo.inimigos[ i ].tipo == 1 )
                src = jogo.info_sprites.T1_SRC[ jogo.inimigos[ i ].status ];
            if( jogo.inimigos[ i ].tipo == 2 )
                src = jogo.info_sprites.T2_SRC[ jogo.inimigos[ i ].status ];
            dst = jogo.inimigos[ i ].pos;

            // Correções
            if( jogo.inimigos[ i ].tipo == 1 ){
                src.x += jogo.inimigos[ i ].frame_atual * 24;
                if( jogo.inimigos[ i ].sentido == ESQUERDA )
                    src.y += 20;
            }
            if( jogo.inimigos[ i ].tipo == 2 ){
                src.x += jogo.inimigos[ i ].frame_atual * 26;
                if( jogo.inimigos[ i ].sentido == ESQUERDA )
                    src.y += 0;
            }

            // Desenho
            DrawTexturePro(
                textura ,
                src ,
                dst ,
                V2_NULL ,
                0 ,
                jogo.inimigos[ i ].cor
            );
        }
    }
}



void desenhar_mario( JOGO jogo ){
//    DrawRectangleRec( jogo.mario.pos , jogo.mario.cor );
    Rectangle src = jogo.info_sprites.MARIO_SRC[ jogo.mario.status ];
    Rectangle dst = jogo.mario.pos;
    Color cor = jogo.mario.cor;
    static int delay_transp_invuln = 0;
    static int qtd_vidas_ant = QTD_VIDAS_DEF;

    // Efeito piscante após morte
    if( jogo.mario.vidas != qtd_vidas_ant )
        delay_transp_invuln = 3 * FPS;
    qtd_vidas_ant = jogo.mario.vidas;
    if( delay_transp_invuln % 5 && jogo.mario.status != SM_MORRENDO ){
        cor.a = 130;
//        cor.b -= 50;
//        cor.g -= 50;
    }
    if( delay_transp_invuln )
        delay_transp_invuln--;

    // Correções
    src.x += jogo.mario.frame_atual * src.width;
    if( jogo.mario.sentido == DIREITA )
        src.y += SRC_DELTA_SENTIDO;

    // Desenho
    DrawTexturePro(
        jogo.src.sprite_geral ,
        src ,
        dst ,
        V2_NULL ,
        0 ,
        cor
    );

}


void efeito_agua( JOGO jogo ){
    static int delay_efeito[ 4 ] = { 0 };
    static int qtd_efeitos = 0;
    static int x_efeito[ 4 ];
    static int y_efeito[ 4 ];
    static int frame[ 4 ] = { 0 };
    Rectangle src;

    for( int i = 0 ; i < jogo.ini_lib_fase_atual[ 2 ] ; i++ ){
        if( jogo.inimigos[ i ].pos.y == jogo.output_devices.tela.alt ){
            delay_efeito[ qtd_efeitos] = 1 * FPS;
            x_efeito[ qtd_efeitos ] = jogo.inimigos[ i ].pos.x;
            y_efeito[ qtd_efeitos ] = jogo.output_devices.tela.alt - ALT_EFEITO_AGUA;
            frame[ qtd_efeitos ] = 0;
            qtd_efeitos++;
            PlaySound( jogo.src.som_agua );
        }
    }
    if( jogo.mario.pos.y == jogo.output_devices.tela.alt ){
        delay_efeito[ qtd_efeitos] = 1 * FPS;
        x_efeito[ qtd_efeitos ] = jogo.mario.pos.x;
        y_efeito[ qtd_efeitos ] = jogo.output_devices.tela.alt - ALT_EFEITO_AGUA;
        frame[ qtd_efeitos ] = 0;
        qtd_efeitos++;
    }

    for( int j = 0 ; j < qtd_efeitos ; j++ )
        if( delay_efeito[ j ] ){
            delay_efeito[ j ] --;
            if( !( delay_efeito[ j ] % 5 ) )
                frame[ j ]++;
            if( frame[ j ] >= 12 )
                frame[ j ] = 0;

            if( delay_efeito[ j ] ){
//                DrawRectangle( x_efeito[ j ] , y_efeito[ j ] , 30 , 10 , SKYBLUE );
//                DrawRectangle( x_efeito[ j ] , y_efeito[ j ] , LARG_EFEITO_AGUA , ALT_EFEITO_AGUA , SKYBLUE );
                src = AGUA_SRC;
                src.x += 155 * ( frame[ j ] % 3 );
                src.y += 63 * ( frame[ j ] / 3 );
                DrawTexturePro(
                    jogo.src.sprite_agua ,
                    src ,
                    (Rectangle){
                        x_efeito[ j ] - LARG_EFEITO_AGUA / 2 + LARG_T1 / 2 ,
                        y_efeito[ j ] + 5 ,
                        LARG_EFEITO_AGUA ,
                        ALT_EFEITO_AGUA
                    } ,
                    V2_NULL ,
                    0 ,
                    WHITE
                );
            }else{
                qtd_efeitos--;
                for( int k = 0 ; k < qtd_efeitos ; k++ ){
                    delay_efeito[ k ] = delay_efeito[ k + 1 ];
                    x_efeito[ k ] = x_efeito[ k + 1 ];
                    y_efeito[ k ] = y_efeito[ k + 1 ];
                }
                if( j )
                    j--;
            }
        }

}


void exibe_nome_nova_fase( JOGO jogo ){
    static int tempo = TEMPO_EXIBIR_NOME_FASE * FPS;
    static char n_ant[ 30 ] = "";
    Font fonte = jogo.src.fonte_mario;
    static float f_size = 40;
    int spc = 4;
    int l_tela = jogo.output_devices.tela.larg;
    int h_tela = jogo.output_devices.tela.alt;
    char nome[ 30 ];
    static int trp = 0;
    static bool flag_trp = false;
    static int red = 0;
    static int green = 255;
    static int blue = 0;
    int tam;
    Color cor = (Color){ red , green , blue , trp };

    TextCopy( nome , jogo.fase_atual.nome );
    nome[ TextLength( nome ) - 4 ] = '\0';

    for( int i = 0 ; i < TextLength( nome ) ; i++ ){
        if( nome[ i ] =='/'  ||  nome[ i ] == '\\' ){
            tam = TextLength( nome );
            for( int j = i ; j <= tam ; j++ )
                nome[ j - i ] = nome[ j + 1 ];
            i--;
        }
    }

    if( !TextIsEqual( n_ant , nome ) ){
        tempo = TEMPO_EXIBIR_NOME_FASE * FPS;
        f_size = 40;
        trp = 0;
        flag_trp = false;
        red = 0;
        green = 255;
        blue = 0;


    }

    if( tempo ){
        DrawTextEx(
            fonte ,
            nome ,
            (Vector2){
                centraliza_textoEX( nome , l_tela , fonte , f_size , spc ),
                ( h_tela - f_size ) / 2.0
            } ,
            f_size ,
            spc ,
            cor
        );
        tempo--;
    }

    TextCopy( n_ant , nome );

    if( trp == 255 )
        flag_trp = true;
    else
        if( !flag_trp ){
            trp += 5;
            f_size ++;
            if( blue + 4 <= 255 )
                blue += 4;
        }


    if( flag_trp )
        if( trp ){
            trp -= 5;
            f_size--;
        }

}


void exibir_mensagem_sucesso_fase( JOGO jogo ){
    static int tempo = 0;
    Font fonte = jogo.src.fonte_mario;
    static float f_size = 40;
    int spc = 4;
    int l_tela = jogo.output_devices.tela.larg;
    int h_tela = jogo.output_devices.tela.alt;
    char nome[ 30 ];
    static int trp = 0;
    static bool flag_trp = false;
    static int red = 0;
    static int green = 255;
    static int blue = 0;
    Color cor = (Color){ red , green , blue , trp };



    if( jogo.ini_abtd_fase_atual >= jogo.fase_atual.qtd_inimigo_t1 + jogo.fase_atual.qtd_inimigo_t2 && !tempo ){
        tempo = TEMPO_EXIBIR_NOME_FASE * FPS;
        f_size = 40;
        trp = 0;
        flag_trp = false;
        red = 0;
        green = 255;
        blue = 0;
        printf( "\n ATIVA\128\199 DAS FLAGS" );
//        switch( nmr_rand( 1 , 3 ) ){
        switch( 1 ){
                case 1:
                    TextCopy( nome , "MUITO BEM!" );
                    break;
                case 2:
                    TextCopy( nome , "BRAVO!" );
                    break;
                case 3:
                    TextCopy( nome , "MISS\199O CUMPRIDA!" );
                    break;
        }
    }


    if( tempo ){
        printf( "\n%s" , nome );
        DrawTextEx(
            fonte ,
            nome ,
            (Vector2){
                centraliza_textoEX( nome , l_tela , fonte , f_size , spc ),
                ( h_tela - f_size ) / 2.0
            } ,
            f_size ,
            spc ,
            cor
        );
        tempo--;
    }

    if( trp == 255 )
        flag_trp = true;
    else
        if( !flag_trp ){
            trp += 5;
            f_size ++;
            if( blue + 4 <= 255 )
                blue += 4;
        }


    if( flag_trp )
        if( trp ){
            trp -= 5;
            f_size--;
        }

}


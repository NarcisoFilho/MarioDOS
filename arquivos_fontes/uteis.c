
#include "../headers_particulares/uteis.h"

float centraliza_texto( char *txt , float larg_tela , int tam_fonte ){
    return ( larg_tela - MeasureText( txt , tam_fonte ) ) / 2.0;
}

float centraliza_textoEX( char *txt , float larg_tela , Font fonte , float tam_fonte , int spc ){
    return ( larg_tela - MeasureTextEx( fonte , txt , tam_fonte , spc ).x ) / 2;
}

Vector2 centraliza_textoRec( Rectangle rec , char *txt , Font fonte , int tam_fonte , int spc ){
    Vector2 vec , tam_txt = MeasureTextEx( fonte , txt , tam_fonte , spc );

    vec.x = rec.x + ( rec.width - tam_txt.x ) / 2;
    vec.y = rec.y + ( rec.height - tam_txt.y ) / 2;

    return vec;
}

int nmr_rand( int n_min , int n_max ){
    return n_min + rand() % ( n_max - n_min + 1 );
}

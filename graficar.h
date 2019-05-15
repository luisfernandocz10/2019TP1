#ifndef _GRAFICAR_H_
#define _GRAFICAR_H_

#define MSJ_SCORE "score"
#define MSJ_TIME "time"
#define MSJ_FUEL "fuel"
#define MSJ_ALTITUD "altitud"
#define MSJ_HORIZONTAL_SPEED "horizontal speed"
#define MSJ_VERTICAL_SPEED "vertical speed"

struct opcion{
    char letra;
    const int (*caracter)[2];
    int longitud;
};
struct opcion opciones[] = {
    {'a',caracter_a,7},
    {'b',caracter_b,12},
    {'c',caracter_c,4},
	{'d',caracter_d,7},
	{'e',caracter_e,7},
	{'f',caracter_f,6},
	{'g',caracter_g,7},
	{'h',caracter_h,6},
	{'i',caracter_i,6},
	{'j',caracter_j,4},
	{'k',caracter_k,6},
	{'l',caracter_l,3},
	{'m',caracter_m,5},
	{'n',caracter_n,4},
	{'o',caracter_o,5},
	{'p',caracter_p,5},
	{'q',caracter_q,9},
	{'r',caracter_r,7},
	{'s',caracter_s,6},
	{'t',caracter_t,4},
	{'u',caracter_u,4},
	{'v',caracter_v,3},
	{'w',caracter_w,5},
	{'x',caracter_x,5},
	{'y',caracter_y,5},
	{'z',caracter_z,4},
	{'0',caracter_0,5},
	{'1',caracter_1,2},
	{'2',caracter_2,6},
	{'3',caracter_3,7},
	{'4',caracter_4,5},
	{'5',caracter_5,6},
	{'6',caracter_6,5},
	{'7',caracter_7,3},
	{'8',caracter_8,7},
	{'9',caracter_9,5},
	{' ',caracter_espacio,1},
};

const int (*opcion_letra(char letra))[2];
int opcion_caracter(char letra);
void graficar_cadena(char *cadena, int px, int py, int escala, SDL_Renderer *renderer);

#endif // _GRAFICAR_H_

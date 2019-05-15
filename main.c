//gcc -o pru caracteres.c main.c naves.c funciones.c -lSDL2 -lm -Wall -pedantic -std=c99
#include <SDL2/SDL.h>

#include "config.h"
#include "naves.h"

#include "funciones.h"
#include "caracteres.h"

#include <stdio.h>
#define MSJ_SCORE "score"
#define MSJ_TIME "time"
#define MSJ_FUEL "fuel"
#define MSJ_ALTITUD "altitud"
#define MSJ_HORIZONTAL_SPEED "horizontal speed"
#define MSJ_VERTICAL_SPEED "vertical speed"
#define ESCALA 10

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

//void gra(SDL_Renderer *renderer);
const int (*opcion_letra(char letra))[2];
void graficar_cadena(char *cadena, int px, int py, int escala, SDL_Renderer *renderer);
int opcion_caracter(char letra);
int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Lunar Lander");

	int dormir = 0;
	

	// BEGIN código del alumno
	// Mi nave:
	float **nave;
	float **chorro;
	float m;
	int x=1;
	// El chorro de la nave:
	const float chorro_nave[3][2] = {
		{-NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y},
		{0, NAVE_GRANDE_TOBERA_Y},
		{NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y}
	};
	
	size_t nave_tam = sizeof(nave_grande) / sizeof(nave_grande[0]);
	size_t chorro_tam = sizeof(chorro_nave) / sizeof(chorro_nave[0]);
	
	nave = matriz_a_vector(nave_grande, nave_tam );
	chorro = matriz_a_vector(chorro_nave, chorro_tam );
	
	//escalamos
	escalar(nave, nave_tam,ESCALA);
	escalar(chorro, chorro_tam ,ESCALA);
	
	imprimir_matriz(chorro, chorro_tam);
	
	rotar(nave,nave_tam,NAVE_ANGULO_INICIAL);
	rotar(chorro,chorro_tam,NAVE_ANGULO_INICIAL);
	
	imprimir_matriz(chorro, chorro_tam);					

	// Queremos que todo se dibuje escalado por f:
	//trasladar(nave,nave_tam,100,700);
	//trasladar(chorro, chorro_tam,100,700);

	//rotar(nave,nave_tam,1.57);
	

	// END código del alumno

	unsigned int ticks = SDL_GetTicks();
	while(1) {
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				// BEGIN código del alumno
				
				switch(event.key.keysym.sym) {
					case SDLK_UP:
						// Agrandamos el dibujo del chorro:
						
						m = (chorro[1][1] - chorro[2][1])/(chorro[1][0] - chorro[2][0]);
						chorro[1][0] += x;
						chorro[1][1] += (chorro[1][0]-x)/m+chorro[1][1];
						imprimir_matriz(chorro, chorro_tam);
						break;
					case SDLK_DOWN:
						// Achicamos el dibujo del chorro:
						
						chorro[1][0] += 1;
						imprimir_matriz(chorro, chorro_tam);
						break;
					case SDLK_RIGHT:
						rotar(nave,nave_tam,NAVE_ROTACION_PASO);
						rotar(chorro,chorro_tam,NAVE_ROTACION_PASO);
						imprimir_matriz(chorro, chorro_tam);
						break;
					case SDLK_LEFT:
						rotar(nave,nave_tam,-NAVE_ROTACION_PASO);
						rotar(chorro,chorro_tam,-NAVE_ROTACION_PASO);
					break;
						
				}
				// END código del alumno


			}
			continue;
		}
        	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        	SDL_RenderClear(renderer);
        	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);


		// BEGIN código del alumno
		// Dibujamos la nave escalada por f en el centro de la pantalla:
		for(int i = 0; i < nave_tam - 1; i++)
			SDL_RenderDrawLine(
				renderer,
				nave[i][0] + NAVE_X_INICIAL,
				VENTANA_ALTO - nave[i][1] - NAVE_Y_INICIAL ,
				nave[i+1][0] + NAVE_X_INICIAL ,
				VENTANA_ALTO - nave[i+1][1] - NAVE_Y_INICIAL 
			);

		// Dibujamos el chorro escalado por f en el centro de la pantalla:
		for(int i = 0; i < 3 - 1; i++)
			SDL_RenderDrawLine(
				renderer,
				chorro[i][0] + NAVE_X_INICIAL ,
				VENTANA_ALTO - chorro[i][1] - NAVE_Y_INICIAL ,
				chorro[i+1][0] + NAVE_X_INICIAL ,
				VENTANA_ALTO - chorro[i+1][1] - NAVE_Y_INICIAL 
			);
		
		for (int i = 0; i < 11; i++)
		{
			SDL_RenderDrawLine(renderer,i*100,0,i*100,100);
		}
		for (int i = 0; i < 8; i++)
		{
			SDL_RenderDrawLine(renderer,0,i*100,100,i*100);
		}
	
		

		graficar_cadena("casa de pepe y lisa 123456789",500,600,3,renderer);
		
		


		// END código del alumno


        	SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
		if(dormir) {
			SDL_Delay(dormir);
			dormir = 0;
		}
		else if(ticks < 1000 / JUEGO_FPS)
			SDL_Delay(1000 / JUEGO_FPS - ticks);
		ticks = SDL_GetTicks();
	}

	// BEGIN código del alumno
	// No tengo nada que destruir.
	// END código del alumno

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

const int (*opcion_letra(char letra))[2]
{
    size_t cantidad = sizeof(opciones)/(sizeof(opciones[0]));
    for (int i = 0; i < cantidad; i++)
    {
        if(opciones[i].letra == letra)
            return opciones[i].caracter;
    }
    return NULL;
}
int opcion_caracter(char letra)
{
    size_t cantidad = sizeof(opciones)/(sizeof(opciones[0]));
    for (int i = 0; i < cantidad; i++)
    {
        if(opciones[i].letra == letra)
            return opciones[i].longitud;
    }
    return 0;
} 



void graficar_cadena(char *cadena, int px, int py , int escala, SDL_Renderer *renderer)
{
	const int (*aux)[2];
	for (int j = 0; cadena[j] != '\0'; j++)
	{
		
		aux = opcion_letra( cadena[j] );
		for (int i = 0; i < opcion_caracter(cadena[j])-1; i++)
		{
			SDL_RenderDrawLine(renderer,
				escala*aux[i][0] + px + j*escala*CARACTER_ANCHO,
				VENTANA_ALTO - escala*aux[i][1]-py,
				escala*aux[i+1][0] + px + j*escala*CARACTER_ANCHO,
				VENTANA_ALTO - escala*aux[i+1][1] - py
				);
		}
		
	}
}

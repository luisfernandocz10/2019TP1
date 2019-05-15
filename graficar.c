#include <SDL2/SDL.h>
#include "caracteres.h"
#include "graficar.h"
#include "config.h"

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
				escala * aux[i][0] + px + j * escala * CARACTER_ANCHO,
				VENTANA_ALTO - escala * aux[i][1] - py,
				escala * aux[i+1][0] + px + j * escala * CARACTER_ANCHO,
				VENTANA_ALTO - escala * aux[i+1][1] - py
				);
		}
		
	}
}


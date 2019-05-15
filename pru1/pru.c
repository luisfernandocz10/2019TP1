#include <stdio.h>
struct opcion{
    char letra;
    const int *caracter;
    int longitud;
};
const int caracter_a[7][2] = {
	{0, 0},
	{0, 4},
	{2, 6},
	{4, 4},
	{4, 0},
	{4, 2},
	{0, 2}
};

const int caracter_b[12][2] = {
	{0, 3},
	{0, 6},
	{3, 6},
	{4, 5},
	{4, 4},
	{3, 3},
	{0, 3},
	{0, 0},
	{3, 0},
	{4, 1},
	{4, 2},
	{3, 3},
};

const int caracter_c[4][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
};

struct opcion opciones[] = {
    {'a',&caracter_a[0][0],7},
    {'b',&caracter_b[0][0],12},
    {'c',&caracter_c[0][0],4},

};

int *opcion_letra(char letra);

int main() {

	const int *ml;
	ml=opcion_letra('a');
	for (int i = 0; i < 4; i++)
	{
		printf("%d\n",*(ml+i));
	}
	
  /*int (*w)[2]=opcion_letra('a');
  printf("%d**%d**%d*%d",w[0][0],w[0][1],w[1][0],w[1][1]);*/


  return 0;
}
int *opcion_letra(char letra)
{
    size_t cantidad = sizeof(opciones)/(sizeof(opciones[0]));
    for (int i = 0; i < cantidad; i++)
    {
        if(opciones[i].letra == letra)
            return opciones[i].caracter;
    }
    return NULL;
} 

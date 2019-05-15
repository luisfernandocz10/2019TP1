/* Como compilar
gcc pru21.c -o pru21 -Wall -std=c99 -pedantic 
valgrind ./pru21
indent -kr pru21.c -o pru21.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COL 2

float **matriz_a_vector(const float m[][2], size_t n);
float **densificar_vector(float **v, size_t nv, size_t nn, float margen);
float **copiar_vector(float **m, size_t n);
float float_rand(float min, float max);

void destruir_vector(float **v, size_t n, size_t m);
void sort_bubble(float **x, int nn);
void imprimir_matriz(float **x, size_t fil, size_t col);

int main()
{
    const float p[][COL] = { {2, 3}, {5, 6}, {10, 4}, {12, 8}, {19, 5} };
    float **x, **z;

    srand(time(NULL));

    x = matriz_a_vector(p, 5);

    z = densificar_vector(x, 5, 23, 2);

    imprimir_matriz(z, 23, COL);

    destruir_vector(z, 23, COL);
    destruir_vector(x, 5, COL);

    return 0;
}

/* Funcion que copia una matriz a un vector dinamico.
La funcion recibe un una matriz (m) y la candidad de filas (n)*/
float **matriz_a_vector(const float m[][2], size_t n)
{
    float **arr = (float **) malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++)
	arr[i] = (float *) malloc(2 * sizeof(float));

    // sabemos que arr[i][j] es equivalente a *(*(arr+i)+j) 
    for (int i = 0; i < n; i++)
	for (int j = 0; j < 2; j++)
	    arr[i][j] = m[i][j];

    return arr;
}
/* Funcion que agrega mas coordenadas (nn) aleatoriamente a una matriz 
dinamica (**v) que previamente tiene una cantidad de coordenadas (nv),
dentro un margen (margen) y retorna un puntero doble a la matriz 
dinamica densificada */
float **densificar_vector(float **v, size_t nv, size_t nn, float margen)
{
    float **aux;

    aux = copiar_vector(v, nv);

    aux = (float **) realloc(aux, nn * sizeof(*aux));
    for (int i = nv; i < nn; i++)
	aux[i] = (float *) malloc(2 * sizeof(float));

    float m, y;
    for (int i = nv; i < nn; i++) {
	aux[i][0] = float_rand(aux[nv - 1][0], aux[0][0]);
	for (int j = 0; j < nv; j++) {
	    // verifica dentro de que intervalo cae
	    if (aux[j][0] <= aux[i][0] && aux[i][0] <= aux[j + 1][0]) {
		//calcula la pendiente entre intervalo
		m = (aux[j + 1][1] - aux[j][1]) / (aux[j + 1][0] -aux[j][0]);
		// Encunetra el valor y perteneciante a la recta 
		y = m * (aux[i][0] - aux[j][0]) + aux[j][1];
		aux[i][1] = float_rand(y + margen, y - margen);
	    }

	}
    }
    sort_bubble(aux, nn);

    return aux;
}

/* Copia un vector dinamico a otro vector dinamico*/
float **copiar_vector(float **m, size_t n)
{
    float **arr = (float **) malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++)
	arr[i] = (float *) malloc(2 * sizeof(float));

    // sabemos que arr[i][j] es equivalente a *(*(arr+i)+j) 
    for (int i = 0; i < n; i++)
	for (int j = 0; j < 2; j++)
	    arr[i][j] = m[i][j];

    return arr;
}

/* Dado un intervalo devuelve un numero con decimales aleatorio acotado*/
float float_rand(float min, float max)
{
    float scale = rand() / (float) RAND_MAX;	/* [0, 1.0] */
    return min + scale * (max - min);	/* [min, max] */
}


/* Funcion que recibe un puntero doble (matriz dinamica) y la 
candidad de filas (n) y la cantidad de columnas (m) */
void destruir_vector(float **v, size_t n, size_t m)
{
    for (int i = 0; i < n; i++) {
	free(v[i]);
    }
    free(v);
}

/* Funcion que ordena una matriz dinamica por ordenamiento burbuja.
la funcion recibe un puntero doble (v) y la cantidad de de 
coordenada (nn) */
void sort_bubble(float **v, int nn)
{
    float *aux = NULL;

    for (int i = 1; i < nn; i++) {
	for (int j = 0; j < nn - 1; j++) {

	    if (v[j][0] > v[j + 1][0]) {
		aux = v[j];
		v[j] = v[j + 1];
		v[j + 1] = aux;
	    }
	}

    }
}

/* funcion que imprime matriz*/
void imprimir_matriz(float **x, size_t fil, size_t col)
{
    for (int i = 0; i < fil; i++) {
	for (int j = 0; j < col; j++) {
	    printf("| %f |", x[i][j]);

	}
	printf("\n");

    }
}

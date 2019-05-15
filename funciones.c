#include<stdio.h>
#include<stdlib.h>
#include<math.h>
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

void trasladar(float **v, int n, float dx, float dy)
{
	for (int i = 0; i < n; ++i)
	{
		v[i][0] += dx;
        v[i][1] += dy;
	}	
}
void escalar(float **v, int n, int escala)
{
	for (int i = 0; i < n; ++i)
	{
		v[i][0] *= escala;
        v[i][1] *= escala;
	}	
}
void rotar(float **coordenadas, int n, double rad)
{
    float aux;
    float cos_aux = cos(rad);
    float sen_aux = sin(rad);
    for (int i = 0; i < n; i++)
    {
        aux = coordenadas[i][0];
        coordenadas[i][0] = aux*cos_aux-coordenadas[i][1]*sen_aux;
        coordenadas[i][1] = aux*sen_aux+coordenadas[i][1]*cos_aux;   
    }    
}
void imprimir_matriz(float **coordenadas, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			printf("\t%-.5f\t", coordenadas[i][j] );
		}
		printf("\n");
	}
	printf("\n");
}



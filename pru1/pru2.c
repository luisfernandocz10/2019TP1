//valgrind ./pru2

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#define COL 2
void destruir_vector(float **v, size_t n, size_t m);
float **matriz_a_vector(const float m[][2], size_t n);
float **densificar_vector(float **v, size_t nv, size_t nn, float margen);
void sort_bubble(float **x,int nn);
float float_rand( float min, float max );
void imprimir_matriz(float **x,size_t fil,size_t col);
int main() 
{ 
    const float p[][COL]={{2,3},{5,6},{10,4},{12,8},{19,5}};
    float **x;
   
    srand (time(NULL));
    
    x = matriz_a_vector(p,5);
    
    x = densificar_vector(x,5,23,2);
    imprimir_matriz(x,23,COL);
    
    destruir_vector(x,23, 2);
return 0; 
} 
/* Funcion que recibe un puntero doble (matriz dinamica) y la 
candidad de filas (n) y la cantidad de columnas (m) */
void destruir_vector(float **v, size_t n, size_t m){
    for (int i = 0; i < n; i++)
    {
        free(v[i]);
    }
    free(v);
    
}
/* Funcion que copia una matriz a un vector dinamico.
La funcion recibe un una matriz y la candidad de filas n */
float **matriz_a_vector(const float m[][2], size_t n)
{
    float **arr = (float **)malloc( n * sizeof(float *));
    for (int i=0; i<n; i++) 
        arr[i] = (float *)malloc( 2* sizeof(float)); 

    // sabemos que arr[i][j] es equivalente a *(*(arr+i)+j) 
    for ( int i = 0; i < n ; i++)
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
    
    v=(float **)realloc(v,nn*sizeof(*v));
    for (int i=nv; i<nn; i++) 
        v[i] = (float *)malloc( 2* sizeof(float));

    float m,y;
    for (int i = nv; i < nn; i++)
    {
        v[i][0] = float_rand(v[nv-1][0],v[0][0]);
        for (int j = 0; j < nv; j++)
        {
            
            if(v[j][0]<= v[i][0] && v[i][0]<=v[j+1][0])
            {
                m=(v[j+1][1]-v[j][1])/(v[j+1][0]-v[j][0]);
                y=m*(v[i][0]- v[j][0])+v[j][1];
                v[i][1]=float_rand(y+margen,y-margen);
            }

        }
    }
    sort_bubble(v,nn);

    return v;
}


/* ordena una matriz mediante el ordenamiento burbuja */
void sort_bubble(float **v,int nn)
{
    float *aux= NULL;
    int cambios;
    do{
        for (int i = 0; i < nn-1; i++)
        {
            cambios =0;
            if (v[i][0] > v[i+1][0]){
                aux=v[i];
                v[i]=v[i+1];
                v[i+1]=aux;
                cambios++;
            }
            
        }
    }while(cambios != 0);
}
/* dado un intervalo devuelve un numero con decimales aleatorio acotado*/
float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}
/* funcion que imprime matriz*/
void imprimir_matriz(float **x,size_t fil,size_t col)
{
	for (int i=0;i<fil;i++)
	{	
		for (int j=0;j<col;j++)
		{	
		printf("| %f |",x[i][j]);					

		}
		printf("\n");

	}
}
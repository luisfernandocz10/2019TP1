#include <stdio.h>
#include <math.h>

void rotar(float coordenadas[][2], int n, double rad);
void imprimir_matriz(float coordenadas[][2], int n);
int main() {
  float a[][2]={{0,0},{5,5},{1,6}};
  rotar(a,3,1.570796327);
  imprimir_matriz(a,3);
  return 0;
}
void rotar(float coordenadas[][2], int n, double rad)
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
void imprimir_matriz(float coordenadas[][2], int n)
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
/*compilar con
gcc pru3.c -o pru3 -Wall -std=c99 -pedantic  
o
gcc pru3.c -o pru3 -Wall -std=c99 -pedantic
./pru3
*/
#include <stdio.h>
struct opcion{
    char letra;
    int (*caracter)[2];
    int longitud;
};

int caracter_a[][2]={{3,2},{5,8},{7,9}};

struct opcion opciones[] = {
    {'a',caracter_a,7}
};

int *opcion_letra(char letra);


struct dato{
	char letra;
    int *ptr;
    int longitud;
};
struct dato datos[] = {
	{'a',&caracter_a[0][0],7}
};

int *opcion_letra1(char letra);
int main() {
	
    int a[]={1,2,3,4,5,6};
    int b[][2]={{4,8},{5,9},{7,3}};
    int (*c)[3], (*d)[2], *e[2];
    int *ptr1, *ptr2, *ptr3,*ptr4;
    // asigno arreglo a un punter
    ptr1 = a;
    printf("%p**%p\n",(void*)a, (void*)ptr1);
// (1)	
    //asigno una matriz a un puntero
    ptr2 = &b[0][0];
    printf("%d\n",*ptr2 );	
//(2)
    // asigno un arreglo a un (*c)[3] puntero a un  arreglo de 3 int 
    c = &a[0];
    printf("%d\n",c[1][1] );
    //	asigno una matriz a un (*d)[2] puntero a un arreglo de 2 int
    // no presenta warning	
    d = b;
    printf("%d***%d\n",d[1][1],*(d+1)[0] );
// (3) Devuelve un puntero
    ptr3 = opcion_letra('a');
    printf("%d***%d\n",*(ptr3+1),*(ptr3+4 ));
// (4)
    //d = ptr3;
// nota: solo puedo acceder al primer elento al que apunta
    // no puedo hacer esto *(e+1)[1]
    e[0]=opcion_letra('a');
    e[1]=ptr3;
    printf("%p**%p\n", (void*)e[0], (void*)e[1]);
// otra dforma de definir la estructura dato
    ptr4 = opcion_letra1('a');
    printf("%d\n",*(ptr4+2) );



  return 0;
}

int *opcion_letra(char letra)
{
    size_t cantidad = sizeof(opciones)/(sizeof(opciones[0]));
    for (int i = 0; i < cantidad; i++)
    {
        if(opciones[i].letra == letra)
            // (3)
            return &opciones[i].caracter[0][0];
    }
    return NULL;
}
int *opcion_letra1(char letra)
{
    size_t cantidad = sizeof(datos)/(sizeof(datos[0]));
    for (int i = 0; i < cantidad; i++)
    {
        if(datos[i].letra == letra)
            // (3)
            return datos[i].ptr;
    }
    return NULL;
}
    /*
	**************(1)************
    Si intentamos poner ptr2 = b o ptr2 = &b tira un warning:
    gcc: assignment from incompatible pointer type [-Wincompatible-pointer-types]
	clang: warning: incompatible pointer types assigning to 'int *' from
      'int [3][2]' [-Wincompatible-pointer-types]
	Para coregirlo usamos ptr2 = &b[0][0] 

	***************(2)*************
	Al colocar de esta forma c = &a[0] aparece esto:
	warning: assignment from incompatible pointer type [-Wincompatible-pointer-types]
    c = &a[0];

    pero al ejecutarlo ./pru3  e imprimiedo un valor no presenta 
    problemas

    **************(3)*******
    dentro de la funcion opcion_letra
	la forma de retornar es:
    return &opciones[i].caracter[0][0];
    
    si omitimos & con clang tira un warning :
    warning: incompatible integer to pointer conversion returning
      'int' from a function with result type 'int *'; take the address with &
      [-Wint-conversion]
            return opciones[i].caracter[0][0];
                   ^~~~~~~~~~~~~~~~~~~~~~~~~~
                   &
	con gcc:
	warning: return makes pointer from integer without a cast [-Wint-conversion]
             return opciones[i].caracter[0][0];
	
	si nos olvidamos de [0][0]:
	clang:
	warning: incompatible pointer types returning 'int (**)[2]' from a
      function with result type 'int *' [-Wincompatible-pointer-types]
            return &opciones[i].caracter;
                   ^~~~~~~~~~~~~~~~~~~~~
    gcc:
     warning: return from incompatible pointer type [-Wincompatible-pointer-types]
             return &opciones[i].caracter;

	**************(4)**************
	warning: incompatible pointer types assigning to 'int (*)[2]' from
      'int *' [-Wincompatible-pointer-types]
    d = ptr3;

    no es posible pensarlo como ques si d espera dos elemy¿tos 

		*/

	
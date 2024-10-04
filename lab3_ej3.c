#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 5
int findLargestLine(int matriz[][SIZE]) {
    int MayorCantidadde1s = 0; 
    int ConteoMomentaneode1s = 0;  
 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
		printf("i:%d, j:%d-val%d", i,j, matriz[i][j]);
	printf(" \n");
            if (matriz[i][j] == 1) {
                ConteoMomentaneode1s++;
            } else {
                if (ConteoMomentaneode1s > MayorCantidadde1s) {
                    MayorCantidadde1s = ConteoMomentaneode1s;
                }
                ConteoMomentaneode1s = 0;
            }
        }
        if (ConteoMomentaneode1s > MayorCantidadde1s) {
            MayorCantidadde1s = ConteoMomentaneode1s;
        }
    }

    return MayorCantidadde1s;
}

void printMatriz(int matriz[][SIZE]) {
    printf("Matriz:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");  // Imprime una nueva línea al final de cada fila
    }
    printf("\n");
}

// Función para llenar la matriz de forma aleatoria
void MatrizRandom(int matriz[][SIZE]) {
    // Inicializa la semilla para el generador de números aleatorios
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matriz[i][j] = rand() % 2;  // Genera un número aleatorio 0 o 1
        }
    }
}

int main() {
    // Definimos una matriz binaria
    int matriz[SIZE][SIZE];

    // Llenamos la matriz de manera aleatoria
    MatrizRandom(matriz);

    // Imprimimos la matriz
    printMatriz(matriz);

    int largestLine = findLargestLine(matriz);
    printf("El tamaño de la secuencia de 1s más grande es: %d\n", largestLine);

    return 0;
}

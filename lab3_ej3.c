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
        printf("\n");  
    printf("\n");
}


void MatrizRandom(int matriz[][SIZE]) { // Función matrizrandom
    // Inicializa la semilla para el generador de números aleatorios
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matriz[i][j] = rand() % 2;  
        }
    }
}

int main() {
    int matriz[SIZE][SIZE];
    MatrizRandom(matriz);
    printMatriz(matriz);
    int largestLine = findLargestLine(matriz);
    printf("El tamaño de la secuencia de 1s más grande es: %d\n", largestLine);

    return 0;
}

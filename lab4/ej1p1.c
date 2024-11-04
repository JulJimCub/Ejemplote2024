#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para encontrar la longitud de la linea más larga de 1s en una matriz cuadrada de tamaño size.
void findLargestLine(int **matrix, int size, int *result) {
    int largestSequence = 0;
    int currentSequence = 0;
    // Punteros
    int *ptr = *matrix;
    for (int i = 0; i < size * size; i++) {
        if (*ptr == 1) {
            currentSequence++; 
        } else {
            if (currentSequence > largestSequence) {
                largestSequence = currentSequence;
            }
            currentSequence = 0;
        }
        ptr++;  
    }

    if (currentSequence > largestSequence) {
        largestSequence = currentSequence;
    }

    *result = largestSequence;
}

// Función para reservar la matriz en memoria dinámica.
void allocateMatrix(int ***matrix, int size) {
    *matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        (*matrix)[i] = (int *)malloc(size * sizeof(int));
    }
}

// Función para llenar la matriz con números aleatorios (0s y 1s)
void fillMatrix(int **matrix, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(matrix + i) + j) = rand() % 2;
        }
    }
}

// Función para imprimir la matriz
void printMatrix(int **matrix, int size) {
    printf("Matrix (%dx%d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

//Función para calcular la matriz transpuestaMatrix
void transpuesta(int **matrix, int **transpuestaMatrix, int size) {
	for (int i=0; i<size; i++){
		for (int j=0; j<size;j++){
		       *(*(transpuestaMatrix + j)+i) = *(*(matrix + i) +j);
		}
	}
}


// Función para liberar la memoria asignada a la matriz
void freeMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Función principal
int main() {
    int size;
    int largestLine;
    int **matrix = NULL;
    int **transpuestaMatrix = NULL;

    printf("Ingrese el tamaño de la matriz: ");
    scanf("%d", &size);
    allocateMatrix(&matrix, size);
    fillMatrix(matrix, size);
    printMatrix(matrix, size);
    findLargestLine(matrix, size, &largestLine);
    printf("El tamaño de la secuencia de 1s más grande en la primera matriz es: %d\n", largestLine);


    allocateMatrix(&transpuestaMatrix, size);
    transpuesta(matrix, transpuestaMatrix, size);
    printf("\nMatriz transpuesta\n");
    printMatrix(transpuestaMatrix, size);
    findLargestLine(transpuestaMatrix, size, &largestLine);
    printf("El tamaño de la secuencia de 1s más grande en la matriz transpuestaMatrix es: %d\n", largestLine); 
    freeMatrix(matrix, size);
    freeMatrix(transpuestaMatrix, size);
    return 0;
}

#include <stdio.h>
#define N 3
/*
 * Descripción del programa: El programita aquí si Diosito así lo quiere, porque de mi parte lo veo dudoso va a bretear en cualquier matriz cuadrada, aunqeu ya queda en el usuario agregar las valores en la matriz y hacerla del tamaño que guste, finalmente dará la suma de las diagonale
 * Autor: Julián Jiménez Cubero
 * Licencia: UCR?? idk

*/
int main() {
    int matriz[N][N] = {
        {1, 2, 3},
        {8, 124, 9},
        {2, 8, 69}
    };
   
    int suma_diagonal_sureste = 0;
    int suma_diagonal_suroeste_osea_pal_otro_lado = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("i:%d - j:%d val:%d ", i, j, matriz[i][j]);
        }
        printf("\n");
    }
   
    for (int a = 0; a < N; a++) {
        suma_diagonal_sureste += matriz[a][a];
        suma_diagonal_suroeste_osea_pal_otro_lado += matriz[a][N - 1 - a]; 
    }

    printf("Suma de la diagonal sureste: %d\n", suma_diagonal_sureste);
    printf("la otra suma diagonal, la que es pal otro lado: %d\n", suma_diagonal_suroeste_osea_pal_otro_lado);
    printf("Suma de ambas: %d\n", suma_diagonal_sureste + suma_diagonal_suroeste_osea_pal_otro_lado);
    return 0;
}

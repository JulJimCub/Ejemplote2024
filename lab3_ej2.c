#include <stdio.h>
int factorial(int n) {
    int i = 1;
    while (n > 1) {
        i = i * n;
        n = n - 1;  //Aquí sería la corrección, el int está redefiniendo el n y eso es un error y tal vez un horror
    }
    return i;
}

int main() { //Aquí se permite que el usuario ingrese su número favorito
    int numero_favoritisimo;    
    printf("Ingrese su número favoritisimo, preferiblemente por su compu que sea menor de 50 ");
    scanf("%d", &numero_favoritisimo);   
    int resultado= factorial(numero_favoritisimo);
    printf("Asistente, usa el mismo número para todos los labs o o va cambiando? Salu2");
	printf("El factorial de %d es: %d\n", numero_favoritisimo, resultado);
    
    return 0;
}

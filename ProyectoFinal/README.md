<p align="center">
    IE-0117
    Programación Bajo Plataformas Abiertas
    <br>
  </p>
</p>

Este repositorio contiene el código del proyecto final del curso IE0117 del segundo semestre 2024.

Responsables: 

Julián Jiménez Cubero C24012

Mauricio Zeledón Zúñiga C18717

Leonardo Vidal Alfaro C18472

## Tabla de contenidos

- [Descripción](#Descripción)
- [Dependencias e instalación](#Dependencias-e-instalación)
- [Ejecución](#Ejecución)

# Descripción 

Para el proyecto final del curso Programación Bajo Plataformas Abiertas se realizó un código en C++ utilizando librerías de código abierto para realizar un programa con una interfaz gráfica de una lista de tareas que pueda ser utilizada por estudiantes universitarios. Desarrollar este código fue posible gracias a aplicar conceptos vistos en el curso como el uso de librerias implementadas por terceros y estructuras logicas aplicadas en el lenguaje C++. Este codigo tiene un diseño y funcionalidad sencillos, lo que lo hace adaptable para diversos contextos, desde uso personal hasta soluciones para grupos de trabajo en el ambito universitario.

Tenga las siguientes consideraciones para ejecutar el código.

- Editor de su preferencia
- Compilador de C++ (g++)
- Si utiliza Sistema Operativo Windows debe tener MinGW o similar

# Dependencias e instalación

El código utiliza varias librerías importantes para suy funcionamiento, tanto estándar como específicas para ciertas tareas:

Las siguientes librerías están incluidas en el compilador por lo que no es necesario instalar dependencias externas para ellas.
- <stdio.h>
- <stdlib.h>
- <string.h>
  
La librería utilizada para utilizar la base de datos SQlite
- <sqlite3.h>
```
sudo apt update
sudo apt install libsqlite3-dev
```
  
La librería de la interfaz gráfica
- <gtk/gtk.h>
  
Esta se puede instalar con
```
sudo apt update
sudo apt install libgtk-3-dev
```

# Ejecución

En la carpeta _ProyectoFinal-IE0117_

1. Para compilar el programa ejecute:

```
gcc main.c -o todolist pkg-config --cflags --libs gtk+-3.0  -lsqlite3 
```

2. Para ejecutar el programa ejecute:
```
./todolist
```

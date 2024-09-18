#!/bin/bash
PID=$1
if [ -z "$1" ]; then
    echo "Uso: $0 como PID"
    exit 1
else
	echo "genial, realmente sabes como digitar esos 4 numeros ;)"
fi  
###
if ! ps -p $PID > /dev/null 2>&1 ; then
    echo "El proceso con PID $PID no existe."
    exit 2
else
	echo "sos un crack asistente, pero estás usando el mismo PID para todos o usas ps para elegir uno?"
fi
###
NOMBRE=$(ps -p $PID -o comm=)
echo "a)Nombre del proceso: $NOMBRE"
PPID=$(ps -p $PID -o ppid=)
echo "b)ID del proceso: $PID"
echo "c)Parent Process ID: $PPID"
USUARIO=$(ps -p $PID -o user=)
echo "d)Usuario propietario: $USUARIO"
CPU=$(ps -p $PID -o %cpu=)
echo "e)Porcentaje de uso de CPU al momento de correr el script: $CPU%"
MEMORIA=$(ps -p $PID -o %mem=)
echo "f)Consumo de memoria: $MEMORIA%"
ESTADO=$(ps -p $PID -o stat=)
echo "g)Status: $ESTADO"
EJECUTABLE=$(readlink -f /proc/$PID/exe)
echo "h)Path del ejecutable: $EJECUTABLE"

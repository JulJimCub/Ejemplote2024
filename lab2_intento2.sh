#!/bin/bash
proceso_excentrico=$1
comando_excentrico=$2

if [ $# -ne 2 ]; then
    echo "Uso: $0 proceso ni comando"
    exit 1
else
	echo "nonono es el primer paso y ya estas devorando"
fi

###

funcion_excentrica() {
    if pgrep "$proceso_excentrico" > /dev/null; then
        echo "'$proceso_excentrico' está en ejecucion, esto no suele pasar a la primera :D"
    else
        echo "El proceso '$proceso_excentrico' no está en ejecución, asi que lo vamos a reiniciar infinitamente hasta que se ejecute"
        eval "$comando_excentrico &"
	echo "'$proceso_excentrico' reiniciado por las malas >:)"
    fi
}



###
while true; do
	funcion_excentrica
    sleep 5
done

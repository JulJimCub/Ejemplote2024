#!/bin/bash
comando=$1
log_file="cpu_log.txt"
temp_file="temp_process.txt"

if [ $# -ne 1 ]; then
    echo "Uso: $0 lo que sea menos un comando"
    exit 1
fi
###
rm -f $log_file

echo "Ahorita se esta jecutando: $comando"
$comando &
pid=$!
echo "Proceso: $pid"
###
echo "timestamp, cpu%, mem%" > $log_file
while kill -0 $pid 2> /dev/null; do
    cpu_info=$(ps -p %cpu= -p $pid )
    mem_info=$(ps -o %mem= -p $pid )
    
    fecha=$(date +"%Y-%m-%d %H:%M:%S")
    
    echo "$fecha, $cpu_info, $mem_info" >> $log_file
    
    sleep 10
done

echo "Proceso terminadisimo, no se duerma que todavía falta el otro ejercicio"

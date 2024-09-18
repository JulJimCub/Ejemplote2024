#!/bin/bash

directorio_bien_cuidado="/ruta/al/directorio"
log_file="/ruta/al/directorio/directory_monitor.log"
###
inotifywait -m -r -e create -e modify -e delete --format '%w%f %e' "$directorio_bien_cuidado" | while read archivo evento
do
    echo "$(date '+%Y-%m-%d %H:%M:%S') - Archivo: $archivo - Evento: $evento" >> "$LOG_FILE"
done
~                                                    
~                          

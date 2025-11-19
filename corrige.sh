#! /bin/bash

ficheros_requeridos=("Metadata.h" "Metadata.cc" "Word.h" "Word.cc" "DictionaryEntry.h" "DictionaryEntry.cc" "Dictionary.h" "Dictionary.cc" "List.h" "List.cc" "OrderedDictionary.h" "OrderedDictionary.cc" "approximate.cc")
clases_compiladas="Metadata.o Word.o DictionaryEntry.o Dictionary.o List.o OrderedDictionary.o"
aplicacion=approximate
directorio=pruebas
compilador=g++
valgrind="valgrind"

function comprobar_valgrind() {
    if ! command -v valgrind &> /dev/null; then
        echo "AVISO: El corrector se ejecutará sin valgrind, por lo que es posible que"
        echo "el resultado de la corrección no sea fiable. Para comprobar realmente que la"
        echo "práctica es correcta, debes probar el corrector en un ordenador Linux"
        echo "con valgrind instalado antes de la entrega."
        echo
        read -p "Pulsa [Enter] para continuar"
        valgrind=""
    fi
}

function limpiar_archivos_temporales() {
    rm -rf *.tmp  $directorio/*.tmp $directorio/*.terr *.o $directorio/*.o $directorio/*.tmp.err
}

function comprobar_fuentes() {
    fuentes=$(ls *.cc *.h 2>/dev/null)
    faltantes=()
    no_pertenecen=()
    
    # Comprobar ficheros requeridos
    for requerido in "${ficheros_requeridos[@]}"; do
        if [[ ! -f $requerido ]]; then
            faltantes+=($requerido)
        fi
    done

    # Comprobar si hay ficheros que no pertenecen a la práctica
    for fichero in $fuentes; do
        if [[ ! " ${ficheros_requeridos[@]} " =~ " ${fichero} " ]]; then
            no_pertenecen+=($fichero)
        fi
    done

    # Mostrar errores si los hay
    if [[ ${#faltantes[@]} -ne 0 ]]; then
        echo "Error, faltan ficheros fuente requeridos: ${faltantes[*]}"
        echo "Nota: 0"
        exit 1
    fi

    if [[ ${#no_pertenecen[@]} -ne 0 ]]; then
        echo "Error, hay ficheros fuente que no pertenecen a la práctica: ${no_pertenecen[*]}"
        echo "Nota: 0"
        exit 1
    fi
}

function compilar_y_verificar() {
    make >/dev/null 2> errores.compilacion
    if grep -q "error:" errores.compilacion; then
        echo "Error de compilacion"
        echo "Nota: 0"
        rm -rf errores.compilacion
        make clean >/dev/null
        exit 1
    else
        rm -rf errores.compilacion
    fi
}

function mover_archivos_compilados() {
    mv *.o $directorio
}

function limpiar_archivos_compilados() {
    rm $directorio/*.o
}

function compilar_prueba() {
    nombre=$1
    $compilador -g -o $nombre $nombre.cc $clases_compiladas 2> $nombre.terr
    if [[ ! -s $nombre.terr ]]; then
        rm -rf $nombre.terr
        return 0
    else
        echo "Prueba $nombre: hay errores de compilacion"
        cat $nombre.terr
        rm -rf $nombre.terr
        return 1
    fi
}

function comprobar_salida() {
    nombre=$1
    ok=0
    if [[ -e $nombre.tmp ]]; then
        diff -w $nombre.tmp $nombre.txt > diff_output.tmp
        if [[ ! -s diff_output.tmp ]]; then
            ok=1
        fi
    fi
    rm -rf diff_output.tmp
    return $ok
}

function ejecutar_pruebas() {
    cd $directorio

    # Si se han pasado argumentos, se ejecutan las pruebas indicadas
    # Si no se han pasado argumentos, se ejecutan todas las pruebas del directorio
    if [[ $# -ne 0 ]]; then
        pruebas=$@
    else
        # Lee las pruebas del directorio de pruebas
        pruebas=$(ls *.cc *.in *.dat 2>/dev/null)
        # Coge los nombres de las pruebas quitando la extensión, eliminando duplicados y ordenando
        pruebas=$(echo $pruebas | tr ' ' '\n' | sed 's/\..*//' | sort | uniq)
    fi

    # Cuenta el número de pruebas
    numero_pruebas=$(echo $pruebas | wc -w)
    echo "Ejecutando $numero_pruebas pruebas"
    pruebas_pasadas=0

    # Ejecuta las pruebas
    for prueba in $pruebas; do

        # Si existe un archivo $prueba.in, lee del fichero los idiomas origen y destino
        if [[ -e $prueba.in ]]; then

	    # Bucle para leer el archivo línea por línea
	    while read -a idiomas
	    do
	      # El comando read lee en los idiomas en el array 'idiomas'
              origen=${idiomas[0]}
              destino=${idiomas[1]}
	    done < $prueba.in # Redirecciona la entrada del bucle al fichero
            #echo "  Origen: [$origen]"
            #echo "  Destino: [$destino]"

            # Si existe un archivo .in, ejecuta el programa translate
            ejecutable=../$aplicacion
            arg="$prueba.text $prueba.dict $origen $destino"

        # Si existe un archivo .cc, lo compila y lo usa como ejecutable
        elif [[ -e $prueba.cc ]]; then
            compilar_prueba $prueba
            error=$?
            if [[ $error -ne 0 ]]; then
                continue
            fi
            ejecutable=$prueba
            
        fi

        # Ejecuta la prueba
        $valgrind ./$ejecutable $arg > $prueba.tmp 2> $prueba.tmp.err.val

       # comprobar si hay errores de ejecución y de liberación de memoria
        sgerr=$(grep "ERROR SUMMARY: 0 errors" $prueba.tmp.err.val)
        if test "$sgerr" == ""; then # hay algún error
          mv $prueba.tmp.err.val $prueba.tmp.err
        else
          sgmem=$(grep "All heap blocks were freed" $prueba.tmp.err.val)
          if test "$sgmem" == ""; then
            mv $prueba.tmp.err.val $prueba.tmp.err
          else # dejar el fichero de error vacío
            rm -f $prueba.tmp.err
            touch $prueba.tmp.err
          fi
        fi
      
        # Comprueba si hubo errores en la ejecución
        if [[ ! -s $prueba.tmp.err ]]; then
            # Si no hubo errores, comprueba si la salida es correcta
            comprobar_salida $prueba
            salida_ok=$?
            if [[ $salida_ok -eq 0 ]]; then
                mensaje="diferencias en fichero salida txt; ejecuta diff -w $prueba.txt $prueba.tmp"
            else
                mensaje="Ok"
                pruebas_pasadas=$(echo "$pruebas_pasadas + 1" | bc)
            fi
            echo "Prueba $prueba: $mensaje"
        else
            # Error en la ejecución, muestra la salida de error
            echo "Prueba $prueba: Hay errores de ejecucion"
            cat $prueba.tmp.err
        fi

    done

    cd ..

    # Calcula la nota
    if [[ $numero_pruebas -eq 0 ]]; then
        echo "No se encontraron pruebas para ejecutar"
    else
        if [[ $pruebas_pasadas -eq $numero_pruebas ]]; then
          echo "Funcionan todas las pruebas, recuerda hacer tus propias pruebas"
        else
          echo "Funcionan $pruebas_pasadas pruebas de $numero_pruebas"
        fi
    fi
}

function main() {
    # Los argumentos de entrada son las pruebas a ejecutar
    # Si no hay argumentos se ejecutan todas las pruebas
    pruebas=""
    if [[ $# -ne 0 ]]; then
        pruebas=$@
    fi

    comprobar_valgrind
    limpiar_archivos_temporales
    comprobar_fuentes
    compilar_y_verificar
    mover_archivos_compilados
    ejecutar_pruebas $pruebas
    limpiar_archivos_compilados
}

main $@

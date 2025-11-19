# Autocorrector de la Práctica 2

Este autocorrector está diseñado para compilar y ejecutar tu código, así como para verificar la salida en comparación con las soluciones esperadas. Sigue las instrucciones a continuación para añadir tus propias pruebas.

## Preparación de los ficheros requeridos

Copia los ficheros de tu práctica en esta carpeta, junto al fichero `corrige.sh`. Los ficheros necesarios están indicados en el enunciado de la práctica.

**No debe haber ningún otro fichero `.cc` o `.h` en la carpeta del autocorrector.**

## Ejecutar el autocorrector

Para ejecutar el autocorrector, ejecuta el script `corrige.sh` desde la terminal:

```bash
./corrige.sh
```

## Cómo añadir nuevas pruebas

El autocorrector permite ejecutar dos tipos de pruebas diferentes:
- Pruebas de código en ficheros `.cc` que contiene una función `main` que llama directamente a los métodos de tus clases.
- Pruebas que usan el programa `approximate` de tu código, que utilizan tres ficheros con extensiones `.text` (texto a traducir), `.dict` (diccionario) y `.in` (con una línea con los idiomas, p.ej. `I E`)

**Todas las pruebas deben tener un fichero `.txt` con la salida correcta esperada**. Al ejecutar la prueba se comparará la salida de la prueba (compilada a partir de tu código) con el contenido de este fichero para comprobar si el funcionamiento del código es el esperado.

### Pruebas con código

Cada prueba con código debe estar en un fichero `.cc` y debe contener una función `main` que pruebe alguna funcionalidad específica de tu programa. Puedes consultar las pruebas del corrector para ver algunos de ejemplos de cómo se deben programar estas pruebas.

Coloca tus ficheros `.cc` y `.txt` en la carpeta `pruebas`.

**Estructura de la carpeta**:
```
.
├── corrige.sh
├── Makefile
├── README.md
├── ficheros de código (.cc, .h)
└── pruebas
      ├── prueba1.cc
      └── prueba1.txt

```

### Pruebas del programa `approximate`

Cada prueba de este tipo debe tener:
 - un fichero con extensión `.text` con el texto a traducir
 - un fichero con extensión `.dict` con el diccionario
 - un fichero con extensión `.in` que tendrá una línea con los idiomas origen y destino (p.ej. `I E`); el corrector lo leerá y obtendrá los idiomas para pasarlos como argumentos al programa `approximate`
 - un fichero `.txt` con la salida esperada de la prueba.

Coloca tus ficheros `.text`, `.dict`, `.in` y `.txt` en la carpeta `pruebas`.

**Estructura de la carpeta**:
```
.
├── corrige.sh
├── Makefile
├── README.md
├── ficheros de código (.cc, .h)
└── pruebas
      ├── prueba2.text
      ├── prueba2.dict
      ├── prueba2.in
      └── prueba2.txt
```

### Consideraciones adicionales

- Asegúrate de que tus ficheros de prueba no contengan errores de compilación. El autocorrector detendrá la ejecución si encuentra errores durante la compilación.
- Debes tener instalado `valgrind` para que el resultado de las pruebas sea totalmente fiable. Si no está instalado podrás probar si la salida de las pruebas es correcta, pero no se realizarán comprobaciones sobre el uso de memoria que sí se harán en el corrector definitivo.

## Solución de problemas

Para cualquier duda o problema, contacta con tu profesor de prácticas.

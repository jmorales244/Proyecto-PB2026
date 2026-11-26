/* ============================================================
   MEMBER 1 - PROGRAM ARCHITECTURE AND INTEGRATION
   (MIEMBRO 1 - Arquitectura e integracion)

   laboratorio.c
   Definiciones de los elementos compartidos declarados en
   laboratorio.h: lista de categorias y funciones auxiliares de
   lectura segura de teclado y presentacion.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "laboratorio.h"

/* ---------- Categorias validas ---------- */
const char *const CATEGORIAS[NUM_CATEGORIAS] = {
    "Computo",
    "Medicion",
    "Electronica"
};

/* leerLinea: lee una linea completa con fgets() y quita el salto de
   linea con strcspn(). Devuelve 1 si la linea cabia en el buffer y
   0 si era demasiado larga (el resto se descarta para que no
   contamine la siguiente lectura). Si se acaba la entrada
   (Ctrl+Z / fin de archivo) cierra el programa para evitar ciclos
   infinitos. */
int leerLinea(char destino[], int tam)
{
    int c;

    if (fgets(destino, tam, stdin) == NULL) {
        printf("\n  Entrada finalizada. Se cierra el programa.\n");
        exit(EXIT_FAILURE);
    }

    if (strchr(destino, '\n') == NULL && !feof(stdin)) {
        /* No cupo el salto de linea: descartar lo que sobra. */
        while ((c = getchar()) != '\n' && c != EOF) {
            /* vaciar el resto de la linea */
        }
        return 0;
    }

    destino[strcspn(destino, "\r\n")] = '\0';
    return 1;
}

/* leerNumero: muestra el mensaje, lee UNA linea y la convierte a int.
   Devuelve 1 si se obtuvo un entero valido (guardado en *valor) y
   0 en caso contrario (letras, vacio, decimales, desbordamiento).
   No imprime errores: cada llamador decide que mensaje mostrar. */
int leerNumero(const char mensaje[], int *valor)
{
    char  linea[LONG_LINEA];
    char *fin;
    long  numero;

    printf("%s", mensaje);
    if (!leerLinea(linea, LONG_LINEA)) {
        return 0;
    }

    errno = 0;
    numero = strtol(linea, &fin, 10);

    if (fin == linea) {                 /* no se leyo ningun digito */
        return 0;
    }
    while (*fin == ' ' || *fin == '\t') {   /* permitir espacios al final */
        fin++;
    }
    if (*fin != '\0') {                 /* sobraron caracteres no numericos */
        return 0;
    }
    if (errno == ERANGE || numero > INT_MAX || numero < INT_MIN) {
        return 0;
    }

    *valor = (int)numero;
    return 1;
}

/* leerEnteroEnRango: repite la pregunta hasta que el usuario escriba
   un entero entre minimo y maximo (inclusive). */
int leerEnteroEnRango(const char mensaje[], int minimo, int maximo)
{
    int valor = 0;
    int valido = 0;

    do {
        if (!leerNumero(mensaje, &valor)) {
            printf("  Error: ingrese un numero entero.\n");
        } else if (valor < minimo || valor > maximo) {
            printf("  Error: el valor debe estar entre %d y %d.\n", minimo, maximo);
        } else {
            valido = 1;
        }
    } while (!valido);

    return valor;
}

/* leerTexto: lee una linea de texto con espacios, le quita los
   espacios de los extremos y la copia a destino.
   Devuelve la longitud del texto (0 si quedo vacio) o -1 si el
   texto no cabe en tam bytes (incluyendo el '\0'). En el caso -1
   destino no se modifica. */
int leerTexto(const char mensaje[], char destino[], int tam)
{
    char linea[LONG_LINEA];
    int  longitud;

    printf("%s", mensaje);
    if (!leerLinea(linea, LONG_LINEA)) {
        return -1;
    }

    recortarEspacios(linea);
    longitud = (int)strlen(linea);
    if (longitud >= tam) {
        return -1;
    }

    strcpy(destino, linea);   /* seguro: ya se verifico que cabe */
    return longitud;
}

/* recortarEspacios: elimina espacios y tabuladores al inicio y al
   final de la cadena (modifica la cadena recibida). */
void recortarEspacios(char texto[])
{
    int    inicio = 0;
    size_t fin;

    while (texto[inicio] == ' ' || texto[inicio] == '\t') {
        inicio++;
    }
    if (inicio > 0) {
        memmove(texto, texto + inicio, strlen(texto + inicio) + 1);
    }

    fin = strlen(texto);
    while (fin > 0 && (texto[fin - 1] == ' ' || texto[fin - 1] == '\t')) {
        texto[fin - 1] = '\0';
        fin--;
    }
}

/* imprimirLinea: dibuja un separador del ancho estandar. */
void imprimirLinea(char caracter)
{
    int i;
    for (i = 0; i < ANCHO_LINEA; i++) {
        putchar(caracter);
    }
    putchar('\n');
}

/* semanaValida: devuelve 1 si la semana esta entre 1 y SEMANAS. */
int semanaValida(int semana)
{
    return semana >= 1 && semana <= SEMANAS;
}

/* ============================================================
   MEMBER 4 - SEARCHING AND SORTING ALGORITHMS
   (MIEMBRO 4 - Busqueda y ordenamiento)

   busquedas.c
   Contenido: buscarCodigoLineal(), buscarCodigoBinaria(),
              buscarPorNombre(), ordenarPorCodigo() y las
              funciones que piden los datos al usuario.
   Estado "catalogo ordenado": la variable catalogoOrdenado vive
   en main() y se pasa por valor a procesarBusquedaBinaria().
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include "busquedas.h"
#include "equipos.h"   /* mostrarEquipo() */

/* buscarCodigoLineal: recorre el arreglo con un apuntador hasta
   encontrar el codigo o llegar al final. No necesita orden.
   Devuelve la direccion del equipo dentro del arreglo original
   (no de una copia local) o NULL si no existe. */
Equipo *buscarCodigoLineal(Equipo equipos[], int cantidad, int codigo)
{
    Equipo *p;
    Equipo *fin = equipos + cantidad;

    for (p = equipos; p < fin; p++) {
        if (p->codigo == codigo) {
            return p;
        }
    }
    return NULL;
}

/* buscarCodigoBinaria: reduce el intervalo [bajo, alto] a la mitad
   en cada paso. REQUIERE el arreglo ordenado ascendentemente por
   codigo (main() lo garantiza con catalogoOrdenado). */
Equipo *buscarCodigoBinaria(Equipo equipos[], int cantidad, int codigo)
{
    int bajo = 0;
    int alto = cantidad - 1;
    int medio;

    while (bajo <= alto) {
        medio = bajo + (alto - bajo) / 2;

        if (equipos[medio].codigo == codigo) {
            return &equipos[medio];
        } else if (equipos[medio].codigo < codigo) {
            bajo = medio + 1;      /* descartar la mitad izquierda */
        } else {
            alto = medio - 1;      /* descartar la mitad derecha   */
        }
    }
    return NULL;
}

/* buscarPorNombre: comparacion exacta con strcmp() (distingue
   mayusculas de minusculas). Devuelve el primer equipo que
   coincida o NULL. */
Equipo *buscarPorNombre(Equipo equipos[], int cantidad, const char nombre[])
{
    int i;
    for (i = 0; i < cantidad; i++) {
        if (strcmp(equipos[i].nombre, nombre) == 0) {
            return &equipos[i];
        }
    }
    return NULL;
}

/* ordenarPorCodigo: ordenamiento por insercion, ascendente, sobre
   el arreglo original. Se mueven estructuras COMPLETAS (la
   asignacion entre structs copia todos los miembros, incluida la
   matriz movimientos), asi que cada codigo conserva sus datos. */
void ordenarPorCodigo(Equipo equipos[], int cantidad)
{
    int    i, j;
    Equipo clave;   /* copia temporal del equipo que se esta insertando */

    for (i = 1; i < cantidad; i++) {
        clave = equipos[i];
        j = i - 1;

        /* Desplazar a la derecha los equipos con codigo mayor */
        while (j >= 0 && equipos[j].codigo > clave.codigo) {
            equipos[j + 1] = equipos[j];
            j--;
        }
        equipos[j + 1] = clave;   /* colocar en su posicion */
    }
}

/* procesarBusquedaLineal: pide un codigo y muestra el resultado. */
void procesarBusquedaLineal(Equipo equipos[], int cantidad)
{
    Equipo *encontrado;
    int codigo;

    printf("\n  BUSQUEDA LINEAL POR CODIGO\n");
    imprimirLinea('-');

    if (!leerNumero("  Codigo a buscar: ", &codigo)) {
        printf("  Busqueda cancelada: el codigo debe ser un numero entero.\n");
        return;
    }

    encontrado = buscarCodigoLineal(equipos, cantidad, codigo);
    if (encontrado == NULL) {
        printf("  No se encontro ningun equipo con el codigo %d.\n", codigo);
    } else {
        mostrarEquipo(encontrado);
    }
}

/* procesarBusquedaBinaria: solo permite buscar si el catalogo ya
   fue ordenado con la opcion 5. */
void procesarBusquedaBinaria(Equipo equipos[], int cantidad, int catalogoOrdenado)
{
    Equipo *encontrado;
    int codigo;

    printf("\n  BUSQUEDA BINARIA POR CODIGO\n");
    imprimirLinea('-');

    if (!catalogoOrdenado) {
        printf("  La busqueda binaria requiere el catalogo ordenado por codigo.\n");
        printf("  Use primero la opcion 5 (Ordenar catalogo por codigo).\n");
        return;
    }

    if (!leerNumero("  Codigo a buscar: ", &codigo)) {
        printf("  Busqueda cancelada: el codigo debe ser un numero entero.\n");
        return;
    }

    encontrado = buscarCodigoBinaria(equipos, cantidad, codigo);
    if (encontrado == NULL) {
        printf("  No se encontro ningun equipo con el codigo %d.\n", codigo);
    } else {
        mostrarEquipo(encontrado);
    }
}

/* procesarBusquedaNombre: busqueda exacta por nombre. */
void procesarBusquedaNombre(Equipo equipos[], int cantidad)
{
    Equipo *encontrado;
    char nombre[LONG_NOMBRE];
    int  longitud;

    printf("\n  BUSQUEDA POR NOMBRE\n");
    imprimirLinea('-');
    printf("  (La comparacion es exacta y distingue mayusculas de minusculas)\n");

    longitud = leerTexto("  Nombre a buscar: ", nombre, LONG_NOMBRE);
    if (longitud < 0) {
        printf("  No se encontro: ningun nombre registrado supera 39 caracteres.\n");
        return;
    }
    if (longitud == 0) {
        printf("  Busqueda cancelada: no se escribio ningun nombre.\n");
        return;
    }

    encontrado = buscarPorNombre(equipos, cantidad, nombre);
    if (encontrado == NULL) {
        printf("  No se encontro ningun equipo llamado \"%s\".\n", nombre);
    } else {
        mostrarEquipo(encontrado);
    }
}

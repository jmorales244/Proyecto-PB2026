/* ============================================================
   MEMBER 2 - EQUIPMENT REGISTRATION AND CATALOG
   (MIEMBRO 2 - Registro de equipos y catalogo)

   equipos.c
   Contenido: capturarEquipos(), mostrarCatalogo(), mostrarEquipo(),
              validaciones de captura, codigos unicos, categorias
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include "equipos.h"
#include "reportes.h"   /* mostrarHistorial(), usada por mostrarEquipo() */

/* categoriaValida: compara con strcmp() contra las categorias
   permitidas. La comparacion es exacta (respeta mayusculas). */
int categoriaValida(const char categoria[])
{
    int i;
    for (i = 0; i < NUM_CATEGORIAS; i++) {
        if (strcmp(categoria, CATEGORIAS[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/* codigoExiste: devuelve 1 si el codigo ya esta entre los primeros
   'cantidad' equipos del arreglo (para mantener codigos unicos). */
int codigoExiste(const Equipo equipos[], int cantidad, int codigo)
{
    int i;
    for (i = 0; i < cantidad; i++) {
        if (equipos[i].codigo == codigo) {
            return 1;
        }
    }
    return 0;
}

/* capturarEquipos: registro inicial.
   Recibe un apuntador a la cantidad para establecerla y
   actualizarla directamente. Un equipo solo se cuenta (*cantidad)
   cuando TODOS sus datos ya fueron capturados y validados. */
void capturarEquipos(Equipo equipos[], int *cantidad)
{
    char    mensaje[LONG_LINEA];
    int     totalARegistrar;
    int     codigo;
    int     longitud;
    int     semana, columna;
    Equipo *nuevo;

    printf("\n");
    imprimirLinea('=');
    printf("  REGISTRO INICIAL DE EQUIPOS\n");
    imprimirLinea('=');

    *cantidad = 0;

    snprintf(mensaje, sizeof(mensaje),
             "Cantidad de equipos diferentes a registrar (1-%d): ", MAX_EQUIPOS);
    totalARegistrar = leerEnteroEnRango(mensaje, 1, MAX_EQUIPOS);

    while (*cantidad < totalARegistrar) {
        nuevo = &equipos[*cantidad];   /* siguiente posicion libre */
        printf("\nEquipo %d de %d\n", *cantidad + 1, totalARegistrar);

        /* --- Codigo: entero 1..99999 y no repetido --- */
        codigo = leerEnteroEnRango("  Codigo (1-99999): ", CODIGO_MIN, CODIGO_MAX);
        while (codigoExiste(equipos, *cantidad, codigo)) {
            printf("  Error: el codigo %d ya esta registrado. Ingrese otro.\n", codigo);
            codigo = leerEnteroEnRango("  Codigo (1-99999): ", CODIGO_MIN, CODIGO_MAX);
        }
        nuevo->codigo = codigo;

        /* --- Nombre: con espacios, maximo 39 caracteres --- */
        do {
            longitud = leerTexto("  Nombre del equipo (max. 39 caracteres): ",
                                 nuevo->nombre, LONG_NOMBRE);
            if (longitud < 0) {
                printf("  Error: el nombre no puede superar 39 caracteres.\n");
            } else if (longitud == 0) {
                printf("  Error: el nombre no puede estar vacio.\n");
            }
        } while (longitud <= 0);

        /* --- Categoria: Computo, Medicion o Electronica --- */
        do {
            longitud = leerTexto("  Categoria (Computo / Medicion / Electronica): ",
                                 nuevo->categoria, LONG_CATEGORIA);
            if (longitud < 0 || !categoriaValida(nuevo->categoria)) {
                printf("  Error: categoria no valida. Use Computo, Medicion o Electronica.\n");
                longitud = -1;
            }
        } while (longitud < 0);

        /* --- Cantidad total: 1..500 --- */
        nuevo->total = leerEnteroEnRango("  Cantidad total de unidades (1-500): ",
                                         TOTAL_MIN, TOTAL_MAX);

        /* --- Valores iniciales --- */
        nuevo->disponibles = nuevo->total;
        nuevo->prestados   = 0;
        for (semana = 0; semana < SEMANAS; semana++) {
            for (columna = 0; columna < COLUMNAS_MOV; columna++) {
                nuevo->movimientos[semana][columna] = 0;
            }
        }

        (*cantidad)++;   /* ahora si cuenta como equipo registrado */
        printf("  Equipo registrado correctamente.\n");
    }

    printf("\n  Registro inicial completado: %d equipo(s).\n", *cantidad);
}

/* mostrarCatalogo: recibe el arreglo como const (no se puede
   modificar) y lo recorre con un apuntador y p++ . */
void mostrarCatalogo(const Equipo equipos[], int cantidad)
{
    const Equipo *p   = equipos;              /* primer equipo        */
    const Equipo *fin = equipos + cantidad;   /* una posicion despues */

    printf("\n  CATALOGO DE EQUIPOS\n");
    imprimirLinea('-');

    if (cantidad <= 0) {
        printf("  El catalogo esta vacio: no hay equipos registrados.\n");
        return;
    }

    printf("%-6s %-39s %-11s %5s %5s %6s\n",
           "Codigo", "Nombre", "Categoria", "Total", "Disp.", "Prest.");
    imprimirLinea('-');

    for (; p < fin; p++) {
        printf("%-6d %-39s %-11s %5d %5d %6d\n",
               p->codigo, p->nombre, p->categoria,
               p->total, p->disponibles, p->prestados);
    }

    imprimirLinea('-');
    printf("Equipos registrados: %d   (Total = existencia, Disp. = disponibles,\n", cantidad);
    printf("Prest. = prestados)\n");
}

/* mostrarEquipo: muestra toda la informacion de un equipo
   encontrado (datos generales + historial semanal). */
void mostrarEquipo(const Equipo *equipo)
{
    printf("\n  EQUIPO ENCONTRADO\n");
    imprimirLinea('-');
    printf("  Codigo      : %d\n", equipo->codigo);
    printf("  Nombre      : %s\n", equipo->nombre);
    printf("  Categoria   : %s\n", equipo->categoria);
    printf("  Total       : %d\n", equipo->total);
    printf("  Disponibles : %d\n", equipo->disponibles);
    printf("  Prestados   : %d\n", equipo->prestados);
    mostrarHistorial(equipo);
}

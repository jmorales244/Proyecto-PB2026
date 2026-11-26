/* ============================================================
   MEMBER 5 - HISTORY AND REPORTING
   (MIEMBRO 5 - Historial y reportes)

   reportes.c
   Contenido: mostrarHistorial(), generarResumen(), matriz de
              resumen semanal y estadisticas del inventario
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include "reportes.h"
#include "busquedas.h"   /* buscarCodigoLineal() */

/* mostrarHistorial: recibe un apuntador constante, asi que solo
   puede consultar el equipo, no modificarlo. */
void mostrarHistorial(const Equipo *equipo)
{
    int semana;
    int totalPrestadas = 0;
    int totalDevueltas = 0;

    if (equipo == NULL) {
        printf("  No hay equipo para consultar.\n");
        return;
    }

    printf("\n  HISTORIAL DE MOVIMIENTOS\n");
    printf("  Equipo: %s (codigo %d)\n", equipo->nombre, equipo->codigo);
    imprimirLinea('-');
    printf("  %6s  %18s  %18s\n", "Semana", "Unidades prestadas", "Unidades devueltas");

    for (semana = 0; semana < SEMANAS; semana++) {
        printf("  %6d  %18d  %18d\n",
               semana + 1,
               equipo->movimientos[semana][COL_PRESTAMOS],
               equipo->movimientos[semana][COL_DEVOLUCIONES]);
        totalPrestadas += equipo->movimientos[semana][COL_PRESTAMOS];
        totalDevueltas += equipo->movimientos[semana][COL_DEVOLUCIONES];
    }

    imprimirLinea('-');
    printf("  %6s  %18d  %18d\n", "Total", totalPrestadas, totalDevueltas);
    printf("  Unidades actualmente prestadas: %d\n", equipo->prestados);
}

/* equipoEsConsistente: comprueba las invariantes de UN equipo.
   Devuelve 1 si todas se cumplen:
     disponibles >= 0, prestados >= 0,
     disponibles + prestados == total,
     prestamos acumulados - devoluciones acumuladas == prestados. */
int equipoEsConsistente(const Equipo *equipo)
{
    int semana;
    int prestadas = 0;
    int devueltas = 0;

    for (semana = 0; semana < SEMANAS; semana++) {
        prestadas += equipo->movimientos[semana][COL_PRESTAMOS];
        devueltas += equipo->movimientos[semana][COL_DEVOLUCIONES];
    }

    return equipo->disponibles >= 0
        && equipo->prestados >= 0
        && equipo->disponibles + equipo->prestados == equipo->total
        && prestadas - devueltas == equipo->prestados;
}

/* generarResumen: calcula los indicadores globales SIN modificar el
   catalogo (parametro const). Los movimientos de todas las
   semanas se consolidan en la matriz resumen[4][2]:
     fila = semana, columna 0 = prestadas, columna 1 = devueltas. */
void generarResumen(const Equipo equipos[], int cantidad)
{
    int resumen[SEMANAS][COLUMNAS_MOV];
    int porCategoria[NUM_CATEGORIAS] = {0};
    int totalUnidades = 0;
    int totalDisponibles = 0;
    int totalPrestados = 0;
    int inconsistentes = 0;
    int totalPrestadasSemanas = 0;
    int totalDevueltasSemanas = 0;
    int i, k, semana, columna;

    /* Inicializar la matriz de resumen */
    for (semana = 0; semana < SEMANAS; semana++) {
        for (columna = 0; columna < COLUMNAS_MOV; columna++) {
            resumen[semana][columna] = 0;
        }
    }

    /* Recorrer todos los equipos acumulando indicadores */
    for (i = 0; i < cantidad; i++) {
        totalUnidades    += equipos[i].total;
        totalDisponibles += equipos[i].disponibles;
        totalPrestados   += equipos[i].prestados;

        for (k = 0; k < NUM_CATEGORIAS; k++) {
            if (strcmp(equipos[i].categoria, CATEGORIAS[k]) == 0) {
                porCategoria[k]++;
            }
        }

        /* Ciclos anidados sobre la matriz movimientos de cada equipo */
        for (semana = 0; semana < SEMANAS; semana++) {
            for (columna = 0; columna < COLUMNAS_MOV; columna++) {
                resumen[semana][columna] += equipos[i].movimientos[semana][columna];
            }
        }

        if (!equipoEsConsistente(&equipos[i])) {
            inconsistentes++;
        }
    }

    /* ---------- Presentacion del reporte ---------- */
    printf("\n  REPORTE GENERAL DEL INVENTARIO\n");
    imprimirLinea('=');
    printf("  Tipos de equipo registrados      : %d\n", cantidad);
    printf("  Unidades existentes (total)      : %d\n", totalUnidades);
    printf("  Unidades disponibles             : %d\n", totalDisponibles);
    printf("  Unidades actualmente prestadas   : %d\n", totalPrestados);

    printf("\n  Tipos de equipo por categoria\n");
    imprimirLinea('-');
    for (k = 0; k < NUM_CATEGORIAS; k++) {
        printf("  %-12s: %d\n", CATEGORIAS[k], porCategoria[k]);
    }

    printf("\n  Movimientos por semana (todos los equipos)\n");
    imprimirLinea('-');
    printf("  %6s  %18s  %18s\n", "Semana", "Unidades prestadas", "Unidades devueltas");
    for (semana = 0; semana < SEMANAS; semana++) {
        printf("  %6d  %18d  %18d\n", semana + 1,
               resumen[semana][COL_PRESTAMOS], resumen[semana][COL_DEVOLUCIONES]);
        totalPrestadasSemanas += resumen[semana][COL_PRESTAMOS];
        totalDevueltasSemanas += resumen[semana][COL_DEVOLUCIONES];
    }
    imprimirLinea('-');
    printf("  %6s  %18d  %18d\n", "Total", totalPrestadasSemanas, totalDevueltasSemanas);

    printf("\n  Verificacion de integridad del inventario\n");
    imprimirLinea('-');
    if (inconsistentes == 0) {
        printf("  CORRECTA: los %d equipo(s) cumplen todas las condiciones.\n", cantidad);
    } else {
        printf("  ERROR: %d equipo(s) no cumplen las condiciones de integridad.\n",
               inconsistentes);
    }
}

/* procesarHistorial: pide un codigo, localiza el equipo con busqueda
   lineal y muestra su historial. */
void procesarHistorial(Equipo equipos[], int cantidad)
{
    Equipo *encontrado;
    int codigo;

    printf("\n  CONSULTAR HISTORIAL DE MOVIMIENTOS\n");
    imprimirLinea('-');

    if (!leerNumero("  Codigo del equipo: ", &codigo)) {
        printf("  Consulta cancelada: el codigo debe ser un numero entero.\n");
        return;
    }

    encontrado = buscarCodigoLineal(equipos, cantidad, codigo);
    if (encontrado == NULL) {
        printf("  No se encontro ningun equipo con el codigo %d.\n", codigo);
    } else {
        mostrarHistorial(encontrado);
    }
}

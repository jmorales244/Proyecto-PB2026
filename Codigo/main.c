/* ============================================================
   MEMBER 1 - PROGRAM ARCHITECTURE AND INTEGRATION
   (MIEMBRO 1 - Arquitectura e integracion)

   main.c
   SISTEMA DE CONTROL DE PRESTAMOS DE EQUIPO DE LABORATORIO
   Proyecto PB2026 - Aplicacion de consola en C

   main() solo COORDINA: registra los equipos, muestra el menu y
   llama a la funcion de cada modulo. Contiene tambien
   mostrarMenu().

   Modulos:
     laboratorio.h/.c  estructura, constantes y auxiliares comunes
     equipos.h/.c      registro de equipos y catalogo
     prestamos.h/.c    prestamos y devoluciones
     busquedas.h/.c    busquedas y ordenamiento
     reportes.h/.c     historial y reporte general
   ============================================================ */

#include <stdio.h>
#include "laboratorio.h"
#include "equipos.h"
#include "prestamos.h"
#include "busquedas.h"
#include "reportes.h"

/* Prototipo de mostrarMenu (definida despues de main) */
int mostrarMenu(void);


/* ---------- Funcion principal: solo coordina el flujo ---------- */
int main(void)
{
    Equipo equipos[MAX_EQUIPOS];   /* arreglo unidimensional de estructuras */
    int cantidad = 0;              /* equipos registrados actualmente       */
    int opcion;
    int catalogoOrdenado = 0;      /* 1 cuando el catalogo ya se ordeno     */

    capturarEquipos(equipos, &cantidad);

    do {
        opcion = mostrarMenu();

        switch (opcion) {
            case 1:
                mostrarCatalogo(equipos, cantidad);
                break;
            case 2:
                procesarPrestamo(equipos, cantidad);
                break;
            case 3:
                procesarDevolucion(equipos, cantidad);
                break;
            case 4:
                procesarBusquedaLineal(equipos, cantidad);
                break;
            case 5:
                ordenarPorCodigo(equipos, cantidad);
                catalogoOrdenado = 1;
                printf("\n  Catalogo ordenado por codigo (ordenamiento por insercion).\n");
                printf("  La busqueda binaria (opcion 6) ya esta habilitada.\n");
                break;
            case 6:
                procesarBusquedaBinaria(equipos, cantidad, catalogoOrdenado);
                break;
            case 7:
                procesarBusquedaNombre(equipos, cantidad);
                break;
            case 8:
                procesarHistorial(equipos, cantidad);
                break;
            case 9:
                generarResumen(equipos, cantidad);
                break;
            case 0:
                printf("\nFin del programa.\n");
                break;
            default:
                printf("\n  Opcion no valida.\n");
        }
    } while (opcion != 0);

    return 0;
}


/* mostrarMenu: imprime las opciones y devuelve la seleccion.
   Si el usuario no escribe un numero entero, devuelve -1 para que
   main() la trate como "Opcion no valida". */
int mostrarMenu(void)
{
    int opcion;

    printf("\n");
    imprimirLinea('=');
    printf("  SISTEMA DE CONTROL DE PRESTAMOS DE LABORATORIO\n");
    imprimirLinea('=');
    printf("  1. Mostrar catalogo de equipos\n");
    printf("  2. Registrar prestamo\n");
    printf("  3. Registrar devolucion\n");
    printf("  4. Buscar equipo (busqueda lineal)\n");
    printf("  5. Ordenar catalogo por codigo\n");
    printf("  6. Buscar equipo (busqueda binaria)\n");
    printf("  7. Buscar equipo por nombre\n");
    printf("  8. Consultar historial de movimientos\n");
    printf("  9. Generar reporte general\n");
    printf("  0. Finalizar programa\n");
    imprimirLinea('-');

    if (!leerNumero("  Seleccione una opcion: ", &opcion)) {
        return -1;
    }
    return opcion;
}

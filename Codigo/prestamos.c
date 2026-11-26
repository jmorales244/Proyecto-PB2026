/* ============================================================
   MEMBER 3 - INVENTORY TRANSACTIONS
   (MIEMBRO 3 - Transacciones de inventario)

   prestamos.c
   Contenido: registrarPrestamo(), registrarDevolucion() y las
              funciones que piden los datos al usuario
   ============================================================ */

#include <stdio.h>
#include "prestamos.h"
#include "busquedas.h"   /* buscarCodigoLineal() */

/* registrarPrestamo: valida TODAS las condiciones antes de tocar
   el registro. Devuelve 1 si el prestamo se registro y 0 si se
   rechazo (en ese caso el equipo queda exactamente igual). */
int registrarPrestamo(Equipo *equipo, int semana, int cantidad)
{
    if (equipo == NULL)                 return 0;
    if (!semanaValida(semana))          return 0;
    if (cantidad <= 0)                  return 0;
    if (cantidad > equipo->disponibles) return 0;

    /* Todas las condiciones se cumplen: actualizar con -> */
    equipo->disponibles -= cantidad;
    equipo->prestados   += cantidad;
    equipo->movimientos[semana - 1][COL_PRESTAMOS] += cantidad;
    return 1;
}

/* registrarDevolucion: igual que el prestamo, pero la cantidad no
   puede exceder las unidades actualmente prestadas. */
int registrarDevolucion(Equipo *equipo, int semana, int cantidad)
{
    if (equipo == NULL)               return 0;
    if (!semanaValida(semana))        return 0;
    if (cantidad <= 0)                return 0;
    if (cantidad > equipo->prestados) return 0;

    equipo->disponibles += cantidad;
    equipo->prestados   -= cantidad;
    equipo->movimientos[semana - 1][COL_DEVOLUCIONES] += cantidad;
    return 1;
}

/* procesarPrestamo: pide codigo, semana y cantidad; localiza el
   equipo con busqueda lineal (funciona con el catalogo ordenado o
   no) y llama a registrarPrestamo(). Cualquier dato invalido
   cancela la operacion sin modificar el inventario. */
void procesarPrestamo(Equipo equipos[], int cantidad)
{
    Equipo *equipo;
    int codigo, semana, unidades;

    printf("\n  REGISTRAR PRESTAMO\n");
    imprimirLinea('-');

    if (!leerNumero("  Codigo del equipo: ", &codigo)) {
        printf("  Prestamo rechazado: el codigo debe ser un numero entero.\n");
        return;
    }
    equipo = buscarCodigoLineal(equipos, cantidad, codigo);
    if (equipo == NULL) {
        printf("  Prestamo rechazado: no existe un equipo con el codigo %d.\n", codigo);
        return;
    }
    printf("  Equipo: %s (disponibles: %d)\n", equipo->nombre, equipo->disponibles);

    if (!leerNumero("  Semana del prestamo (1-4): ", &semana) || !semanaValida(semana)) {
        printf("  Prestamo rechazado: la semana debe ser un entero entre 1 y %d.\n", SEMANAS);
        return;
    }
    if (!leerNumero("  Cantidad de unidades a prestar: ", &unidades) || unidades <= 0) {
        printf("  Prestamo rechazado: la cantidad debe ser un entero positivo.\n");
        return;
    }

    if (registrarPrestamo(equipo, semana, unidades)) {
        printf("  Prestamo registrado: %d unidad(es) de \"%s\" en la semana %d.\n",
               unidades, equipo->nombre, semana);
        printf("  Disponibles: %d   Prestados: %d\n",
               equipo->disponibles, equipo->prestados);
    } else {
        /* Semana y cantidad ya se validaron arriba: solo queda la
           falta de existencias. */
        printf("  Prestamo rechazado: se solicitaron %d unidad(es) pero solo hay %d disponible(s).\n",
               unidades, equipo->disponibles);
        printf("  El inventario no fue modificado.\n");
    }
}

/* procesarDevolucion: misma estructura que procesarPrestamo. */
void procesarDevolucion(Equipo equipos[], int cantidad)
{
    Equipo *equipo;
    int codigo, semana, unidades;

    printf("\n  REGISTRAR DEVOLUCION\n");
    imprimirLinea('-');

    if (!leerNumero("  Codigo del equipo: ", &codigo)) {
        printf("  Devolucion rechazada: el codigo debe ser un numero entero.\n");
        return;
    }
    equipo = buscarCodigoLineal(equipos, cantidad, codigo);
    if (equipo == NULL) {
        printf("  Devolucion rechazada: no existe un equipo con el codigo %d.\n", codigo);
        return;
    }
    printf("  Equipo: %s (prestados: %d)\n", equipo->nombre, equipo->prestados);

    if (!leerNumero("  Semana de la devolucion (1-4): ", &semana) || !semanaValida(semana)) {
        printf("  Devolucion rechazada: la semana debe ser un entero entre 1 y %d.\n", SEMANAS);
        return;
    }
    if (!leerNumero("  Cantidad de unidades devueltas: ", &unidades) || unidades <= 0) {
        printf("  Devolucion rechazada: la cantidad debe ser un entero positivo.\n");
        return;
    }

    if (registrarDevolucion(equipo, semana, unidades)) {
        printf("  Devolucion registrada: %d unidad(es) de \"%s\" en la semana %d.\n",
               unidades, equipo->nombre, semana);
        printf("  Disponibles: %d   Prestados: %d\n",
               equipo->disponibles, equipo->prestados);
    } else {
        printf("  Devolucion rechazada: se devolverian %d unidad(es) pero solo hay %d prestada(s).\n",
               unidades, equipo->prestados);
        printf("  El inventario no fue modificado.\n");
    }
}

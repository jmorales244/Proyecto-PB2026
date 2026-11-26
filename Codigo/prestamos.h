/* ============================================================
   MEMBER 3 - INVENTORY TRANSACTIONS
   (MIEMBRO 3 - Transacciones de inventario)

   prestamos.h - Declaraciones del modulo de prestamos y
   devoluciones.
   ============================================================ */

#ifndef PRESTAMOS_H
#define PRESTAMOS_H

#include "laboratorio.h"

int  registrarPrestamo(Equipo *equipo, int semana, int cantidad);
int  registrarDevolucion(Equipo *equipo, int semana, int cantidad);
void procesarPrestamo(Equipo equipos[], int cantidad);
void procesarDevolucion(Equipo equipos[], int cantidad);

#endif /* PRESTAMOS_H */

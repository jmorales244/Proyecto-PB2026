/* ============================================================
   MEMBER 5 - HISTORY AND REPORTING
   (MIEMBRO 5 - Historial y reportes)

   reportes.h - Declaraciones del modulo de historial y reportes.
   ============================================================ */

#ifndef REPORTES_H
#define REPORTES_H

#include "laboratorio.h"

void mostrarHistorial(const Equipo *equipo);
int  equipoEsConsistente(const Equipo *equipo);
void generarResumen(const Equipo equipos[], int cantidad);
void procesarHistorial(Equipo equipos[], int cantidad);

#endif /* REPORTES_H */

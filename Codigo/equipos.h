/* ============================================================
   MEMBER 2 - EQUIPMENT REGISTRATION AND CATALOG
   (MIEMBRO 2 - Registro de equipos y catalogo)

   equipos.h - Declaraciones del modulo de equipos.
   ============================================================ */

#ifndef EQUIPOS_H
#define EQUIPOS_H

#include "laboratorio.h"

void capturarEquipos(Equipo equipos[], int *cantidad);
void mostrarCatalogo(const Equipo equipos[], int cantidad);
void mostrarEquipo(const Equipo *equipo);
int  categoriaValida(const char categoria[]);
int  codigoExiste(const Equipo equipos[], int cantidad, int codigo);

#endif /* EQUIPOS_H */

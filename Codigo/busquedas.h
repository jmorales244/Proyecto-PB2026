/* ============================================================
   MEMBER 4 - SEARCHING AND SORTING ALGORITHMS
   (MIEMBRO 4 - Busqueda y ordenamiento)

   busquedas.h - Declaraciones del modulo de busquedas y
   ordenamiento.
   ============================================================ */

#ifndef BUSQUEDAS_H
#define BUSQUEDAS_H

#include "laboratorio.h"

Equipo *buscarCodigoLineal(Equipo equipos[], int cantidad, int codigo);
Equipo *buscarCodigoBinaria(Equipo equipos[], int cantidad, int codigo);
Equipo *buscarPorNombre(Equipo equipos[], int cantidad, const char nombre[]);
void    ordenarPorCodigo(Equipo equipos[], int cantidad);
void    procesarBusquedaLineal(Equipo equipos[], int cantidad);
void    procesarBusquedaBinaria(Equipo equipos[], int cantidad, int catalogoOrdenado);
void    procesarBusquedaNombre(Equipo equipos[], int cantidad);

#endif /* BUSQUEDAS_H */

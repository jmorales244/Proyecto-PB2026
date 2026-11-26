/* ============================================================
   MEMBER 1 - PROGRAM ARCHITECTURE AND INTEGRATION
   (MIEMBRO 1 - Arquitectura e integracion)

   laboratorio.h
   Elementos COMPARTIDOS por todos los modulos:
     - constantes del sistema
     - estructura Equipo (typedef)
     - lista de categorias validas
     - declaraciones de las funciones auxiliares comunes
       (definidas en laboratorio.c)

   Este archivo solo contiene declaraciones de codigo. La
   documentacion academica NO va aqui (ver carpeta Documentacion).
   ============================================================ */

#ifndef LABORATORIO_H
#define LABORATORIO_H

/* ---------- Constantes del sistema ---------- */
#define MAX_EQUIPOS       100   /* capacidad maxima del catalogo      */
#define SEMANAS           4     /* semanas de operacion               */
#define COLUMNAS_MOV      2     /* columnas de la matriz movimientos  */
#define COL_PRESTAMOS     0     /* columna 0: unidades prestadas      */
#define COL_DEVOLUCIONES  1     /* columna 1: unidades devueltas      */

#define LONG_NOMBRE       40    /* 39 caracteres visibles + '\0'      */
#define LONG_CATEGORIA    20
#define CODIGO_MIN        1
#define CODIGO_MAX        99999
#define TOTAL_MIN         1
#define TOTAL_MAX         500

#define LONG_LINEA        128   /* tamano del buffer de lectura       */
#define ANCHO_LINEA       77    /* ancho de tablas y separadores      */
#define NUM_CATEGORIAS    3

/* ---------- Estructura principal ----------
   movimientos[SEMANAS][COLUMNAS_MOV] equivale a movimientos[4][2]:
     fila    = semana (0 a 3, que corresponde a semanas 1 a 4)
     columna = 0 prestadas, 1 devueltas                               */
typedef struct {
    int  codigo;
    char nombre[LONG_NOMBRE];
    char categoria[LONG_CATEGORIA];
    int  total;
    int  disponibles;
    int  prestados;
    int  movimientos[SEMANAS][COLUMNAS_MOV];
} Equipo;

/* ---------- Categorias validas (definidas en laboratorio.c) ---------- */
extern const char *const CATEGORIAS[NUM_CATEGORIAS];

/* ---------- Funciones auxiliares comunes (laboratorio.c) ---------- */
int  leerLinea(char destino[], int tam);
int  leerNumero(const char mensaje[], int *valor);
int  leerEnteroEnRango(const char mensaje[], int minimo, int maximo);
int  leerTexto(const char mensaje[], char destino[], int tam);
void recortarEspacios(char texto[]);
void imprimirLinea(char caracter);
int  semanaValida(int semana);

#endif /* LABORATORIO_H */

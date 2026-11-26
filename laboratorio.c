/* ============================================================
   SISTEMA DE CONTROL DE PRESTAMOS DE EQUIPO DE LABORATORIO
   Proyecto PB2026 - Aplicacion de consola en C

   Archivo unico: laboratorio.c
   Compilacion (GCC en Windows):
     gcc -Wall -Wextra -pedantic -std=c99 -o laboratorio.exe laboratorio.c

   Organizacion del archivo (buscar los letreros "MEMBER n"):
     MEMBER 1 - Arquitectura e integracion  (constantes, typedef,
                prototipos, main, menu)
     SHARED   - Funciones auxiliares compartidas (lectura segura
                de teclado, validaciones comunes)
     MEMBER 2 - Registro de equipos y catalogo
     MEMBER 3 - Transacciones de inventario (prestamo/devolucion)
     MEMBER 4 - Busqueda y ordenamiento
     MEMBER 5 - Historial y reportes

   Convenciones comunes a todo el archivo:
     - Nombres de funciones y variables en espanol.
     - Todo el texto de consola va sin acentos para verse bien en
       la consola estandar de Windows.
     - Las operaciones devuelven 1 cuando se realizan y 0 cuando
       se rechazan; una operacion rechazada NUNCA modifica datos.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>


/* ============================================================
   MEMBER 1 - PROGRAM ARCHITECTURE AND INTEGRATION
   (MIEMBRO 1 - Arquitectura e integracion)
   Contenido: constantes, typedef Equipo, prototipos, main(),
              mostrarMenu()
   ============================================================ */

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

/* ---------- Categorias validas (compartidas por todo el programa) ---------- */
static const char *const CATEGORIAS[NUM_CATEGORIAS] = {
    "Computo",
    "Medicion",
    "Electronica"
};

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

/* ---------- Prototipos de las funciones obligatorias ---------- */
void    capturarEquipos(Equipo equipos[], int *cantidad);
int     mostrarMenu(void);
void    mostrarCatalogo(const Equipo equipos[], int cantidad);
Equipo *buscarCodigoLineal(Equipo equipos[], int cantidad, int codigo);
Equipo *buscarCodigoBinaria(Equipo equipos[], int cantidad, int codigo);
Equipo *buscarPorNombre(Equipo equipos[], int cantidad, const char nombre[]);
void    ordenarPorCodigo(Equipo equipos[], int cantidad);
int     registrarPrestamo(Equipo *equipo, int semana, int cantidad);
int     registrarDevolucion(Equipo *equipo, int semana, int cantidad);
void    mostrarHistorial(const Equipo *equipo);
void    generarResumen(const Equipo equipos[], int cantidad);

/* ---------- Prototipos de funciones auxiliares ---------- */
/* Compartidas (lectura de teclado y presentacion) */
int  leerLinea(char destino[], int tam);
int  leerNumero(const char mensaje[], int *valor);
int  leerEnteroEnRango(const char mensaje[], int minimo, int maximo);
int  leerTexto(const char mensaje[], char destino[], int tam);
void recortarEspacios(char texto[]);
void imprimirLinea(char caracter);
int  semanaValida(int semana);
/* Member 2 */
int  categoriaValida(const char categoria[]);
int  codigoExiste(const Equipo equipos[], int cantidad, int codigo);
void mostrarEquipo(const Equipo *equipo);
/* Member 3 */
void procesarPrestamo(Equipo equipos[], int cantidad);
void procesarDevolucion(Equipo equipos[], int cantidad);
/* Member 4 */
void procesarBusquedaLineal(Equipo equipos[], int cantidad);
void procesarBusquedaBinaria(Equipo equipos[], int cantidad, int catalogoOrdenado);
void procesarBusquedaNombre(Equipo equipos[], int cantidad);
/* Member 5 */
int  equipoEsConsistente(const Equipo *equipo);
void procesarHistorial(Equipo equipos[], int cantidad);


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


/* ============================================================
   SHARED - FUNCIONES AUXILIARES COMPARTIDAS
   (Usadas por todos los miembros; no pertenecen a uno solo)
   ============================================================ */

/* leerLinea: lee una linea completa con fgets() y quita el salto de
   linea con strcspn(). Devuelve 1 si la linea cabia en el buffer y
   0 si era demasiado larga (el resto se descarta para que no
   contamine la siguiente lectura). Si se acaba la entrada
   (Ctrl+Z / fin de archivo) cierra el programa para evitar ciclos
   infinitos. */
int leerLinea(char destino[], int tam)
{
    int c;

    if (fgets(destino, tam, stdin) == NULL) {
        printf("\n  Entrada finalizada. Se cierra el programa.\n");
        exit(EXIT_FAILURE);
    }

    if (strchr(destino, '\n') == NULL && !feof(stdin)) {
        /* No cupo el salto de linea: descartar lo que sobra. */
        while ((c = getchar()) != '\n' && c != EOF) {
            /* vaciar el resto de la linea */
        }
        return 0;
    }

    destino[strcspn(destino, "\r\n")] = '\0';
    return 1;
}

/* leerNumero: muestra el mensaje, lee UNA linea y la convierte a int.
   Devuelve 1 si se obtuvo un entero valido (guardado en *valor) y
   0 en caso contrario (letras, vacio, decimales, desbordamiento).
   No imprime errores: cada llamador decide que mensaje mostrar. */
int leerNumero(const char mensaje[], int *valor)
{
    char  linea[LONG_LINEA];
    char *fin;
    long  numero;

    printf("%s", mensaje);
    if (!leerLinea(linea, LONG_LINEA)) {
        return 0;
    }

    errno = 0;
    numero = strtol(linea, &fin, 10);

    if (fin == linea) {                 /* no se leyo ningun digito */
        return 0;
    }
    while (*fin == ' ' || *fin == '\t') {   /* permitir espacios al final */
        fin++;
    }
    if (*fin != '\0') {                 /* sobraron caracteres no numericos */
        return 0;
    }
    if (errno == ERANGE || numero > INT_MAX || numero < INT_MIN) {
        return 0;
    }

    *valor = (int)numero;
    return 1;
}

/* leerEnteroEnRango: repite la pregunta hasta que el usuario escriba
   un entero entre minimo y maximo (inclusive). */
int leerEnteroEnRango(const char mensaje[], int minimo, int maximo)
{
    int valor = 0;
    int valido = 0;

    do {
        if (!leerNumero(mensaje, &valor)) {
            printf("  Error: ingrese un numero entero.\n");
        } else if (valor < minimo || valor > maximo) {
            printf("  Error: el valor debe estar entre %d y %d.\n", minimo, maximo);
        } else {
            valido = 1;
        }
    } while (!valido);

    return valor;
}

/* leerTexto: lee una linea de texto con espacios, le quita los
   espacios de los extremos y la copia a destino.
   Devuelve la longitud del texto (0 si quedo vacio) o -1 si el
   texto no cabe en tam bytes (incluyendo el '\0'). En el caso -1
   destino no se modifica. */
int leerTexto(const char mensaje[], char destino[], int tam)
{
    char linea[LONG_LINEA];
    int  longitud;

    printf("%s", mensaje);
    if (!leerLinea(linea, LONG_LINEA)) {
        return -1;
    }

    recortarEspacios(linea);
    longitud = (int)strlen(linea);
    if (longitud >= tam) {
        return -1;
    }

    strcpy(destino, linea);   /* seguro: ya se verifico que cabe */
    return longitud;
}

/* recortarEspacios: elimina espacios y tabuladores al inicio y al
   final de la cadena (modifica la cadena recibida). */
void recortarEspacios(char texto[])
{
    int    inicio = 0;
    size_t fin;

    while (texto[inicio] == ' ' || texto[inicio] == '\t') {
        inicio++;
    }
    if (inicio > 0) {
        memmove(texto, texto + inicio, strlen(texto + inicio) + 1);
    }

    fin = strlen(texto);
    while (fin > 0 && (texto[fin - 1] == ' ' || texto[fin - 1] == '\t')) {
        texto[fin - 1] = '\0';
        fin--;
    }
}

/* imprimirLinea: dibuja un separador del ancho estandar. */
void imprimirLinea(char caracter)
{
    int i;
    for (i = 0; i < ANCHO_LINEA; i++) {
        putchar(caracter);
    }
    putchar('\n');
}

/* semanaValida: devuelve 1 si la semana esta entre 1 y SEMANAS. */
int semanaValida(int semana)
{
    return semana >= 1 && semana <= SEMANAS;
}


/* ============================================================
   MEMBER 2 - EQUIPMENT REGISTRATION AND CATALOG
   (MIEMBRO 2 - Registro de equipos y catalogo)
   Contenido: capturarEquipos(), mostrarCatalogo(), validaciones
              de captura, codigos unicos, categorias
   ============================================================ */

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


/* ============================================================
   MEMBER 3 - INVENTORY TRANSACTIONS
   (MIEMBRO 3 - Transacciones de inventario)
   Contenido: registrarPrestamo(), registrarDevolucion() y las
              funciones que piden los datos al usuario
   ============================================================ */

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


/* ============================================================
   MEMBER 4 - SEARCHING AND SORTING ALGORITHMS
   (MIEMBRO 4 - Busqueda y ordenamiento)
   Contenido: buscarCodigoLineal(), buscarCodigoBinaria(),
              buscarPorNombre(), ordenarPorCodigo() y las
              funciones que piden los datos al usuario.
   Estado "catalogo ordenado": la variable catalogoOrdenado vive
   en main() y se pasa por valor a procesarBusquedaBinaria().
   ============================================================ */

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


/* ============================================================
   MEMBER 5 - HISTORY AND REPORTING
   (MIEMBRO 5 - Historial y reportes)
   Contenido: mostrarHistorial(), generarResumen(), matriz de
              resumen semanal y estadisticas del inventario
   ============================================================ */

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

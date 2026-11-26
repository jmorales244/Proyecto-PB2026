# Miembro 2 — Registro de equipos y catálogo

**Integrante:** _______________________

**Código a tu cargo:** `equipos.h`, `equipos.c`

## Secciones que te corresponden (PDF 8.2)

- **3. Marco teórico — tema: aritmética de apuntadores**
- **4. Diseño de la estructura `Equipo`** (miembros y matriz de movimientos)
- **6. Documentación de funciones** — las de tu módulo
- **11. Evidencias de ejecución** — registro y visualización del catálogo

## Qué pide el PDF

- Explicar la estructura `Equipo`, sus miembros y la matriz `movimientos[4][2]`.
- Documentar parámetros, retorno y responsabilidad de cada función.
- Captura que demuestre el registro y la visualización del catálogo.
- El PDF exige recorrer el arreglo con una variable de apuntador y `p++` en `mostrarCatalogo()`.

## Dónde está en el código

| Elemento | Archivo |
|---|---|
| `typedef struct { ... } Equipo` | `laboratorio.h` |
| `capturarEquipos()` | `equipos.c` |
| `mostrarCatalogo()` (recorrido con `p++`) | `equipos.c` |
| `mostrarEquipo()`, `categoriaValida()`, `codigoExiste()` | `equipos.c` |

## Preguntas guía para investigar

- ¿Qué significa sumar o incrementar un apuntador a estructura? ¿Cuántos bytes avanza `p++`?
- ¿Qué relación hay entre `equipos[i]` y `*(equipos + i)`?
- ¿Por qué `mostrarCatalogo()` recibe el arreglo como `const`?
- ¿Cómo se interpreta la matriz `movimientos`: qué es una fila y qué es una columna?
- ¿Por qué `capturarEquipos()` recibe un apuntador a la cantidad y no el valor?
- ¿Cómo se garantiza que los códigos no se repitan y que la categoría sea válida?
- ¿Para qué se usan `fgets()`, `strcspn()` y `strcmp()` en el registro?

## Capturas de pantalla requeridas

- [ ] Registro de equipos (captura de varios equipos durante la captura).
- [ ] Catálogo mostrado con la opción 1.
- [ ] (Opcional) Un rechazo por código repetido o categoría inválida.

## Tu texto

### Marco teórico: aritmética de apuntadores
_(escribe aquí)_

### Diseño de la estructura `Equipo`
_(escribe aquí)_

### Documentación de las funciones de mi módulo
_(para cada función: parámetros, tipo de retorno, responsabilidad)_

### Evidencias
_(inserta capturas con un pie de figura)_

## Fuentes consultadas (Teams)

- 

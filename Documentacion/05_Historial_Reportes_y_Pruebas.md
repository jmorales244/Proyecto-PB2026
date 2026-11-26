# Miembro 5 — Historial, reportes y pruebas

**Integrante:** _______________________

**Código a tu cargo:** `reportes.h`, `reportes.c`

## Secciones que te corresponden (PDF 8.2)

- **6. Documentación de funciones** — las de tu módulo
- **10. Resultados de las pruebas realizadas** (consolidas las pruebas de todo el equipo)
- **11. Evidencias de ejecución** — consulta de historial y reporte general

## Qué pide el PDF

- Documentar parámetros, retorno y responsabilidad de cada función.
- Presentar los resultados de las pruebas. El PDF (sección 7) pide verificar las condiciones de integridad mediante pruebas de ejecución, y el equipo debe probar con **al menos 20 registros de equipo**.
- Capturas de la consulta de historial y del reporte general.
- Recordar que el reporte debe construir una matriz de resumen de 4 filas × 2 columnas con ciclos anidados.

## Dónde está en el código

| Elemento | Archivo |
|---|---|
| `mostrarHistorial()` (recibe `const Equipo *`) | `reportes.c` |
| `generarResumen()` (recibe el arreglo `const`) | `reportes.c` |
| `equipoEsConsistente()` | `reportes.c` |
| `procesarHistorial()` | `reportes.c` |

## Preguntas guía para investigar

- ¿Qué impide modificar los datos cuando un parámetro es `const Equipo *`?
- ¿Cómo se consolida la matriz de resumen a partir de las matrices de cada equipo?
- ¿Qué indicadores pide el PDF en el reporte general y de dónde sale cada uno?
- ¿Cómo comprobarían, después de cada transacción, que se cumplen las invariantes?
- ¿Cómo registrarán el resultado de cada prueba (datos de entrada, resultado obtenido, cumple/no cumple)?

## Escenarios de prueba a ejecutar y registrar

Usa `../Codigo/datos_prueba_20_equipos.txt` para el registro de 20 equipos. Completa las
columnas con lo que **observes** al ejecutar el programa.

| # | Escenario | Datos de entrada que usaste | Resultado obtenido | ¿Invariantes cumplidas? |
|---|---|---|---|---|
| 1 | Registro de al menos 20 equipos | | | |
| 2 | Visualización del catálogo | | | |
| 3 | Préstamo exitoso | | | |
| 4 | Préstamo rechazado por falta de existencias | | | |
| 5 | Préstamo rechazado por código, semana o cantidad inválidos | | | |
| 6 | Devolución exitosa | | | |
| 7 | Devolución rechazada por exceder lo prestado | | | |
| 8 | Búsqueda lineal (con y sin coincidencia) | | | |
| 9 | Búsqueda binaria antes de ordenar | | | |
| 10 | Búsqueda por nombre (con y sin coincidencia) | | | |
| 11 | Ordenamiento por inserción | | | |
| 12 | Búsqueda binaria después de ordenar | | | |
| 13 | Consulta de historial | | | |
| 14 | Reporte general | | | |
| 15 | Opción de menú inválida | | | |
| 16 | Errores en el registro (cantidad, código repetido, categoría) | | | |
| 17 | Registro con 100 equipos (capacidad máxima) | | | |

## Capturas de pantalla requeridas

- [ ] Consulta de historial de un equipo con movimientos.
- [ ] Reporte general.

## Tu texto

### Documentación de las funciones de mi módulo
_(para cada función: parámetros, tipo de retorno, responsabilidad)_

### Resultados de las pruebas
_(resume los resultados de la tabla anterior y explica cómo verificaron las invariantes)_

### Evidencias
_(inserta capturas con un pie de figura)_

## Fuentes consultadas (Teams)

- 

# Miembro 4 — Búsqueda y ordenamiento

**Integrante:** _______________________

**Código a tu cargo:** `busquedas.h`, `busquedas.c`

## Secciones que te corresponden (PDF 8.2)

- **6. Documentación de funciones** — las de tu módulo
- **7. Uso de apuntadores en las operaciones de búsqueda**
- **8. Descripción del algoritmo de ordenamiento por inserción y de la búsqueda binaria**
- **11. Evidencias de ejecución** — búsqueda exitosa y sin coincidencia; ordenamiento y búsqueda binaria

## Qué pide el PDF

- Explicar el uso de apuntadores en las búsquedas (retorno de dirección de estructura y `NULL`).
- Describir el ordenamiento por inserción y la búsqueda binaria.
- Capturas: búsqueda exitosa, búsqueda sin coincidencia, ordenamiento y búsqueda binaria.
- Recordar los requisitos del PDF: el ordenamiento mueve estructuras completas y la búsqueda binaria solo se usa con el catálogo ya ordenado.

## Dónde está en el código

| Elemento | Archivo |
|---|---|
| `buscarCodigoLineal()` | `busquedas.c` |
| `buscarCodigoBinaria()` | `busquedas.c` |
| `buscarPorNombre()` | `busquedas.c` |
| `ordenarPorCodigo()` | `busquedas.c` |
| `procesarBusquedaLineal/Binaria/Nombre()` | `busquedas.c` |
| Indicador `catalogoOrdenado` | `main.c` (se pasa a `procesarBusquedaBinaria()`) |

## Preguntas guía para investigar

- ¿Qué devuelve una función que retorna `Equipo *` y qué significa `NULL` en ese contexto?
- ¿Por qué es correcto devolver la dirección de un elemento del arreglo original y no la de una variable local?
- ¿Cómo funciona la búsqueda lineal y cuántas comparaciones puede requerir?
- ¿Por qué la búsqueda binaria exige un arreglo ordenado? ¿Cómo se reduce el intervalo en cada paso?
- ¿Cómo funciona el ordenamiento por inserción? ¿Qué papel cumple la variable temporal?
- ¿Por qué se ordenan estructuras completas y no solo los códigos?
- ¿Qué diferencia hay entre una comparación exacta con `strcmp()` y una que ignora mayúsculas?

## Capturas de pantalla requeridas

- [ ] Búsqueda lineal exitosa.
- [ ] Búsqueda sin coincidencia.
- [ ] Intento de búsqueda binaria antes de ordenar (rechazo).
- [ ] Ordenamiento (opción 5) y catálogo resultante.
- [ ] Búsqueda binaria exitosa.

## Tu texto

### Documentación de las funciones de mi módulo
_(para cada función: parámetros, tipo de retorno, responsabilidad)_

### Uso de apuntadores en las búsquedas
_(escribe aquí)_

### Ordenamiento por inserción
_(escribe aquí)_

### Búsqueda binaria
_(escribe aquí)_

### Evidencias
_(inserta capturas con un pie de figura)_

## Fuentes consultadas (Teams)

- 

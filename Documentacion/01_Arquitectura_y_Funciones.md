# Miembro 1 — Arquitectura e integración

**Integrante:** _______________________

**Código a tu cargo:** `main.c`, `laboratorio.h`, `laboratorio.c`

## Secciones que te corresponden (PDF 8.2)

- **1. Portada**
- **2. Descripción del problema y objetivo del sistema**
- **3. Marco teórico — tema: funciones** (prototipado, paso de parámetros por valor y por referencia)
- **5. Diagrama o descripción de la organización funcional** (relación entre `main()` y las funciones)
- **6. Documentación de funciones** — las de tu módulo (lista abajo)

## Qué pide el PDF

- Portada.
- Describir el problema y el objetivo del sistema (el PDF lo plantea en sus secciones 2 y 3).
- Marco teórico con base en las fuentes aportadas en Teams.
- Mostrar cómo se relacionan `main()` y las funciones implementadas.
- Documentar cada función: parámetros, tipo de retorno y responsabilidad.

## Dónde está en el código

| Elemento | Archivo |
|---|---|
| `main()` | `main.c` |
| `mostrarMenu()` | `main.c` |
| Constantes, `typedef Equipo`, `CATEGORIAS` | `laboratorio.h` / `laboratorio.c` |
| `leerLinea`, `leerNumero`, `leerEnteroEnRango`, `leerTexto`, `recortarEspacios`, `imprimirLinea`, `semanaValida` | `laboratorio.h` (declaración) / `laboratorio.c` (definición) |
| Variable `catalogoOrdenado` | `main.c` |

Para el diagrama (punto 5) revisa qué función de qué módulo llama cada `case` del `switch` en `main()`.

## Preguntas guía para investigar

- ¿Para qué sirve un prototipo y por qué debe declararse antes de la llamada?
- ¿Qué diferencia hay entre pasar un parámetro por valor y por referencia (mediante apuntador)?
- En el proyecto, ¿qué parámetros se pasan por valor y cuáles por apuntador? ¿Por qué?
- ¿Por qué `main()` no debe concentrar el procesamiento? ¿Qué responsabilidad conserva?
- ¿Qué hace un archivo de cabecera y qué evita la protección `#ifndef`?
- ¿Por qué `catalogoOrdenado` se pasa por valor a la función de búsqueda binaria?

## Capturas de pantalla / material

- [ ] Menú principal mostrado en la consola.
- [ ] Diagrama de la organización funcional (lo preparas tú).

## Tu texto

### Portada
_(escribe aquí)_

### Descripción del problema y objetivo
_(escribe aquí)_

### Marco teórico: funciones
_(escribe aquí)_

### Organización funcional
_(escribe aquí)_

### Documentación de las funciones de mi módulo
_(para cada función: parámetros, tipo de retorno, responsabilidad)_

## Fuentes consultadas (Teams)

- 

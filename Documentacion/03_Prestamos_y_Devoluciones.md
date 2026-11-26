# Miembro 3 — Transacciones de inventario

**Integrante:** _______________________

**Código a tu cargo:** `prestamos.h`, `prestamos.c`

## Secciones que te corresponden (PDF 8.2)

- **3. Marco teórico — tema: apuntadores** (conceptos generales, operador `->`, apuntadores constantes)
- **6. Documentación de funciones** — las de tu módulo
- **7. Uso de apuntadores en préstamo y devolución**
- **9. Condiciones de integridad** usadas para controlar préstamos y devoluciones
- **11. Evidencias de ejecución** — préstamo y devolución (exitosos y rechazados)

## Qué pide el PDF

- Explicar cómo se usan los apuntadores en las operaciones de préstamo y devolución.
- Describir las condiciones de integridad (el PDF las lista en su sección 7).
- Capturas: préstamo exitoso, préstamo rechazado por falta de existencias, devolución exitosa, devolución rechazada por exceder lo prestado.

## Dónde está en el código

| Elemento | Archivo |
|---|---|
| `registrarPrestamo()` | `prestamos.c` |
| `registrarDevolucion()` | `prestamos.c` |
| `procesarPrestamo()`, `procesarDevolucion()` (piden datos y llaman a las anteriores) | `prestamos.c` |
| Verificación de las invariantes de un equipo | `equipoEsConsistente()` en `reportes.c` |

## Preguntas guía para investigar

- ¿Qué es un apuntador y qué guarda? ¿Qué diferencia hay entre `.` y `->`?
- ¿Por qué `registrarPrestamo()` recibe un `Equipo *` y no una copia de `Equipo`?
- ¿Qué pasaría con el inventario real si recibiera una copia?
- ¿Qué condiciones se validan antes de modificar el registro, y en qué orden?
- ¿Qué garantiza que una operación rechazada no modifique el inventario?
- ¿Qué significa cada condición de integridad de la sección 7 del PDF y cómo se verifica en las pruebas?
- ¿Qué valor devuelven las funciones para indicar éxito o rechazo?

## Capturas de pantalla requeridas

- [ ] Préstamo exitoso.
- [ ] Préstamo rechazado por falta de existencias.
- [ ] Devolución exitosa.
- [ ] Devolución rechazada por exceder las unidades prestadas.

## Tu texto

### Marco teórico: apuntadores
_(escribe aquí)_

### Documentación de las funciones de mi módulo
_(para cada función: parámetros, tipo de retorno, responsabilidad)_

### Uso de apuntadores en préstamo y devolución
_(escribe aquí)_

### Condiciones de integridad
_(escribe aquí)_

### Evidencias
_(inserta capturas con un pie de figura)_

## Fuentes consultadas (Teams)

- 

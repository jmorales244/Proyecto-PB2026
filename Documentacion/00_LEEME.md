# Documentación técnica — Guía del equipo

Esta carpeta contiene **plantillas vacías**, una por integrante. No contiene el texto del
informe: el PDF del proyecto (sección 8.2, punto 6) permite usar IA para implementar las
funciones, **pero no para la documentación**. Cada integrante investiga y redacta su parte.

Los archivos de código (`../Codigo/`) y esta carpeta son independientes: nada de lo que
escriban aquí debe copiarse dentro de los archivos `.h` o `.c`.

## Reparto de secciones

Numeración tomada del PDF, sección 8.2 (Documento técnico).

| Archivo | Integrante | Módulo de código | Secciones del documento técnico |
|---|---|---|---|
| `01_Arquitectura_y_Funciones.md` | Miembro 1 | `main.c`, `laboratorio.h/.c` | 1 Portada · 2 Descripción y objetivo · 3 (parte: funciones) · 5 Organización funcional · 6 (parte) |
| `02_Equipos_y_Catalogo.md` | Miembro 2 | `equipos.h/.c` | 3 (parte: aritmética de apuntadores) · 4 Diseño de `Equipo` · 6 (parte) · 11 (evidencias) |
| `03_Prestamos_y_Devoluciones.md` | Miembro 3 | `prestamos.h/.c` | 3 (parte: apuntadores) · 6 (parte) · 7 (préstamo y devolución) · 9 Integridad · 11 (evidencias) |
| `04_Busquedas_y_Ordenamiento.md` | Miembro 4 | `busquedas.h/.c` | 6 (parte) · 7 (búsquedas) · 8 Algoritmos · 11 (evidencias) |
| `05_Historial_Reportes_y_Pruebas.md` | Miembro 5 | `reportes.h/.c` | 6 (parte) · 10 Resultados de pruebas · 11 (evidencias) |

El **marco teórico (sección 3)** se divide en tres temas (apuntadores, aritmética de
apuntadores, funciones). Cada tema lo redacta quien lo tiene asignado en la tabla y, al
armar el documento final, se unen en el orden del PDF. Las fuentes deben ser las aportadas
en Teams.

## Cómo está organizado cada archivo

1. Qué pide el PDF para tu parte.
2. Dónde está tu parte en el código (archivo y función).
3. Preguntas guía para investigar (no son respuestas).
4. Capturas de pantalla que debes tomar.
5. Espacio para tu texto.
6. Fuentes consultadas.

## Para armar el documento final

Orden sugerido (el del PDF): 1 Portada, 2 Descripción, 3 Marco teórico, 4 Diseño de
`Equipo`, 5 Organización funcional, 6 Documentación de funciones, 7 Uso de apuntadores,
8 Algoritmos, 9 Integridad, 10 Resultados de pruebas, 11 Evidencias de ejecución.
Acuerden entre todos el formato (tipografía, numeración de figuras, estilo de citas)
antes de redactar.

## Compilar y ejecutar para sus pruebas

Ver `../Codigo/` y las instrucciones de compilación entregadas con el proyecto.
Los datos de prueba con 20 equipos están en `../Codigo/datos_prueba_20_equipos.txt`.

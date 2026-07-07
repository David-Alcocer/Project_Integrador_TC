# Generador de código (MiniLang → C)

El objetivo es que, además de validar un programa, el compilador lo **traduzca a C equivalente**, lo compile y lo ejecute.

---

## ¿Qué es un generador de código?

Hasta ahora el compilador solo **verifica** que un programa esté bien escrito (análisis léxico y sintáctico). El generador de código da un paso más, **produce un programa nuevo** en otro lenguaje que hace lo mismo.
 
En este caso, toma un programa MiniLang válido y genera un archivo `.c` equivalente. Ese `.c` se compila con gcc y, al ejecutarse, produce el mismo comportamiento que describía el programa MiniLang.

La diferencia conceptual es grande, el parser solo *revisaba y descartaba* los tokens; el generador, además de revisar, tiene que *recordar y construir* código de salida.

---

## MiniLang y C se parecen, pero no son iguales

MiniLang se diseñó parecido a C, lo que facilita la traducción. Pero hay diferencias que el generador debe resolver:

- **Declaración de variables.** En MiniLang las variables se usan directamente (`a = 10;`). En C hay que declararlas antes (`int a;`). El generador debe detectar todas las variables y declararlas al inicio.
- **Impresión.** El `print(x)` de MiniLang debe volverse `printf("%d\n", x);` en C. Con cadenas, `print("texto")` se traduce con el formato adecuado.
- **Bloques.** El `begin ... end` de MiniLang equivale a las llaves `{ }` del `main` en C.
- **Estructura general.** Un programa MiniLang es solo una lista de sentencias; en C hay que envolverlas en un `#include`, un `int main()` y un `return 0;`.

Lo que **sí** se traduce casi directo: las expresiones aritméticas, los operadores relacionales, las asignaciones, y las estructuras `if`, `else` y `while`, porque su sintaxis es muy similar entre ambos lenguajes.

---

## Tabla de equivalencias MiniLang → C

| MiniLang | C generado |
|---|---|
| `begin` ... `end` | `int main() {` ... `return 0; }` |
| `a = 10;` | `a = 10;` |
| `print(x);` | `printf("%d\n", x);` |
| `print("texto");` | `printf("texto\n");` |
| `if (c) { ... }` | `if (c) { ... }` |
| `if (c) { ... } else { ... }` | `if (c) { ... } else { ... }` |
| `while (c) { ... }` | `while (c) { ... }` |
| `a + b * c` | `a + b * c` |
| `x < 5`, `x == 5` | `x < 5`, `x == 5` |
| (variables usadas) | `int a, b, c;` al inicio del `main` |

---

## 4. Cómo funciona la generación

La idea es reutilizar el parser que ya existe. Cada función del parser (que hoy solo valida) se amplía para que, además, **escriba el código C correspondiente** en un archivo de salida.

El flujo sería:

1. El programa se lee y se analiza como hasta ahora.
2. Conforme el parser reconoce cada estructura, va escribiendo su equivalente en C a un archivo `.c` de salida.
3. Antes del cuerpo, se declaran todas las variables detectadas.
4. Al terminar, el `.c` queda completo: se compila con gcc y se ejecuta.

Ejemplo. Este programa MiniLang:

`````
begin
  a = 10;
  b = 20;
  print(a + b);
end
`````

Debería generar un `.c` equivalente a:

`````c
#include <stdio.h>

int main() {
    int a, b;
    a = 10;
    b = 20;
    printf("%d\n", a + b);
    return 0;
}
`````

---

## Plan de construcción 
El generador se dividió en pasos, de la base hacia arriba:

1. **Diseño** — definir la plantilla del `.c` y la tabla de traducción.
2. **Infraestructura de salida** — el mecanismo para escribir el código C generado.
3. **Plantilla base** — generar el esqueleto (`#include`, `main`, `return`).
4. **Expresiones** — traducir expresiones y términos (la base que casi todo usa).
5. **Asignaciones y print** — las sentencias simples.
6. **Recolección de variables** — detectar y declarar todas las variables (el reto mayor).
7. **Condiciones y control de flujo** — traducir `if`, `else` y `while`.
8. **Integración y pruebas** — generar el `.c` completo, compilarlo y verificar la salida.

El orden respeta las dependencias: primero la infraestructura y las expresiones, y al final lo más complejo (variables, control de flujo, integración).

---

## Cómo se probará

Se tomarán los programas `.mini` de prueba ya existentes, se generará su `.c`, se compilará con gcc y se comparará la salida con la esperada. La prueba se considera exitosa cuando un `.mini` válido produce un `.c` que compila sin errores y ejecuta correctamente.

---

## Consideraciones y limitaciones

- El generador asume que el programa de entrada **ya es válido** (pasó el análisis sintáctico). No es su trabajo detectar errores; eso lo hizo el parser.
- Todas las variables se traducen como `int`, ya que MiniLang solo maneja números enteros.
- Es una traducción directa, sin optimizaciones: el objetivo es que el `.c` sea correcto y equivalente, no que sea el más eficiente.



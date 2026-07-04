# MiniLang: Analizador léxico y sintáctico

Proyecto integrador de Teoría de Compiladores. El objetivo es implementar, en lenguaje **C**, un analizador **léxico** y **sintáctico** para un pequeño lenguaje de programación llamado **MiniLang**.

El programa recibe un archivo de texto con un programa escrito en MiniLang y determina si ese programa es **correcto o no** según las reglas del lenguaje.

```
> ./minilang testing/prog1.mini
Programa correcto
```

---

## ¿De qué trata el proyecto?

Un compilador, antes de traducir o ejecutar un programa, primero tiene que entenderlo. Eso se hace en dos fases, y este proyecto implementa esas dos:

- **Análisis léxico:** lee el texto carácter por carácter y lo agrupa en *tokens* (las "palabras" del lenguaje: identificadores, números, operadores, palabras reservadas, etc.).
- **Análisis sintáctico:** toma esos tokens y revisa que estén en un **orden válido** según la gramática del lenguaje. Si el orden es correcto, el programa es válido; si no, se reporta un error de sintaxis indicando la línea.

De forma opcional, el proyecto contempla un **generador de código** que traduce un programa válido de MiniLang a C para poder ejecutarlo.

---

## El lenguaje MiniLang

MiniLang es un lenguaje mínimo con asignaciones, condicionales, ciclos e impresión.

### Palabras reservadas

`begin`, `end`, `if`, `else`, `while`, `print`

### Operadores

- Aritméticos: `+`, `-`, `*`, `/`, `=`
- Relacionales: `<`, `>`, `==`

### Delimitadores

`(`, `)`, `{`, `}`, `;`

### Tokens con patrón

- **Identificadores (variables):** `[A-Za-z_][A-Za-z0-9_]*`
- **Números:** `[0-9][0-9]*`
- **Cadenas:** texto entre comillas dobles, por ejemplo `"Fin del ciclo"`

---

## Gramática Libre de Contexto

La gramática se transformó en tres pasos para poder implementarla por descenso recursivo: se partió de la forma natural, se eliminó la ambigüedad introduciendo niveles de precedencia (expresión, término, factor) y se eliminó la recursividad por la izquierda con reglas auxiliares.

```
<programa>         ::= begin <lista_sentencias> end

<lista_sentencias> ::= <sentencia> <lista_sentencias>
                     | ε

<sentencia>        ::= <asignacion>
                     | <if>
                     | <while>
                     | <print>

<asignacion>       ::= id = <expresion> ;

<if>               ::= if ( <condicion> ) { <lista_sentencias> }
                     | if ( <condicion> ) { <lista_sentencias> }
                       else { <lista_sentencias> }

<while>            ::= while ( <condicion> ) { <lista_sentencias> }

<print>            ::= print ( <expresion> ) ;

<condicion>        ::= <expresion> <relop> <expresion>

<relop>            ::= < | > | ==

<expresion>        ::= <termino> <expresion'>
<expresion'>       ::= + <termino> <expresion'>
                     | - <termino> <expresion'>
                     | ε

<termino>          ::= <factor> <termino'>
<termino'>         ::= * <factor> <termino'>
                     | / <factor> <termino'>
                     | ε

<factor>           ::= id
                     | numero
                     | cadena
                     | ( <expresion> )
```

---

## Ejemplos de programas

Programa con operaciones aritméticas:

```
begin
  a = 10;
  b = 20;
  c = a + b;
  d = c * 2;
  e = d - 5;
  print(e);
end
```

Programa con ciclo y condicional:

```
begin
  contador = 0;
  while (contador < 5) {
    print(contador);
    contador = contador + 1;
  }
  if (contador == 5) {
    print("Fin del ciclo");
  } else {
    print("Error");
  }
end
```

---

## Notas de diseño

El enunciado original tiene algunos puntos ambiguos. Para que el equipo trabajara sobre las mismas reglas, el proyecto adopta estas convenciones:

1. El `;` es un delimitador obligatorio al final de cada asignación y de cada `print`.
2. Los operadores relacionales (`<`, `>`, `==`) se permiten dentro de las condiciones de `if` y `while` (regla `<condicion>`).
3. Una cadena (`"..."`) es un factor válido, de modo que `print` puede recibir tanto una expresión como una cadena.
4. Las cadenas pueden contener letras, dígitos, guiones bajos y espacios (para admitir textos como `"Fin del ciclo"`).

---

## Estructura del proyecto

Todos los archivos viven en una sola carpeta para que la compilación sea directa:

```
minilang/
├── main.c          Punto de entrada: lee el archivo .mini y lanza el análisis
├── lexico.c        Análisis léxico (reconocimiento de tokens)
├── lexico.h        Definición de los tokens (TokenType, Token) y firmas
├── sintactico.c    Análisis sintáctico (parser por descenso recursivo)
├── sintactico.h    Firma del parser y documentación de la gramática
├── Makefile        Compila los .c y genera el ejecutable `minilang`
├── testing/        Programas de ejemplo (.mini) válidos e inválidos
├── .gitignore      Ignora el ejecutable y archivos generados
└── README.md
```

`main.c` incluye únicamente los encabezados (`#include "lexico.h"` y `#include "sintactico.h"`). Los archivos `.c` no se incluyen entre sí: se compilan por separado y se enlazan al final mediante el `Makefile`.

---

## Compilación y ejecución

Compilar:

```
make
```

Ejecutar sobre un archivo MiniLang:

```
./minilang testing/prog1.mini
```

> En Windows el ejecutable se llama `minilang.exe`.

La salida es `Programa correcto` si el programa es sintácticamente válido, o `Error sintactico en la linea N` indicando dónde se encontró el problema.

---

## Pruebas

En la carpeta `testing/` se incluyen programas de ejemplo, tanto válidos como inválidos, para verificar que el analizador acepta lo correcto y rechaza lo incorrecto.

| Archivo | Qué prueba | Resultado esperado | Resultado obtenido |
|---|---|---|---|
| `prueba.mini` | Programa mínimo (`begin`, una asignación, `end`) | Programa correcto | Programa correcto |
| `prog1.mini` | Asignaciones y expresiones aritméticas | Programa correcto | Programa correcto |
| `prog2.mini` | `while`, `if/else`, condiciones relacionales y cadenas | Programa correcto | Programa correcto |
| `error1.mini` | Asignación a la que le falta el `;` | Error sintáctico | Error sintáctico en la línea correspondiente |

---

## Dificultades encontradas y cómo se resolvieron

Durante el desarrollo surgieron varios problemas. Documentarlos forma parte del aprendizaje del proyecto.

**Adaptar la base de una calculadora.** El código de partida era un analizador de expresiones aritméticas. Reconocer el patrón "una regla de la gramática, una función" permitió reutilizar la estructura existente (`E`, `T`, `F`) y ampliarla, en lugar de empezar de cero.

**Distinguir `=` de `==` en el léxico.** Ambos operadores empiezan igual, y el analizador léxico solo mira un carácter a la vez. Se resolvió con una técnica de *lookahead*: al encontrar un `=`, se revisa el siguiente carácter para decidir si es asignación (`=`) o comparación (`==`), consumiendo el segundo carácter solo cuando corresponde.

**Separar palabras reservadas de identificadores.** Palabras como `while` y nombres de variables como `contador` se leen igual (letras seguidas de letras o dígitos). La solución fue leer primero la palabra completa como si fuera un identificador y, al terminar, compararla contra la lista de palabras reservadas; si no coincide con ninguna, es un identificador.

**Conflictos al integrar (merge de Git).** Al unir el trabajo de los integrantes se produjeron conflictos que dejaron código duplicado en algunos archivos (por ejemplo, dos versiones del bloque de cadenas en el léxico). Se resolvieron limpiando los duplicados y dejando una única versión correcta, y se acordó un método de integración más cuidadoso para el resto del proyecto.

**Ejecutar una versión antigua del programa.** En un momento el analizador rechazaba programas válidos. La causa no estaba en el código, sino en que el ejecutable no se había recompilado tras los últimos cambios. Se solucionó forzando una compilación limpia con `make clean` seguido de `make`, y quedó como recordatorio de recompilar después de cada cambio.

**Reporte de errores con número de línea.** Para poder indicar dónde falla un programa, cada token guarda la línea en la que aparece (`line`). Cuando el parser encuentra un error, usa ese dato para informar la línea exacta, lo que hace mucho más útil el mensaje de error.

---

## Equipo

- **Misael**
- **Mariana**
- **Edwin**

---

## Organización del trabajo

La división de tareas, el avance y los responsables se gestionan en el tablero de **GitHub Projects** del repositorio.
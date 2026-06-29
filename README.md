# MiniLang: Analizador léxico y sintáctico

Proyecto integrador de Teoría de Compiladores. El objetivo es implementar, en lenguaje **C**, un analizador **léxico** y **sintáctico** para un pequeño lenguaje de programación llamado **MiniLang**.

El programa recibe un archivo de texto con un programa escrito en MiniLang y determina si ese programa es **correcto o no** según las reglas del lenguaje.

```
> minilang prog1.mini
Programa correcto
```

---

## ¿De qué trata el proyecto?

Un compilador, antes de traducir o ejecutar un programa, primero tiene que entenderlo. Eso se hace en dos fases, y este proyecto implementa esas dos:

- **Análisis léxico:** lee el texto carácter por carácter y lo agrupa en *tokens* (las "palabras" del lenguaje: identificadores, números, operadores, palabras reservadas, etc.).
- **Análisis sintáctico:** toma esos tokens y revisa que estén en un **orden válido** según la gramática del lenguaje. Si el orden es correcto, el programa es válido; si no, se reporta un error de sintaxis.

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

```
<programa>         ::= begin <lista_sentencias> end

<lista_sentencias> ::= <sentencia> <lista_sentencias>
                     | ε

<sentencia>        ::= <asignacion>
                     | <if>
                     | <while>
                     | <print>

<asignacion>       ::= id = <expresion> ;

<if>               ::= if ( <expresion> ) { <lista_sentencias> }
                     | if ( <expresion> ) { <lista_sentencias> }
                       else { <lista_sentencias> }

<while>            ::= while ( <expresion> ) { <lista_sentencias> }

<print>            ::= print ( <expresion> ) ;

<expresion>        ::= <termino>
                     | <expresion> + <termino>
                     | <expresion> - <termino>

<termino>          ::= <factor>
                     | <termino> * <factor>
                     | <termino> / <factor>

<factor>           ::= id
                     | numero
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

El enunciado original tiene algunos puntos ambiguos. Para que el equipo trabaje sobre las mismas reglas, el proyecto adopta estas convenciones:

1. El `;` es un delimitador obligatorio al final de cada asignación y de cada `print`.
2. Los operadores relacionales (`<`, `>`, `==`) se permiten dentro de las expresiones que se usan como condición en `if` y `while`.
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
├── pruebas/        Programas de ejemplo (.mini) válidos e inválidos
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
./minilang pruebas/prog1.mini
```

> En Windows el ejecutable se llama `minilang.exe`.

La salida indica si el programa es sintácticamente correcto o reporta el error encontrado.

---

## Equipo

- **Misael**
- **Mariana**
- **Edwin**

---

## Organización del trabajo

La división de tareas, el avance y los responsables se gestionan en el tablero de **GitHub Projects** del repositorio.
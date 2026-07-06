#ifndef PARSER_H
#define PARSER_H


/*

Paso 1: GLC

E -> E + E
E -> E * E
E -> (E)
E -> num
E -> id
E -> cadena

Paso 2: Eliminar ambiguedad

E -> E + T
E -> E - T
E -> T

T -> T * F
T -> T / F
T -> F

F -> (E)
F -> num
F -> id
F -> cadena

Paso 3: Eliminar recursividad izquierda


E  -> T E'
E' -> + T E' | - T E' | e

T  -> F T'
T' -> * F T' | / F T' | e

F  -> id | (E) | num | cadena

Condicion -> E Relop E

Relop -> < | > | == 


*/



void parse();



#endif

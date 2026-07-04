#ifndef PARSER_H
#define PARSER_H
#include "lexico.h"

extern Token current;

void programa();
void lista_sentencias();
void sentencia();

void match(TokenType expexted);
void error();
void asignacion();
void sentencia_if();
void sentencia_while();
void sentencia_print();
#endif

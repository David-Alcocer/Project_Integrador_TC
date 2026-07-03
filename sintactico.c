#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"
#include "sintactico.h"

Token current;

void error()
{
	printf("Error sintactico\n");
	exit(1);
}

void match(TokenType expected)
{
	if(current.type == expected)
		current = getNextToken();
	else
		error();
}

void programa()
{
	match(TOKEN_BEGIN);
	lista_sentencias();
	match(TOKEN_END);
}

void lista_sentencias()
{
	while(current.type == TOKEN_ID||current.type == TOKEN_IF || 
		current.type == TOKEN_WHILE|| current.type == TOKEN_PRINT)
	{
		sentencia();
	}
}

void sentencia()
{
	switch(current.type){
		case TOKEN_ID:
		asignacion();
		break;

		case TOKEN_IF:
		sentencia_if();
		break;

		case TOKEN_WHILE:
		sentencia_while();
		break;

		case TOKEN_PRINT:
	    sentencia_print();
		break;

		default:
		error();
	}
}
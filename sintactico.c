#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"
#include "sintactico.h"
#include "generador.h"

Token current;

void error()
{
	printf("Error sintactico en la linea %d\n", current.line);
	exit(1);
}

void match(TokenType expected)
{
	if (current.type == expected)
		current = getNextToken();
	else
		error();
}

void E();
void EPrime();
void T();
void TPrime();
void F();
void Condicion();
void Relop();
void programa();
void lista_sentencias();
void sentencia();
void asignacion();
void print_stmt();
void if_stmt();
void while_stmt();

void E()
{
	T();
	EPrime();
}

void EPrime()
{
	if (current.type == TOKEN_PLUS)
	{
		fprintf(salida, " + ");
		match(TOKEN_PLUS);
		T();
		EPrime();
	}
	else if (current.type == TOKEN_MINUS)
	{
		fprintf(salida, " - ");
		match(TOKEN_MINUS);
		T();
		EPrime();
	}
}

void T()
{
	F();
	TPrime();
}

void TPrime()
{
	if (current.type == TOKEN_MULT)
	{
		fprintf(salida, " * ");
		match(TOKEN_MULT);
		F();
		TPrime();
	}
	else if (current.type == TOKEN_DIV)
	{
		fprintf(salida, " / ");
		match(TOKEN_DIV);
		F();
		TPrime();
	}
}

void F()
{
	if (current.type == TOKEN_ID)
	{
		fprintf(salida, "%s", current.lexeme);
		match(TOKEN_ID);
	}
	else if (current.type == TOKEN_NUMBER)
	{
        fprintf(salida, "%s", current.lexeme);
		match(TOKEN_NUMBER);
	}

	else if (current.type == TOKEN_STRING)
	{
		fprintf(salida, "\"%s\"", current.lexeme);
		match(TOKEN_STRING);
	}
	else if (current.type == TOKEN_LPAREN)
	{
		fprintf(salida, "(");
		match(TOKEN_LPAREN);
		E();
		fprintf(salida, ")"); 
		match(TOKEN_RPAREN);
	}
	else
	{
		error();
	}
}

void Relop()
{
	if (current.type == TOKEN_LT)
	{
		match(TOKEN_LT);
	}
	else if (current.type == TOKEN_GT)
	{
		match(TOKEN_GT);
	}
	else if (current.type == TOKEN_EQ)
	{
		match(TOKEN_EQ);
	}
	else
	{
		error();
	}
}

void Condicion()
{
	E();
	Relop();
	E();
}

// Regla de la gramática: <programa> -> begin <lista_sentencia> end

void programa()
{
	match(TOKEN_BEGIN);
	lista_sentencias();
	match(TOKEN_END);
}

void lista_sentencias()
{
	while (current.type == TOKEN_ID ||
		   current.type == TOKEN_IF ||
		   current.type == TOKEN_WHILE ||
		   current.type == TOKEN_PRINT)
	{
		sentencia();
	}
}

void sentencia()
{
	if (current.type == TOKEN_ID)
	{
		asignacion();
	}
	else if (current.type == TOKEN_IF)
	{
		if_stmt();
	}
	else if (current.type == TOKEN_WHILE)
	{
		while_stmt();
	}
	else if (current.type == TOKEN_PRINT)
	{
		print_stmt();
	}
	else
	{
		error();
	}
}

void asignacion()
{

	char nombre[64];
	strcpy(nombre, current.lexeme);
	match(TOKEN_ID);
	match(TOKEN_ASSIGN);
	
	fprintf(salida, "%s = ", nombre); 
	E();                             
	match(TOKEN_SEMICOLON);
	fprintf(salida, ";\n");
}

void print_stmt()
{
	match(TOKEN_PRINT);
	match(TOKEN_LPAREN);

	fprintf(salida, "printf(\"%%d\\n\", ");
	E();
	fprintf(salida, ");\n");
	match(TOKEN_RPAREN);
	match(TOKEN_SEMICOLON);
}

void if_stmt()
{
	match(TOKEN_IF);
	match(TOKEN_LPAREN);
	Condicion();
	match(TOKEN_RPAREN);
	match(TOKEN_LBRACE);
	lista_sentencias();
	match(TOKEN_RBRACE);

	if (current.type == TOKEN_ELSE)
	{
		match(TOKEN_ELSE);
		match(TOKEN_LBRACE);
		lista_sentencias();
		match(TOKEN_RBRACE);
	}
}

void while_stmt()
{
	match(TOKEN_WHILE);
	match(TOKEN_LPAREN);
	Condicion();
	match(TOKEN_RPAREN);
	match(TOKEN_LBRACE);
	lista_sentencias();
	match(TOKEN_RBRACE);
}

void parse()
{
	iniciar_generador();

	current = getNextToken();

	programa();

	if (current.type == TOKEN_EOF)
		printf("Programa correcto\n");
	else
		error();

	terminar_generador();

}



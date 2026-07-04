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

void E();
void EPrime();
void T();
void TPrime();
void F();
void Condicion();
void Relop();

void E()
{
	T();
	EPrime();
}

void EPrime()
{
	if(current.type == TOKEN_PLUS)
	{
		match(TOKEN_PLUS);
		T();
		EPrime();
	}
	else if(current.type == TOKEN_MINUS)
	{
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
	if(current.type == TOKEN_MULT)
	{
		match(TOKEN_MULT);
		F();
		TPrime();
	}
	else if(current.type == TOKEN_DIV)
	{
		match(TOKEN_DIV);
		F();
		TPrime();
	}
}

void F()
{
	if(current.type == TOKEN_ID)
	{
		match(TOKEN_ID);
	}
	else if(current.type == TOKEN_NUMBER)
	{
		match(TOKEN_NUMBER);
	}

	else if(current.type == TOKEN_STRING)
	{
		match(TOKEN_STRING);
	}
	else if(current.type == TOKEN_LPAREN)
	{
		match(TOKEN_LPAREN);
		
		E();
		
		match(TOKEN_RPAREN);
	}
	else
	{
		error();
	}
}

void Relop()
{
	if(current.type == TOKEN_LT)
	{
		match(TOKEN_LT);
	}
	else if(current.type == TOKEN_GT)
	{
		match(TOKEN_GT);
	}
	else if(current.type == TOKEN_EQ)
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

void parse()
{
	current = getNextToken();
	
	E();
	
	if(current.type == TOKEN_EOF)
		printf("Cadena valida\n");
	else
		error();
}

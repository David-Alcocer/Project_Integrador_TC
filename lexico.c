#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexico.h"

char *input;
int pos = 0;

Token getNextToken()
{
	while(input[pos] == ' ')
		pos++;
	
	while(input[pos] == '\n')
		pos++;
	
	if(input[pos] == '\0')
		return (Token){TOKEN_EOF, "", 0};
		
	if(isdigit(input[pos]))
		{
			int value = 0;
			
			while(isdigit(input[pos]))
			{
				value = value * 10 + (input[pos] - '0');
				pos++;
			}
			
			return (Token){TOKEN_NUMBER,"", 0};
		}
		if(isalpha(input[pos]) || input[pos] == '_'){
			char lexeme[64];
		
		int i = 0;

		while(isalnum(input[pos])){ //isalnum -> si la función del lenguaje es alfanúmerico 
			lexeme[i] = input[pos];
			i++;
			pos++;
		}
		lexeme[i] = '\0';

		TokenType type = TOKEN_ID;

		if(strcmp(lexeme, "begin") == 0) type = TOKEN_BEGIN;
		else if(strcmp(lexeme, "end") == 0) type = TOKEN_END;
		else if(strcmp(lexeme, "if") == 0) type = TOKEN_IF;
		else if(strcmp(lexeme, "else") == 0) type = TOKEN_ELSE;
		else if(strcmp(lexeme, "while") == 0) type = TOKEN_WHILE;
		else if(strcmp(lexeme, "print") == 0) type = TOKEN_PRINT;

		Token t;
		t.type = type;
		strcpy(t.lexeme, lexeme);
		t.line = 0;
		return t;

	}

		
		char c = input[pos++];
		
		switch(c)
		{
		case '+': return (Token){TOKEN_PLUS, "",0};
		case '-': return (Token){TOKEN_MINUS, "",0};
		case '*': return (Token){TOKEN_MULT, "",0};
		case '/': return (Token){TOKEN_DIV, "",0};
		case '(': return (Token){TOKEN_LPAREN, "",0};
		case ')': return (Token){TOKEN_RPAREN, "",0};
		
		default:
			printf("Caracter invalido: %c ", c);
			return (Token){TOKEN_EOF, "",0};
		}


}


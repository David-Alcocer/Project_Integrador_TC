#include <stdio.h>
#include <ctype.h>
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
		return (Token){TOKEN_EOF, 0};
		
		if(isdigit(input[pos]))
		{
			int value = 0;
			
			while(isdigit(input[pos]))
			{
				value = value * 10 + (input[pos] - '0');
				pos++;
			}
			
			return (Token){TOKEN_NUMBER, value};
		}
		
		char c = input[pos++];
		
		switch(c)
		{
		case '+': return (Token){TOKEN_PLUS,0};
		case '-': return (Token){TOKEN_MINUS,0};
		case '*': return (Token){TOKEN_MULT,0};
		case '/': return (Token){TOKEN_DIV,0};
		case '(': return (Token){TOKEN_LPAREN,0};
		case ')': return (Token){TOKEN_RPAREN,0};
		
		default:
			printf("Caracter invalido: %c ", c);
			return (Token){TOKEN_EOF,0};
		}
}


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexico.h"

char *input;
int pos = 0;
int line = 1;
void setInput(FILE *f)
{
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, 0, SEEK_SET);

	input = (char *) malloc(size + 1);
	fread(input, 1, size, f);
	input[size]= '\0';

	pos = 0;
	line = 1;
}

Token getNextToken()
{
	Token t;
	char lexeme[64];
	int i;

	while(input[pos] == ' '){
		pos++;
	}
	while(input[pos] == '\n'){
		pos++;
		line++;
	}

	if(input[pos] == '\0')
		return (Token){TOKEN_EOF, "", line};
		
	if(isdigit(input[pos]))
		{
			i= 0;
			
			while(isdigit(input[pos]))
			{

				lexeme[i++] = input[pos++];
			}
				lexeme[i]= '\0';

			 t.type = TOKEN_NUMBER;
			 strcpy(t.lexeme, lexeme);
			 t.line = line;
			 return t;
		}
		
        if(isalpha(input[pos]) || input[pos] == '_')
		{
			i= 0;
			while(isalnum(input[pos])|| input[pos] == '_'){
				lexeme[i++] = input[pos++];
			}
			lexeme[i]= '\0';
			TokenType type = TOKEN_ID;

			if(strcmp(lexeme, "begin") == 0) type = TOKEN_BEGIN;
				else if(strcmp(lexeme, "end") == 0) type = TOKEN_END;
				else if(strcmp(lexeme, "if") == 0) type = TOKEN_IF;
				else if(strcmp(lexeme, "else") == 0) type = TOKEN_ELSE;
				else if(strcmp(lexeme, "while") == 0) type = TOKEN_WHILE;
				else if(strcmp(lexeme, "print") == 0) type = TOKEN_PRINT;
            t.type = type;
			strcpy(t.lexeme, lexeme);
			t.line = line;
				return t;
		}

		char c = input[pos++];
		
		switch(c)
		{
		case '+': return (Token){TOKEN_PLUS, "",line};
		case '-': return (Token){TOKEN_MINUS, "",line};
		case '*': return (Token){TOKEN_MULT, "",line};
		case '/': return (Token){TOKEN_DIV, "",line};
		case '(': return (Token){TOKEN_LPAREN, "",line};
		case ')': return (Token){TOKEN_RPAREN, "",line};
		case '{': return (Token){TOKEN_LBRACE, "", line};
		case '}': return (Token){TOKEN_RBRACE, "", line};
		case ';': return (Token){TOKEN_SEMICOLON, "", line};
		case '<': return (Token){TOKEN_LT, "", line};
		case '>': return (Token){TOKEN_GT, "", line};

		case '=':
		if(input[pos] == '='){
			pos++;
			return (Token){TOKEN_EQ, "", line};
		}else{
			return (Token){TOKEN_ASSIGN, "", line};
		}

		case '"':
		{
			char lexeme[64];
			int i = 0;

			while(input[pos] != '"' && input[pos] != '\0'){
				if(i < 63){
					lexeme[i] = input[pos];
				}
				pos++;
				i++;
			}

			lexeme[i] = '\0';

			if (input[pos]== '"') {
				pos++;
            t.type = TOKEN_STRING;
            strcpy(t.lexeme, lexeme);
            t.line = line;
            return t;
			}else {
				printf("Error lexico encontado en la linea %d", line);
				return (Token){TOKEN_EOF, "", line};
			}
		}
		
		default:
			printf("Caracter invalido: %c ", c);
			return (Token){TOKEN_EOF, "",line};
		}
}


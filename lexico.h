#ifndef LEXER_H
#define LEXER_H

typedef enum {
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULT,
	TOKEN_DIV,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF
} TokenType;

typedef struct {
	TokenType type;
	int value;
} Token;




extern char *input;
extern int pos;

Token getNextToken();

#endif

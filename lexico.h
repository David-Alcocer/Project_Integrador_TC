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
	TOKEN_EOF,
	TOKEN_BEGIN,
	TOKEN_END,
	TOKEN_IF,
	TOKEN_ELSE,
	TOKEN_WHILE,
	TOKEN_PRINT,
	TOKEN_ASSIGN,
	TOKEN_LT,
	TOKEN_GT,
	TOKEN_EQ,
	TOKEN_LBRACE,
	TOKEN_RBRACE,
	TOKEN_SEMICOLON,
	TOKEN_ID,
	TOKEN_STRING 



} TokenType;

typedef struct {
	TokenType type;
	char lexeme[64];
	int line;
} Token;




extern char *input;
extern int pos;

Token getNextToken();

#endif

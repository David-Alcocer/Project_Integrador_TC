#include <stdio.h>
#include "lexico.h"
#include "sintactico.h"

int main()
{
	char expr[256];
	
	printf("Ingrese expresion: ");
	fgets(expr, sizeof(expr), stdin);
	
	input = expr;
	pos = 0;
	
	parse();
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"
#include "sintactico.h"

extern Token current;

int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		printf("Uso: ./minilang archivo.mini\n");
		return 1;
	}

	FILE *archivo = fopen(argv[1], "r");

	if (archivo == NULL)
	{
		return 1;
	}
    
	setInput(archivo);
	current = getNextToken();

    programa();
	 if (current.type == TOKEN_EOF){
	 printf("Programa correcto\n");
	 }
	 else {
		printf("Error en el archivo\n");
	 }
	 fclose(archivo);
	 	return 0;
}

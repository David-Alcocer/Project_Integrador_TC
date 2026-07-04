#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"
#include "sintactico.h"

extern Token current;
void parse();

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Uso: ./minilang archivo.mini\n");
        return 1;
    }

    FILE *archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    
    fseek(archivo, 0, SEEK_END);
    long tam = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    char *buffer = malloc(tam + 1);
    fread(buffer, 1, tam, archivo);
    buffer[tam] = '\0';
    fclose(archivo);
    
    input = buffer;
    pos = 0;

	parse();


    free(buffer);
    return 0;
}
#include <stdio.h>
#include "generador.h"
#include <stdlib.h>

FILE *salida;

void iniciar_generador()
{
    salida = fopen("salida.c", "w");
    fprintf(salida, "#include <stdio.h>\n\n");
    fprintf(salida, "int main() {\n");
}

void terminar_generador()
{
    fprintf(salida, "return 0;\n");
    fprintf(salida, "}\n");
    fclose(salida);
}
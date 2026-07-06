CC = gcc #compiler
CFLAGS = -Wall -g

minilang: main.c lexico.c sintactico.c lexico.h sintactico.h generador.h #ejecuto estos archivos para generar el ejecutable
	$(CC) $(CFLAGS) -o minilang main.c lexico.c sintactico.c generador.c

clean:
	rm -f minilang 
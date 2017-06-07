#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>
#include "grafo.h"
#include "sudoku.h"

typedef struct{
	int id;
	int cor;
	int linha;
	int coluna;
	Grafo *grafo;
}gui_colore_dados;

typedef struct{
	GtkWidget *grid;
	GtkWidget **horizontal;
	GtkWidget ***button;
}gui_grid;

typedef struct{
	Grafo *grafo;
	int altura;
	int largura;

	GtkWidget *box;
	GtkWidget **linha;
	gui_grid ***grid;
	GtkWidget **separator;
}gui_sudoku;

gui_grid* gui_cria_grid(int altura, int largura, int *cor, int *ids);

gui_sudoku* gui_cria_sudoku(Grafo *grafo, int altura, int largura);

int gui(int argc, char *argv[]);

#endif
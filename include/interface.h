#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>
#include "grafo.h"
#include "sudoku.h"

typedef struct{
	int id;
	int linha;
	int coluna;
	int cor;
	Sudoku *sudoku;
}gui_colore_vertice_dados;

typedef struct{
	GtkWidget *grid;
	GtkWidget **horizontal;
	GtkWidget ***button;
}gui_grid;

typedef struct{
	Sudoku *sudoku;

	GtkWidget *box;
	GtkWidget **linha;
	gui_grid ***grid;
	GtkWidget **separator;
}gui_sudoku;

gui_grid* gui_cria_grid(int altura, int largura, int *cor, int *ids);

gui_sudoku* gui_cria_sudoku(Sudoku *sudoku);

int gui(int argc, char *argv[]);

#endif
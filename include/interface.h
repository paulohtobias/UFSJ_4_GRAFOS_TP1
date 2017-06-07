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
	Sudoku *sudoku;

	GtkWidget *box;
	GtkWidget ***button;
}gui_sudoku;

GtkWidget *gui_cria_grid(gui_sudoku *sudoku_gui, int *ids, int *cor);

gui_sudoku* gui_cria_sudoku(Sudoku *sudoku);

int gui(int argc, char *argv[]);

#endif
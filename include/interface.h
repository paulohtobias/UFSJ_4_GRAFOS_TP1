#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>
#include "grafo.h"
#include "sudoku.h"

///Principal
typedef struct{
	Sudoku *sudoku;

	GtkWidget *box;
	GtkWidget ***button;
}gui_sudoku;
//Cria um grid.
GtkWidget *gui_cria_grid(gui_sudoku *sudoku_gui, int *ids, int *cor);
//Cria o Sudoku.
gui_sudoku* gui_cria_sudoku(Sudoku *sudoku);

///Coloração
typedef struct{
	int id;
	int linha;
	int coluna;
	int cor;
	gui_sudoku *gsudoku;
}gui_colore_vertice_dados;
//Inicializa os dados que serão passados para a função gui_colore_vertice
gui_colore_vertice_dados *gui_colore_dados_novo(gui_sudoku *gsudoku, int id, int linha, int coluna, int cor);
//Muda o label do botão se foi possível mudar sua cor.
bool gui_colore_vertice(GtkButton *vertice, gpointer data);

///Extra
//Remove todos os Widgets de um Container
void gui_container_esvazia(GtkWidget *container);

int gui(int argc, char *argv[]);

#endif
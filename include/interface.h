#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>
#include "grafo.h"
#include "sudoku.h"

///Principais
typedef struct{
	GtkWidget *box;
	GtkWidget **button;
}gui_selecionador;

typedef struct{
	Sudoku *sudoku;

	GtkWidget *box;
	GtkWidget ***button;
	gui_selecionador* selecionador;
}gui_sudoku;

///Coloração
typedef struct{
	int id;
	int linha;
	int coluna;
	int cor;
}gui_colore_vertice_dados;

gui_selecionador* gui_cria_selecionador(int altura, int largura);

//Cria um grid.
GtkWidget *gui_cria_grid( int *ids, int *cor);

//Cria o Sudoku.
gui_sudoku* gui_cria_sudoku(Sudoku *sudoku);

//Inicializa os dados que serão passados para a função gui_colore_vertice
gui_colore_vertice_dados *gui_colore_dados_novo( int id, int linha, int coluna, int cor);

//Muda o label do botão se foi possível mudar sua cor.
bool gui_colore_vertice(GtkButton *vertice, gpointer data);

///Extra
//Remove todos os Widgets de um Container
void gui_container_esvazia(GtkWidget *container);

int gui(int argc, char *argv[]);

#endif
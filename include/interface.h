#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>
#include "backtracking.h"
#include "dsatur.h"

///Principais
//Cria um novo Sudoku a partir do botão "Criar"
void gui_novo_Sudoku(GtkButton *button, gpointer data);

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

//Cria o Sudoku.
gui_sudoku* gui_cria_sudoku(Sudoku *sudoku);

//Cria um grid.
GtkWidget *gui_cria_grid( int *ids, int *cor);

///Preenche
typedef struct{
    void (*algoritmo)(Sudoku *sudoku);
}gui_preenche_dados;
//Chama uma função (exata ou heurística) para preencher o Sudoku.
void gui_preenche(GtkButton *button, gpointer data);

///Gera os sinais para os botões do grid.
//Quando clicado, o botão do grid será colorido (se possível) com a
//cor selecionada usando os botões do selecionador.
void gui_sudoku_button_signal_connect();

///Define o valor a ser inserido no sudoku.
void define_valor_a_inserir(GtkButton *button, gpointer data);

///Função chamada quando um botão do Sudoku é clicado.
//Altera o label dos botões do sudoku.
void gui_sudoku_button_clicked(GtkButton *button, gpointer data);

///Pega a linha e a coluna do botão correspondente do grid.
void gui_sudoku_botao_get_lc(GtkButton *button, int *linha, int *coluna);

//Cria uma caixa de botões que seleciona um número para inserir no sudoku.
gui_selecionador* gui_cria_selecionador(int altura, int largura);

///Coloração
typedef struct{
	int id;
	int linha;
	int coluna;
	int cor;
}gui_colore_vertice_dados;

//Inicializa os dados que serão passados para a função gui_colore_vertice
gui_colore_vertice_dados *gui_colore_dados_novo(int id, int linha, int coluna, int cor);
//Muda o label do botão se foi possível mudar sua cor.
bool gui_colore_vertice(GtkButton *vertice, gpointer data);


///Extra
//Remove todos os Widgets de um Container
void gui_container_esvazia(GtkWidget *container);

int gui(int argc, char *argv[]);

#endif

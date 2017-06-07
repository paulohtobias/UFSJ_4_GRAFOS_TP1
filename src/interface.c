#include <gtk/gtk.h>
#include "interface.h"

bool gui_colore_vertice(GtkButton *vertice, gpointer data){
	gui_colore_vertice_dados *dados = (gui_colore_vertice_dados*)data;

	int id = dados->id;
	int dimensao = dados->sudoku->dimensao;
	int altura = dados->sudoku->altura;
	int largura = dados->sudoku->largura;

	if(dados->id < 0){
		id = sudoku_lc_para_vertice_id(dimensao, dados->linha, dados->coluna);
	}

	if(grafo_colore_vertice(dados->sudoku->grafo, id, dados->cor) == true){
		int *sudoku_lc = vertice_id_para_sudoku_lc(dimensao, id);
		int sudoku_linha = sudoku_lc[0];
		int sudoku_coluna = sudoku_lc[1];
		int *quadrante_dados = sudoku_lc_para_quadrante_lc(sudoku_linha, sudoku_coluna, largura, altura);
	}
	
	return  true;
}

gui_grid* gui_cria_grid(int altura, int largura, int *cor, int *ids){
	int i,j;
	gui_grid* grid = malloc(sizeof(gui_grid));

	///Inicialização
	grid->grid = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	grid->horizontal = malloc(altura * sizeof(GtkWidget*));
	grid->button = malloc(altura * sizeof(GtkWidget**));
	for(i=0; i<altura; i++){
		grid->button[i] = malloc(largura * sizeof(GtkWidget*));
		for(j=0; j<largura; j++){
			char label[10];
			sprintf(label, "%d", cor[ ids[i * largura + j] ]);
			if(cor[ ids[i * largura + j] ] == 0){
				strcpy(label, " ");
			}
			grid->button[i][j] = gtk_button_new_with_label(label);

		}
	}

	for(i=0; i < altura; i++){
		grid->horizontal[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
		gtk_box_pack_start(GTK_BOX(grid->grid), grid->horizontal[i], TRUE, TRUE, 0);
		for(j=0; j<largura; j++){
			gtk_box_pack_start(GTK_BOX(grid->horizontal[i]), grid->button[i][j], TRUE, TRUE, 0);
		}
	}

	return grid;
}

gui_sudoku* gui_cria_sudoku(Sudoku *sudoku){
	int i, j, k;

	//Atributos do Sudoku.
	int dimensao, altura, largura;
	int linhas, colunas, qnt_separator;

	dimensao = sudoku->dimensao;
	altura = sudoku->altura;
	largura = sudoku->largura;
	linhas = dimensao/altura;
	colunas= dimensao/largura;
	
	///Inicialização
	gui_sudoku *sudoku_gui = malloc(sizeof(gui_sudoku));

	sudoku_gui->sudoku = sudoku;

	sudoku_gui->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	qnt_separator = linhas * colunas - 1;
	sudoku_gui->linha = malloc(linhas*sizeof(GtkWidget*));
	sudoku_gui->grid = malloc(linhas * sizeof(gui_grid**));
	sudoku_gui->separator = malloc(qnt_separator*sizeof(GtkWidget*));

	k=0;
	for(i = 0; i < linhas; i++){
		sudoku_gui->linha[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
		gtk_box_pack_start(GTK_BOX(sudoku_gui->box), sudoku_gui->linha[i], TRUE, TRUE, 0);

		sudoku_gui->grid[i] = malloc(colunas * sizeof(gui_grid*));

		if(i + 1 < linhas){
			sudoku_gui->separator[k] = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
			gtk_box_pack_start(GTK_BOX(sudoku_gui->box), sudoku_gui->separator[k++], FALSE, TRUE, 5);
		}
		for(j=0; j < colunas; j++){

			sudoku_gui->grid[i][j] = gui_cria_grid(altura, largura, sudoku->grafo->cor, sudoku_ids_quadrante(altura, largura, j, i));
			gtk_box_pack_start(GTK_BOX(sudoku_gui->linha[i]), sudoku_gui->grid[i][j]->grid, TRUE, TRUE, 0);

			if(j + 1 < colunas){
				sudoku_gui->separator[k] = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
				gtk_box_pack_start(GTK_BOX(sudoku_gui->linha[i]), sudoku_gui->separator[k++], FALSE, TRUE, 5);
			}
		}

	}
	
	return sudoku_gui;
}

int gui(int argc, char *argv[]){
	GtkBuilder *gtkBuilder;
	GtkWidget *janela;

	Sudoku *sudoku = novo_Sudoku("000000010400000000020000000000050407008000300001090000300400200050100000000806000",3,3);

	gtk_init(&argc, &argv);
	
	gtkBuilder = gtk_builder_new_from_file("interface.glade");

	janela = GTK_WIDGET(gtk_builder_get_object(gtkBuilder,"janela_principal"));

	g_signal_connect(G_OBJECT(janela), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *lado_esquerdo = GTK_WIDGET(gtk_builder_get_object(gtkBuilder,"lado_esquerdo"));
	
	gui_sudoku *sudoku_gui = gui_cria_sudoku(sudoku);

	gtk_box_pack_start(GTK_BOX(lado_esquerdo), sudoku_gui->box, TRUE, TRUE, 0);

	gtk_widget_show_all(janela);
	gtk_main();
	
	return 0;
}
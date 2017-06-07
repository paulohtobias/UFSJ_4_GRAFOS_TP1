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

GtkWidget *gui_cria_grid(gui_sudoku *sudoku_gui, int *ids, int *cor){
	int i,j;

	int dimensao = sudoku_gui->sudoku->dimensao;
	int altura = sudoku_gui->sudoku->altura;
	int largura = sudoku_gui->sudoku->largura;

	//Inicialização
	GtkWidget *vertical = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_set_homogeneous(GTK_BOX(vertical), TRUE);

	GtkWidget *horizontal[altura];
	for(i=0; i<altura; i++){
		horizontal[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	}

	for(i=0; i<altura; i++){
		gtk_box_pack_start(GTK_BOX(vertical), horizontal[i], TRUE, TRUE, 0);
		gtk_box_set_homogeneous(GTK_BOX(horizontal[i]), TRUE);
		for(j=0; j<largura; j++){
			int k = i*largura + j;
			int *lc = vertice_id_para_sudoku_lc(dimensao, ids[k]);
			int linha = lc[0];
			int coluna = lc[1];

			char label[10];
			sprintf(label, "%d", cor[ids[k]]);
			if(cor[ids[k]] == 0){
				strcpy(label, " ");
			}
			sudoku_gui->button[linha][coluna] = gtk_button_new_with_label(label);
			gtk_box_pack_start(GTK_BOX(horizontal[i]), sudoku_gui->button[linha][coluna], TRUE, TRUE, 0);
		}
	}
	return vertical;
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

	sudoku_gui->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

	qnt_separator = linhas * colunas - 1;
	GtkWidget *linha[linhas];
	GtkWidget *grid[linhas][colunas];
	GtkWidget *separator[qnt_separator];
	
	sudoku_gui->button = malloc(dimensao * sizeof(GtkWidget**));
	for(i=0; i<dimensao; i++){
		sudoku_gui->button[i] = malloc(dimensao * sizeof(GtkWidget*));
	}

	k=0;
	for(i = 0; i < linhas; i++){
		linha[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
		gtk_box_set_homogeneous(GTK_BOX(linha[i]), TRUE);
		gtk_box_pack_start(GTK_BOX(sudoku_gui->box), linha[i], TRUE, TRUE, 0);

		if(i + 1 < linhas){
			separator[k] = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
			//gtk_box_pack_start(GTK_BOX(sudoku_gui->box), separator[k++], FALSE, TRUE, 5);
		}
		for(j=0; j < colunas; j++){

			grid[i][j] = gui_cria_grid(sudoku_gui, sudoku_ids_quadrante(altura, largura, j, i), sudoku->grafo->cor);
			gtk_box_pack_start(GTK_BOX(linha[i]), grid[i][j], TRUE, TRUE, 0);

			if(j + 1 < colunas){
				separator[k] = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
				//gtk_box_pack_start(GTK_BOX(linha[i]), separator[k++], FALSE, TRUE, 5);
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
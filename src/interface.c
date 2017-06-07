#include <gtk/gtk.h>
#include "interface.h"

bool gui_colore_vertice(GtkButton *vertice, gpointer dados){
	int cor = *((int*)dados);
	printf("cor: %d\n",cor);
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
			int *cc = malloc(sizeof(int));
			*cc = i*largura+j;
			grid->button[i][j] = gtk_button_new_with_label(label);
			g_signal_connect(GTK_BUTTON(grid->button[i][j]),"clicked",G_CALLBACK(gui_colore_vertice),(void*)cc);

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

gui_sudoku* gui_cria_sudoku(Grafo *grafo, int altura, int largura){
	int i, j, k;
	int linhas, colunas, qnt_separator, dimensao;
	
	///inicialização
	gui_sudoku *sudoku = malloc(sizeof(gui_sudoku));
	sudoku->altura = altura;
	sudoku->largura = largura;
	sudoku->grafo = grafo;

	sudoku->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	dimensao = altura * largura;
	linhas = dimensao/altura;
	colunas= dimensao/largura;
	qnt_separator = linhas * colunas - 1;
	sudoku->linha = malloc(linhas*sizeof(GtkWidget*));
	sudoku->grid = malloc(linhas * sizeof(gui_grid**));
	sudoku->separator = malloc(qnt_separator*sizeof(GtkWidget*));

	k=0;
	for(i = 0; i < linhas; i++){
		sudoku->linha[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
		gtk_box_pack_start(GTK_BOX(sudoku->box), sudoku->linha[i], TRUE, TRUE, 0);

		sudoku->grid[i] = malloc(colunas * sizeof(gui_grid*));

		if(i + 1 < linhas){
			sudoku->separator[k] = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
			gtk_box_pack_start(GTK_BOX(sudoku->box), sudoku->separator[k++], FALSE, TRUE, 5);
		}
		for(j=0; j < colunas; j++){

			sudoku->grid[i][j] = gui_cria_grid(altura, largura, grafo->cor, sudoku_ids_quadrante(altura, largura, j, i));
			gtk_box_pack_start(GTK_BOX(sudoku->linha[i]), sudoku->grid[i][j]->grid, TRUE, TRUE, 0);

			if(j + 1 < colunas){
				sudoku->separator[k] = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
				gtk_box_pack_start(GTK_BOX(sudoku->linha[i]), sudoku->separator[k++], FALSE, TRUE, 5);
			}
		}

	}
	
	return sudoku;
}

int gui(int argc, char *argv[]){
	GtkBuilder *gtkBuilder;
	GtkWidget *janela;
	Grafo *grafo = novo_Sudoku("000000010400000000020000000000050407008000300001090000300400200050100000000806000",3,3);

	gtk_init(&argc, &argv);
	
	gtkBuilder = gtk_builder_new_from_file("interface.glade");

	janela = GTK_WIDGET(gtk_builder_get_object(gtkBuilder,"janela_principal"));

	g_signal_connect(G_OBJECT(janela), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *lado_esquerdo = GTK_WIDGET(gtk_builder_get_object(gtkBuilder,"lado_esquerdo"));
	
	gui_sudoku *sudoku = gui_cria_sudoku(grafo, 3, 3);

	gtk_box_pack_start(GTK_BOX(lado_esquerdo), sudoku->box, TRUE, TRUE, 0);

	gtk_widget_show_all(janela);
	gtk_main();
	
	return 0;
}
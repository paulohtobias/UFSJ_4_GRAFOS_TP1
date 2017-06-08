#include <gtk/gtk.h>
#include "interface.h"

gui_sudoku *gsudoku;

///Principal
//Cria um grid.
GtkWidget *gui_cria_grid(int *ids, int *cor){
	int i,j;

	int dimensao = gsudoku->sudoku->dimensao;
	int altura = gsudoku->sudoku->altura;
	int largura = gsudoku->sudoku->largura;

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
			gsudoku->button[linha][coluna] = gtk_button_new_with_label(label);
			gtk_box_pack_start(GTK_BOX(horizontal[i]), gsudoku->button[linha][coluna], TRUE, TRUE, 0);
		}
	}
	return vertical;
}
//Cria o Sudoku.
gui_sudoku* gui_cria_sudoku(Sudoku *sudoku){
	int i, j;

	//Atributos do Sudoku.
	int dimensao, altura, largura;
	int linhas, colunas;

	dimensao = sudoku->dimensao;
	altura = sudoku->altura;
	largura = sudoku->largura;
	linhas = dimensao/altura;
	colunas= dimensao/largura;
	
	///Inicialização
	gsudoku = malloc(sizeof(gui_sudoku));

	gsudoku->sudoku = sudoku;

	gsudoku->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

	GtkWidget *linha[linhas];
	GtkWidget *grid[linhas][colunas];
	
	gsudoku->button = malloc(dimensao * sizeof(GtkWidget**));
	for(i=0; i<dimensao; i++){
		gsudoku->button[i] = malloc(dimensao * sizeof(GtkWidget*));
	}

	for(i = 0; i < linhas; i++){
		linha[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
		gtk_box_set_homogeneous(GTK_BOX(linha[i]), TRUE);
		gtk_box_pack_start(GTK_BOX(gsudoku->box), linha[i], TRUE, TRUE, 0);

		for(j=0; j < colunas; j++){
			grid[i][j] = gui_cria_grid( sudoku_ids_quadrante(altura, largura, j, i), sudoku->grafo->cor);
			gtk_box_pack_start(GTK_BOX(linha[i]), grid[i][j], TRUE, TRUE, 0);
		}
	}
	
	return gsudoku;
}

///Coloração
//Inicializa os dados que serão passados para a função gui_colore_vertice
gui_colore_vertice_dados *gui_colore_dados_novo(int id, int linha, int coluna, int cor){
	gui_colore_vertice_dados *dados = malloc(sizeof(gui_colore_vertice_dados));

	dados->id = id;
	dados->linha = linha;
	dados->coluna = coluna;
	dados->cor = cor;

	return dados;
}
//Muda o label do botão se foi possível mudar sua cor.
bool gui_colore_vertice(GtkButton *vertice, gpointer data){
	gui_colore_vertice_dados *dados = (gui_colore_vertice_dados*)data;

	int id = dados->id;
	int dimensao = gsudoku->sudoku->dimensao;

	if(dados->id < 0){
		//Se o id não estiver definido, então foi usado a posição linha x coluna do Sudoku.
		id = sudoku_lc_para_vertice_id(dimensao, dados->linha, dados->coluna);
	}

	if(grafo_colore_vertice(gsudoku->sudoku->grafo, id, dados->cor) == true){
		int *sudoku_lc = vertice_id_para_sudoku_lc(dimensao, id);
		int linha = sudoku_lc[0];
		int coluna = sudoku_lc[1];
		
		char label[10];
		sprintf(label, "%d", dados->cor);
		gtk_button_set_label(GTK_BUTTON(gsudoku->button[linha][coluna]), label);

		return true;
	}

	return  false;
}

///Extra
//Remove todos os Widgets de um Container
void gui_container_esvazia(GtkWidget *container){
	GList *child = gtk_container_get_children(GTK_CONTAINER(container));
	while(child != NULL){
		gtk_container_remove(GTK_CONTAINER(container), GTK_WIDGET(child->data));
		child = child->next;
	}
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
	
	gsudoku = gui_cria_sudoku(sudoku);

	gtk_box_pack_start(GTK_BOX(lado_esquerdo), gsudoku->box, TRUE, TRUE, 0);

	gtk_widget_show_all(janela);

	//Testando a função de colorir
	printf("colore: %d\n",
		gui_colore_vertice(
			NULL,
			gui_colore_dados_novo(-1, 7, 5, 9)
		)
	);

	printf("colore: %d\n",
		gui_colore_vertice(
			NULL,
			gui_colore_dados_novo(-1, 7, 2, 9)
		)
	);

	gtk_main();
	
	return 0;
}
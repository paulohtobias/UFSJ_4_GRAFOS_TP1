#include <gtk/gtk.h>
#include "interface.h"

int valores_vazios;
int valor_a_inserir;
gui_sudoku *gsudoku;

///Pega a linha e a coluna do botão correspondente
void get_lc_botao(GtkButton *button, int *linha, int *coluna){
	int i, j;
	*linha = -1;
	*coluna= -1;
	int dimensao = gsudoku->sudoku->altura*gsudoku->sudoku->largura;
	for(i = 0; i < dimensao; i++){
		for(j = 0; j < dimensao; j++){
			if(button == GTK_BUTTON(gsudoku->button[i][j])){
				*linha = i;
				*coluna= j;
				return;
			}
		}
	}
}

///Altera os labels dos botões acessíveis
void gui_button_signal(GtkButton *button, gpointer data){
	int linha, coluna;
	char label[10];
	sprintf(label,"%d",valor_a_inserir);
	///Se o valor já foi inserido nessa posição, ignore
	if(atoi(gtk_button_get_label(GTK_BUTTON(button)))==valor_a_inserir){
		return;
	}

	///Se o valor a ser inserido é maior que zero, indica preencher uma posição
	if(valor_a_inserir > 0){
		get_lc_botao(button,&linha,&coluna); //Pega a coordenada do botão
		///Se o valor a ser inserido é válido, remove uma posição vazia
		if(gui_colore_vertice(button,gui_colore_dados_novo(-1,linha,coluna,valor_a_inserir))){
			valores_vazios--; //Reduz posições vazias
			///Se o contador chegar a zero ou menos, indica que o sudoku está completo
			if(valores_vazios <= 0){ //Trava todos os botões
				int i,j;
				int dimencao = gsudoku->sudoku->altura*gsudoku->sudoku->largura;
				for(i = 0; i < dimencao; i++){
					for(j = 0; j < dimencao; j++){
						gtk_widget_set_sensitive(GTK_WIDGET(gsudoku->button[i][j]),FALSE);
					}
				}
			}
		}
	///Se o valor não for maior que 0, então irá remover posições preenchidas
	}else{
		valores_vazios++; //Aumenta posições vazias
		get_lc_botao(button,&linha,&coluna);
		gui_colore_vertice(button,gui_colore_dados_novo(-1,linha,coluna,0));
		gtk_button_set_label(GTK_BUTTON(button)," ");
	}
}

///Gera os sinais para os botões
void gui_define_sinal_para_button(){
	int i, j;
	int dimensao = gsudoku->sudoku->largura*gsudoku->sudoku->altura;

	valores_vazios = 0; //Contador de posições vazias
	for(i = 0; i < dimensao; i++){
		for(j = 0; j < dimensao; j++){
			///Se a label do botão é vazia indica uma posição válida a ser inserida
			if(strcmp(gtk_button_get_label(GTK_BUTTON(gsudoku->button[i][j]))," ")==0){ //É clicavel
				valores_vazios++;
				g_signal_connect(G_OBJECT(gsudoku->button[i][j]),"clicked",G_CALLBACK(gui_button_signal),NULL);
			}else{ //Não é clicavel
				gtk_widget_set_sensitive(GTK_WIDGET(gsudoku->button[i][j]),FALSE);
			}
		}
	}
}

///Define o valor a ser inserido no sudoku
void define_valor_a_inserir(GtkButton *button, gpointer data){
	int valor = atoi((char*)data);
	printf("insere: %d\n", valor);
	valor_a_inserir = valor;
}

///Cria selecionador dinâmico
gui_selecionador* gui_cria_selecionador(int altura, int largura){
	int i;
	char label[10];
	int dimensao = altura*largura;
	gui_selecionador* selecionador = malloc(sizeof(gui_selecionador));

	selecionador->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
	selecionador->button = calloc(sizeof(GtkWidget*),dimensao+1);
	for(i = 0; i < dimensao; i++){
		sprintf(label,"%d",i+1);
		selecionador->button[i] = gtk_button_new_with_label(label);
		g_signal_connect(G_OBJECT(selecionador->button[i]),"clicked",G_CALLBACK(define_valor_a_inserir),(void*)gtk_button_get_label(GTK_BUTTON(selecionador->button[i])));
		gtk_box_pack_start(GTK_BOX(selecionador->box),selecionador->button[i],TRUE,TRUE,0);
	}
	selecionador->button[dimensao] = gtk_button_new_with_label("Limpa");
	g_signal_connect(G_OBJECT(selecionador->button[i]),"clicked",G_CALLBACK(define_valor_a_inserir),(void*)"0");
	gtk_box_pack_start(GTK_BOX(selecionador->box),selecionador->button[dimensao],TRUE,TRUE,0);
	return selecionador;
} 

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

	gsudoku->selecionador = gui_cria_selecionador(altura,largura);

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
	gui_define_sinal_para_button();

	gtk_box_pack_start(GTK_BOX(lado_esquerdo), gsudoku->box, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(lado_esquerdo), gsudoku->selecionador->box, FALSE, FALSE, 0);

	gtk_widget_show_all(janela);

	//Testando a função de colorir
	/*printf("colore: %d\n",
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
	);*/

	gtk_main();
	
	return 0;
}
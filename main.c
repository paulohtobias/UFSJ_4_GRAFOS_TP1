#include <sys/time.h>
#include <sys/resource.h>
#include "dsatur.h"
#include "backtracking.h"
#include "interface.h"

int main(int argc , char *argv[]){
	GtkWidget *janela;

    gtk_init(&argc, &argv);

    extern GtkBuilder *builder;
	builder = gtk_builder_new_from_file("interface.glade");

    janela = GTK_WIDGET(gtk_builder_get_object(builder, "janela_principal"));

    g_signal_connect(G_OBJECT(janela), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    ///Conectando o botão de criar sudoku.
    GtkWidget *btn_criar = GTK_WIDGET(gtk_builder_get_object(builder, "btn_novo_sudoku"));
    g_signal_connect(G_OBJECT(btn_criar), "clicked", G_CALLBACK(gui_novo_Sudoku), (void*)janela);

    ///Conectando os botões dos algoritmos.
    //Exato
    GtkWidget *btn_exato = GTK_WIDGET(gtk_builder_get_object(builder, "btn_exato"));
    gui_preenche_dados dado_exato;
    dado_exato.algoritmo = algoritmo_exato;
    dado_exato.window = janela;
    g_signal_connect(G_OBJECT(btn_exato), "clicked", G_CALLBACK(gui_preenche), (void*)&dado_exato);
    //Heurística
    GtkWidget *btn_heuristica = GTK_WIDGET(gtk_builder_get_object(builder, "btn_heuristica"));
    gui_preenche_dados dado_heuristica;
    dado_heuristica.algoritmo = dsatur;
    dado_heuristica.window = janela;
    g_signal_connect(G_OBJECT(btn_heuristica), "clicked", G_CALLBACK(gui_preenche), (void*)&dado_heuristica);

    gtk_widget_show_all(janela);
    gtk_main();

    return 0;
}

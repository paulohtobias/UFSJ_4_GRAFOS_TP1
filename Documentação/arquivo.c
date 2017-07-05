#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho 49151

int main(int argc, char *argv[]){
	char operacao[50];
	int cores;
	int quantidade_passou;
	double tempo_exec;
	double tempo_syst;

	int maior_cor = 0;

	int vetor_maiores_cores[81] = {0};
	
	int maior_qnt_passou = 0;

	double med_qnt_passou = 0;
	double med_maior_cor = 0;

	double tempo_total_h = 0;
	double tempo_total_b = 0;
	double maior_tempo_heur = 0;
	double maior_tempo_back = 0;

	FILE *arquivo = fopen(argv[1], "r"); 
	
	while(!feof(arquivo)){
		fscanf(arquivo,"%s %d %d %lf %lf", 	operacao,&cores,&quantidade_passou,
											&tempo_exec,&tempo_syst);

		if(strcmp(operacao,"backtraking")==0){
			tempo_total_b += tempo_exec;
			if(tempo_exec >maior_tempo_back){
				maior_tempo_back = tempo_exec;
			}
		}else if(strcmp(operacao,"heuristica")==0){
			
			tempo_total_h += tempo_exec;
			med_maior_cor += ((double)cores)/tamanho;
			med_qnt_passou += ((double)quantidade_passou)/tamanho;

			vetor_maiores_cores[cores-1]++;

			if(tempo_exec >maior_tempo_heur){
				maior_tempo_heur = tempo_exec;
			}
			if(maior_cor < cores){
				maior_cor = cores;
			}
		}
	}
	FILE *dados = fopen(argv[2],"w");
	///Backtracking
	fprintf(dados,"backtracking\n");
	fprintf(dados, "maior_tempo;%lf\n", maior_tempo_back);
	fprintf(dados, "tempo_total;%lf\n", tempo_total_b);
	fprintf(dados, "media_tempo;%lf\n\n", tempo_total_b/tamanho);

	///Heuristica
	fprintf(dados,"heuristica\n");
	fprintf(dados, "maior_tempo;%lf\n", maior_tempo_heur);
	fprintf(dados, "tempo_total;%lf\n", tempo_total_h);
	fprintf(dados, "media_tempo;%lf\n\n", tempo_total_h/tamanho);
	fprintf(dados, "maior_cor;%d\n", maior_cor);
	fprintf(dados, "med_qnt_passou;%lf\n", med_qnt_passou);
	fprintf(dados, "med_maior_cor;%lf\n\ndistribuicao;cor;qnt\n", med_maior_cor);

	int i;
	///Começa da cor 9 e vai até a maior+1
	for(i=8; i <= maior_cor; i++){
		fprintf(dados,";%d;%d\n",i+1,vetor_maiores_cores[i]);
	}

	fclose(dados);
	fclose(arquivo);
	return 0;
}
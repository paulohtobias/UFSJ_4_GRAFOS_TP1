#Millas Nasser
#Paulo Tobias
# Força bruta
forcaBruta = Forca-Bruta.c
saida = Backtracking
compiler = gcc -std=c99
header = verificador.h
source = verificador.c
flags = -Wall -O3 -o

deped_verif = verificador.o

all: $(deped_verif)
	$(compiler) $(deped_verif) $(forcaBruta) $(flags) $(saida)

$(deped_verif): $(header) $(source)
	$(compiler) -c $(header) $(source)

clear:
	rm *.o *.gch $(saida)

clean:
	clean
	rm $(saida)
	
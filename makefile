# Limpa os arquivos na pasta output
clean:
	rm -rf /output/*

# Compila o programa
all: clean
	g++ src/Main.cpp src/Auxiliar.cpp src/Sequencial.cpp src/ParaleloThreads.cpp  src/ParaleloProcessos.cpp -o programa
	clear
	./programa
# Executa o programa
run: all
	./programa
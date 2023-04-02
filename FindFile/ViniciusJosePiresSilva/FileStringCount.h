#pragma once

#include <vector>
#include <string>

#define NEW_LINE_ADD 1
#define NO_LINE_ADD 0

using namespace std;

/*
	Classe responsável por representar a contagem de determinada String em um Arquivo (file).
*/
class FileStringCount {
public:
	FileStringCount() = default;
	FileStringCount(string name, size_t stringCount);

	string getName() const;
	size_t getStringCount() const;
	vector<size_t> getLines() const;

	void setName(string name);
	
	/*
		Reseta a contagem. Deleta os valores dos atributos.
	*/
	void resetCount();

	/*
		Adiciona uma nova ocorrência. Incrementa a contagem e adiciona a linha ao vector lines, caso a mesma ainda não tenha sido adicionada.
		Retorna:
			NEW_LINE_ADD caso adicione a nova linha (line) ao vector lines.
			NO_LINE_ADD caso não adicione a nova linha (line) ao vector lines.
	*/
	int addOccurrence(size_t line);

private:
	// Nome do arquivo
	string name;

	// Contagem das ocorrências da String. Seu valor padrão é 0 (zero).
	size_t stringCount = 0;

	// Linhas onde a string aparece.
	vector<size_t> lines;
};


#pragma once

#include <string>
#include <cstdint>
#include <filesystem>

using namespace std;

// O descritor representa um arquivo ou diretório do sistema de arquivos.
class Descriptor {
public:
	Descriptor() = default;
	Descriptor(string name);
	Descriptor(string name, string path, uintmax_t size);

	//virtual ~Descriptor();

	void setName(string name);
	string getName() const;

	void setPath(string path);
	string getPath() const;

	void setSize(uintmax_t size);
	uintmax_t getSize() const;

	void setDate(string date);
	string getDate() const;

	void setHour(string hour);
	string getHour() const;

	bool isFile();
	bool isDirectory();

private:
	// Nome do descritor.
	string name;

	// Localização com o caminho absoluto do descritor.
	string path;

	// Tamanho em bytes do descritor.
	uintmax_t size = 0;

	// Data da última alteração do descritor.
	string date;

	// Hora da última alteração do descritor.
	string hour;
};
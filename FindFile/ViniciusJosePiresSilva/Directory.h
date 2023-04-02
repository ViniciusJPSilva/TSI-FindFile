#pragma once

#include <vector>
#include <optional>
#include <memory>
#include "File.h"

/* Representa um diretório do sistema de arquivos.
 
  Nota: O template de classe optional representa um objeto que pode ter um valor opcional, ou seja, 
         um valor que pode ou não está presente no objeto.
		 Veja detalhes em: https://en.cppreference.com/w/cpp/utility/optional
*/ 
class Directory : public Descriptor {
public:
	Directory() = default;
	Directory(string name);
	Directory(string name, string path, uintmax_t size);

	// Adiciona um arquivo no diretório.
	void add(File file);

	// Adiciona um subdiretório no diretório.
	void add(Directory subdirectory);

	// Pesquisa o nome do arquivo no diretório. Retorna o arquivo.
	optional<File> findFile(string nameFile);

	// Pesquisa o nome do subdiretório no diretório. Retorna o diretório.
	optional<Directory> findDirectory(string nameSubdirectory);

	// Obtém o tamanho total do diretório.
	uintmax_t getTotalSize() const;

	vector<Descriptor> getAllFiles();

	// Obtém o tamanho total do diretório identificado por name.
	static uintmax_t getTotalSize(string name);

	// Obtém o número total de subdiretórios.
	size_t getTotalSubdirectories();

private:
	// Arquivos e subdiretórios do diretório.
	vector<Descriptor> descriptors;
	vector<Directory> subdirectories;
};
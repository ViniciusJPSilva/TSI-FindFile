#pragma once

#include "Descriptor.h"

enum class FileType { LOG, TXT };

// Representa um arquivo do sistema de arquivos.
class File : public Descriptor {
public:
	const string LOG = "log", TXT = "txt";

	File() = default;
	File(string name);
	File(string name, string path, uintmax_t size, FileType fileType);
	
	void setFileType(FileType fileType);
	FileType getFileType() const;

	// Retorna o tipo ou extensão do arquivo.
	string getFileType(FileType fileType) const;

private:
	// Tipo do arquivo.
	FileType fileType;
};
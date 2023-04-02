#include "File.h"
#include <iostream>

File::File(string name) : Descriptor(name) {
	setFileType(FileType::TXT);
}

File::File(string name, string path, uintmax_t size, FileType fileType) : Descriptor(name, path, size) {
	setFileType(fileType);
}

void File::setFileType(FileType fileType) {
	this->fileType = fileType;
}

FileType File::getFileType() const {
	return fileType;
}

string File::getFileType(FileType fileType) const {
	cout << this->LOG << endl;
	return (fileType == FileType::LOG) ? this->LOG : this->TXT;
}

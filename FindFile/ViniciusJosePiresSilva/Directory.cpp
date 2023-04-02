#include "Directory.h"
#include <iostream>


Directory::Directory(string name) : Descriptor(name) {
}

Directory::Directory(string name, string path, uintmax_t size) : Descriptor(name, path, size) {
}

void Directory::add(File file) {
	descriptors.push_back(file);
}

void Directory::add(Directory subdirectory) {
	subdirectories.push_back(subdirectory);
}

optional<File> Directory::findFile(string nameFile) {
	for (size_t i = 0; i < descriptors.size(); i++) 
		if (descriptors[i].isFile() && descriptors[i].getName() == nameFile) 
			return static_cast<File&>(descriptors[i]);

	return {};
}

optional<Directory> Directory::findDirectory(string nameSubdirectory) {
	for (Directory& directory : subdirectories) 
		if (directory.isDirectory() && directory.getName() == nameSubdirectory)
			return directory;

	return {};
}

uintmax_t Directory::getTotalSize() const {
	return this->getSize();
}

vector<Descriptor> Directory::getAllFiles() {
	vector<Descriptor> files, subdirectoryFiles;
	Directory subdirectory;

	for (auto& descriptor : descriptors) 
		if (descriptor.isFile())
			files.push_back(descriptor);
	
	for (Directory& directory : subdirectories) {
			subdirectoryFiles = directory.getAllFiles();
			files.reserve(files.size() + subdirectoryFiles.size());
			files.insert(files.end(), subdirectoryFiles.begin(), subdirectoryFiles.end());
			subdirectoryFiles.clear();
	}

	return files;
}

uintmax_t Directory::getTotalSize(string name) {
	return 0;
}

size_t Directory::getTotalSubdirectories() {
	size_t count = subdirectories.size();
	vector<Descriptor> subdirectoryFiles;
	Directory subdirectory;

	for (Directory& directory : subdirectories)
		count += directory.getTotalSubdirectories();
	
	return count;
}

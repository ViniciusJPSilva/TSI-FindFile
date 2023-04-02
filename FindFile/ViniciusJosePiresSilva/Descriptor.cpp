#include "Descriptor.h"


Descriptor::Descriptor(string name) : name(name) {
	setSize(0);
}

Descriptor::Descriptor(string name, string path, uintmax_t size) : name(name), path(path), size(size) {
}

//Descriptor::~Descriptor() {
//}

void Descriptor::setName(string name) {
	this->name = name;
}

string Descriptor::getName() const {
	return name;
}

void Descriptor::setPath(string path) {
	this->path = path;
}

string Descriptor::getPath() const {
	return path;
}

void Descriptor::setSize(uintmax_t size) {
	this->size = size;
}

uintmax_t Descriptor::getSize() const {
	return size;
}

void Descriptor::setDate(string date) {
	this->date = date;
}

string Descriptor::getDate() const {
	return date;
}

void Descriptor::setHour(string hour) {
	this->hour = hour;
}

string Descriptor::getHour() const {
	return hour;
}

bool Descriptor::isFile() {
	filesystem::path p(this->path);
	return p.has_extension();
}

bool Descriptor::isDirectory() {
	filesystem::path p(this->path);
	return !p.has_extension();
}

#include "FileStringCount.h"

FileStringCount::FileStringCount(string name, size_t stringCount) : name(name), stringCount(stringCount) {
}

string FileStringCount::getName() const {
	return name;
}

size_t FileStringCount::getStringCount() const {
	return stringCount;
}

vector<size_t> FileStringCount::getLines() const {
	return lines;
}

void FileStringCount::setName(string name) {
	this->name = name;
}

void FileStringCount::resetCount() {
	name = "";
	stringCount = 0;
	lines.clear();
}

int FileStringCount::addOccurrence(size_t line) {
	stringCount++;
	bool findLine = false;

	for(const size_t& l : lines)
		if (l == line) {
			findLine = true;
			break;
		}

	if (!findLine) {
		lines.push_back(line);
		return NEW_LINE_ADD;
	}

	return NO_LINE_ADD;
}


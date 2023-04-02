#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <clocale>
#include <sstream>
#include <string>
#include <format>
#include <vector>
#include <ctime>
#include <cstdio>

#include "FileStringCount.h"
#include "ArquivoTexto.h"
#include "FindFile.h"
#include "File.h"


using namespace std;
using namespace filesystem;

int main(int argc, char* argv[]) {
	return findFile(argc, argv);
}

int findFile(int argc, char* argv[]) {
	setlocale(LC_ALL, "pt-BR");

	cout << MSG_WELLCOME;

	// Verifica se há ao menos 1 argumento.
	if (argc >= MINIMUM_NUMBER_ARGUMENTS) {
		optional<FindFile> findFile = FindFile::createFindFile(argc, argv);
		if (findFile.has_value()) 
			findFile.value().findFile();
		else
			cout << format(ERR_CREATE_FIND_FILE, argv[OPTIONAL_PATH_INDEX]);
	}
	else
		cout << ERR_INVALID_NUMBER_ARGUMENTS;

	cout << MSG_KEY_CONTINUE <<endl;
	char c = getchar();

	return EXIT_SUCCESS;
}

vector<wstring> splitStringByLines(wstring text) {
	wistringstream iss(text);
	vector<wstring> lines;

	// Extraindo as subwstrings
	wstring line;
	while (getline(iss, line, L'\n')) {
		lines.push_back(line);
	}

	// Verifica se sobrou alguma linha.
	if (!iss.eof()) {
		getline(iss, line, L'\0');
		lines.push_back(line);
	}

	return lines;
}

FileStringCount findAndCountSearchString(string searchString, vector<wstring> splitedText, string fileName) {
	FileStringCount fileStringCount(fileName, 0);
	size_t start, lineCount = 0;
	wstring searchStr = wstring(searchString.begin(), searchString.end());

	// Busca pela searchString.
	for (wstring& str : splitedText) {
		start = 0;
		lineCount++;

		while ((start = str.find(searchStr, start)) != string::npos) {
			fileStringCount.addOccurrence(lineCount);
			start += searchStr.length();
		}
	}

	return fileStringCount;
}

string toLower(string str) {
	transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return tolower(c); });
	return str;
}

wstring toLower(wstring str) {
	transform(str.begin(), str.end(), str.begin(), [](wchar_t c) { return tolower(c); });
	return str;
}

/*
	Utilizada pela função printInt(), pois a mesma utiliza recursão para formatar os valores.
	Função interna, deve ser utilizada com cautela, caso precise formatar um valor inteiro utilize a função printInt().
*/
void printIntSeparador(unsigned long long numero, const char separador) {
	if (numero < 1000) {
		printf("%llu", numero);
		return;
	}
	printIntSeparador(numero / 1000, separador);
	printf("%c%03llu", separador, numero % 1000);
}

void printInt(unsigned long long numero, const char separador) {
	printIntSeparador(numero, separador);
}

void generateOutputToFileLog(string logFileName, string searchString, vector<FileStringCount> files) {
	ArquivoTexto textFile;
	tm time_info;
	time_t currentTime;
	wstring strFinal;
	size_t count = 0, index;

	if (!textFile.abrir(logFileName, TipoDeAcesso::ESCRITA)) return;
	
	
	time(&currentTime);
	localtime_s(&time_info, &currentTime);
	string buffer = format("Arquivo {} criado em {:02}/{:02}/{:04}", logFileName, time_info.tm_mday, time_info.tm_mon + 1 , 1900 + time_info.tm_year);
	
	strFinal = wstring(buffer.begin(), buffer.end());
	strFinal.append(L" às ");

	buffer = format("{:02}:{:02}.\n\nString pesquisada: \"{}\"\n\n", time_info.tm_hour, time_info.tm_min, searchString);
	strFinal.append(wstring(buffer.begin(), buffer.end()));

	if (files.size() > 0) {
		strFinal.append(L"- Arquivos de texto pesquisados\n\n");
		for (const auto& file : files) {
			buffer = format("{}. {}\nQuantidade = {}\nLinhas = ", ++count, file.getName(), file.getStringCount());
			strFinal.append(wstring(buffer.begin(), buffer.end()));

			vector<size_t> lines = file.getLines();
			for (index = 0; index < lines.size() - 1; index++) {
				buffer = format("{}, ", lines[index]);
				strFinal.append(wstring(buffer.begin(), buffer.end()));
			}

			buffer = format("{}\n\n", lines[index]);
			strFinal.append(wstring(buffer.begin(), buffer.end()));
		}
	
	} else {
		strFinal.append(L"- Zero ocorrências da string pesquisada nos arquivos vasculhados!\n\n");
	}
	
	textFile.escrever(strFinal);

	textFile.fechar();
}


// ===================================================================================================================


FindFile::FindFile(string searchString) : searchString(searchString) {
	searchTime = SearchTime();
}

int FindFile::findFile() {
	return findFile(searchString, directory);
}

int FindFile::findFile(string searchString, string directory) {
	optional<Directory> optionalDirectory = this->directory.findDirectory(directory);

	if (optionalDirectory.has_value())
		return findFile(searchString, optionalDirectory.value());

	return NOT_FOUND;
}

int FindFile::findFile(string searchString, Directory directory) {
	int count = 0;
	ArquivoTexto textFile;

	FileStringCount fileStringCount;
	vector<FileStringCount> filesCount;

	searchString = toLower(searchString);
	
	time_t beginTime, endTime;	

	time(&beginTime);
	for (const auto& file : directory.getAllFiles())
		if (textFile.abrir(file.getPath(), TipoDeAcesso::LEITURA)) {
			printMessagem(file.getName());
			fileStringCount = findAndCountSearchString(searchString, splitStringByLines(toLower(textFile.ler())), file.getName());

			if (fileStringCount.getStringCount() > 0) {
				count++;
				filesCount.push_back(fileStringCount);
			}

			textFile.fechar();
			fileStringCount.resetCount();
		}
	time(&endTime);

	this->searchTime = SearchTime(beginTime, endTime);
	showReport(directory, searchTime);

	if (!createLogFile(LOG_FILE_NAME))
		cout << ERR_CREATE_LOG_FILE;
	else
		generateOutputToFileLog(LOG_FILE_NAME, searchString, filesCount);

	return count;
}

optional<Directory> FindFile::readDirectory(string directory) {
	const string EXTENSION_TXT = ".txt", EXTENSION_LOG = ".log";

	directory_entry directoryEntry(directory);
	directory_iterator directoryIterator(directory);
	uintmax_t directorySize = 0; 

	if (!directoryEntry.exists())
		return {};

	Directory concreteDirectory(directoryEntry.path().filename().string(), directoryEntry.path().string(), directorySize);

	for (auto const& dirEntry : directory_iterator{ path(directory)} ){
		if (dirEntry.is_directory()) {
			optional<Directory> optionalDirectory = readDirectory(dirEntry.path().string());
			if (optionalDirectory.has_value()) {
				concreteDirectory.add(optionalDirectory.value());
				directorySize += optionalDirectory.value().getSize();
			}
		} else if (dirEntry.is_regular_file()) {
			string extension = dirEntry.path().extension().string();			

			if (extension == EXTENSION_TXT || extension == EXTENSION_LOG) {
				directorySize += dirEntry.file_size();
				concreteDirectory.add(File(dirEntry.path().filename().string(), dirEntry.path().string(), dirEntry.file_size(), ((extension == EXTENSION_TXT) ? FileType::TXT : FileType::LOG)));
			}
		}
	}

	concreteDirectory.setSize(directorySize);
	return concreteDirectory;
}

bool FindFile::createLogFile(string nameFile) {
	ArquivoTexto textFile;
	if (textFile.abrir(nameFile, TipoDeAcesso::ESCRITA)) {
		textFile.fechar();
		return true;
	}
	return false;
}

void FindFile::showReport(Directory directory, SearchTime searchTime) {
	time_t initialTime = searchTime.getInitialTime(), 
		finalTime = searchTime.getFinalTime();
	tm time_info;

	cout << "\n\n\n\t--------------------- Resultado da Pesquisa ---------------------\n\n\t - Diretório: " << directory.getPath()
		<< "\n\n\t - Conteúdo do diretório"
		<< format("\n\t\tArquivos de texto pesquisados = {}\n\t\tNúmero total de subdiretórios = {}\n\t\tTamanho total dos arquivos pesquisados = ", directory.getAllFiles().size(), directory.getTotalSubdirectories());

	printIntSeparador(directory.getSize(), '.');
	
	localtime_s(&time_info, &initialTime);
	cout << format(" bytes\n\n\t - Tempo da pesquisa\n\t\tInício : {:02}:{:02}:{:02}", time_info.tm_hour, time_info.tm_min, time_info.tm_sec);

	localtime_s(&time_info, &finalTime);
	cout << format("\n\t\tTérmino: {:02}:{:02}:{:02}", time_info.tm_hour, time_info.tm_min, time_info.tm_sec);

	printf("\n\t\tDuração: %lld segundos\n\n", (long long)finalTime - initialTime);
	cout << "\t-----------------------------------------------------------------\n\n";
}

optional<FindFile> FindFile::createFindFile(int argc, char* argv[]) {
	string directoryPath = (argc > MINIMUM_NUMBER_ARGUMENTS) ? argv[OPTIONAL_PATH_INDEX] : current_path().string();

	directory_entry directoryEntry(directoryPath);
	if (!directoryEntry.exists())
		return {};

	FindFile findFile = FindFile(argv[SEARCH_STRING_INDEX]);
	optional<Directory> directory = findFile.readDirectory(directoryPath);
	if (!directory.has_value()) 
		return {};

	findFile.directory = directory.value();

	return findFile;
}

int FindFile::findFile(string searchString, vector<Descriptor> files) {
	Directory directory;

	for (const auto file : files)
		directory.add(static_cast<const File&>(file));

	return findFile(searchString, directory);
}

void FindFile::printMessagem(string nameFile) {
	cout << format("\n\tPesquisando no arquivo {}...", nameFile);
}


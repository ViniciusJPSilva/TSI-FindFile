#pragma once

#include "Directory.h"
#include "SearchTime.h"

// Número mínimo de argumentos.
#define MINIMUM_NUMBER_ARGUMENTS 2

// Index da string de pesquisa.
#define SEARCH_STRING_INDEX 1

// Index do caminho (path) opcional.
#define OPTIONAL_PATH_INDEX 2

// Representa "Não encontrado"
#define NOT_FOUND -1

// Tamanho máximo da string hora.
#define TAMANHO_STR_HORA 10

// Nome do arquivo de log
#define LOG_FILE_NAME "findfile.log"

// Mensagens
#define MSG_WELLCOME "\n\t+---------------------------------------------------+\n\t| FindFile [versão 0.1.5]                           |\n\t| Vinicius J P Silva. Todos os direitos reservados. |\n\t+---------------------------------------------------+\n"
#define MSG_KEY_CONTINUE "\tPressione qualquer tecla para finalizar...\n"

// Erros
#define ERR_INVALID_NUMBER_ARGUMENTS "\n\tForneça pelo menos 1 argumento!\n\t\tExemplo: c:\\> findfile \"browser\"\n"
#define ERR_CREATE_FIND_FILE "\n\tOcorreu um erro durante a leitura do caminho \"{}\".\n\tCertifique-se que o caminho informado exista e tente novamente!\n\n"
#define ERR_CREATE_LOG_FILE "\n\tOcorreu um erro ao abrir o arquivo de log \"findfile.log\"! O programa será encerrado...\n\n"

/* Representa os serviços do programa findfile. 

   Nota: O template de classe optional representa um objeto que pode ter um valor opcional, ou seja, 
         um valor que pode ou não está presente no objeto.
		 Veja detalhes em: https://en.cppreference.com/w/cpp/utility/optional
*/ 
class FindFile {
public:
	FindFile() = default;
	FindFile(string searchString);

	/* Pesquisa a string em todos os arquivos do diretório do FindFile. O tipo dos arquivos é definido por File::FILE_TYPE.
	   Retorna o número de arquivos em que a string foi localizada no diretório e/ou subdiretórios ou -1 se não achá-la em nenhum arquivo.
	*/
	int findFile();

	/* Pesquisa a string em todos os arquivos do diretório. O tipo dos arquivos é definido por File::FILE_TYPE.
	   Retorna o número de arquivos em que a string foi localizada no diretório e/ou subdiretórios ou -1 se não achá-la em nenhum arquivo.
	*/ 
	int findFile(string searchString, string directory);

	/* Pesquisa a string em todos os arquivos do diretório. O tipo dos arquivos é definido por File::FILE_TYPE.
	   Retorna o número de arquivos em que a string foi localizada no diretório e/ou subdiretórios ou -1 se não achá-la em nenhum arquivo.
	*/
	int findFile(string searchString, Directory directory);

	/* Lê o conteúdo do diretório.
	   Cria um objeto File para cada arquivo, um objeto Directory para o diretório da linha de comando e para cada um de seus subdiretórios. 
	   Retorna o diretório com todos os seus atributos.
	*/
	optional<Directory> readDirectory(string directory);

	// Cria o arquivo de log com nome definido por nameFile. Retorna true se o arquivo foi criado com sucesso e false em caso de erro.
	bool createLogFile(string nameFile);

	// Exibe o relatório com o tempo da pesquisa, nome e conteúdo do diretório pesquisado. 
	void showReport(Directory directory, SearchTime searchTime);
	
	// Cria um objeto tipo FindFile utilizando os argumentos formais da função main
	static optional<FindFile> createFindFile(int argc, char* argv[]);

private:
	// String a ser pesquisada nos arquivos.
	string searchString;

	// Diretório fornecido como parâmetro para o programa findfile.
	Directory directory;

	// Tempo da pesquisa realizada no diretório.
	SearchTime searchTime;

	/* Pesquisa a string em todos os arquivos do vector files. O tipo dos arquivos é definido por File::FILE_TYPE.
	   Retorna o número de arquivos em que a string foi localizada ou -1 se não achá-la em nenhum arquivo.
	*/
	int findFile(string searchString, vector<Descriptor> files);

	// Exibe a mensagem "Pesquisando no arquivo <nomeArquivo>..." e um std::endl, onde <nomeArquivo> é substituído por nameFile.
	void printMessagem(string nameFile);
};

/*
	Função responsável por ler os argumentos informados na linha de comando, efetuar a pesquisa e exibir o relatório.
	Retorna:
		EXIT_SUCCESS
*/
int findFile(int argc, char* argv[]);

/*
	Divide uma wstring a cada ocorrência do caracter L'\n', ou seja, separa a wstring texto em um vector que contém suas respectivas linhas.
	Retorna o vector com as linhas divididas.
*/
vector<wstring> splitStringByLines(wstring text);

/*
	Encontra e contabiliza cada ocorrência de determinada string no vector de strings.
	Cria, preenche e retorna um objeto do tipo FileStringCount.
*/
FileStringCount findAndCountSearchString(string searchString, vector<wstring> splitedText, string fileName);

/*
	Transforma todos os caracteres de uma string para caixa baixa (minúsculo) e retorna a mesma.
*/
string toLower(string str);

/*
	Sobrecarga: 
	Transforma todos os caracteres de uma wstring para caixa baixa (minúsculo) e retorna a mesma.
*/
wstring toLower(wstring str);

/*
	Função responsável por formatar e exibir na saida padrão um valor natural, utilizando o modelo de separação de milhar.
	Exemplo:
		Caso o usuário forneça o número 1000 e o caracter separador '.', a função exibe na saída padrão o texto "1.000"
*/
void printInt(unsigned long long numero, const char separador);

/*
	Abre o arquivo de LOG e o preenche com os dados obtidos na pesquisa do findFile().
*/
void generateOutputToFileLog(string logFileName, string searchString, vector<FileStringCount> files);


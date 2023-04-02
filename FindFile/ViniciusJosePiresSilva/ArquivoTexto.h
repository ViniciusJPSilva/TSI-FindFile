#ifndef ARQUIVO_TEXTO
#define ARQUIVO_TEXTO

#include <fstream>
#include <string>

using namespace std;

/* Define os tipos de acesso que podem ser usados para acessar o arquivo. Os modos disponíveis são:

   ACRESCENTAR: abre o arquivo apenas para acrescentar dados no fim do arquivo;
   ESCRITA: abre o arquivo apenas para a escrita de dados;
   LEITURA: abre o arquivo apenas para a leitura de dados.
*/
enum class TipoDeAcesso { ACRESCENTAR, ESCRITA, LEITURA };

// A letra L maiúscula é usada para definir uma string literal do tipo wstring.
const wstring NOVA_LINHA = L"\n";

// Codificação de caracteres UTF-8.
const string UTF_8 = ".UTF8";

/*
	Esta classe fornece os métodos básicos para manipular um arquivo texto.
*/
class ArquivoTexto {
public: 
	ArquivoTexto() = default;

	// Fecha o arquivo texto antes do objeto ser removido da memória.
	virtual ~ArquivoTexto();

	// Obtém o nome do arquivo texto.
	string getNomeArquivo();

	/* Abre um arquivo texto identificado por nomeArquivo. O modo de abertura do arquivo deve ser especificado por 
	   uma das constantes de TipoDeAcesso. Se o arquivo não existir ele será criado. 
	   Se o modo for ESCRITA e o arquivo já existir em disco, todo o seu conteúdo será excluído.
	   Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
	 */
	bool abrir(string nomeArquivo, TipoDeAcesso tipoDeAcesso);

	/* Escreve no arquivo texto o conteúdo do objeto string usando a codificação UTF-8.
       A escrita sempre ocorre no fim do arquivo.
       Retorna true se a operação foi realizada com sucesso e false caso contrário.
     */
	bool escrever(wstring conteudo);

	/* Escreve no arquivo texto o conteúdo do objeto string usando a codificação especificada, p. ex., ".1252".
	   A escrita sempre ocorre no fim do arquivo.
	   Retorna true se a operação foi realizada com sucesso e false caso contrário.
	 */
	bool escrever(wstring conteudo, const string codificacao);

	/* Lê o conteúdo do arquivo texto usando a codificação UTF-8.
	   Retorna uma string com todo o conteúdo do arquivo texto.
	 */
	wstring ler();

	/* Lê o conteúdo do arquivo texto usando a codificação especificada, p. ex., ".1252".
	   Retorna uma string com todo o conteúdo do arquivo texto.
	 */
	wstring ler(const string codificacao);

	/* Lê o conteúdo de uma linha de texto. A primeira linha de texto é de número zero (0).
	   Retorna um objeto string com o conteúdo da linha de texto.
	  
	   ATENÇÃO: Este método só irá recuperar a linha de texto correta do arquivo se todas as linhas possuírem o mesmo comprimento em bytes.
	 */
	wstring ler(int numeroLinha);

	// Fecha o arquivo texto.
	void fechar();

private:
	string nomeArquivo;
	wstring texto;

	// Objeto para ler caracteres de 2 bytes (wchar_t), tamanho usado no UTF-16.
	wifstream inputFile;  

	// Objeto para escrever caracteres de 2 bytes (wchar_t), tamanho usado no UTF-16. 
	wofstream outputFile;
}; 
#endif 
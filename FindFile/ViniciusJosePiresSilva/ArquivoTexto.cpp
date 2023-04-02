#include <iostream>
#include <locale>
#include "ArquivoTexto.h"

// Fecha o arquivo texto antes do objeto ser removido da memória.
ArquivoTexto::~ArquivoTexto() 
{
	fechar();
}

// Obtém o nome do arquivo texto.
string ArquivoTexto::getNomeArquivo() 
{
	return nomeArquivo;
}

/* Abre um arquivo texto identificado por nomeArquivo. O modo de abertura do arquivo deve ser especificado por
   uma das constantes de TipoDeAcesso. Se o arquivo não existir ele será criado.
   Se o modo for ESCRITA e o arquivo já existir em disco, todo o seu conteúdo será excluído.
   Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
*/
bool ArquivoTexto::abrir(string nomeArquivo, TipoDeAcesso tipoDeAcesso) 
{
	this->nomeArquivo = nomeArquivo;

	// Abre o arquivo segundo o modo de abertura ou tipo de acesso escolhido.
	switch (tipoDeAcesso) {
	case TipoDeAcesso::ACRESCENTAR: outputFile.open(nomeArquivo, ios::app);
								    return outputFile.is_open() ? true : false;
						   
	case TipoDeAcesso::ESCRITA: outputFile.open(nomeArquivo, ios::out);
							    return outputFile.is_open() ? true : false;

	case TipoDeAcesso::LEITURA: inputFile.open(nomeArquivo, ios::in);
								return inputFile.is_open() ? true : false;
	}
	return false;
} 

/* Escreve no arquivo texto o conteúdo do objeto string usando a codificação UTF-8.
   A escrita sempre ocorre no fim do arquivo.
   Retorna true se a operação foi realizada com sucesso e false caso contrário.
 */
bool ArquivoTexto::escrever(wstring conteudo) 
{
	return escrever(conteudo, UTF_8);
} 

/* Escreve no arquivo texto o conteúdo do objeto string usando a codificação especificada, p. ex., ".1252".
   A escrita sempre ocorre no fim do arquivo.
   Retorna true se a operação foi realizada com sucesso e false caso contrário.
*/
bool ArquivoTexto::escrever(wstring conteudo, const string codificacao)
{
	// Cria um objeto locale com a codificação especificada.
	const locale local(codificacao);

	// Define o locale do arquivo.
	outputFile.imbue(local);

	// Verifica se o arquivo está aberto. 
	if (outputFile.is_open())
	{
		// Posiciona o ponteiro no fim do arquivo e escreve o conteúdo.
		outputFile.seekp(0, ios::end);
		outputFile << conteudo << endl;
		return true;
	}
	return false;
}

/* Lê o conteúdo do arquivo texto usando a codificação UTF-8.
   Retorna uma string com todo o conteúdo do arquivo texto.
 */
wstring ArquivoTexto::ler() 
{
	return ler(UTF_8);
}


/* Lê o conteúdo do arquivo texto usando a codificação especificada.
   Retorna uma string com todo o conteúdo do arquivo texto.
*/
wstring ArquivoTexto::ler(const string codificacao) 
{
	wstring linha;
	
	// Cria um objeto locale com a codificação especificada.
	const locale local(codificacao);

	// Define o locale do arquivo.
	inputFile.imbue(local);

	// Lê o conteúdo do arquivo até atingir o fim do arquivo.
	do { // Lê o conteúdo de uma linha do arquivo até encontrar o caractere nova linha ('\n'). 
		getline(inputFile, linha);

	     // Verifica se atingiu o fim do arquivo. Se não atingiu armazena as linhas lidas do texto em um objeto string.
		 if (!inputFile.eof()) 
		 {
			 texto.append(linha);
			 texto.append(NOVA_LINHA);
		 }
	} while (!inputFile.eof());

	// Cria um objeto string e inicializa-o com as linhas do texto.
   return texto;
} 

/* Lê o conteúdo de uma linha de texto. A primeira linha de texto é de número zero (0).
   Retorna um objeto string com o conteúdo da linha de texto.

   ATENÇÃO: Este método só irá recuperar a linha de texto correta do arquivo se todas as linhas possuírem o mesmo comprimento em bytes.
 */
wstring ArquivoTexto::ler(int numeroLinha) 
{
	wstring linha;

	// Lê o conteúdo do arquivo até atingir o fim do arquivo.
	if (numeroLinha >= 0) 
	{
		inputFile.seekg(numeroLinha);
		getline(inputFile, linha);
	}

	// Cria um objeto string e inicializa-o com o conteúdo da linha.
	return linha;
} 

// Fecha o arquivo texto.
void ArquivoTexto::fechar() 
{
	// Verifica se o arquivo está aberto.
	if (inputFile.is_open()) inputFile.close();
	if (outputFile.is_open()) outputFile.close();

	// Apaga o conteúdo do texto.
	texto.clear();
}
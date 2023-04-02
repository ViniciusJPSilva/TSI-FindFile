# TSI-FindFile
O algoritmo procura uma string em todos arquivos de texto simples com extensão txt ou log localizados no diretório e em todos os seus subdiretórios indicados pelo usuário. A pesquisa não faz distinção entre as letras maiúsculas e minúsculas que formam a cadeia de caracteres.

<hr>

<h3>Funcionamento</h3>
O usuário digita na linha de comando do sistema operacional o nome do programa findfile e passa como argumento a string e o diretório. Se o diretório for omitido realiza a busca a partir do diretório corrente. Veja os exemplos abaixo.
<br>
c:\> findfile “browser”

> Localiza a string “browser” em todos os arquivos de texto do diretório atual e seus subdiretórios.

<br>
c:\> findfile “Mozilla Firefox” “C:\Program Files\Mozilla Firefox”

> Localiza a string “Mozilla Firefox” em todos os arquivos de texto do diretório “C:\Program Files\Mozilla Firefox” e seus subdiretórios.

<br>

<hr>
<h3>Saída no stdout</h3>
<h4>Ocorre durante a execução do programa.</h4>

![image](https://user-images.githubusercontent.com/81810017/229361105-25127773-e0c9-4302-b62e-4b80fd140b72.png)

<hr>
<h3>Saída no arquivo de Log</h3>
<h4>Ao terminar a busca da string o programa findfile deve criar um arquivo de log no diretório corrente para registrar o resultado da pesquisa.</h4>

![image](https://user-images.githubusercontent.com/81810017/229361360-8e5e57cc-1b58-44c3-be65-2af7e33c4782.png)

<hr>

<h3>Diagrama de Classes</h3>

![image](https://user-images.githubusercontent.com/81810017/229360609-3cbb9563-7396-4cae-ac44-03147c1fedc4.png)

<hr>

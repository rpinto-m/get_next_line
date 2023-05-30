/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:31:41 by fde-carv          #+#    #+#             */
/*   Updated: 2023/05/16 12:06:08 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Este código é uma implementação simplificada da função get_next_line, que
é usada para ler linhas de um arquivo de texto (fd representa o descritor
de arquivo correspondente). A função usa um buffer para ler do arquivo em
partes e armazena o conteúdo lido numa variável str. Em seguida, a função
get_theline é usada para extrair a primeira linha da variável str e armazená-la
em uma variável line. A função get_new_str é usada para atualizar a variável str,
removendo a linha que já foi lida. A função get_next_line retorna a linha lida
ou NULL se houver erro.

> ft_calloc aloca memória e inicializa-a com zero.
> ft_strchr encontra a primeira ocorrência de um caractere numa string.
> ft_strlen retorna o tamanho de uma string.
> ft_strjoin concatena duas strings.
Estas funções são usadas para manipular as strings durante a leitura e a
extração das linhas do arquivo.

É importante notar que o código usa uma variável static char *str para
armazenar o conteúdo lido do arquivo entre chamadas sucessivas da função
get_next_line. Isso significa que a função get_next_line pode ser chamada
várias vezes para ler linhas sucessivas de um arquivo sem precisar reabrir
o arquivo a cada chamada. No entanto, isso também significa que a função não
é segura para uso simultâneo em vários threads, pois a variável static será
compartilhada entre todos eles.
*/

/*
Uma variável static é uma variável que mantém seu valor entre chamadas
sucessivas à função em que ela é declarada. Uma variável estática é declarada
usando a palavra-chave "static" e é inicializada apenas uma vez, na primeira
vez que a função é chamada. Nas chamadas subsequentes da função, a variável
mantém seu valor anterior.

Uma das principais utilizações das variáveis estáticas é para criar contadores
locais a uma função, que são usados para manter o controle do número de vezes
que a função foi chamada. Outra utilização comum das variáveis estáticas é
para armazenar valores constantes que não precisam ser recalculados em cada
chamada da função. Por exemplo, uma função que calcula a raiz quadrada de um
número pode armazenar o valor da precisão da raiz quadrada como uma variável
estática, de modo que o valor não precisa ser recalculado em cada chamada da
função.

Em geral, as variáveis estáticas são úteis quando precisamos manter o estado
entre chamadas sucessivas numa função e quando queremos evitar a redeclaração
de variáveis em cada chamada da função.
*/

#include "get_next_line.h"

char	*get_str(int fd, char *str)
{
	char		*tab;
	char		*tmp;
	int			read_bytes;

	tab = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!tab)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !(ft_strchr(tab, '\n')))
	{
		read_bytes = read(fd, tab, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			if (str)
				free(str);
			free(tab);
			return (NULL);
		}
		tab[read_bytes] = '\0';
		tmp = ft_strjoin(str, tab);
		free(str);
		str = tmp;
	}
	free(tab);
	return (str);
}

/*
get_str que recebe dois argumentos: um descritor de arquivo fd e uma
string str. A função lê o conteúdo do arquivo referenciado por fd e
armazena em str até encontrar um caractere de nova linha (\n) ou o
final do arquivo.

Primeiramente, a função aloca um buffer de memória tab com o tamanho
BUFFER_LEN + 1 usando a função ft_calloc. Se a alocação falhar, a função
retorna NULL.

Em seguida, a variável read_bytes é inicializada com 1. A função entra num
loop enquanto a quantidade de bytes lidos for maior do que zero
(read_bytes > 0) e não encontrar um caractere de nova linha
(!ft_strchr(tab, '\n')).

Dentro do loop, a função lê os bytes do arquivo para o buffer tab usando
a função read. Se read retornar um valor negativo, a função desaloca a
memória alocada para str (se existir) e buf e retorna NULL.

Caso a leitura do arquivo seja bem-sucedida, o buffer tab é finalizado
com um caractere nulo (\0) para que possa ser tratado como uma string.
A função ft_strjoin é usada para concatenar str e tab, armazenando o
resultado numa variável temporária tmp. Em seguida, str é desalocado
e tmp é atribuído a str.

Depois de ler todo o conteúdo do arquivo ou encontrar um caractere de
nova linha, o buffer tab é desalocado e a função retorna str. Se não houver
conteúdo a ser lido no arquivo, a função retornará uma string vazia ou nula,
dependendo do valor inicial de str.
*/

/*
"read" é uma função em C que é usada para ler dados de um arquivo ou de um
descritor de arquivo (file descriptor) num buffer. Ela é geralmente usada
em sistemas Unix-like, incluindo Linux e macOS.

A função "read" é usada para ler os dados do descritor de arquivo (fd) num
buffer (tab) com o tamanho definido por BUFFER_LEN. A variável "read_bytes"
armazena o número de bytes lidos pela função "read". O loop while continuará
lendo bytes do arquivo até encontrar um caractere de nova linha ('\n') ou
até que a função "read" retorne um valor menor ou igual a zero.

É importante notar que a função "read" pode falhar em certas condições,
como quando não há mais dados para ler ou quando ocorre um erro durante a
leitura. Neste caso há uma verificação para o caso em que "read_bytes" é menor
que zero. Se isso acontecer, a função retorna NULL após libertar a memória
alocada para o buffer.

A função "read" é uma função de entrada e saída (I/O) em C que lê dados de um
arquivo ou de um descritor de arquivo (file descriptor) num buffer.
A assinatura da função é a seguinte:
	#include <unistd.h>
		ssize_t read(int fd, void *buf, size_t count);
> "fd": o descritor de arquivo a partir do qual os dados serão lidos.
> "buf": o buffer em que os dados lidos serão armazenados.
> "count": o número máximo de bytes que podem ser lidos.
A função "read" retorna o número de bytes lidos ou -1 em caso de erro. Se não
houver mais dados para ler, a função retorna 0.

Uma das principais características da função "read" é que ela é uma chamada de
sistema de baixo nível. Isso significa que ela é uma função muito básica que é
executada diretamente pelo kernel do sistema operacional, sem a ajuda de
bibliotecas ou de funções de mais alto nível. Isso faz com que a função "read"
seja rápida e eficiente em termos de desempenho, mas também significa que é
preciso tomar alguns cuidados ao usá-la, especialmente em relação a possíveis
erros e condições de retorno.
*/

/*
!ft_strchr(tab, '\n') --> ou seja nos queresmos que ('\n') nao esteja presente.
! sozinho significa o inverso / oposto do que se procura. 
Quando usamos a expressão "!ft_strchr(tab, '\n')", estamos a verificar se o
caractere da nova linha ('\n') não está presente na string "tab". Se essa
condição for verdadeira, o loop while continuará lendo bytes do arquivo até
encontrar o caractere de nova linha ou até que não haja mais bytes para ler.
Em outras palavras, o loop continuará até que leia uma linha completa de texto.
*/

char	*get_theline(char *str)
{
	char	*result;
	int		i;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	result = ft_calloc(sizeof(char), (i + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{	
		result[i] = str[i];
		i++;
	}
	else
		result[i] = '\0';
	return (result);
}

/*
get_theline que recebe uma string str como argumento. A função retorna
uma nova string contendo a primeira linha da string str, incluindo o
caractere de nova linha (\n), se houver.

Primeiro, a função inicializa uma variável i como zero. Se o primeiro
caractere de str for um caractere nulo (\0), a função retorna NULL.
Caso contrário, a função entra num loop que percorre os caracteres de
str até encontrar um caractere de nova linha (\n) ou o final da string (\0).
O loop incrementa a variável i a cada iteração.

Em seguida, a função aloca uma nova string result com tamanho i + 2
usando a função ft_calloc. O tamanho é i + 2 porque a nova string incluirá
o caractere de nova linha (\n) e um caractere nulo (\0) no final.

Se a alocação falhar, a função retorna NULL. Caso contrário, a função entra
em outro loop que percorre os caracteres de str até encontrar um caractere
de nova linha (\n) ou o final da string (\0). O loop copia cada caractere de
str para a nova string result até encontrar o caractere de nova linha (\n)
ou o final da string (\0).

Após copiar a primeira linha de str para result, a função adiciona o caractere
de nova linha (\n) à nova string result, incrementa a variável i e adiciona um
caractere nulo (\0) ao final de result.

Por fim, a função retorna a nova string result contendo a primeira linha de str.
// --> Se não houver nenhuma linha em str, a função retornará uma string vazia
ou nula, dependendo do valor inicial de result.
*/

char	*get_new_str(char *str)
{
	char	*new_str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	new_str = ft_calloc(sizeof(char), (ft_strlen(str) - i));
	if (!new_str)
		return (NULL);
	i++;
	while (str[i] != '\0')
	{
		new_str[count] = str[i];
		count++;
		i++;
	}
	free(str);
	return (new_str);
}

/*
get_new_str recebe uma string str como argumento. A função retorna
uma nova string que contém tudo que estava depois da primeira linha da
string str, excluindo o caractere de nova linha (\n) da primeira linha,
ou seja sem o caractere '\n'.

Primeiro, a função inicializa duas variáveis i e count como zero. A
variável i é usada para percorrer os caracteres da string str, e a
variável count é usada para contar o número de caracteres na nova string
new_str.

O 1º loop percorre os caracteres de str até encontrar um caractere de nova
linha (\n) ou o final da string (\0). O loop incrementa a variável i a
cada iteração.

Se a primeira linha da string str não contém um caractere de nova linha
(\n) e termina com um caractere nulo (\0), a função libera a memória alocada
para a string str e retorna NULL.

Em seguida, a função aloca uma nova string new_str com tamanho igual à
diferença entre o comprimento de str e a posição do caractere de nova
linha (\n) na primeira linha. A alocação é feita usando a função ft_calloc.

Se a alocação falhar, a função retorna NULL. Caso contrário, a função entra
em outro loop que percorre os caracteres de str a partir da posição após o
caractere de nova linha (\n) até o final da string (\0). O loop copia cada
caractere de str para a nova string new_str e incrementa a variável count
a cada iteração.

Após copiar todos os caracteres da string str após o primeiro caractere de
nova linha (\n) para a nova string new_str, a função libera a memória alocada
para a string str e retorna a nova string new_str.

Por fim, a função retorna a nova string new_str contendo tudo que estava
depois da primeira linha da string str, excluindo o caractere de nova linha
(\n) da primeira linha. Se a string str não contiver um caractere de nova
linha (\n) na primeira linha, a função retornará NULL.
*/

/*
A expressão "(ft_strlen(str) - i)" é usada para determinar o tamanho da nova
string "new_str" que será criada na função "get_new_str()".

O valor de retorno da expressão é a diferença entre o comprimento total da
string "str" e o índice "i" do primeiro caractere após a primeira linha da
string. Isso é necessário porque a nova string "new_str" será usada para
armazenar todas as linhas restantes da string "str", que começa após o primeiro
caractere de nova linha '\n'.

Por exemplo, se a string "str" tiver o seguinte conteúdo:
"Esta é a primeira linha.\nEsta é a segunda linha.\nEsta é a terceira linha.\n"
então a função "get_new_str()" será chamada após a primeira linha ser lida pela
função "get_theline()", passando a string "str" que agora começa com "Esta é a
segunda linha.\nEsta é a terceira linha.\n".

Nesse caso, a expressão "(ft_strlen(str) - i)" retornará o valor "29"
(comprimento total da string "str" - índice do primeiro caractere após a primeira
linha), indicando que a nova string "new_str" precisa ter tamanho suficiente para
armazenar 29 caracteres, incluindo os caracteres de nova linha '\n'.
*/

/*
O segundo i++ é colocado fora do primeiro loop porque seu objetivo é mover o
índice i para o próximo caractere após o caractere de quebra de linha ('\n').

A intenção é que a cópia de str para new_str comece a partir do primeiro
caractere que não foi copiado. Portanto, após o primeiro loop, a variável i já
aponta para o caractere de quebra de linha e o segundo i++ é usado para
avançar o índice i para o próximo caractere a ser copiado.

Isso garante que o segundo loop comece a copiar os caracteres de str para new_str
a partir do primeiro caractere após o caractere de quebra de linha ('\n')
encontrado anteriormente, e continue até que todos os caracteres restantes de str
sejam copiados para new_str.

Se se str[i] for igual a '\0' no primeiro loop, a função irá liberar a memória
alocada para str e retornar NULL imediatamente, sem alocar memória para new_str.

O segundo loop não será executado, pois não há caracteres para serem copiados.
Nesse caso, a função retorna NULL, indicando que não há nova string a ser
retornada.

Portanto, se str[i] for igual a '\0', a função não retorna a new_str, mas sim
retorna NULL.
*/

char	*get_next_line(int fd)
{
	static char		*str;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = get_str(fd, str);
	if (!str)
		return (NULL);
	line = get_theline(str);
	str = get_new_str(str);
	return (line);
}

/*
get_next_line recebe um file descriptor fd como argumento. A função
retorna uma linha do arquivo identificado pelo file descriptor fd a cada
chamada, até que o final do arquivo seja atingido ou ocorra um erro.
A função utiliza outras duas funções auxiliares, get_str e get_theline.

A função get_next_line começa verificando se o valor do file descriptor
fd é válido e se o valor da constante BUFFER_SIZE é maior que zero. Se
algum desses valores não for válido, a função retorna NULL.

Em seguida, a função chama a função auxiliar get_str com os argumentos
fd e str. A variável str é uma variável estática que armazena o conteúdo
restante do arquivo do qual a última chamada a get_next_line leu. A função
get_str lê BUFFER_SIZE bytes do arquivo e armazena o resultado em str,
concatenando com o conteúdo restante do arquivo da última chamada. A função
get_str retorna a nova string lida ou NULL em caso de erro.

Se a chamada a get_str retornar NULL, a função get_next_line também retorna
NULL.

Caso contrário, a função get_next_line chama a função auxiliar get_theline,
que recebe a string str como argumento e retorna a primeira linha da string,
incluindo o caractere de nova linha (\n). A função get_next_line atribui o
resultado de get_theline à variável line.
You asked many relevant questions and it was a good evaluation. 
Em seguida, a função get_next_line chama a função auxiliar get_new_str, que
recebe a string str como argumento e retorna a parte da string str que vem
após a primeira linha (excluindo o caractere de nova linha). A função
get_next_line atribui o resultado de get_new_str à variável estática str.

Por fim, a função get_next_line retorna a string line, que contém a primeira
linha lida do arquivo. Se não houver mais linhas para ler no arquivo, a função
retornará NULL.
*/


#include <stdio.h>

int	main(void)
{
	int	i;
	int	fd;
	char	*line;

	fd = open("tests/test2.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR ON FILE");
		return (0);
	}
	i = 0;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}


/*
A função "open()" é usada para abrir um arquivo em um programa C. Ela é
definida na biblioteca padrão "fcntl.h" e tem a seguinte sintaxe:
	#include <fcntl.h>
		int open(const char *path, int oflag, ...);
O primeiro argumento, "path", é uma string que representa o caminho do
arquivo que deve ser aberto. Ele pode ser um caminho absoluto ou relativo.

O segundo argumento, "oflag", é uma série de opções que especificam como
o arquivo deve ser aberto. Essas opções são formadas pela combinação de
constantes definidas em "fcntl.h", como "O_RDONLY", "O_WRONLY", "O_RDWR",
"O_APPEND", "O_CREAT", "O_TRUNC", entre outras. As opções são combinadas
usando operações de bit a bit (bitwise), como a operação OR "|" (pipe).

O terceiro argumento, quando presente, é um conjunto de permissões que
serão aplicadas ao arquivo recém-criado, caso a opção "O_CREAT" tenha sido
especificada.

A função "open()" retorna um descritor de arquivo (um número inteiro) que
representa o arquivo aberto. Esse descritor é usado posteriormente para
realizar operações de leitura ou escrita no arquivo, usando outras funções
como "read()", "write()", "close()", entre outras.

É importante lembrar que a função "open()" não realiza operações de leitura
ou escrita no arquivo, ela apenas abre o arquivo e retorna um descritor
que pode ser usado posteriormente para acessá-lo.
*/

/*
Um descritor de arquivo, ou file descriptor em inglês, é um identificador
numérico usado para acessar um arquivo ou um recurso de E/S em sistemas
operacionais baseados em UNIX, como Linux e macOS. O descritor de arquivo
é uma abstração que representa a conexão entre um programa e um arquivo ou
dispositivo.

Existem três tipos principais de descritores de arquivo:

    Descritores de arquivo padrão:
        0: stdin (entrada padrão)
        1: stdout (saída padrão)
        2: stderr (saída de erro padrão)

Esses descritores de arquivo são abertos automaticamente quando um
programa é executado e estão associados aos fluxos de entrada e saída
padrão do programa.

Descritores de arquivo abertos:
Esses descritores de arquivo são criados quando um programa abre um arquivo
usando funções como open() ou fopen(). Eles são representados por números
inteiros maiores do que 2.

Descritores de arquivo reservados:
Além dos descritores de arquivo padrão e abertos, alguns números de
descritores de arquivo podem estar reservados para uso interno pelo sistema
operacional ou bibliotecas. Esses números geralmente são negativos.

Os descritores de arquivo permitem que um programa realize operações de
leitura, escrita e controle em arquivos e outros recursos de E/S. Eles são
usados em chamadas de sistema e funções de biblioteca para realizar operações
como leitura de dados de um arquivo, gravação de dados em um arquivo ou
redirecionamento de saída para um arquivo específico.

É importante gerenciar adequadamente os descritores de arquivo, fechendo-os
corretamente quando não forem mais necessários, para evitar vazamentos de
recursos e problemas de desempenho.
*/

/*
"O_RDONLY" é uma constante definida na biblioteca padrão do C "fcntl.h"
que é usada para especificar a abertura de um arquivo em modo somente leitura.

Quando um arquivo é aberto com essa opção, ele só pode ser lido, mas não pode
ser escrito. O modo somente leitura é útil quando você deseja proteger um
arquivo de escrita acidental ou indesejada.

Além de "O_RDONLY", existem outras opções que podem ser usadas ao abrir um
arquivo, como:

> O_WRONLY: abre o arquivo em modo somente escrita.
> O_RDWR: abre o arquivo em modo leitura e escrita.
> O_APPEND: acrescenta os dados ao final do arquivo ao invés de substituir o
            seu conteúdo.
> O_CREAT: cria o arquivo se ele não existir.
> O_TRUNC: trunca (apaga) o arquivo se ele já existir.

Estas opções são passadas como argumentos para a função "open()", que é usada
para abrir um arquivo em um programa C.
*/

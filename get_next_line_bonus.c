/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:53:26 by fde-carv          #+#    #+#             */
/*   Updated: 2023/05/16 12:08:05 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*get_theline(char *str)
{
	char	*result;
	int		i;

	i = 0;
	if (!(str[i]))
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

char	*get_new_str(char *str)
{
	char	*new_str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (!(str[i] == '\n'))
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

char	*get_next_line(int fd)
{
	static char		*str[FOPEN_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	str[fd] = get_str(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = get_theline(str[fd]);
	str[fd] = get_new_str(str[fd]);
	return (line);
}

/*
Essa é uma função que lê um arquivo de texto linha por linha, a partir de um
descritor de arquivo ("fd"). A função utiliza outras três funções auxiliares:
"get_str()", "get_theline()" e "get_new_str()".

A variável "str" é uma matriz estática de ponteiros para caracteres, que
armazena o conteúdo do arquivo lido. A matriz tem o tamanho máximo de arquivos
abertos simultaneamente ("FOPEN_MAX", definido em "stdio.h").

FOPEN_MAX representa o número máximo de arquivos que podem ser abertos
simultaneamente por um programa. É um valor que depende da implementação e
pode variar entre sistemas operacionais ou ambientes de desenvolvimento.
Em geral, seu valor é grande o suficiente para atender às necessidades da maioria
dos programas, como 256 ou 1024.

A função começa verificando se o descritor de arquivo é válido e se o tamanho
do buffer é maior que zero. Se qualquer uma dessas condições não for satisfeita,
a função retorna "NULL".

A função chama a função auxiliar "get_str()" para obter uma string que contém
o conteúdo do arquivo a partir do ponto atual (indicado pelo descritor de
arquivo "fd") até o final da linha ou do arquivo.

Em seguida, a função "get_theline()" é chamada para obter a próxima linha da
string "str[fd]", e a função "get_new_str()" é chamada para atualizar a string
"str[fd]" com o restante do arquivo.

Por fim, a função retorna a linha lida como uma string ("line"), e a matriz
"str" é atualizada com o restante do arquivo para ser lido na próxima chamada
da função.

Essa função é útil para ler arquivos de texto grandes sem precisar armazenar
todo o conteúdo na memória de uma só vez, o que pode ser ineficiente e causar
problemas de desempenho em casos de arquivos muito grandes.
*/

/*
FOPEN_MAX não é uma função, mas uma constante definida em algumas
implementações da linguagem C.

Essa constante representa o número máximo de arquivos que podem ser abertos
simultaneamente por um programa usando as funções de E/S padrão da
biblioteca C. O valor de FOPEN_MAX varia dependendo da implementação, mas
geralmente é um número relativamente alto, como 256.

Neste código, FOPEN_MAX é usado para verificar se o descritor de arquivo fd
está dentro do intervalo válido. Se fd for menor que 0, ou se BUFFER_SIZE
for menor ou igual a 0, ou se fd for maior que FOPEN_MAX, a função
get_next_line retorna NULL, indicando um erro. Caso contrário, o código
continua executando.

Lembrando que essa é apenas uma possível implementação da função get_next_line,
e a presença de FOPEN_MAX depende da biblioteca e do sistema em que o código
está sendo compilado.
*/

/*
#include <stdio.h>

int	main(void)
{
	int	fd;
	char	*line;
	int	i;
	
	fd = open("tests/fred2.txt", O_RDONLY);
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
*/

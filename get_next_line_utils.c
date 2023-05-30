/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:31:46 by fde-carv          #+#    #+#             */
/*   Updated: 2023/05/16 12:07:51 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

/*
Em resumo, a função ft_strlen percorre uma string str contando quantos
caracteres ela contém e retorna esse valor.

A função começa inicializando uma variável i do tipo size_t com zero.
Em seguida, um while é usado para percorrer a string str enquanto ela não
for nula e o caractere atual não for nulo. A cada iteração, a variável i
é incrementada. str --> verifica se a string str não é nula.

Quando o while termina, a variável i contém o número de caracteres na
string str. A função então retorna esse valor.
*/

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0' && *str != c)
		str++;
	if (c == *str)
		return ((char *)str);
	return (NULL);
}

/*
Em resumo, a função ft_strchr percorre uma string s procurando a primeira
ocorrência de um caractere c. Se encontrar, retorna um ponteiro para essa
posição na string. Se não encontrar, retorna um ponteiro nulo.

O código começa com um while que verifica se o caractere atual apontado
pelo ponteiro s não é nulo e se não é o caractere procurado c. Se o
caractere atual não for nulo e não for o caractere procurado, o ponteiro s
é incrementado para apontar para o próximo caractere na string s.

Se o caractere procurado c for encontrado na string s, o código retorna um
ponteiro para a posição na string onde o caractere foi encontrado,
convertido para o tipo char*.

Se o caractere procurado não for encontrado na string, o código retorna um
ponteiro nulo.
*/

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new_str;
	size_t	len;
	int		i;
	int		j;

	len = (ft_strlen(s1) + ft_strlen(s2));
	new_str = ft_calloc(sizeof(char), (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0')
	{	
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/*
Este trecho de código é uma implementação da função ft_strjoin, que concatena
duas strings s1 e s2. Ela aloca memória suficiente para armazenar a nova string
concatenada e copia os caracteres das duas strings fornecidas para a nova string.

O código começa declarando uma variável new_str do tipo ponteiro de caractere,
uma variável len do tipo size_t, que é o tamanho total da nova string, e as
variáveis de contagem i e j, que serão usadas nos loops.

Em seguida, a variável len é definida como a soma dos tamanhos das strings
s1 e s2, utilizando a função ft_strlen, que retorna o comprimento da string
fornecida. A seguir, é alocada memória para a nova string usando a função
ft_calloc, que aloca e inicializa a memória alocada com zeros.

O código então verifica se a alocação de memória foi bem sucedida. Se não for,
retorna um ponteiro nulo.

O primeiro loop while copia os caracteres da string s1 para a nova string
new_str, enquanto o segundo loop while copia os caracteres da string s2 para
new_str, seguindo a posição atual de i.

Finalmente, um caractere nulo é adicionado ao final da nova string new_str
para indicar seu fim, e a nova string é retornada.

Em resumo, a função ft_strjoin concatena duas strings, alocando memória
para a nova string resultante e copiando as duas strings fornecidas para ela.
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;
	int		total_size;

	total_size = nmemb * size;
	tab = malloc(total_size);
	if (!tab)
		return (NULL);
	while (--total_size >= 0)
		tab[total_size] = '\0';
	return ((void *)tab);
}

/*
A função ft_calloc reserva na memória um bloco de dados com um tamanho
total de nmemb * size bytes e preenche esse bloco com zeros.

O primeiro parâmetro, nmemb, é o número de elementos a serem alocados,
enquanto o segundo parâmetro, size, é o tamanho em bytes de cada elemento.

A função começa calculando o tamanho total necessário para alocar o bloco
de dados, multiplicando nmemb por size. Em seguida, a função usa a função
malloc para alocar um bloco de memória com o tamanho calculado. Se a
alocação for bem-sucedida, um ponteiro para o bloco alocado é retornado.
Caso contrário, a função retorna NULL.

Depois de alocar o bloco de memória, a função usa um loop while para
preencher o bloco com zeros. O loop começa no último byte do bloco e
decrementa o contador total_size a cada iteração até que ele alcance zero.
Em cada iteração, o byte atual do bloco é definido como '\0', ou seja, é
preenchido com um byte nulo.

Por fim, a função retorna um ponteiro genérico para o bloco de memória
alocado, convertendo o ponteiro de char * para void * porque a função é
projetada para alocar blocos de memória para qualquer tipo de dado, não
apenas para dados do tipo char. Ao retornar um ponteiro genérico do
tipo void *, a função permite que o bloco de memória alocado seja usado
para armazenar dados de qualquer tipo. Isso significa que o usuário pode
receber o ponteiro retornado por ft_calloc e convertê-lo de volta para
um ponteiro do tipo de dados desejado (por exemplo, int *, float *,
struct *, etc.) usando um typecast adequado.

Portanto, a conversão de char * para void * é feita para tornar a
função ft_calloc mais genérica e flexível em relação ao tipo de dados
que ela pode manipular.
*/

/*
SIGSEGV é um sinal de erro que indica que o processo está tentando acessar
uma região de memória inválida. Esse sinal é gerado pelo sistema operacional
quando o programa tenta acessar uma área de memória que não foi alocada
para ele, ou que está fora de seus limites de acesso.

O SIGSEGV é um sinal sério de erro e geralmente resulta em um comportamento
imprevisível do programa, podendo causar falhas no sistema, travamentos
ou encerramento do programa.

As causas comuns de um erro SIGSEGV incluem:
> Desreferenciar um ponteiro nulo ou não inicializado
> Tentar acessar uma área de memória que não foi alocada ou que já foi liberada
> Tentar escrever ou ler em uma área de memória que não tem permissão de acesso
> Acesso a uma posição inválida de um vetor ou matriz

Ao receber um sinal SIGSEGV, o programa deve imediatamente tratar o erro para
evitar problemas maiores. Isso pode envolver verificar se o ponteiro é válido
antes de acessá-lo, alocar corretamente a memória necessária para o programa,
ou corrigir erros de lógica que levaram ao acesso indevido da memória.
*/
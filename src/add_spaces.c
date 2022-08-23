/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:30:49 by coder             #+#    #+#             */
/*   Updated: 2022/08/24 00:37:46 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// teste teste teste
/*
** checa se o caracetere antes do índice indicado deveria ser um espaço;
*/
int	need_space_before(char *buffer, int op_index, char operator)
{
	int	flag;

	flag = 0;
	if (op_index == 0)
		return (0);
	op_index--;
	while (op_index)
	{
		if (buffer[op_index] == operator)
		{
			if (flag)
				return (1);
			flag++;
		}
		if (flag && buffer[op_index - 1] != operator)
			return (0);
		else if (buffer[op_index] != ' ')
			return (1);
		else if (buffer[op_index] == ' ')
			return (0);
		op_index--;
	}
	return (0);
}

/*
** checa se o caracetere antes do índice indicado deveria ser um espaço;
*/
int	need_space_after(char *buffer, int op_index, char operator)
{
	int	flag;

	flag = 0;
	op_index++;
	while (op_index)
	{
		if (buffer[op_index] == operator)
		{
			if (flag == 2)
				return (1);
			flag++;
		}
		if (flag && buffer[op_index + 1] != operator)
			return (0);
		else if (buffer[op_index] != ' ' && buffer[op_index] != 0)
			return (1);
		else if (buffer[op_index] == ' ' || buffer[op_index] == 0)
			return (0);
		op_index++;
	}
	return (0);
}

/*
** Cria uma string nova, adicionando [espaço] depois do índice indicado;
*/
char	*add_space_before_index(char *buffer, int index)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc (sizeof (char) * (ft_strlen(buffer) + 2));
	while (buffer[i])
	{
		if (i == index)
		{
			ret[j] = ' ';
			j++;
		}
		ret[j] = buffer[i];
		i++;
		j++;
	}
	ret[j] = 0;
	return (ret);
}

char	*recursively_does_some_black_magic(char *buffer, int i)
{
	char	*temp;

	if (need_space_before(buffer, i, buffer[i]))
	{
		temp = add_space_before_index(buffer, i);
		safe_free(buffer);
		buffer = temp;
		temp = NULL;
		return (add_spaces(buffer));
	}
	if (need_space_after(buffer, i, buffer[i]))
	{
		temp = add_space_before_index(buffer, i + 1);
		safe_free(buffer);
		buffer = temp;
		temp = NULL;
		return (add_spaces(buffer));
	}
	return (buffer);
}

/*
** cria string allocada, adicionando espaços se antes ou depois de '<', '>',
** '<<', '>>' ou '|', não houverem espaços. Não trata ||;
*/
char	*add_spaces(char *buffer)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (buffer[i])
	{
		if (is_operator(buffer[i]))
			buffer = recursively_does_some_black_magic(buffer, i);
		i++;
	}
	return (buffer);
}

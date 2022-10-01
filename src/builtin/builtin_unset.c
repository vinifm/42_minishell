/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:05:53 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/30 03:48:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Frees environment list node if it matches unset argument
void	compare_arg_env(char *arg, t_ms_data *ms)
{
	t_env_list	*head;
	t_env_list	*tmp;

	if (!arg)
		return ;
	if (vars_match(ms->env_head->content, arg))
	{
		tmp = ms->env_head;
		ms->env_head = ms->env_head->next;
		free(tmp->content);
		free(tmp);
	}
	head = ms->env_head;
	while (head->next)
	{
		if (vars_match(head->next->content, arg))
		{
			tmp = head->next;
			head->next = head->next->next;
			safe_free(tmp->content);
			safe_free(tmp);
		}
		else
			head = head->next;
	}
}

int	builtin_unset(char **args, t_ms_data *ms)
{	
	if (!args)
		return (0);
	while (*args)
	{
		compare_arg_env (*args, ms);
		args++;
	}
	return (0);
}

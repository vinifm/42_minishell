/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:59:48 by coder             #+#    #+#             */
/*   Updated: 2022/09/10 01:21:53 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** THIS IS A DEBUGGING FUNCTION
** prints the tokens. Yup. With printf.
*/
int	print_token_list(t_ms_data *ms)
{
	int	ret;
	t_tokens *temp;

	ret = 0;
	temp = ms->tokens;
	while (temp)
	{
		printf ("<: %p\n", temp->prev);
		printf ("v: %p\n", temp);
		printf (">: %p\n", temp->next);
		ret += printf ("v: %s\n", temp->value);
		printf ("t: %d\n", temp->type);
		printf ("\n------------------\n");
		temp = temp->next;
	}
	// printf ("total printed: %d\n", ret);
	// sleep(5);
	return (ret);
}

/*
** THIS IS A DEBUGGING FUNCTION
** sets state to state to -1 and returns the number of fucked up shit you've got
** if all goes well, it'll continue to execute
*/
int	check_for_some_shady_shit(t_ms_data *ms)
{
	int	shaddy_shit_has_happened;

	shaddy_shit_has_happened = 0;
	if (!ms->tokens)
	{
		ms->state = -1;
		shaddy_shit_has_happened++;
	}
	if (!ms->rl_prompt)
	{
		ms->state = -1;
		shaddy_shit_has_happened++;
	}
	if (!ms->env_head)
	{
		ms->state = -1;
		shaddy_shit_has_happened++;
	}
	return (shaddy_shit_has_happened);
}

/*
** executes the parsed and categorized commands
*/
int	exec_state(t_ms_data *ms, char **envp)
{
	if (check_for_some_shady_shit(ms))
		return (-1);
	ms->exit_code = exec_MVP_TESTE(ms, envp);
	// print_token_list(ms);
	ms->state = CLEANSTATE;
	return (0);
}

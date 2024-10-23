/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:53:35 by ttero             #+#    #+#             */
/*   Updated: 2024/10/23 20:35:48 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int check_errors(t_token *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next != NULL)
	{
		if (lst ->type > 3)
		{
			if (lst->next == NULL || lst->next->type > 3)
			{
				printf("syntax error near unexpected token, %s", lst->str);
			}
		}
		lst = lst->next;
	}
	return (1);

}

int reg(char *str)
{
	if (str[0] == '\0')
		return (EMPTY);
	else if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APPEND);
		return (OUTPUT);
	}
	else if (str[0] == '<')
	{
		if (str[1] == '<')
			return (HEREDOC);
		return (INPUT);
	}
	else if (str[0] == '-')
		return (DASH);
	else if (str[0] == '|')
		return (PIPE);
	else
		return (ARG);
}

int	set_types(t_token *lst)
{

	if (lst == 0)
		return (0);
	while (lst->next != NULL)
	{
		lst->type = reg(lst->str);
		lst = lst->next;
	}
	return (1);
}


int	count_pipes (t_token *lst)
{
	int i;

	i = 0;
	if (lst == 0)
		return (0);
	while (lst->next != NULL)
	{
		if (lst ->type == PIPE)
			i++;
		lst = lst->next;
	}
	return (i);
}


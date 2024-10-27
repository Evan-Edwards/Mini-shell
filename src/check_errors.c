/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:32:47 by ttero             #+#    #+#             */
/*   Updated: 2024/10/27 12:32:49 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int check_errors(t_token *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next != NULL)
	{
        if (lst ->type >= 4)
		{
            if (lst->next == NULL || lst->next->type >= 3)
			{
				printf("syntax error near unexpected token, %s\n", lst->content);
                return (0);
			}
		}
		lst = lst->next;
	}
    return (1);
}
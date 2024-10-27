/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:58:48 by eedwards          #+#    #+#             */
	/*   Updated: 2024/10/27 13:18:11 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free memory before calling
void	ft_perror_close(char *perror_message)
{
	perror(perror_message);
	exit(EXIT_FAILURE);
}

//is it necessary?
//free memory before calling
void	ft_error_close(char **arg, t_mini *mini, char **envp)
{
	if (arg)
		free_str_array(arg);
	if (envp)
		free_str_array(envp);
	free_mini(mini);
	exit(EXIT_FAILURE);
}

//free memory before calling
//CAN HANDLE MORE ARGS TO FREE?
void	ft_close(char *input, t_mini *mini, char **envp)
{
	if (input)
		free(input);
	if (envp)
		free_str_array(envp);
	free_mini(mini);
	exit(EXIT_SUCCESS);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:04:57 by ttero             #+#    #+#             */
/*   Updated: 2024/10/25 19:50:13 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int number_of_arguments (t_token *lst)
{
	int i;

	i = 0;
    while (lst->next != NULL && lst->type != PIPE)
	{
		if (lst->type >= 3)
		{
			lst->next->type = 3;
            lst = lst->next;
		}
        else
        {
            i++;
        }
		if (lst->next != NULL)
            lst = lst->next;
	}
    if (lst->type <= 2)
        i++;
    return (i);
}

char **build_exe (t_token *lst)
{
    int arg_num;
    char **arg_array;
    int i;

    i = 0;
    arg_num = number_of_arguments(lst);
    arg_array = malloc(sizeof(char*) * (arg_num +1));
    while (lst->next != NULL && lst->type != PIPE)
	{
		if (lst->type >= 3)
		{
			lst->next->type = 3;
            lst = lst->next;
		}
        else
        {
            arg_array[i] = lst->content;
            i++;
        }
		if (lst->next != NULL)
            lst = lst->next;
	}
    if (lst->type <= 2)
        {
            arg_array[i] = lst->content;
            i++;
        }
    arg_array[i] = 0;
    return (arg_array);
}

void print_array(char **arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        printf("%s\n", arg[i]);
        i++;
    }
    printf("%s\n", arg[i]);
}

int is_buildin(char *arg)
{
    if (strcmp(arg, "echo") == 0)
        return (1);
    if (strcmp(arg, "cd") == 0)
        return (1);
    if (strcmp(arg, "pwd") == 0)
        return (1);
    if (strcmp(arg, "export") == 0)
        return (1);
    if (strcmp(arg, "unset") == 0)
        return (1);
    if (strcmp(arg, "env") == 0)
        return (1);
    if (strcmp(arg, "exit") == 0)
        return (1);
    return (0);
}

int file_in (t_token *lst)
{
	int i;
	int file_fd;

	i = 0;
	file_fd = -1;

	while (lst->next != NULL && lst->type != PIPE)
	{
		if (lst->type == 4)
		{
			file_fd = input_file(lst->type, lst->next->content);
            if (file_fd < 0)
                return (-1);
		}
		lst = lst->next;
	}
	if (file_fd != -1)
		dup2(file_fd, STDIN_FILENO);
	return (1);
}

int file_out (t_token *lst)
{
	int i;
	int file_fd;

	i = 0;
	file_fd = -1;

	while (lst->next != NULL && lst->type != PIPE)
	{
		if (lst->type >= 6)
		{
			file_fd = output_file(lst->type, lst->next->content);
            if (file_fd < 0)
                return (-1);
		}
		lst = lst->next;
	}
	if (file_fd != -1)
		dup2(file_fd, STDOUT_FILENO);
	return (1);
}


int distribute(t_mini *mini, char **envp)
{
    int number_of_commands;
    int i;
    char **arg;
    int file_fd;
    char *path;

     file_fd = -1;
    if (file_in(mini->lst) < 0)
        {
            printf("error\n");
            return (0);
        }
    file_fd = file_out(mini->lst);
    if (file_fd < 0)
    {
        printf("error\n");
        return (0);
    }
    //printf("%d\n", file_fd);
    number_of_commands =number_of_arguments(mini->lst);
    i = 0;
    arg = build_exe(mini->lst);
    if (is_buildin(arg[i]) == 1)
    {
        printf("buildin");
        //buildin(arg, mini, env);
    }
     else
    {
        exe(arg, mini, envp);
    }
    /* while (i < number_of_commands)
    {

    } */
   return (1);
}

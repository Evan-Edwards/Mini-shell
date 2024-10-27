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
			i++;
		if (lst->next != NULL)
			lst = lst->next;
	}
	if (lst->type <= 2)
		i++;
	return (i);
}

//This function builds an array of strings (char) from the linked list of tokens
//It allocates memory for the array and copies the content of tokens with type
//ARG, EMPTY, or DASH (2 or lower) into the array.
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
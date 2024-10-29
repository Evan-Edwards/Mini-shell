/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_env_new_try.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:58:52 by eedwards          #+#    #+#             */
/*   Updated: 2024/10/29 19:46:25 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Utility Functions */

// Function to check if a character is a valid variable name character
int is_valid_char(char c)
{
    if (c == '_')
        return (1);
    if (c >= 'a' && c <= 'z')
        return (1);
    if (c >= 'A' && c <= 'Z')
        return (1);
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

// Function to get the length of the variable name
int get_var_len(char *str)
{
    int i;

    i = 0;
    while (is_valid_char(str[i]))
    {
        i++;
    }
    return (i);
}

// Function to expand a single variable
char *expand_variable(char *var_name, t_mini *mini)
{
    int k;
    size_t var_name_len;
    char *env_entry;

    k = 0;
    var_name_len = strlen(var_name);
    while (mini->envp[k])
    {
        env_entry = mini->envp[k];
        if (strncmp(env_entry, var_name, var_name_len) == 0 
            && env_entry[var_name_len] == '=')
        {
            return (strdup(env_entry + var_name_len + 1));
        }
        k++;
    }
    return (strdup(""));
}

/* Helper Functions */

/**
 * Ensures that the buffer has enough capacity to add 'additional' characters.
 * If not, reallocates the buffer to increase its capacity.
 *
 * @param buffer Pointer to the buffer.
 * @param current_size Pointer to the current allocated size of the buffer.
 * @param j Current position in the buffer.
 * @param additional Number of additional characters to accommodate.
 * @return 0 on success, -1 on failure.
 */
static int ensure_buffer_capacity(char **buffer, int *current_size, int j, int additional)
{
    if (j + additional >= *current_size)
    {
        int new_size = (*current_size) * 2 + additional;
        char *new_buffer = realloc(*buffer, new_size);
        if (!new_buffer)
            return (-1);
        *buffer = new_buffer;
        *current_size = new_size;
    }
    return (0);
}

/**
 * Copies a single character into the expanded buffer, ensuring enough capacity.
 *
 * @param c The character to copy.
 * @param expanded The buffer to copy into.
 * @param j Pointer to the current position in the buffer.
 * @param buffer_size Pointer to the current allocated size of the buffer.
 * @return 0 on success, -1 on failure.
 */
static int copy_literal_char(char c, char **expanded, int *j, int *buffer_size)
{
    if (ensure_buffer_capacity(expanded, buffer_size, *j, 1) == -1)
        return (-1);
    (*expanded)[(*j)++] = c;
    return (0);
}

/**
 * Appends a string to the expanded buffer, ensuring enough capacity.
 *
 * @param str The string to append.
 * @param expanded The buffer to append to.
 * @param j Pointer to the current position in the buffer.
 * @param buffer_size Pointer to the current allocated size of the buffer.
 * @return 0 on success, -1 on failure.
 */
static int append_string(const char *str, char **expanded, int *j, int *buffer_size)
{
    int len = strlen(str);
    if (ensure_buffer_capacity(expanded, buffer_size, *j, len) == -1)
        return (-1);
    strcpy(&(*expanded)[*j], str);
    *j += len;
    return (0);
}

/**
 * Appends the expanded variable to the result string.
 *
 * @param var_name The name of the variable to expand.
 * @param expanded The buffer to append to.
 * @param j Pointer to the current position in the buffer.
 * @param buffer_size Pointer to the current allocated size of the buffer.
 * @param mini The shell's state containing environment variables.
 * @return 0 on success, -1 on failure.
 */
static int append_expanded_variable(char *var_name, char **expanded, int *j, int *buffer_size, t_mini *mini)
{
    char *expanded_var = expand_variable(var_name, mini);
    if (!expanded_var)
        return (-1);
    if (append_string(expanded_var, expanded, j, buffer_size) == -1)
    {
        free(expanded_var);
        return (-1);
    }
    free(expanded_var);
    return (0);
}

/**
 * Extracts the variable name starting after the current index.
 *
 * @param input The input string.
 * @param i Pointer to the current index in the input string.
 * @return The extracted variable name, or NULL on failure.
 */
static char *extract_var_name(char *input, int *i)
{
    int var_len;
    char *var_name;

    var_len = get_var_len(&input[*i + 1]);
    if (var_len == 0)
        return (NULL);
    var_name = malloc(var_len + 1);
    if (!var_name)
        return (NULL);
    strncpy(var_name, &input[*i + 1], var_len);
    var_name[var_len] = '\0';
    *i += var_len + 1; // Move index past the variable name and '$'
    return (var_name);
}

/**
 * Handles variable expansion based on the current quotation context.
 *
 * @param input The input string.
 * @param i Pointer to the current index in the input string.
 * @param expanded The buffer to append to.
 * @param j Pointer to the current position in the buffer.
 * @param buffer_size Pointer to the current allocated size of the buffer.
 * @param mini The shell's state containing environment variables.
 * @param quote_state The current quote state (0: none, 1: single, 2: double).
 * @return 0 on success, -1 on failure.
 */
static int handle_variable_expansion(char *input, int *i, char **expanded, int *j, int *buffer_size, t_mini *mini, int quote_state)
{
    char *var_name;

    if (input[*i + 1] == '?')
    {
        // Handle special variable $? (exit status)
        char exit_status_str[12]; // Enough for 32-bit int
        snprintf(exit_status_str, sizeof(exit_status_str), "%d", mini->exit_status);
        if (append_string(exit_status_str, expanded, j, buffer_size) == -1)
            return (-1);
        *i += 2; // Skip past '?'
        return (0);
    }

    if (!is_valid_char(input[*i + 1]))
    {
        // Not a valid variable name character, copy '$' literally
        if (copy_literal_char('$', expanded, j, buffer_size) == -1)
            return (-1);
        (*i)++;
        return (0);
    }

    var_name = extract_var_name(input, i);
    if (!var_name)
    {
        // Extraction failed, copy '$' literally
        if (copy_literal_char('$', expanded, j, buffer_size) == -1)
            return (-1);
        return (0);
    }

    if (quote_state == 2 || quote_state == 0)
    {
        // Inside double quotes or unquoted: expand the variable
        if (append_expanded_variable(var_name, expanded, j, buffer_size, mini) == -1)
        {
            free(var_name);
            return (-1);
        }
    }
    else
    {
        // Inside single quotes: copy '$' and the variable name literally
        if (copy_literal_char('$', expanded, j, buffer_size) == -1)
        {
            free(var_name);
            return (-1);
        }
        for (int k = 0; var_name[k]; k++)
        {
            if (copy_literal_char(var_name[k], expanded, j, buffer_size) == -1)
            {
                free(var_name);
                return (-1);
            }
        }
    }
    free(var_name);
    return (0);
}

/**
 * Processes quotes and expands variables in the input string.
 *
 * @param input The input string.
 * @param expanded The buffer to append to.
 * @param j Pointer to the current position in the buffer.
 * @param buffer_size Pointer to the current allocated size of the buffer.
 * @param mini The shell's state containing environment variables.
 * @return 0 on success, -1 on failure.
 */
static int process_quotes_and_expand(char *input, char **expanded, int *j, int *buffer_size, t_mini *mini)
{
    int i = 0;
    int len = strlen(input);
    int quote_state = 0; // 0: no quotes, 1: single quotes, 2: double quotes

    while (i < len)
    {
        if (input[i] == '\'' && quote_state != 2)
        {
            // Toggle single quote state
            quote_state = (quote_state == 1) ? 0 : 1;
            i++;
            continue;
        }
        else if (input[i] == '"' && quote_state != 1)
        {
            // Toggle double quote state
            quote_state = (quote_state == 2) ? 0 : 2;
            i++;
            continue;
        }

        if (input[i] == '$' && (quote_state == 0 || quote_state == 2))
        {
            // Handle variable expansion
            if (handle_variable_expansion(input, &i, expanded, j, buffer_size, mini, quote_state) == -1)
                return (-1);
        }
        else
        {
            // Copy character literally
            if (copy_literal_char(input[i], expanded, j, buffer_size) == -1)
                return (-1);
            i++;
        }
    }
    return (0);
}

/* Main Function */

/**
 * Expands environmental variables in the input string.
 *
 * @param input The input string to expand.
 * @param mini The shell's state containing environment variables.
 * @return A newly allocated expanded string on success, NULL on failure.
 */
char *env_var_expansion(char *input, t_mini *mini)
{
    char *expanded;
    int j;
    int initial_size = 1024; // Starting with a reasonable buffer size

    // Allocate initial buffer
    expanded = malloc(initial_size);
    if (!expanded)
        return (NULL);
    j = 0;

    if (process_quotes_and_expand(input, &expanded, &j, &initial_size, mini) == -1)
    {
        free(expanded);
        return (NULL);
    }

    // Null-terminate the expanded string
    if (ensure_buffer_capacity(&expanded, &initial_size, j, 1) == -1)
    {
        free(expanded);
        return (NULL);
    }
    expanded[j] = '\0';
    return (expanded);
}
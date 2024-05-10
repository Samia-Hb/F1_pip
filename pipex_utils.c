/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:23:19 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/10 10:19:28 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_counter(char *str, char c)
{
	int	i;
	int	word_counter;

	i = 0;
	word_counter = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			word_counter++;
			while (str[i + 1] == c)
			{
				i++;
			}
		}
		i++;
	}
	if (str[0] != c && str[ft_strlen(str) - 1] != c)
		word_counter++;
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		word_counter--;
	return (word_counter);
}

void remove_string(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void    ft_clean (char **arr1, char **arr2)
{
	free(arr1);
	free(arr2);
}

int check_full_command(char *cmd)
{
    if (cmd[0] == 39 && cmd[strlen(cmd) - 1] == 39)
		return (-4);
		
	return (1);
}

char    **arr(char *cmd)
{
    int     arr_count;
    int     i;
    char    **arr;
    char    **new_arr;

    arr = ft_split(cmd,' ');
    i = 0;
    arr_count = 0;
    check_cmds(arr);
    while (arr[arr_count] != NULL)
        arr_count++;
    new_arr = malloc((arr_count + 2) * sizeof(char *));
    if (new_arr == NULL)
    {
        perror("malloc");
        exit(1);
    }
    while (i < arr_count)
    {
        new_arr[i] = arr[i];
        i++;
    }
    new_arr[arr_count] = NULL;
    return (new_arr);
}









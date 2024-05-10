/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:21:26 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/08 13:55:47 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_clean (char **arr1, char **arr2)
{
	free(arr1);
	free(arr2);
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


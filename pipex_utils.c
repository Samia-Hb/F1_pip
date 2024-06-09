/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:23:19 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/20 10:02:04 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_counter(char *str, char c) //work
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

void	remove_string(char **str) //work
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_full_command(char *cmd) //work
{
	if (cmd[0] == 39 && cmd[strlen(cmd) - 1] == 39)
		return (-4);
	return (1);
}

char	**arr(char *cmd) //work
{
	int		arr_count;
	int		i;
	char	**arr;
	char	**new_arr;

	arr = ft_split(cmd, ' ');
	i = 0;
	arr_count = 0;
	check_cmds(arr);
	while (arr[arr_count] != NULL)
		arr_count++;
	new_arr = malloc((arr_count + 2) * sizeof(char *));
	if (!new_arr)
	{
		free(arr);
		exit(1);
	}
	while (i < arr_count)
	{
		new_arr[i] = arr[i];
		i++;
	}
	free(arr);
	new_arr[arr_count] = NULL;
	return (new_arr);
}

void	execute_commands(char **argv, char **envp)
{
	int	pipefd[2];
	int	pid1;
	int	pid2;

	if (pipe(pipefd) == -1)
		return (perror("pipe"));
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork"));
	else if (pid1 == 0)
		execute_cmd1(pipefd[0], pipefd[1], argv, envp);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			return (perror("fork"));
		else if (pid2 == 0)
			execute_cmd2(pipefd[0], pipefd[1], argv, envp);
		else
			norm(pipefd[0], pipefd[1], pid1, pid2);
	}
}

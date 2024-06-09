/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:29:39 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/20 15:58:52 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**empty_case(char **arr) //work
{
	if (!arr[0])
	{
		free(arr);
		arr = malloc(2 * sizeof(char *));
		arr[0] = ft_strdup(" ");
		arr[1] = NULL;
	}
	return (arr);
}

void	first_part(char *infile, char **arr2, char *cmd2, char **envp) //done
{
	char	*result;

	ft_printf("zsh: no such file or directory: %s\n", infile);
	if (check_full_command(cmd2) == -4 && ft_counter(cmd2, ' ') > 1)
		ft_printf("zsh: command not found: %s\n", ft_strtrim(cmd2, "'"));
	result = get_executable(arr2[0], find_path(envp));
	if (!result)
		ft_printf("zsh: command not found: %s\n", arr2[0]);
	if (result)
		free(result);
}

void	second_part(char *cmd1, char *cmd2, char **envp, int *count) //done
{
	char	*result;
	char	**arr1;
	char	**arr2;

	arr1 = ft_split(cmd1, ' ');
	arr2 = ft_split(cmd2, ' ');
	arr1 = empty_case(arr1);
	arr2 = empty_case(arr2);
	result = get_executable(arr1[0], find_path(envp));
	if (check_full_command(cmd1) == -4 && ft_counter(cmd1, ' ') > 1)
		ft_printf("zsh: command not found: %s\n", ft_strtrim(cmd1, "'"));
	else if (result == NULL)
		ft_printf("zsh: command not found: %s\n", arr1[0]);
	free(result);
	result = get_executable(arr2[0], find_path(envp));
	if (check_full_command(cmd2) == -4 && ft_counter(cmd2, ' ') > 1)
		ft_printf("zsh: command not found: %s\n", ft_strtrim(cmd2, "'"));
	else if (result == NULL)
		ft_printf("zsh: command not found: %s\n", arr2[0]);
	if (result)
		free(result);
	remove_string(arr1);
	remove_string(arr2);
	*count = 0;
}

int	check_param(char *infile, char *cmd1, char *cmd2, char **envp)
{
	int		count;
	char	*result1;
	char	*result2;
	char	**arr1;
	char	**arr2;

	count = 1;
	arr2 = ft_split(cmd2, ' ');
	arr1 = ft_split(cmd1, ' ');
	arr1 = empty_case(arr1);
	arr2 = empty_case(arr2);
	result1 = get_executable(arr1[0], find_path(envp));
	result2 = get_executable(arr2[0], find_path(envp));
	if (access(infile, F_OK) != 0)
	{
		first_part(infile, arr2, cmd2, envp);
		count = 0;
	}
	else if (!result1 || !result2)
		second_part(cmd1, cmd2, envp, &count);
	remove_string(arr1);
	remove_string(arr2);
	free(result1);
	free(result2);
	return (count);
}

int	main(int argc, char **argv, char **envp) //work
{
	if (!envp)
		return (0);
	if (argc == 5)
	{
		if (!check_param(argv[1], argv[2], argv[3], envp))
			return (0);
		execute_commands(argv, envp);
	}
	else
		ft_printf("zsh: parse error near `\\n' \n");
	return (0);
}

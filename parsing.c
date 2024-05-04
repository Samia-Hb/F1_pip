/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:16:09 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/04 01:04:58 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void remove_string(char **str)
{
	int i;

	i = 0;
	while(str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void    check_cmds(char **arr)
{
    int     i;
    char    cmp;

    i = 0;
    cmp = 39;
    while (arr[i] != NULL)
    {
        if (arr[i][0] == cmp)
            arr[i] = ft_strtrim(arr[i], "'");
        i++;
    }
}

int check_full_command(char *cmd)
{
    if (cmd[0] == 39 && cmd[strlen(cmd) - 1] == 39)
        return (-4);
    return (1);
}

char *get_executable(char *command, char *path)
{
    int		i;
    char	*full_path;
    char	**dir;

    i = 0;
    dir = ft_split(path, ':');
	if (access(command, X_OK) == 0)
		return (command);
    while (dir[i])
    {
        full_path = malloc(strlen(dir[i]) + strlen(command) + 2);
        if (full_path == NULL)
        {
            perror("malloc");
        	exit(1);
        }
		full_path = ft_strjoin(dir[i], "/", command);
        if (access(full_path, X_OK) == 0)
            break;
        free(full_path);
        i++;
    }
    if(dir[i] != NULL)
	{
		remove_string(dir);
        return (full_path);
	}
	remove_string(dir);
	return (NULL);
}

char	*find_path(char **envp)
{
	char	*path_env;
	int		i;

	path_env = NULL;
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path_env);
}

int	check_param(char *infile, char *cmd1, char *cmd2, char **envp)
{
	int		count;
	char	**arr1;
	char	**arr2;

	count = 0;
    arr1 = ft_split(cmd1, ' ');
    arr2 = ft_split(cmd2, ' ');
    if (access(infile,F_OK) != 0)
    {
		if (check_full_command(cmd2) == -4 && ft_counter(cmd2, ' ') > 1)
			ft_printf("zsh: command not found: %s\n", ft_strtrim(cmd2,"'"));
		if (get_executable(arr2[0], find_path(envp)) == NULL)
        	ft_printf("zsh: command not found: %s\n", arr2[0]);
	}
	//else
	//{
			if (check_full_command(cmd2) == -4 && ft_counter(cmd2, ' ') > 1)
				ft_printf("zsh: command not found: %s\n",  ft_strtrim(cmd2, "'"));
			if(get_executable(ft_strtrim(arr2[0], "'"), find_path(envp)) == NULL)
    			ft_printf("zsh: command not found: %s\n", ft_strtrim(arr2[0], "'"));
			else if (check_full_command(cmd1) == -4 && ft_counter(cmd1, ' ') > 1)
				ft_printf("zsh: command not found: %s\n", ft_strtrim(cmd1, "'"));
			else if (get_executable(ft_strtrim(arr1[0], "'"), find_path(envp)) == NULL)
        		ft_printf("zsh: command not found: %s\n", ft_strtrim(arr1[0], "'"));
	//}
			else
				count = 1; 
	ft_clean(arr1,arr2);
	return(count);
}

int check_command(char *cmd)
{
	char **arr = ft_split(cmd, ' ');

	if (access(arr[0], X_OK ) == 0)
	{
		free(arr);
		return (1);
	}
	free(arr);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
	{
		char	**arr1 ;
		char	**arr2;
		
		arr1 = ft_split(argv[2], ' ');
		arr2 = ft_split(argv[3], ' ');
		check_cmds(arr1);
		check_cmds(arr2);
		if(check_param(argv[1], argv[2], argv[3], envp) == 0)
		{
			remove_string(arr1);
			remove_string(arr2);
			return (0);
		}
		execute_commands(argv[2], argv[3], argv[1], argv[4], envp);
		remove_string(arr1);
		remove_string(arr2);
	}
	else
		ft_printf("zsh: parse error near `\\n' \n");
	return (0);
}
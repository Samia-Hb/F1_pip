/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:16:09 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/10 12:22:15 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
	////////parsing

void	check_cmds(char **arr) //done
{
    int		i;
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

char	*find_path(char **envp)
{
	char	*path_env;
	int		i;
	
	if(!envp)
		return (0);
	path_env = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path_env);
}

int check_command(char *cmd)
{
	char **arr = ft_split(cmd, ' ');

	if (access(arr[0], X_OK ) == 0)
	{
		remove_string(arr);
		return (1);
	}
	remove_string(arr);
	return (0);
}

char *get_executable(char *command, char *path)
{
    int		i;
    char	*full_path;
    char	**dir;

    i = 0;
    dir = ft_split(path, ':');
	if (access(command, X_OK) == 0)
	{
		remove_string(dir);
		return (command);
	}
	while (dir[i])
    {
        full_path = malloc(strlen(dir[i]) + strlen(command) + 2);
        if (!full_path)
        {
            perror("malloc");
			remove_string(dir);
        	exit (1);
        }
		sprintf(full_path, "%s/%s", dir[i], command);
        if (access(full_path, X_OK) == 0)
        {
            remove_string(dir);
            return full_path;
        }
        free(full_path); // Free full_path if not found
        i++;
    }
	remove_string(dir);
	return (NULL);
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
		ft_printf("zsh: no such file or directory: %s\n", infile);
		if (ft_strlen(cmd2) == 0 || ft_counter(cmd2,' ') == 0)
			ft_printf("zsh: permissionn denied:\n");
		else if (check_full_command(cmd2) == -4 && ft_counter(cmd2, ' ') > 1)
			ft_printf("zsh: command not found: %s\n", ft_strtrim(cmd2,"'"));
		if (get_executable(arr2[0], find_path(envp)) == NULL)
        	ft_printf("zsh: command not found: %s\n", arr2[0]);
	}
	else
	{
		//check_first_command
		if (ft_strlen(cmd1) == 0 || ft_counter(cmd1,' ') == 0)
			ft_printf("zsh: permissionn denied:\n");
		else if (check_full_command(cmd1) == -4 && ft_counter(cmd1, ' ') > 1)
			ft_printf("zsh: command not found: %s\n", ft_strtrim(cmd1, "'"));
		else if (get_executable(ft_strtrim(arr1[0], "'"), find_path(envp)) == NULL)
			ft_printf("zsh: command not found: %s\n", ft_strtrim(arr1[0], "'"));
		//check_second_command
		if (ft_strlen(cmd2) == 0 || ft_counter(cmd2,' ') == 0)
			ft_printf("zsh: permissionn denied:\n");
		else if (check_full_command(cmd2) == -4 && ft_counter(cmd2, ' ') > 1)
			ft_printf("zsh: command not found: %s\n",  ft_strtrim(cmd2, "'"));
		else if (get_executable(ft_strtrim(arr2[0], "'"), find_path(envp)) == NULL)
			ft_printf("zsh: command not found: %s\n", ft_strtrim(arr2[0], "'"));
		else
			count = 1;
	}
	remove_string(arr1);
	remove_string(arr2);
	return(count);
}


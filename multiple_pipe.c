/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:20:07 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/11 14:41:40 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct map
{
	int		height;
	int		width;
	char	**map;
}			t_map;

void	calcul_height(int fd, t_map *map)
{
	char	*str;

	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		map->height++;
		free(str);
	}
}

void	delete_line(t_map *map, int pos)
{
	int	i;

	i = pos;
	free(map->map[pos]);
	while (i < map->height - 1)
	{
		map->map[i] = map->map[i + 1];
		i++;
	}
	map->height--;
}

void	check_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height - 1)
	{
		j = i + 1;
		while (j < map->height)
		{
			if (!strcmp(map->map[i], map->map[j]))
			{
				delete_line(map, j);
				j--;
			}
			j++;
		}
		i++;
	}
}

void get_2d_array(t_map *map, int fd_read)
{
    int m;
    char *str;

	m = 0;
    map->map = malloc((map->height + 1) * sizeof(char *));
    if (!map->map)
		return;
    while ((str = get_next_line(fd_read)) != NULL)
	{
        map->map[m] = strdup(str);
        if (!map->map[m])
		{
            free(str);
            return;
        }
        free(str);
        m++;
    }
    map->map[m] = NULL;
}

void parsing(int argc, char **argv, char **envp)
 {
    t_map *map;
    int fd[2];
    int saved_stdout;
    int i;

    map = malloc(sizeof(t_map));
    if (!map) 
		return;
    map->height = 0;
    if (pipe(fd) == -1)
	{
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    saved_stdout = dup(STDOUT_FILENO);
    if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd[1]);
	i = 3;
	while(i < argc - 1)
	{
        check_param(argv[1], argv[i - 1], argv[i], envp);
		if(i == argc - 1)
			break;
		i++;
    }
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    calcul_height(fd[0], map);
    close(fd[0]);
    if (pipe(fd) == -1)
	{
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    saved_stdout = dup(STDOUT_FILENO);
    if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd[1]);
	i = 3;
    while (i < argc)
	{
        check_param(argv[1], argv[i - 1], argv[i], envp);
		if(i == argc - 1)
			break;
		i++;
    }
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    get_2d_array(map, fd[0]);
    close(fd[0]);
    check_map(map);
	i = 0;
    while (i < map->height)
	{
		write(1, map->map[i],ft_strlen(map->map[i]));
        free(map->map[i]);
		i++;
    }
    free(map->map);
    free(map);
}
/////////////////Execute command
char	*execute_command(int argc, char **argv, char **envp)
{
	int	pipe_fd[pow(2, )];
	int	fd;
	int	pid = fork();
	if(pid == 0)
		execute_cmd1(pipe_fd[0], pipe_fd[1], argv, envp);
	else if(pid > 0)
		execute_cmd2(pipe_fd[0],pipe_fd[1], argv, envp);
	else
		perror("Error\n");
	fd = open(argv[1], O_RDWR, 0777);
	if (fd == -1)
		return (NULL);	
}
void	multiple_pipe(int argc, char **argv, char **envp)
{
	
	parsing(argc, argv, envp);
	printf("command number = %d\n", argc - 3);
	execute_command(argc, argv, envp);
	argc--;
}
//pipe_nbr = argc - 4
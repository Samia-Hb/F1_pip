#include "pipex.h"

typedef struct map
{
	int height;
	int width;
	char **map;
}t_map;

void calcul_height(int fd, t_map *map)
{
	char *str;

	while (1)
	{
		str = get_next_line(fd);
		if(!str)
			break;
		map->height++;
		free(str);
	}
}
void delete_line(t_map *map, int pos)
{
	int i = 0;
	int j = 0;
	while (i < )
	{

	}
}
void check_map(t_map *map)
{
	int i;
	int j = 0;
	int k = 0;

	while (i < map->height - 2)
	{
		j = i + 1;
		while(j < map->height - 1)
		{
			if (strcmp(map->map[i], map->map[j]))
			{
				delete_line(map, j);
			}
			j++;
		}
	}
}

void parsing(char **argc, char **argv, char **envp)
{
	t_map *map;
	int pip ;
	int i;
	int fd[2];
	int j;
	int m = 0;
	int n = 0;
	char *str;

	i = 3;

	t_map *map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = 0;
	int k = pipe(fd);
	if(k == -1)
	{
		ft_printf("Error : something got wrong with the pipe");
		exit(1);
	}
	dup2(fd[1] , STDOUT_FILENO);
	calcul_height(fd[1], map);
	while (i < argc - 1)
	{
		j = i - 1;
		check_param(argv[1], argv[j], argv[i],envp);
		i++;
	}
	map->map = malloc(map->height + 1);
	if(!map->map)
		return (NULL);
	while(1)
	{
		str = get_next_line(fd[1]);
		if (!str)
			break;
		map->map[m] = malloc(ft_strlen(str) + 1);
		if (!map->map[m])
			return (NULL);
		while (m < map->height)
		{
			n = 0;
			while (n < ft_strlen(str))
			{ 
				map->map[m][n] = str[n];
				n++;
			}
			map->map[m][n] = '\0';
		}
	}
	check_map(map);
}
void	multiple_pipe(int argc,char **argv, char **envp)
{
	int i ;
	int j ;

	i = 3;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:35:00 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/20 10:02:06 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_empty_cmd1(char *infile)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY, 0777);
	if (infile_fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	return ;
}

void	execute_cmd1(int pipe_fd_0, int pipe_fd_1, char **argv, char **envp)
{
	int		infile_fd;
	char	**new_arr;
	char	*command_path;

	if (!ft_counter(argv[2], ' ') || !ft_strlen(argv[2]))
		return (execute_empty_cmd1(argv[1]));
	close(pipe_fd_0);
	dup2(pipe_fd_1, STDOUT_FILENO);
	close(pipe_fd_1);
	infile_fd = open(argv[1], O_RDONLY, 0777);
	if (infile_fd == -1)
		exit(1);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	new_arr = arr(argv[2]);
	command_path = get_executable(new_arr[0], find_path(envp));
	if (execve(command_path, new_arr, envp) == -1)
	{
		perror("execve");
		free(command_path);
		remove_string(new_arr);
		exit(1);
	}
	remove_string(new_arr);
}

void	execute_empty_cmd2(char *outfile, int pipe_fd_0)
{
	int	outfile_fd;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(pipe_fd_0, STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(pipe_fd_0);
	close(outfile_fd);
	return ;
}

void	execute_cmd2(int pipe_fd_0, int pipe_fd_1, char **argv, char **envp)
{
	int		outfile_fd;
	char	**new_arr;
	char	*command_path;

	if (!ft_counter(argv[3], ' ') || !ft_strlen(argv[3]))
		return (execute_empty_cmd2(argv[4], pipe_fd_0));
	close(pipe_fd_1);
	dup2(pipe_fd_0, STDIN_FILENO);
	close(pipe_fd_0);
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		exit(1);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	new_arr = arr(argv[3]);
	command_path = get_executable(new_arr[0], find_path(envp));
	if (execve(command_path, new_arr, envp) == -1)
	{
		perror("execve");
		free(command_path);
		remove_string(new_arr);
		exit(1);
	}
	remove_string(new_arr);
}

void	norm(int pipe_fd_0, int pipe_fd_1, int pid1, int pid2)
{
	close(pipe_fd_0);
	close(pipe_fd_1);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

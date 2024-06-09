/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:23:19 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/09 15:33:00 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

char	*get_executable(char *command, char *path);
char	*find_path(char **envp);
void	execute_cmd2(int pipe_fd_0, int pipe_fd_1, char **argv, char **envp);
void	check_cmds(char **arr);
void	execute_cmd1(int pipe_fd_0, int pipe_fd_1, char **argv, char **envp);
void	execute_commands(char **argv, char **envp);
char	**arr(char *cmd);
void	remove_string(char **str);
int		check_param(char *infile, char *cmd1, char *cmd2, char **envp);
int		check_full_command(char *cmd);
void	norm(int pipe_fd_0, int pipe_fd_1, int pid1, int pid2);
void	multiple_pipe(int argc,char **argv, char **envp);
#endif

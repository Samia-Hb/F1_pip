// char *get_executable(char *command, char *path)
// {
//     int  i;
//     char *full_path;
//     char **dir;

//     i = 0;
//     dir = ft_split(path,':');
    
//     while (dir[i])
//     {
//         full_path = malloc(strlen(dir[i]) + strlen(command) + 2);
//         if(full_path == NULL)
//         {
//             perror("malloc");
//         	exit(1);
//         }
//         strcpy(full_path, dir[i]);
//         strcat(full_path, "/");
//         strcat(full_path, command);
//         if (access(full_path, X_OK) == 0)
//             break;
//         free(full_path);
//         i++;
//     }
//     //free(dir);
//     if(dir[i])
//         return (full_path);
//     return (NULL);
// }


// char	*find_path(char **envp)
// {
// 	char	*path_env;
// 	int		i;

// 	path_env = NULL;
// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 		{
// 			path_env = envp[i] + 5;
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (path_env);
// }

// void	check_command(char *cmd)
// {
// 	char c = 39;;
// 	if (cmd[0] == c && cmd[ft_strlen(cmd) - 1] == c && ft_counter(cmd , ' ') > 1)
// 		ft_printf("zsh: command not found: %s\n", ft_strtrim(cmd, "'"));
// 	else if (((cmd[0] < 'a' && cmd[0] > 'z') || (cmd[0] < 'A' && cmd[0] > 'Z')) && cmd[1] == '"')
// 		ft_printf("zsh: command not found: %s\n",cmd);
// }

// int	main(int argc, char **argv,char **envp)
// {
// 	(void)(envp);
// 	if (argc == 5)
// 	{
// 		check_param(argv[1], argv[2], argv[3], envp);
// 		execute_commands(argv[2], argv[3], argv[1], argv[4], envp);
// 	}
// 	else{
// 		ft_printf("zsh: parse error near `\\n' ");
// 	}return 0;
// }
//=>"Redirect the standard output to the writing end of the pipe" means that the standard output of a process is set to write its output into the writing end of a pipe (pipefd[1])



// void check_param(char *infile, char *cmd1, char *cmd2, char **envp)
// {
// 	int     count;
// 	char    **arr1;
// 	char    **arr2;

//  check_command(cmd1);
// 	check_command(cmd2);
// 	count = 1;
// 	arr1 = ft_split(cmd1,' ');
// 	arr2 = ft_split(cmd2,' ');
// 	check_cmds(arr1);
// 	check_cmds(arr2);
// 	if (access(infile,F_OK) != 0)
// 	{
// 		ft_printf("zsh: no such file or directory: %s\n",infile);
// 		count = 0;
// 	}
// 	if (get_executable(arr2[0],find_path(envp)) == NULL)
// 	{
// 		ft_printf("zsh: command not found: %s\n", arr2[0]);
// 		if (count == 0)
// 		{
// 			ft_clean(arr1,arr2);        
// 			exit(0);
// 		}
// 	}
// 	if (get_executable(arr1[0],find_path(envp)) == NULL)
// 		ft_printf("zsh: command not found: %s\n", arr1[0]);
// 	ft_clean(arr1,arr2);
// }


// void    check_cmds(char **arr)
// {
//     int     i;
//     char    cmp;

//     i = 0;
//     cmp = 39;
//     while (arr[i] != NULL)
//     {
//         if (arr[i][0] == cmp)
//             arr[i] = ft_strtrim(arr[i], "'");
//         i++;
//     }
// }



// char *get_executable(char *command, char *path)
// {
//     int i;
//     char *full_path;
//     char **dir;
//     char *result = NULL;

//     i = 0;
//     dir = ft_split(path, ':');
//     if (access(command, X_OK) == 0)
//     {
//         remove_string(dir);
//         return (command);
//     }
//     while (dir[i])
//     {
//         full_path = malloc(strlen(dir[i]) + strlen(command) + 2);
//         if (!full_path)
//         {
//             perror("malloc");
//             remove_string(dir);
//             exit(1);
//         }
//         sprintf(full_path, "%s/%s", dir[i], command);
//         if (access(full_path, X_OK) == 0)
//         {
//             result = strdup(full_path);  // Make a copy of the path
//             break;
//         }
//         free(full_path);
//         i++;
//     }
//     remove_string(dir);
//     return result;
// }

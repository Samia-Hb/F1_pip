/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:29:39 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/10 10:24:00 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**arr1;
	char	**arr2;

	if (argc == 5)
	{
		arr1 = ft_split(argv[2], ' ');
		arr2 = ft_split(argv[3], ' ');
		check_cmds(arr1);
		check_cmds(arr2);
		if (check_param(argv[1], argv[2], argv[3], envp) == 0)
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

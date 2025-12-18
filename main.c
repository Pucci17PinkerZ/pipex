/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfiora-d <nfiora-d@student.42.f            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:18:34 by nfiora-d          #+#    #+#             */
/*   Updated: 2025/12/16 17:32:55 by nfiora-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipe;


	(void)envp;
	(void)ac;

	pipe.file1 = av[1];
	pipe.fd = open(pipe.file1, O_WRONLY, 0644);//potentiel bug pour le cas write_only
	if (pipe.fd == -1)
		return (1);
	pipe.fd2 = dup2(pipe.fd, 0);
	if (pipe.fd2 == -1)
		return (1);
	// path_check();
	
}

// char	*path_check(t_pipe *pipe, char **envp)
// {
// 	path_find();
// }

// int	path_find(t_pipe *pipe, char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
		
// 	}
// }

// Should behave like:
// $> ./pipex infile "grep a1" "wc -w" outfile
//		int dup2(int oldfd, int newfd);
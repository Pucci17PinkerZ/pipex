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


	// (void)envp;
	// (void)ac;

	pipe.file1 = av[1];
	pipe.fd = open(pipe.file1, O_WRONLY, 0644);//potentiel bug pour le cas write_only
	if (pipe.fd == -1)
		return (1);
	pipe.fd2 = dup2(pipe.fd, 0);
	if (pipe.fd2 == -1)
		return (1);
	path_check();
	
}
//être écolo avec mon i c'est dangereux?
char	*path_check(t_pipe *pipe, char **envp)
{
	int		i;
	char	**all_path;
	i = path_find(envp);
	all_path = ft_split(&envp[i][4], ':');
	if (!all_path)
		return (NULL);
	i = 0;
	while ()//bloqué ici trouver uun condition pour access
	access();
}

int	path_find(char **envp)
{
	int	i;

	i = 0;
	while (strncmp(envp[i], "PATH=", 5) != 0)
	{
		i++;
	}
	return (i);
}

// Should behave like:
// $> ./pipex infile "grep a1" "wc -w" outfile
//		int dup2(int oldfd, int newfd);
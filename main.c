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

	(void)ac;

	pipe.file1 = av[1];
	pipe.fd = open(pipe.file1, O_WRONLY, 0644);
	if (pipe.fd == -1)
		return (1);
	pipe.fd2 = dup2(pipe.fd, 0);
	if (pipe.fd2 == -1)
		return (1);
	pipe.path1 = ft_strjoin("/", av[2]);
	printf("path de la commande == %s\n", path_check(&pipe, envp));
	return (0);
}

char	*path_check(t_pipe *pipe, char **envp)
{
	int		i;
	char	**all_path;
	char	*path_checker;

	i = path_find(envp);
	all_path = ft_split(&envp[i][4], ':');
	if (!all_path)
		return (NULL);
	i = 0;
	path_checker = path_exist(pipe, all_path);
	if (!path_checker)
		return (perror("path_checker :("), NULL);
	return (path_checker);
}

int	path_find(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "PATH=", 5))
			return (i);
		i++;
	}
	perror("pas PATH dans envp");
	return (1);
}

char	*path_exist(t_pipe *pipe, char **all_path)
{
	int	i;
	char *tmp;

	i = 0;
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], pipe->path1);
		printf("tmp == %s\n", tmp);
		if (!access(tmp, F_OK))
			return (tmp);
		free(tmp);
		i++;
	}
	perror("PATH inexistant");
	return (NULL);
}

// Should behave like:
// $> ./pipex infile "grep a1" "wc -w" outfile
//		int dup2(int oldfd, int newfd);
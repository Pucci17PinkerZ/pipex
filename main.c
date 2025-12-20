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
	t_pipex	pipex;

	ft_bzero(&pipex, sizeof(t_pipex));
	(void)ac;
	if (setup(&pipex, av, envp))
		return (clean_exit(&pipex),1);
	new_child();
	printf("valeur de de true_path == %s\n", pipex.true_path1);
	return (clean_exit(&pipex), 0);
}

int	setup(t_pipex *pipex, char **av, char **envp)
{
	pipex->file1 = av[1];
	pipex->fd = open(pipex->file1, O_WRONLY, 0644);
	if (pipex->fd == -1)
		return (perror("open error"), 1);
	pipex->fd2 = dup2(pipex->fd, 0);
	if (pipex->fd2 == -1)
		return (perror("dup2 error"), 1);
	pipex->cmd_args = ft_split(av[2], ' ');
	if (!pipex->cmd_args)
		return (1);
	pipex->path1 = ft_strjoin("/", pipex->cmd_args[0]);
	pipex->true_path1 = path_check(pipex, envp);
	if (!pipex->true_path1)
		return (1);
	return (0);
}

char	*path_check(t_pipex *pipex, char **envp)
{
	int		i;
	char	*path_checker;

	i = path_find(envp);
	pipex->all_path = ft_split(&envp[i][5], ':');
	if (!pipex->all_path)
		return (NULL);
	path_checker = path_exist(pipex, pipex->all_path);
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

char	*path_exist(t_pipex *pipex, char **all_path)
{
	int	i;
	char *tmp;

	i = 0;
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], pipex->path1);
		printf("tmp == %s\n", tmp);
		if (!access(tmp, F_OK))
			return (strdup(tmp));
		free(tmp);
		i++;
	}
	perror("PATH inexistant");
	return (NULL);
}

// Should behave like:
// $> ./pipex infile "grep a1" "wc -w" outfile
//		int dup2(int oldfd, int newfd);
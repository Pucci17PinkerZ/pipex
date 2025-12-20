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

	if (ac != 4)
		return (1);
	ft_bzero(&pipex, sizeof(t_pipex));
	(void)ac;
	if (setup(&pipex, av, envp))
		return (clean_exit(&pipex),1);
	if (new_child(&pipex))
		return (clean_exit(&pipex), 1);
	// printf("valeur de de true_path == %s\n", pipex.true_path1);
	return (clean_exit(&pipex), 0);
}

int	setup(t_pipex *pipex, char **av, char **envp)
{
	if (set_fd(pipex, av))
		return (perror("set_fd"), 1);
	pipex->av = av;//utile????
	pipex->cmd_args = ft_split(av[2], ' ');
	if (!pipex->cmd_args)
		return (perror("ft_split"), 1);
	pipex->path1 = ft_strjoin("/", pipex->cmd_args[0]);
	pipex->true_path1 = path_check(pipex, envp, pipex->path1);
	if (!pipex->true_path1)
		return (perror("path_check"), 1);
	return (0);
	pipex->cmd2_args = ft_split(av[3], ' ');
	if (!pipex->cmd2_args)
		return (perror("ft_split"), 1);
	pipex->path2 = ft_strjoin("/", pipex->cmd2_args[0]);
	pipex->true_path2 = path_check(pipex, envp, pipex->path2);
	if (!pipex->true_path2)
		return (perror("path_check"), 1);
	return (0);
}

char	*path_check(t_pipex *pipex, char **envp, char *path)
{
	int		i;
	char	*path_checker;

	i = path_find(envp);
	pipex->all_path = ft_split(&envp[i][5], ':');
	if (!pipex->all_path)
		return (free_tab(pipex->all_path), perror("ft_split"), NULL);
	path_checker = path_exist(pipex, pipex->all_path, path);
	if (!path_checker)
		return (free_tab(pipex->all_path), perror("path_exist"), NULL);
	return (free_tab(pipex->all_path), path_checker);
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
	return (1);
}

char	*path_exist(t_pipex *pipex, char **all_path, char *path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], path);
		printf("tmp == %s\n", tmp);
		if (!access(tmp, F_OK))
			return (strdup(tmp));
		free(tmp);
		i++;
	}
	return (NULL);
}

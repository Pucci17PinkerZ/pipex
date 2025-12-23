/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfiora-d <nfiora-d@student.42.f            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:18:34 by nfiora-d          #+#    #+#             */
/*   Updated: 2025/12/16 17:32:55 by nfiora-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	setup2(t_pipex *pipex, char **av, char **envp)
{
	char *tmp;

	tmp = ft_strtrim(av[3], " ");
	if (tmp)
	{
		if (ft_strlen(tmp) == 0)
		{
			ft_printf("full whitespaces cmd");
			return(free(tmp), 1);
		}
	}
	pipex->cmd2_args = ft_split(av[3], ' ');
	if (!pipex->cmd2_args)
		return (perror("ft_split"), 1);
	pipex->true_path2 = before_path_check(pipex, envp, pipex->cmd2_args[0]);
	if (!pipex->true_path2)
		return (perror("path_check"), 1);
	if (set_fd(pipex, av))
		return (perror("set_fd"), 1);
	return (0);
}

int	setup1(t_pipex *pipex, char **av, char **envp)
{
	char *tmp;

	tmp = ft_strtrim(av[2], " ");
	if (tmp)
	{
		if (ft_strlen(tmp) == 0)
		{
			ft_printf("full whitespaces cmd");
			return(free(tmp), 1);
		}
	}
	pipex->cmd_args = ft_split(av[2], ' ');
	if (!pipex->cmd_args)
		return (perror("ft_split"), 1);
	pipex->true_path1 = before_path_check(pipex, envp, pipex->cmd_args[0]);
	if (!pipex->true_path1)
		return (perror("path_check"), 1);
	if (set_fd(pipex, av))
		return (perror("set_fd"), 1);
	return (0);
}

char	*before_path_check(t_pipex *pipex, char **envp, char *path)
{
	char	*path_checker;
	char	*tmp_path;

	if (strchr(path, '/'))
	{
		if ((path_checker = access_check("", path)) != NULL)
			return (path_checker);
		return (NULL);
	}
	tmp_path = ft_strjoin("/", path);
	path_checker = path_check(pipex, envp, tmp_path);
	if (path_checker)
		return (free(tmp_path), path_checker);
	return (perror("path_check"), free(tmp_path),  NULL);
}

char	*path_check(t_pipex *pipex, char **envp, char *path)
{
	int		i;
	char	*path_checker;

	i = path_find(envp);
	if (i == -1)
	{
		if ((path_checker = access_check("", path)) != NULL)
			return (path_checker);
		return (perror("access_check"), NULL);
	}
	pipex->all_path = ft_split(&envp[i][5], ':');
	if (!pipex->all_path)
		return (free_tab(pipex->all_path), perror("ft_split"), NULL);
	path_checker = path_exist(pipex->all_path, path);
	if (!path_checker)
		return (free_tab(pipex->all_path), perror("path_exist"), NULL);
	return (free_tab(pipex->all_path), path_checker);
}

int	path_find(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (-1);
	while (envp[i])
	{
		if (!strncmp(envp[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (-1);
}

char	*path_exist(char **all_path, char *path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (all_path[i])
	{
		if ((tmp = access_check(all_path[i], path)) != NULL)
			return (tmp);
		i++;
	}
	return (NULL);
}

char	*access_check(char *all_path, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(all_path, path);
	if (!access(tmp, F_OK | X_OK))
		return (tmp2 = ft_strdup(tmp), free(tmp), tmp2);
	free(tmp);
	return (NULL);
}

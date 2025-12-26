/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfiora-d <nfiora-d@student.42.f            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:18:34 by nfiora-d          #+#    #+#             */
/*   Updated: 2025/12/16 17:32:55 by nfiora-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	new_child(t_pipex *pipex, char **av, char **envp)
{
	if (pipe(pipex->pipedes))
		return (perror("pipe"), 1);
	pipex->child1 = fork();
	if (pipex->child1 == -1)
		return (perror("fork"), 1);
	else if (pipex->child1 == 0)
	{
		if (child_do(pipex, av, envp))
			return (1);
	}
	else
	{
		if (parent_do(pipex, av, envp))
			return (perror("parent _do"), 1);
	}
	return (0);
}

int	child_do(t_pipex *pipex, char **av, char **envp)
{
	if (setup1(pipex, av, envp))
		return (1);
	if (pipex->oldfd1 == -1)
		return (1);
	if ((dup2(pipex->oldfd1, 0)) == -1)
		return (perror("dup2"), 1);
	if ((dup2(pipex->pipedes[1], 1)) == -1)
		return (perror("dup2"), 1);
	close(pipex->pipedes[0]);
	close(pipex->pipedes[1]);
	close(pipex->oldfd1);
	if (execve(pipex->true_path1, pipex->cmd_args, envp))
		return (1);
	return (0);
}

int	parent_do(t_pipex *pipex, char **av, char **envp)
{
	pipex->child2 = fork();
	if (pipex->child2 == -1)
		return (perror("fork"), 1);
	else if (pipex->child2 == 0)
	{
		if (setup2(pipex, av, envp))
			return (1);
		if ((dup2(pipex->pipedes[0], 0)) == -1)
			return (perror("dup2.1"), 1);
		if ((dup2(pipex->oldfd2, 1)) == -1)
			return (perror("dup2.2"), 1);
		close(pipex->pipedes[1]);
		close(pipex->pipedes[0]);
		close(pipex->oldfd2);
		if (execve(pipex->true_path2, pipex->cmd2_args, envp))
			return (perror("execve"), 1);
	}
	else
		fd_close(pipex);
	return (0);
}

int	setup1(t_pipex *pipex, char **av, char **envp)
{
	char	*tmp;

	tmp = ft_strtrim(av[2], " ");
	if (tmp)
	{
		if (ft_strlen(tmp) == 0)
			return (free(tmp), 1);
	}
	free(tmp);
	pipex->cmd_args = ft_split(av[2], ' ');
	if (!pipex->cmd_args)
		return (perror("ft_split"), 1);
	pipex->true_path1 = before_path_check(pipex, envp, pipex->cmd_args[0]);
	if (!pipex->true_path1)
		return (perror("path_check, path does not exist"), 1);
	return (0);
}

int	setup2(t_pipex *pipex, char **av, char **envp)
{
	char	*tmp;

	tmp = ft_strtrim(av[3], " ");
	if (tmp)
	{
		if (ft_strlen(tmp) == 0)
			return (free(tmp), 1);
	}
	free(tmp);
	pipex->cmd2_args = ft_split(av[3], ' ');
	if (!pipex->cmd2_args)
		return (perror("ft_split"), 1);
	pipex->true_path2 = before_path_check(pipex, envp, pipex->cmd2_args[0]);
	if (!pipex->true_path2)
		return (perror("path_check, path does not exist"), 1);
	return (0);
}

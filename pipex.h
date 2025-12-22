/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pucci_pinker <pucci_pinker@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:18:34 by pucci_pinke       #+#    #+#             */
/*   Updated: 2025/12/16 17:32:55 by pucci_pinke      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"

typedef struct s_pipex
{
	int		pipedes[2];
	char	**cmd_args;
	char	**cmd2_args;
	char	**all_path;
	char	**av;
	char	*file1;
	char	*file2;
	char	*true_path1;
	char	*path1;
	char	*true_path2;
	char	*path2;
	int		oldfd1;
	int		newfd1;
	int		oldfd2;
	int		newfd2;
	pid_t	child1;
	pid_t	child2;
}	t_pipex;

int		setup(t_pipex *pipex, char **av, char **envp);
int		set_fd(t_pipex *pipex, char **av);
char	*path_check(t_pipex *pipex, char **envp, char *path);
int		path_find(char **envp);
char	*path_exist(char **all_path, char *path);
char	*access_check(char *all_path, char *path);

int		new_child(t_pipex *pipex, char **envp);
int		child_do(t_pipex *pipex, char **envp);
int		parent_do(t_pipex *pipex, char **envp);

void	free_tab(char **tab);
int		tab_element(char *tab);
int		fd_close(t_pipex *pipex);
void	clean_exit(t_pipex *pipex);
int		test_input(char **av);

#endif

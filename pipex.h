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
#define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft/libft.h"

typedef struct s_pipex
{
	char	**cmd_args;
	char	**all_path;
	char	*file1;
	char	*file2;
	char	*true_path1;
	char	*path1;
	char	*true_path2;//check si tu le utilise
	char	*path2;
	int		fd;
	int		fd2;
}	t_pipex;

int		setup(t_pipex *pipex, char **av, char **envp);
char	*path_check(t_pipex *pipex, char **envp);
int		path_find(char **envp);
char	*path_exist(t_pipex *pipex, char **all_path);

void	free_tab(char **tab);
int		tab_element(char *tab);

void	clean_exit(t_pipex *pipex);

#endif


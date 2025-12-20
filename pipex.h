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

typedef struct s_pipe
{
	char	*file1;
	char	*file2;
	char	*path1;
	char	*path2;
	int		fd;
	int		fd2;
}	t_pipe;

char	*path_check(t_pipe *pipe, char **envp);
int		path_find(char **envp);
char	*path_exist(t_pipe *pipe, char **all_path);

void	free_tab(char **tab);
int		tab_element(char *tab);

#endif


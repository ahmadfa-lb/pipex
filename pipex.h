/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:43:28 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/13 10:43:29 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <stddef.h>
# include "ft_printf/ft_printf.h"

typedef struct pipe_fork
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	int		out_fd;
	int		in_fd;
}	t_pf;

typedef struct cmd
{
	char	*cmd;
	char	**cmd_paths;
	char	*paths;
	char	**cmd_args;
}	t_cmd;

void	handle_error(const char *msg);
void	free_after_parent_work(t_pf *pipex, t_cmd *cmdx);
char	*get_cmd(char **paths, char *cmd);
void	work_child1(char **argv, char **envp, t_pf pipex, t_cmd cmd_x);
void	work_child2(char **argv, char **envp, t_pf pipex, t_cmd cmd_x);
void	forkinit(char **argv, char **envp, t_pf pipe_x, t_cmd cmd_x);
char	*find_path(char **envp);

#endif

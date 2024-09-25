/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:43:25 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/13 10:43:26 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_after_parent_work(t_pf *pipex, t_cmd *cmdx)
{
	int	i;

	i = 0;
	close(pipex->in_fd);
	close(pipex->out_fd);
	while (cmdx->cmd_paths[i])
	{
		free(cmdx->cmd_paths[i]);
		i++;
	}
	free(cmdx->cmd_paths);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*temp;
	char	*command;

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	work_child1(char **argv, char **envp, t_pf pipex, t_cmd cmd_x)
{
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close(pipex.pipefd[0]);
	dup2(pipex.in_fd, STDIN_FILENO);
	cmd_x.cmd_args = ft_split(argv[2], ' ');
	cmd_x.cmd = get_cmd(cmd_x.cmd_paths, cmd_x.cmd_args[0]);
	if (cmd_x.cmd == NULL)
	{
		free(cmd_x.cmd_args);
		free(cmd_x.cmd);
		handle_error("ivalid command 1");
	}
	execve(cmd_x.cmd, cmd_x.cmd_args, envp);
	handle_error("execve failed for command 1");
}

void	work_child2(char **argv, char **envp, t_pf pipex, t_cmd cmd_x)
{
	dup2(pipex.pipefd[0], STDIN_FILENO);
	close(pipex.pipefd[1]);
	dup2(pipex.out_fd, STDOUT_FILENO);
	cmd_x.cmd_args = ft_split(argv[3], ' ');
	cmd_x.cmd = get_cmd(cmd_x.cmd_paths, cmd_x.cmd_args[0]);
	if (cmd_x.cmd == NULL)
	{
		free(cmd_x.cmd_args);
		free(cmd_x.cmd);
		handle_error("ivalid command 2");
	}
	execve(cmd_x.cmd, cmd_x.cmd_args, envp);
	handle_error("execve failed for command 2");
}
